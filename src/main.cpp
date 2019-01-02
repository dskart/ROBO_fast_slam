#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>      
#include <array>
#include <random>
#include <fstream>
#include <iterator>

#include <Eigen/Dense>
#include "particle.hpp"
#include "functions.hpp"
#include "constants.hpp"
#include "fastslam.hpp"

using namespace Eigen;

int main()
{
  float time = 0.0;

  MatrixXd RFID(14,2);
  RFID << 1.2000,    1.0000,
            1.0812,    1.5207,
            0.7482,    1.9382,
            0.2670,    2.1699,
           -0.2670,    2.1699,
           -0.7482,    1.9382,
           -1.0812,    1.5207,
           -1.2000,    1.0000,
           -1.0812,    0.4793,
           -0.7482,    0.0618,
           -0.2670,   -0.1699,
            0.2670,   -0.1699,
            0.7482,    0.0618,
            1.0812,    0.4793;

  int N_LM = RFID.rows();

  // State Vector [x, y, yaw, v]
  MatrixXd x_est(STATE_SIZE, 1); // SLAM estimation
  MatrixXd x_true(STATE_SIZE,1); // True estate
  MatrixXd x_dr(STATE_SIZE,1);   // Dead reckoning

  // history
  std::vector<MatrixXd> hx_est;
  std::vector<MatrixXd> hx_true;
  std::vector<MatrixXd> hx_dr;
  std::vector<std::array<Particle*, N_PARTICLE>> h_particles;

  std::ofstream output_file0("./h_particles.txt");
  std::ofstream output_file01("./h_lm.txt");

  FastSlam fs(N_LM);
  while(SIM_TIME >= time)
  {
    time += DT;

    // u -> [v, yawrate]
    // x_true/x_dr/x_est -> [x,y,yaw]
    MatrixXd u = CalcInput(time); 

    std::array<MatrixXd,2> z_ud = Observation(x_true, x_dr, u, RFID);
    MatrixXd z = z_ud[0];
    MatrixXd ud = z_ud[1];

    fs.PredictParticles(ud);
    fs.UpdateWithObservation(z);
    fs.Resampling();

    x_est = fs.CalcFinalState();

    hx_est.push_back(x_est);
    hx_true.push_back(x_true);
    hx_dr.push_back(x_dr);
}

