#include "fastslam.hpp"

FastSlam::FastSlam(const int &N_LM) 
{
  Q_ = MatrixXd(2,2);
  R_ = MatrixXd(2,2);
  Q_ << 9, 0,
        0, 0.03046174; 
  R_ << 1, 0,
        0, 0.12184697;
  //Populate an array of particles
  for(Particle* &p: particles_)
  {
    p = new Particle(N_LM);
  }
}

void FastSlam::PredictParticles(const MatrixXd &u)
{
  for(Particle* &p: particles_)
  {
    MatrixXd px(STATE_SIZE,1);  

    px(0,0) = p->x_;
    px(1,0) = p->y_;
    px(2,0) = p->yaw_;

    MatrixXd rand_normal(1,2);
    rand_normal << normal_(gen_), normal_(gen_);
    MatrixXd ud = u + (rand_normal * R_).transpose();

    px = MotionModel(px,ud);

    p->x_ = px(0,0);
    p->y_ = px(1,0);
    p->yaw_ = px(2,0);
  }
}

void FastSlam::UpdateWithObservation(MatrixXd z)
{
  for(int i = 0; i < z.cols(); ++i)
  {
    int lmid = z(2, i);

    for(Particle* &p : particles_)
    {
      //new landmark
      if(abs(p->lm_(lmid,0)) <= 0.01)
      {
        MatrixXd z_vector(3,1);
        z_vector << z(0,i) , z(1,i), z(2,i);
        p->AddNewLM(z_vector, Q_);
      } 
      //unknown landmark
      else
      {
        MatrixXd z_vector(3,1);
        z_vector << z(0,i) , z(1,i), z(2,i);
        double w = p->ComputeWeight(z_vector, Q_);
        p->w_ *= w;
        p->UpdateLM(z_vector, Q_);
      }
    }
  } 

}

void FastSlam::Resampling()
{
  //low variance resampling 
  NormalizeWeights();

  std::vector<double> pw;
  for(Particle* &p: particles_)
  {
    pw.push_back(p->w_);
  }

  MatrixXd pw_mat(1,pw.size());

  for(size_t i = 0; i < pw.size(); ++i)
  {
    pw_mat(i) = pw[i];
  }
  double Neff = 1.0 / (pw_mat * pw_mat.transpose())(0); // effective particle number
  
  std::vector<double> wcum;
  wcum.assign(pw.begin(), pw.end()); 
  std::partial_sum(pw.begin(), pw.end(),  wcum.begin());

  std::vector<double> base;
  base.assign(pw.begin(), pw.end()); 
  for(double &value : base)
  {
    value = 1.0 / N_PARTICLE;
  }
  std::partial_sum(base.begin(), base.end(),  base.begin());
  for(double &value : base)
  {
    value -= 1.0 / N_PARTICLE; 
  }

  std::vector<double> resample_id;
  for(size_t i = 0; i< base.size(); ++i)
  {
    double r = ((double) rand() / (RAND_MAX));
    resample_id.push_back(base[i] + r / N_PARTICLE);
  }

  if(Neff < NTH)
  {
    std::vector<double> wcum;
    wcum.assign(pw.begin(), pw.end()); 
    std::partial_sum(pw.begin(), pw.end(),  wcum.begin());

    std::vector<double> base;
    base.assign(pw.begin(), pw.end()); 
    for(double &value : base)
    {
      value = 1.0 / N_PARTICLE;
    }
    std::partial_sum(base.begin(), base.end(),  base.begin());
    for(double &value : base)
    {
      value -= 1.0 / N_PARTICLE; 
    }

    std::vector<double> resample_id;
    for(size_t i = 0; i< base.size(); ++i)
    {
      double r = ((double) rand() / (RAND_MAX));
      resample_id.push_back(base[i] + r / N_PARTICLE);
    }

    std::vector<double> inds;
    size_t ind = 0;
    for(int i = 0; i < N_PARTICLE; ++i)
    {
      while(ind < wcum.size()-1 && resample_id[i] > wcum[ind])
      {
        ++ind;
      }
      inds.push_back(ind);
    }
    std::array<Particle*, N_PARTICLE> tparticles = particles_;

    for(size_t i = 0; i < inds.size(); ++i)
    {
      particles_[i]->x_ = tparticles[inds[i]]->x_;
      particles_[i]->y_ = tparticles[inds[i]]->y_;
      particles_[i]->yaw_ = tparticles[inds[i]]->yaw_;
      particles_[i]->lm_= tparticles[inds[i]]->lm_;
      particles_[i]->lmp_ = tparticles[inds[i]]->lmp_;
      particles_[i]->w_ = 1.0 / N_PARTICLE;
    }
  }
}

void FastSlam::NormalizeWeights()
{
  double sumw = 0;
  for(Particle* &p: particles_)
  {
    sumw += p->w_;
  }

  if(sumw != 0)
  {
    for(Particle* &p: particles_)
    {
      p->w_ /= sumw;
    }
  }
  else
  {
    for(Particle* &p: particles_)
    {
      p->w_ = 1.0 / N_PARTICLE;
    }
  }
}

MatrixXd FastSlam::CalcFinalState()
{
  MatrixXd x_est(STATE_SIZE,1);
  x_est << 0,0,0;

  NormalizeWeights();

  for(Particle* &p: particles_)
  {
    x_est(0,0) += p->w_ * p->x_;  
    x_est(1,0) += p->w_ * p->y_;  
    x_est(2,0) += p->w_ * p->yaw_;  
  }

  x_est(2,0) = Pi2Pi(x_est(2,0));

  return x_est;
   
}

