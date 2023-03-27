#include "philo.h"

// Initialize the simulation
bool init_simulation(t_simulation *simulation)
{
    int i;

    // Allocate memory for philosophers and forks
    simulation->philosophers = malloc(sizeof(t_philosopher) * simulation->num_philosophers);
    simulation->forks = malloc(sizeof(pthread_mutex_t) * simulation->num_philosophers);
    if (!simulation->philosophers || !simulation->forks)
        return false;

    // Initialize forks mutexes
    for (i = 0; i < simulation->num_philosophers; i++)
    {
        if (pthread_mutex_init(&simulation->forks[i], NULL) != 0)
            return false;
    }

    // Initialize the philosophers
    for (i = 0; i < simulation->num_philosophers; i++)
    {
        simulation->philosophers[i].id = i + 1;
        simulation->philosophers[i].left_fork = &simulation->forks[i];
        simulation->philosophers[i].right_fork = &simulation->forks[(i + 1) % simulation->num_philosophers];
        simulation->philosophers[i].last_meal = get_timestamp();
        simulation->philosophers[i].meals_eaten = 0;
        simulation->philosophers[i].is_dead = false;
        simulation->philosophers[i].simulation = simulation;
    }

    // Initialize the state mutex
    if (pthread_mutex_init(&simulation->state_mutex, NULL) != 0)
        return false;

    simulation->simulation_ended = false;

    return true;
}

// Run the simulation by creating and starting philosopher threads
void run_simulation(t_simulation *simulation)
{
    int i;

	/*This for loop iterates through each philosopher in the simulation and creates a new 
	thread for them, running the philosopher_routine function.*/
    for (i = 0; i < simulation->num_philosophers; i++)
    {
        if (pthread_create(&simulation->philosophers[i].thread, NULL, philosopher_routine, &simulation->philosophers[i]) != 0)
        {
            stop_simulation(simulation);
            return;
        }
    }

    // Wait for the philosopher threads to finish
	/*The purpose of this loop is to make sure the main thread waits for all philosopher threads to complete their execution 
	before proceeding, ensuring proper cleanup and termination of the program.
	*/
    for (i = 0; i < simulation->num_philosophers; i++)
    {
        pthread_join(simulation->philosophers[i].thread, NULL);
    }
}

// Stop the simulation by setting the simulation_ended flag to true
void stop_simulation(t_simulation *simulation)
{
    simulation->simulation_ended = true;
}

// Clean up resources used by the simulation
void cleanup_simulation(t_simulation *simulation)
{
    int i;

    // Destroy forks mutexes
    for (i = 0; i < simulation->num_philosophers; i++)
    {
        pthread_mutex_destroy(&simulation->forks[i]);
    }

    // Destroy the state mutex
    pthread_mutex_destroy(&simulation->state_mutex);

    // Free allocated memory for philosophers and forks
    free(simulation->philosophers);
    free(simulation->forks);
}
