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

#define NUM_ITERATIONS 1000

template <typename LockType>
void thread_work_simulation(int, LockType&, int&);

template <typename LockType>
void simulate_lock_work(int, LockType&);

int main(int argc, char *argv[])
{
  // ========== Process Program Arguments and Verify Correctness ==========

  // Check that exactly 2 arguments were passed to the program
  if (argc != 3)
  {
    std::cerr << "Error: Invalid number of arguments. " 
              << "Check that exactly 2 arguments were passed to the program and try again."
              << std::endl;
    std::cerr << "For more information and examples, see README.md" << std::endl;
    exit(INVALID_NUMBER_OF_ARGS_ERROR);
  }

  // Convert the algorithm type argument to an integer
  int algo_type_argument = (int)argv[1][0] - (int)'0';

  // Check that the algorithm type argument is a single digit number
  if (algo_type_argument < 0 || algo_type_argument > 9) 
  {
    std::cerr << "Error: Invalid Algorithm Type Argument. Must be a single digit number." 
              << std::endl;
    exit(INVALID_ALGO_ARG_ERROR);
  }

  // Convert the thread count argument to an integer
  int n = std::stoi(argv[2]);

  // Check that the thread count argument is a positive integer
  if (n <= 0) 
  {
    std::cerr << "Error: Invalid Thread Count Argument. Must be a positive integer." << std::endl;
    exit(INVALID_THREAD_ARG_ERROR);
  }

  // ========== Execute the algorithm based on the first argument (algorithm type argument) ==========
  switch (algo_type_argument)
  {
    case 0:
    {
      std::cout << "Starting TournamentTree based algorithm with " << n << " threads." << std::endl;
      TournamentTree<PetersonsLock> tree_metalock(n);
      simulate_lock_work(n, tree_metalock);
      std::cout << "End of TournamentTree based algorithm." << std::endl;
      break;
    }

    case 1: 
    {
      std::cout << "Starting Test-And-Set based algorithm with " << n << " threads." << std::endl;
      TASLock lock;
      simulate_lock_work(n, lock);
      std::cout << "End of Test-And-Set based algorithm." << std::endl;
      break;
    }

    case 2: 
    {
      std::cout << "Starting Fetch-And-Increment based algorithm with " << n << " threads." << std::endl;
      FAILock lock;
      simulate_lock_work(n, lock);
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

/*
 * Thread work simulation function
 * 
 * This function is called by each thread to simulate the work of acquiring and releasing a lock around a critical region
 * 
 * @param id: The id of the thread
 * @param lock: The lock to be used by the thread
 * @param x: The shared integer to be incremented in the critical section
*/
template <typename LockType>
void thread_work_simulation(__attribute__((unused)) int id, LockType& lock, int& x) 
{
    for (int i = 0; i < NUM_ITERATIONS; i++) 
    {
        lock.acquire();
        x = x + 1;
        lock.release();
    }
}


/*
 * Specialization of thread_work_simulation for TournamentTree<PetersonsLock>
 */
template <>
void thread_work_simulation<TournamentTree<PetersonsLock>>(int id, TournamentTree<PetersonsLock>& tree, int& x) 
{
    for (int i = 0; i < NUM_ITERATIONS; i++) 
    {
      tree.acquire(id);
      x = x + 1;
      tree.release(id);
    }
}

/*
 * Function to simulate the work of acquiring and releasing a lock of type `LockType`
 * 
 * @param n: The number of threads
 * @param lock: The lock to be used by the threads
 */
template <typename LockType>
void simulate_lock_work(int n, LockType& lock) 
{
  int x = 0; // Shared integer to be incremented in the critical section

  std::vector<std::thread> threads; // Vector to hold all threads

  // Create n threads running the `x` incrementing code
  for (int i = 0; i < n; ++i) 
  {
    threads.emplace_back(thread_work_simulation<LockType>, i, std::ref(lock), std::ref(x));
    std::cout << "Thread " << i << " created." << std::endl;
  }

  // Join all threads
  for (auto& thread : threads) 
  {
    thread.join();
  }

  // Print results
  std::cout << "All threads have completed their execution." << std::endl;
  std::cout << "Final value of x = " << x << std::endl;
  std::cout << "Expected value of x = " << n * NUM_ITERATIONS << std::endl;
}
