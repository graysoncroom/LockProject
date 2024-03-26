#include "TestAndSet.h"

TASLock::TASLock(): lock_(false) {}

/*
 * Acquire requests the lock which spins
 * until it gets access to perform tasks
 * which happens only when exchange == false
 */
void TASLock::acquire()
{
  // lock is held, spin
  while (this->lock_.exchange(true, std::memory_order_acquire));
}

/*
 * release relinquishes hold of the lock
 * stores false in the lock for another thread to take
 */
void TASLock::release()
{
  // releasing lock
  this->lock_.store(false, std::memory_order_release);
}

