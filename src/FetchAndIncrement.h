#pragma once

#include <atomic>
#include <thread>

class FAILock 
{
    std::atomic<int> token_;
    std::atomic<int> turn_;
 public:
    FAILock() : token_(0), turn_(0) {}

    void acquire() 
    {
        int myturn = std::atomic_fetch_add(&this->token_, 1);
        while (this->turn_ != myturn);
    }

    void release() 
    {
        std::atomic_fetch_add(&this->turn_, 1);
    }
};

