#include "PetersonsLock.h"

void PetersonsLock::lock(int process_id) {
  this->flag[process_id] = true;
  int j = (process_id + 1) % 2;
  // Set `this->turn` to be the other process' identifier
  this->turn = j;
  while (flag[j] && turn == j);
}

void PetersonsLock::unlock(int process_id) {
  this->flag[process_id] = false;
}

