#include "PetersonsLock.h"
#include "TournamentTree.h"
#include "TestAndSet.h"

#include <iostream> // std::cout, std::cerr, std::endl
#include <string>   // std::stoi
#include <cstdlib>  // std::exit
#include <thread>
#include <vector>

#define INVALID_ALGO_ARG_ERROR 1
#define INVALID_THREAD_ARG_ERROR 2
#define INVALID_NUMBER_OF_ARGS_ERROR 3

// Note that the `int` parameter
// indicates, in each case, how many
// threads the algorithm should use.
void run_TT_based_algo(int);
void run_TAS_based_algo(int);
void run_FAI_based_algo(int);

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
      run_TT_based_algo(n);
      break;
    case 1:
      run_TAS_based_algo(n);
      break;
    case 2:
      run_FAI_based_algo(n);
      break;
    default:
      std::cerr << "Error: Invalid Algorithm Type Argument. Must be an integer between 0 and 2, inclusive." << std::endl;
      exit(INVALID_ALGO_ARG_ERROR);
  }

  return 0;
}

void dummy_TT_critical_region(int id, TournamentTree<PetersonsLock>& tree, int& x) {
    // Simulate critical region work
    for (int i = 0; i < 10000; i++) {
      tree.acquire(id);
      x = x + 1;
      tree.release(id);
    }
}

void dummy_TAS_critical_region(int id, TASLock& lock, int& x) {
    // Simulate critical region work
    for (int i = 0; i < 10000; i++) {
      lock.acquire();
      x = x + 1;
      lock.release();
    }
}

void run_TT_based_algo(int n)
{
  TournamentTree<PetersonsLock> tree(n); // Construct the TournamentTree object

  int x = 0; // Shared integer to be incremented in the critical section

  std::vector<std::thread> threads; // Vector to hold all threads

  std::cout << "Starting TournamentTree based algorithm with " << n << " threads." << std::endl;

  // Create n threads running the dummy critical region
  for (int i = 0; i < n; ++i) {
    threads.emplace_back(dummy_TT_critical_region, i, std::ref(tree), std::ref(x));
    std::cout << "Thread " << i << " created." << std::endl;
  }

  // Join all threads to ensure they complete before moving on
  for (auto& thread : threads) {
    thread.join();
  }

  // Print out results or completion message
  std::cout << "All Tournament Tree threads have completed their execution." << std::endl;
  std::cout << "Final value of x = " << x << std::endl;
  std::cout << "Expected value of x = " << n * 10000 << std::endl;

  std::cout << "End of TournamentTree based algorithm." << std::endl;
}

void run_TAS_based_algo(int n)
{
  TASLock lock;

  int x = 0; // Shared integer to be incremented in the critical section

  std::vector<std::thread> threads; // Vector to hold all threads

  std::cout << "Starting TASLock based algorithm with " << n << " threads." << std::endl;

  // Create n threads running the dummy critical region
  for (int i = 0; i < n; ++i) {
    threads.emplace_back(dummy_TAS_critical_region, i, std::ref(lock), std::ref(x));
    std::cout << "Thread " << i << " created." << std::endl;
  }

  // Join all threads to ensure they complete before moving on
  for (auto& thread : threads) {
    thread.join();
  }

  // Print out results or completion message
  std::cout << "All Tournament Tree threads have completed their execution." << std::endl;
  std::cout << "Final value of x = " << x << std::endl;
  std::cout << "Expected value of x = " << n * 10000 << std::endl;

  std::cout << "End of TournamentTree based algorithm." << std::endl;
}

void run_FAI_based_algo(int n)
{
  // TODO: Implement
}
