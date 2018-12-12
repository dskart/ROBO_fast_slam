#include "particle.hpp"

Particle::Particle(const int &N_LM)
{
	lm_ = MatrixXd(N_LM,LM_SIZE);
	lmp_ = MatrixXd(N_LM * LM_SIZE, LM_SIZE);	
}

void Particle::AddNewLM(const MatrixXd &z, const MatrixXd &Q)
{
	double r = z(0);
	double b = z(1);
	int lm_id = z(2);

	double s = sin(Pi2Pi(yaw_ + b));
	double c = cos(Pi2Pi(yaw_ + b));

	lm_(lm_id,0) = x_ + r * c;
	lm_(lm_id,1) = y_ + r * s;

	//Covariance
	MatrixXd gz (2,2);
	gz << c, -r * s,
        s, r * c;

  MatrixXd pos_covariance(2,2);
  pos_covariance = gz * Q * gz.transpose();
  int start_row = 2 * lm_id;

  lmp_(start_row, 0) = pos_covariance(0,0);
  lmp_(start_row, 1) = pos_covariance(0,1);
  lmp_(start_row+1, 0) = pos_covariance(1,0);
  lmp_(start_row+1, 1) = pos_covariance(1,1);
}

double Particle::ComputeWeight(const MatrixXd &z, const MatrixXd &Q)
{
	int lm_id = z(2);
	MatrixXd xf(2,1);
	xf << lm_(lm_id,0), lm_(lm_id,1);
	int start_row = 2 * lm_id;

	MatrixXd Pf(2,2);
	Pf << lmp_(start_row, 0), lmp_(start_row, 1),
			  lmp_(start_row+1, 0), lmp_(start_row+1, 1);

	std::array<MatrixXd,4> zp_Hv_Hf_Sf = ComputeJacobian(this, xf, Pf, Q);
	MatrixXd zp = zp_Hv_Hf_Sf[0];
	MatrixXd Hv = zp_Hv_Hf_Sf[1];
	MatrixXd Hf = zp_Hv_Hf_Sf[2];
	MatrixXd Sf = zp_Hv_Hf_Sf[3];

	MatrixXd dx(2,1);
	dx << z(0)-zp(0), z(1)-zp(1);
	dx(1,0) = Pi2Pi(dx(1,0));

	MatrixXd invS;
	try 
	{  
		invS = Sf.inverse();
	} 
	catch (const std::exception& e) 
	{ 
		std::cout << "singuler" << std::endl;
		return 1.0;
  }


  MatrixXd in_exp =  -0.5 * dx.transpose() * invS * dx;
  double numerator = exp(in_exp(0));
  double denominator = 2.0 * M_PI * sqrt(Sf.determinant()); 

  double w = numerator / denominator;

  return w;
}

void Particle::UpdateLM(const MatrixXd &z, const MatrixXd &Q)
{
	int lm_id = z(2);
	MatrixXd xf(2,1);
	xf << lm_(lm_id,0), lm_(lm_id,1);
	int start_row = 2 * lm_id;

	MatrixXd Pf(2,2);
	Pf << lmp_(start_row, 0), lmp_(start_row, 1),
			  lmp_(start_row+1, 0), lmp_(start_row+1, 1);

	std::array<MatrixXd,4> zp_Hv_Hf_Sf = ComputeJacobian(this, xf, Pf, Q);
	MatrixXd zp = zp_Hv_Hf_Sf[0];
	MatrixXd Hv = zp_Hv_Hf_Sf[1];
	MatrixXd Hf = zp_Hv_Hf_Sf[2];
	MatrixXd Sf = zp_Hv_Hf_Sf[3];

	MatrixXd dz(2,1);
	dz << z(0)-zp(0), z(1)-zp(1);
	dz(1,0) = Pi2Pi(dz(1,0));
	UpdateKF(xf, Pf, dz, Q, Hf);

	lm_(lm_id,0) = xf.transpose()(0);
	lm_(lm_id,1) = xf.transpose()(1);

	lmp_(start_row, 0) = Pf(0,0);
  lmp_(start_row, 1) = Pf(0,1);
  lmp_(start_row+1, 0) = Pf(1,0);
  lmp_(start_row+1, 1) = Pf(1,1);
}



//---------------------------------OUT OF CLASS FUNCTIONS--------------------------------------------

std::array<MatrixXd,4> ComputeJacobian(const Particle* p, const MatrixXd &xf, const MatrixXd &Pf, const MatrixXd &Q)
{
	double dx = xf(0,0) - p->x_;
	double dy = xf(1,0) - p->y_;
	double d2 = dx * dx + dy * dy;
	double d = sqrt(d2);

	MatrixXd zp(2,1);
	zp << d, Pi2Pi(atan2(dy, dx) - p->yaw_);

	MatrixXd Hv(2,3);
	Hv << -dx / d, -dy / d, 0.0,
        dy / d2, -dx / d2, -1.0;

  MatrixXd Hf(2,2);
	Hf << dx / d, dy / d,
        -dy / d2, dx / d2;

  MatrixXd Sf(2,2);
  Sf = Hf * Pf * Hf.transpose() + Q;
	std::array<MatrixXd,4> out = {zp,Hv,Hf,Sf};
	return out;
}

void UpdateKF(MatrixXd &xf, MatrixXd &Pf, const MatrixXd &v, const MatrixXd &Q, const MatrixXd &Hf)
{

	MatrixXd PHt = Pf * Hf.transpose();
	MatrixXd S = Hf * PHt + Q;

	S = (S + S.transpose()) * 0.5;
	MatrixXd SChol = (S.llt().matrixL()).transpose();
	MatrixXd SChol_inv = SChol.inverse();
	MatrixXd W1 = PHt * SChol_inv;
	MatrixXd W = W1 * SChol_inv.transpose();

	xf = xf + W * v;
	Pf  = Pf - W1 * W1.transpose();

	return;
}
