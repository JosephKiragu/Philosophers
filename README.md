# Dining Philosophers Problem
This is an implementation of the classic Dining Philosophers Problem using C and the pthread library. The problem simulates five philosophers sitting around a circular table, where each philosopher has a plate of spaghetti and a fork to their left. The philosophers spend their lives alternating between thinking and eating. However, they need two forks to eat, so they must wait until both the fork on their left and the fork on their right are available. The goal is to avoid deadlock and ensure that all philosophers can eat without starving.

Problem Statement
The program simulates the following constraints:

* Five philosophers are seated around a circular table.
* Each philosopher has a plate of spaghetti.
* A fork is placed between each pair of adjacent philosophers.
* A philosopher must have both forks to eat.
* The philosophers do not talk to each other.
* The philosophers alternate between thinking, eating, and sleeping.

## Usage

1. Clone the repository:
- `git clone https://https://github.com/JosephKiragu/Philosophers.git`
- `cd Philosophers`
2. Compile the program:
- `make`
3. Run the program with the following command line arguments:
- `./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
* number_of_philosophers: The number of philosophers (mandatory).
* time_to_die: Time in milliseconds
* time_to_die: Time in milliseconds for a philosopher to die if they do not start eating (mandatory).
* time_to_eat: Time in milliseconds for a philosopher to finish eating (mandatory).
* time_to_sleep: Time in milliseconds for a philosopher to sleep after eating (mandatory).
* number_of_times_each_philosopher_must_eat (optional): If all philosophers have eaten at least this number of times, the simulation stops. If not         specified, the simulation stops when a philosopher dies.

## Example

To run the simulation with 5 philosophers, a time to die of 800 ms, a time to eat of 200 ms, a time to sleep of 200 ms, and each philosopher must eat 5 times, execute the following command:
- `./philo 5 800 200 200 5`

## Implementation Details
The implementation uses the pthread library to create separate threads for each philosopher, and mutexes to represent the forks. The main challenge in the implementation is to avoid deadlock and ensure that all philosophers can eat without starving.

The code is organized into the following files:

* philo.h: Contains the function prototypes and structure definitions.
* main.c: Parses the command line arguments and initializes the simulation.
* simulation.c: Contains functions related to the simulation, such as initializing and stopping the simulation.
* philosopher.c: Contains the philosopher thread routines and actions (eating, sleeping, thinking, and checking for death).
* utils.c: Contains utility functions, such as converting strings to integers and getting the current timestamp.

## Contributing
Feel free to fork the repository

