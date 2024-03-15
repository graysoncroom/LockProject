#pragma once

#include <cstddef>
#include <array>

/*
 * `Pow` is a template metafunction that performs the operation 2^N
 * at compile time.
 *
 * Example Usage:
 * const int x = Pow<5>::value;
 *
 * The value of `x` will be 32 (i.e. 2^5)
 * and at run time no computation will be performed.
 *
 * This was necessary to implement in order to pass a template
 * argument to TournamentTree that indicates how many processes/threads
 * will be needing a leaf node in the tree.
 *
 * We also considered making it a constructor argument, but felt that
 * the induced overhead was unnecessary.
 *
 * Warning:
 * On most architectures, going above around N = 62 results in a
 * metafunction return value of 0. This has to do with the limitations
 * of integral representation. A fix for this, if needed in the future,
 * would be to replace the type of value with a BigInteger.
 */
template <unsigned N>
struct Pow
{ static const std::size_t value = 2 * Pow<N-1>::value; };

template <>
struct Pow<0>
{ static const std::size_t value = 1; };

/*
 * `IdWrappedLock` is a simple container that consists of
 * a Lock of type `LockType` and an identifier of type `int`
 *
 * This wrapped-lock type is helpful when dealing with locks in
 * a tournament tree.
 */
template <typename LockType>
struct IdWrappedLock {
   int id_;
   LockType lock_;
};

/*
 * Our implementation of `TournamentTree` expects 2 template arguments,
 * namely, an integer `N` indicating how many threads will be in competition
 * for resources, and a Lock implementation `LockType`.
 *
 * By passing in the type of lock, we generalize this Tournament Tree to work
 * for arbitrary locks. This means our PetersonLock, TASLock, and FAILock will
 * all be scalable to n-threads under this TournamentTree. Very handy.
 */
template <int N, typename LockType>
class TournamentTree 
{
  std::array<IdWrappedLock<LockType>, Pow<N>::value - 1> wrapped_locks_;
 public:
  TournamentTree();
  void acquire(int id);
  void release(int id);
};

