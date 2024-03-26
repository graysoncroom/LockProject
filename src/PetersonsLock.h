#pragma once

#include <atomic>

class PetersonsLock
{
  std::atomic<bool> flag_[2];
  std::atomic<int> turn_;

 public:
  PetersonsLock();

  // The argument should be either 0 or 1.
  // This is how the algorithm knows which process is asking to lock / unlock
  void acquire(int);
  void release(int);
};
