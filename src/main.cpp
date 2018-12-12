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
#include "matplotlibcpp.hpp"


using namespace Eigen;
namespace plt = matplotlibcpp;

bool show_animation = true;
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

    std::cout<< x_est << std::endl;
    std::cout<< '\n' << std::endl;
    for(Particle* &p : fs.particles_)
    {
      output_file0 << p->x_ << " " <<p->y_ << " ";
      for(int i = 0; i < p->lm_.rows(); ++i)
      {
        output_file01 << p->lm_(i,0) << " " << p->lm_(i,1) << " ";
      }
    }
    output_file0 << "\n";
    output_file01 << "\n";
  }

  std::ofstream output_file1("./hx_est.txt");
  for(MatrixXd m : hx_est)
  {
    output_file1 << m(0) << " " << m(1)  << " " << m(2) << "\n";
  }

  std::ofstream output_file2("./hx_true.txt");
  for(MatrixXd m : hx_true)
  {
    output_file2 << m(0) << " " << m(1)  << " " << m(2) << "\n";
  }

  std::ofstream output_file3("./hx_dr.txt");
  for(MatrixXd m : hx_dr)
  {
    output_file3 << m(0) << " " << m(1)  << " " << m(2) << "\n";
  }

}

