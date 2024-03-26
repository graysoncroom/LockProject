#pragma once

#include <atomic>

class TASLock
{
  // our shared lock var
  std::atomic<bool> lock_;

public:
  TASLock();
  
  void acquire();
  void release();
};

