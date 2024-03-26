#include "PetersonsLock.h"
#include "TournamentTree.h"
#include "TestAndSet.h"
#include "FetchAndIncrement.h"

#include <iostream> // std::cout, std::cerr, std::endl
#include <string>   // std::stoi
#include <cstdlib>  // std::exit
#include <thread>
#include <vector>

#define INVALID_ALGO_ARG_ERROR 1
#define INVALID_THREAD_ARG_ERROR 2
#define INVALID_NUMBER_OF_ARGS_ERROR 3

template <typename LockType>
void thread_work_simulation(int, LockType&, int&);

template <typename LockType>
void simulate_lock_work(int, LockType&);

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Error: Invalid number of arguments. " 
              << "Check that exactly 2 arguments were passed to the program and try again."
              << std::endl;
    exit(INVALID_NUMBER_OF_ARGS_ERROR);
  }

  int algo_type_argument = (int)argv[1][0] - (int)'0';

  if (algo_type_argument < 0 || algo_type_argument > 9) 
  {
    std::cerr << "Error: Invalid Algorithm Type Argument. Must be a single digit number." 
              << std::endl;
    exit(INVALID_ALGO_ARG_ERROR);
  }

  int n = std::stoi(argv[2]);

  if (n <= 0) 
  {
    std::cerr << "Error: Invalid Thread Count Argument. Must be a positive integer." << std::endl;
    exit(INVALID_THREAD_ARG_ERROR);
  }

  switch (algo_type_argument)
  {
    case 0:
    {
      std::cout << "Starting TournamentTree based algorithm with " << n << " threads." << std::endl;
      TournamentTree<PetersonsLock> tree_metalock(n);
      simulate_lock_work(n, tree_metalock);
      // run_TAS_based_algo(n);
      std::cout << "End of TournamentTree based algorithm." << std::endl;
      break;
    }

    case 1: 
    {
      std::cout << "Starting Test-And-Set based algorithm with " << n << " threads." << std::endl;
      TASLock lock;
      simulate_lock_work(n, lock);
      // run_TAS_based_algo(n);
      std::cout << "End of Test-And-Set based algorithm." << std::endl;
      break;
    }

    case 2: 
    {
      std::cout << "Starting Fetch-And-Increment based algorithm with " << n << " threads." << std::endl;
      FAILock lock;
      simulate_lock_work(n, lock);
      // run_FAI_based_algo(n);
      std::cout << "End of Fetch-And-Increment based algorithm." << std::endl;
      break;
    }

    default: 
    {
      std::cerr << "Error: Invalid Algorithm Type Argument. Must be an integer between 0 and 2, inclusive." << std::endl;
      exit(INVALID_ALGO_ARG_ERROR);
    }
  }

  return 0;
}

template <typename LockType>
void thread_work_simulation(__attribute__((unused)) int id, LockType& lock, int& x) 
{
    for (int i = 0; i < 1000; i++) {
        lock.acquire();
        // std::cout << "Thread " << id << " acquired lock." << std::endl;
        x = x + 1;
        // std::cout << "x = " << x << std::endl;
        // std::cout << "Thread " << id << " released lock." << std::endl;
        lock.release();
    }
}

template <>
void thread_work_simulation<TournamentTree<PetersonsLock>>(int id, TournamentTree<PetersonsLock>& tree, int& x) 
{
    for (int i = 0; i < 1000; i++) {
      tree.acquire(id);
      x = x + 1;
      tree.release(id);
    }
}

template <typename LockType>
void simulate_lock_work(int n, LockType& lock) 
{
  int x = 0; // Shared integer to be incremented in the critical section

  std::vector<std::thread> threads; // Vector to hold all threads

  // Create n threads running the `x` incrementing code
  for (int i = 0; i < n; ++i) {
    threads.emplace_back(thread_work_simulation<LockType>, i, std::ref(lock), std::ref(x));
    std::cout << "Thread " << i << " created." << std::endl;
  }

  // Join all threads
  for (auto& thread : threads) {
    thread.join();
  }

  // Print results
  std::cout << "All threads have completed their execution." << std::endl;
  std::cout << "Final value of x = " << x << std::endl;
  std::cout << "Expected value of x = " << n * 1000 << std::endl;
}
