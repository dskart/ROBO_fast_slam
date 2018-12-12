#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP



#define DT  0.1  // time tick s
#define SIM_TIME  50  // simulation time [s]
#define MAX_RANGE  20.0  // maximum observation range
#define M_DIST_TH  2.0  // Threshold of Mahalanobis distance for data association.
#define STATE_SIZE  3  // State size [x,y,yaw]
#define LM_SIZE  2  // LM srate size [x,y]
#define N_PARTICLE  10  // number of particle
#define NTH  N_PARTICLE / 1.5  // Number of particle for re-sampling
#define OFFSET_YAWRATE_NOISE 0.01


#endif //CONSTANTS_HPP