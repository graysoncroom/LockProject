#include "FetchAndIncrement.h"


/*
 * Fetch and Increment Lock
 * 
 * A lock implementation using Fetch and Increment
 * 
 * @param token_: The token to be used for the lock
 * @param turn_: The turn to be used for the lock
*/
FAILock::FAILock() : token_(0), turn_(0) {}

/*
 * Acquire the lock
 * 
 * This function is called by each thread to acquire the lock
*/
void FAILock::acquire() 
{
  int myturn = std::atomic_fetch_add(&this->token_, 1);
  while (this->turn_ != myturn);
}

/*
 * Release the lock
 * 
 * This function is called by each thread to release the lock
*/
void FAILock::release() 
{
  std::atomic_fetch_add(&this->turn_, 1);
}