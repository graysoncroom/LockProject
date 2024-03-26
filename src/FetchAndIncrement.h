#pragma once

#include <atomic>
#include <thread>

class FAILock 
{
  std::atomic<int> token_;
  std::atomic<int> turn_;
 public:
  FAILock();

  void acquire();
  void release();
};

