#pragma once

#include <atomic>

class TASLock
{
  // our shared lock var
  std::atomic<bool> lock_;

public:
  TASLock(): lock_(false) {}

  /*
   * Acquire requests the lock which spins
   * until it gets access to perform tasks
   * which happens only when exchange == false
   */
  void acquire()
  {
    // lock is held, spin
    while (lock_.exchange(true, std::memory_order_acquire));
  }

  /*
    * release relinquishes hold of the lock
    * stores false in the lock for another thread to take
    */
  void release()
  {
      // releasing lock
      lock_.store(false, std::memory_order_release);
  }
};