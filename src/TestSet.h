#pragma once

#include <atomic>

using namespace std;

// shared lock variable
atomic<bool> lock(false); 

class TAS {
private:
    atomic<bool> lock;
    //our shared lock 

public:
	TAS(): lock(false){}

    /*
    * Acquire requests the lock which spins
    * until it gets access to perform tasks
    * which happens only when exchange == false
    *
    */
    void acquire()
    {
        // lock is held, spin
        while (lock.exchange(true)) {

        }
    }

    /*
    * release relinquishes hold of the lock
    * stores false in the lock for another thread to take
    */
    void release()
    {
        // releasing lock
        lock.store(false);
    }

};