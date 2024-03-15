Homework 2 for CS 4348.006 with Professor Mittal
Written by Ashton Smith (ajs190019) and William Grayson Croom (wgc180002).
This program implements 3 mutual exclusion algorithms discussed in class
each one handles the task of synchronization using n threads differently
The selection for which algorithm and how many threads is used as follows:

Our options:
argv[1]: The algorithm type
0- Tournament Tree algorithm
1- Test and set
2- Fetch and Increment

argv[2]: The n number of threads to utilize
(This value of n doesn't need to be a power of 2)

Example: we want to choose TAS Based with 10 threads
./mutual 1 10
