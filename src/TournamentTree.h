#pragma once

#include <cstddef>
#include <vector>
#include <iostream>
#include <cmath>

/*
 * `int N` - The number of threads
 * Returns the total number of nodes in the tournament tree
 */
std::size_t calculateTotalNodes(int N) {
    if (N <= 1) {
        return 1; // Base case: For N=1, the tree has only one node.
    }
    int height = std::ceil(std::log2(N)); // Calculate the height of the tree
    return std::pow(2, height) - 1; // Total nodes in a binary tree = 2^(height+1) - 1
}

/*
 * `TournamentTree<LockType>` constructs a full binary tree of locks.

 * It assumes that each thread is has a unique id from 0 to N-1, 
 * where N is the argument to the `TournamentTree` constructor.
 * 
 * It also assumes that the given Lock has 2 methods - acquire and release - which both take in an id argument
 * which can be either 0 or 1. This requirement must be met in order for `TournamentTree` to function properly.
 * 
 * `LockType` - The type of lock to be used in the tournament tree
 */
template <typename LockType>
class TournamentTree 
{
 public:
  std::size_t total_nodes_;
  std::vector<LockType> locks_;

  explicit TournamentTree(int N): total_nodes_(calculateTotalNodes(N)), locks_(total_nodes_) {}

  /*
   * Acquire the lock for the given thread `id`
   */
  void acquire(int id) 
  {
    // int depth = std::ceil(std::log2(total_nodes_));
    int nodeIndex = id + locks_.size(); // Calculate the starting leaf node index
    while (nodeIndex > 0)
    {
      int parentIndex = (nodeIndex - 1) / 2;
      bool isLeftChild = nodeIndex % 2 == 1;
      this->locks_[parentIndex].acquire(isLeftChild ? 0 : 1);
      nodeIndex = parentIndex;
    }
  }

  /*
   * Release the lock for the given thread `id`
   */
  void release(int id) {
    // To store the path from leaf to root
    std::vector<int> path;

    // Calculate the starting leaf node index
    int nodeIndex = id + locks_.size();
    while (nodeIndex > 0)
    {
      path.push_back(nodeIndex);
      nodeIndex = (nodeIndex - 1) / 2;
    }
    path.push_back(0); // Add the root node

    // Release locks in reverse order
    // Note: The `path` vector contains the path from leaf to root
    // We need to release locks in reverse order from root (inclusive) 
    // to leaf (exclusive). This is due to the fact that leaves do not actually
    // a node of their own in the tree, rather, each leaf shares a lock with one
    // of its neighbors.
    for (auto it = path.rbegin(); it != path.rend() - 1; ++it)
    {
      bool isLeftChild = *(it+1) % 2 == 1;
      this->locks_[*it].release(isLeftChild ? 0 : 1);
    }
  }
};


