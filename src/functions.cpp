#include "functions.hpp"

MatrixXd CalcInput(const float &time)
{
  double v;
  double yawrate;

  if(time <= 3.0)
  {
    v = 0.0;
    yawrate = 0.0;
  }
  else
  {
    v = 0.5;       // m/s
    yawrate = 0.1; // rad/s
  }

  MatrixXd u(2,1);
  u << v, yawrate;

  return u;
}

std::array<MatrixXd,2> Observation(MatrixXd &x_true, MatrixXd &xd, const MatrixXd &u, const MatrixXd &RFID)
{
  MatrixXd Qsim(2,2);
  MatrixXd Rsim(2,2);
  Qsim << 0.09, 0,
          0,    0.0121847; 
  Rsim << 0.25, 0,
          0,    0.03046174;

  // rand normal distrubition generator
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::normal_distribution<double> normal;
  // calc true state
  x_true = MotionModel(x_true, u);

  //add noise to range observation
  std::vector<MatrixXd> z_vec;
  for(int i = 0; i < RFID.rows(); ++i)
  {
    double dx = RFID(i,0) - x_true(0,0);
    double dy = RFID(i, 1) - x_true(1, 0);
    double d = sqrt(dx * dx + dy * dy);

    double angle = Pi2Pi(atan2(dy, dx) - x_true(2,0));

    if(d <= MAX_RANGE)
    {
      double dn = d + normal(gen) * Qsim(0,0); // add noise
      double anglen = angle + normal(gen) * Qsim(1,1); // add noise
      MatrixXd zi(3,1);
      zi << dn,
            Pi2Pi(anglen),
            i;
      z_vec.push_back(zi); 
    }
  }
  MatrixXd z(3,z_vec.size());
  for(size_t i = 0; i < z_vec.size(); ++i)
  {
    z(0,i) = z_vec[i](0);
    z(1,i) = z_vec[i](1);
    z(2,i) = z_vec[i](2);
  }

  //add noise to input
  double ud1 = u(0,0) + normal(gen) * Rsim(0,0);
  double ud2 = u(1,0) + normal(gen) * Rsim(1,1) + OFFSET_YAWRATE_NOISE;
  MatrixXd ud(2,1);
  ud << ud1, ud2;

  xd = MotionModel(xd, ud);

  std::array<MatrixXd,2> out = {z,ud};
  return out;
}

MatrixXd MotionModel(const MatrixXd &x, const MatrixXd &u)
{
  MatrixXd F(3,3);
  F << 1.0, 0, 0,
       0, 1.0, 0,
       0, 0, 1.0;

  MatrixXd B(3,2);
  B << DT * cos(x(2, 0)), 0,
       DT * sin(x(2, 0)), 0,
       0.0              , DT;
  MatrixXd v(2,1);
  v << u(0), u(0);

  MatrixXd mm(3,1);
  mm << 2, 2, 2;

  MatrixXd x_new =  F * x + B * v ;

  x_new(2,0) =  Pi2Pi(x_new(2,0));

  return x_new;
}

double Pi2Pi(const double &angle)
{
  return fmod(angle + M_PI,2 * M_PI) - M_PI;
}