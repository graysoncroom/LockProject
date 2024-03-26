#pragma once

#include <atomic>
#include <stdatomic.h>
#include <thread>

using namespace std;

class FAILock {
private:
	// shared token counter
	atomic<int> token_;
	// shared turn counter
	atomic<int> turn_;


public:
	FAILock() : token_(0), turn_(0) {}

	// fetch a value from token for our thread turn 
	// and increment token ctr before returning initial token val
	int fetchToken()
	{
		// atomically get the value of the token and increment
		int currToken = atomic_fetch_add(&token_, 1);

		return currToken;
	}

	// atomically fetch the turn counters value
	int fetchTurn()
	{
		// atomically get the value of our turn counter
		int currTurn = atomic_load(&turn_);

		return currTurn;
	}

};
