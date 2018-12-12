#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>      
#include <array>
#include <random>

#include <Eigen/Dense>
#include "particle.hpp"
#include "constants.hpp"

using namespace Eigen;

MatrixXd CalcInput(const float &time);

std::array<MatrixXd,2> Observation(MatrixXd &x_true, MatrixXd &xd, const MatrixXd &u, const MatrixXd &RFID);

MatrixXd MotionModel(const MatrixXd &x, const MatrixXd &u);

double Pi2Pi(const double &angle);

#endif // FUNCTIONS_HPP