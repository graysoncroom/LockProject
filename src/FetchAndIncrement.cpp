#include "FetchAndIncrement.h"


FAILock::FAILock() : token_(0), turn_(0) {}

void FAILock::acquire() 
{
  int myturn = std::atomic_fetch_add(&this->token_, 1);
  while (this->turn_ != myturn);
}

void FAILock::release() 
{
  std::atomic_fetch_add(&this->turn_, 1);
}