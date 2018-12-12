#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#define _USE_MATH_DEFINES
#include <math.h>      

#include <Eigen/Dense>
#include <Eigen/Cholesky>
#include "constants.hpp"
#include "functions.hpp"

using namespace Eigen;

class Particle {
	private:
	
	public:	

		Particle(const int &N_LM);

		void AddNewLM(const MatrixXd &z, const MatrixXd &Q);
		double ComputeWeight(const MatrixXd &z, const MatrixXd &Q);
		void UpdateLM(const MatrixXd &z, const MatrixXd &Q);

		double w_ = 0.0;
		double x_ = 0.0;
		double y_ = 0.0;
		double yaw_ = 0.0;

		//landmark x-y postion
		MatrixXd lm_; 

		//landmarks position covariance
		MatrixXd lmp_;
};

std::array<MatrixXd,4> ComputeJacobian(const Particle* p, const MatrixXd &xf, const MatrixXd &pf, const MatrixXd &Q);
void UpdateKF(MatrixXd &xf, MatrixXd &pf, const MatrixXd &v, const MatrixXd &Q, const MatrixXd &Hf);



#endif // PARTICLE_HPP