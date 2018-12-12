#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>      
#include <array>
#include <random>

#include <Eigen/Dense>
#include "particle.hpp"
#include "functions.hpp"
#include "constants.hpp"
#include "fastslam.hpp"


using namespace Eigen;


int main()
{
  float time = 0.0;

  // SET OF LANDMARKS
  // should work with any size but like I wouldn't fuck around too much 
  MatrixXd RFID(8,2);
  RFID << 10.0,  -2.0,
          15.0,  10.0,
          15.0,  15.0,
          10.0,  20.0,
          3.0,   15.0,
          -5.0,  20.0,
          -5.0,  5.0,
          -10.0, 15.0;

  int N_LM = RFID.rows();

  // State Vector [x, y, yaw, v]
  MatrixXd x_est(STATE_SIZE, 1); // SLAM estimation
  MatrixXd x_true(STATE_SIZE,1); // True estate
  MatrixXd x_dr(STATE_SIZE,1);   // Dead reckoning

  // history
  MatrixXd hx_est = x_est; 
  MatrixXd hx_true = x_true;
  MatrixXd hx_dr = x_dr;

  FastSlam fs(N_LM);
  while(SIM_TIME >= time)
  {
    time += DT;

    // u -> [v, yawrate]
    // x_true/x_dr/x_est -> [x,y,yaw,v]
    
    MatrixXd u = CalcInput(time); 

    std::array<MatrixXd,2> z_ud = Observation(x_true, x_dr, u, RFID);
    MatrixXd z = z_ud[0];
    MatrixXd ud = z_ud[1];

    fs.PredictParticles(ud);
    fs.UpdateWithObservation(z);
    fs.Resampling();

    x_est = fs.CalcFinalState();

    std::cout << x_est <<std::endl; 
    std::cout<< '\n' << std::endl;
  }
}

