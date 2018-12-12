#ifndef FASTSLAM_HPP
#define FASTSLAM_HPP

#include "constants.hpp"
#include "particle.hpp"
#include "functions.hpp"


#include <iostream>
#include <random>
#include <iterator>
#include <numeric>
#include <functional>

using namespace Eigen;

class FastSlam{
	private:
    // rand normal distrubition generator
    std::random_device rd_{};
    std::mt19937 gen_{rd_()};
    std::normal_distribution<double> normal_;

    //Fast SLAM covariance
    MatrixXd Q_;
    MatrixXd R_;

	public:
    std::array<Particle*, N_PARTICLE> particles_;
    FastSlam(const int &N_LM);

    void PredictParticles(const MatrixXd &u);
    void UpdateWithObservation(MatrixXd z);
    void Resampling();
    void NormalizeWeights();
    MatrixXd CalcFinalState();
};
  
#endif //FASTSLAM_HPP
