Dining Philosophers Problem
This is an implementation of the classic Dining Philosophers Problem using C and the pthread library. The problem simulates five philosophers sitting around a circular table, where each philosopher has a plate of spaghetti and a fork to their left. The philosophers spend their lives alternating between thinking and eating. However, they need two forks to eat, so they must wait until both the fork on their left and the fork on their right are available. The goal is to avoid deadlock and ensure that all philosophers can eat without starving.

Problem Statement
The program simulates the following constraints:

Five philosophers are seated around a circular table.
Each philosopher has a plate of spaghetti.
A fork is placed between each pair of adjacent philosophers.
A philosopher must have both forks to eat.
The philosophers do not talk to each other.
The philosophers alternate between thinking, eating, and sleeping.
