#include "PetersonsLock.h"

PetersonsLock::PetersonsLock() {
  this->turn_.store(0, std::memory_order_release);
  this->flag_[0].store(false, std::memory_order_release);
  this->flag_[1].store(false, std::memory_order_release);
}

void PetersonsLock::acquire(int process_id)
{
  this->flag_[process_id].store(true, std::memory_order_acq_rel);
  this->turn_.store(1 - process_id, std::memory_order_release);
  while (this->flag_[1 - process_id].load(std::memory_order_acquire) && this->turn_.load(std::memory_order_acquire) == 1 - process_id) {
    continue; // spin
  }
}

void PetersonsLock::release(int process_id)
{
  this->flag_[process_id].store(false, std::memory_order_release);
}
