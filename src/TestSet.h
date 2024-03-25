#pragma once

#include <atomic>
#include <thread>

using namespace std;

class TAS {
private:
    // our shared lock var
    atomic<bool> lock;
    // shared counter for displaying our critical section
    atomic<int> ctr;

    // our function to increment the counter via threads
    void incrementCtr(int n) 
    {
        //getting the lock to increment the critical section
        acquire();
        // incrementing the counter variable and outputting result
        ctr++;
        cout << ctr << endl;
        // releasing the lock for another thread to use
        release();

        // spinning till every lock is done incrementing
        while (ctr != n) {

        }
    }

public:
	TAS(): lock(false), ctr(0) {}

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

    void TestAndSet(int n)
    {
        
        // spawning n number of threads to independently function
        for (int i = 0; i < n; i++)
        {
            thread(incrementCtr, n).detach();
        }

    }

};