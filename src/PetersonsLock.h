#pragma once

#include <atomic>

class PetersonsLock
{
 private:
   std::atomic<bool> flag_[2];
   std::atomic<int> turn_;

 public:
  PetersonsLock();
  
  // A `process_id` should be either 0 or 1.
  // This is how the algorithm knows which process is asking to lock / unlock
  void acquire(int process_id);
  void release(int process_id);
};
