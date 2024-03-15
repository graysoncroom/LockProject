#pragma once

#include <atomic>

class PetersonsLock
{
 private:
   std::atomic<bool> flag[2];
   std::atomic<int> turn;

 public:
  // A `process_id` should be either 0 or 1.
  // This is how the algorithm knows which process is asking to lock / unlock
  void lock(int process_id);
  void unlock(int process_id);
};
