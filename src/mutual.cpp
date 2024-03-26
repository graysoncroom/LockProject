#include "PetersonsLock.h"
#include "TournamentTree.h"
#include "TestAndSet.h"

#include <iostream> // std::cout, std::cerr, std::endl
#include <string>   // std::stoi
#include <cstdlib>  // std::exit

#define INVALID_ALGO_ARG_ERROR 1
#define INVALID_THREAD_ARG_ERROR 2
#define INVALID_NUMBER_OF_ARGS_ERROR 3

// Note that the `int n` parameter
// indicates, in each case, how many
// threads the algorithm should use.
void run_TT_based_algo(int n);
void run_TAS_based_algo(int n);
void run_FAI_based_algo(int n);

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

void run_TT_based_algo(int n)
{
  // TODO: Implement
}

void run_TAS_based_algo(int n)
{
  // TODO: Implement
}

void run_FAI_based_algo(int n)
{
  // TODO: Implement
}
