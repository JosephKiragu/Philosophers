#include "philo.h"


// The philosopher starts thinking
void think(t_philosopher *philosopher)
{
    print_status(philosopher->simulation, philosopher->id, "is thinking");
}

// The philosopher goes to sleep for the specified amount of time
void sleep_philosopher(t_philosopher *philosopher)
{
    print_status(philosopher->simulation, philosopher->id, "is sleeping");
    usleep(philosopher->simulation->time_to_sleep * 1000); // Convert milliseconds to microseconds and sleep
}

// The philosopher attempts to eat
bool eat(t_philosopher *philosopher)
{
    // Lock the left and right forks
    if (pthread_mutex_lock(philosopher->left_fork) != 0 || pthread_mutex_lock(philosopher->right_fork) != 0)
        return false; // Failed to lock both forks
	print_status(philosopher->simulation, philosopher->id, "has taken a fork");

    // Philosopher is eating
    print_status(philosopher->simulation, philosopher->id, "is eating");
    usleep(philosopher->simulation->time_to_eat * 1000); // Convert milliseconds to microseconds and sleep
    update_last_meal(philosopher); // Update the last meal timestamp
    update_meals_eaten(philosopher); // Increment the number of meals eaten

    // Check if all philosophers have eaten the required number of meals
    if (philosopher->simulation->meals_required > 0)
    {
        int i;
        bool all_philosophers_have_eaten = true;
        for (i = 0; i < philosopher->simulation->num_philosophers; i++)
        {
                        if (philosopher->simulation->philosophers[i].meals_eaten < philosopher->simulation->meals_required)
            {
                all_philosophers_have_eaten = false;
                break; // If any philosopher hasn't eaten the required number of meals, break the loop
            }
        }

        // If all philosophers have eaten the required number of meals, stop the simulation
        if (all_philosophers_have_eaten)
            stop_simulation(philosopher->simulation);
    }

    // Unlock the left and right forks
    if (pthread_mutex_unlock(philosopher->right_fork) != 0 || pthread_mutex_unlock(philosopher->left_fork) != 0)
        return false; // Failed to unlock both forks

    return true;
}

// Check if a philosopher has died (exceeded the time_to_die threshold)
bool check_death(t_philosopher *philosopher)
{
    if (get_timestamp() - philosopher->last_meal >= philosopher->simulation->time_to_die)
    {
        philosopher->is_dead = true;
        print_status(philosopher->simulation, philosopher->id, "died");
        return true;
    }
    return false;
}

// Update the last meal timestamp for a philosopher
void update_last_meal(t_philosopher *philosopher)
{
    philosopher->last_meal = get_timestamp();
}

// Increment the number of meals eaten by a philosopher
void update_meals_eaten(t_philosopher *philosopher)
{
    philosopher->meals_eaten++;
}

// The main routine for each philosopher thread
void *philosopher_routine(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;

    // Continue executing the routine until the philosopher is dead or the simulation has ended
    while (!philosopher->is_dead && !philosopher->simulation->simulation_ended)
    {
		if (check_death(philosopher))
			break;
        // Attempt to eat; if the philosopher fails to eat, break the loop
        if (!eat(philosopher))
            break;

        // If the philosopher has eaten the required number of meals, break the loop
        if (philosopher->simulation->meals_required > 0 && philosopher->meals_eaten >= philosopher->simulation->meals_required)
		{
			stop_simulation(philosopher->simulation);
            break;
		}
        // Sleep for the specified duration
        sleep_philosopher(philosopher);

        // Start thinking
        think(philosopher);
    }

    return NULL;
}










































// void think(t_philosopher *philosopher)
// {
//     print_status(philosopher->simulation, philosopher->id, "is thinking");
// }

// void sleep_philosopher(t_philosopher *philosopher)
// {
//     print_status(philosopher->simulation, philosopher->id, "is sleeping");
//     usleep(philosopher->simulation->time_to_sleep * 1000);
// }

// bool eat(t_philosopher *philosopher)
// {
//     if (pthread_mutex_lock(philosopher->left_fork) != 0 || pthread_mutex_lock(philosopher->right_fork) != 0)
//         return false;

//     write_logs(philosopher->simulation, philosopher->id, "is eating");
//     usleep(philosopher->simulation->time_to_eat * 1000);
//     update_last_meal(philosopher);
//     update_meals_eaten(philosopher);

//     // Check if all philosophers have eaten the required number of meals
//     if (philosopher->simulation->meals_required > 0)
//     {
//         int i;
//         bool all_philosophers_have_eaten = true;
//         for (i = 0; i < philosopher->simulation->num_philosophers; i++)
//         {
//             if (philosopher->simulation->philosophers[i].meals_eaten < philosopher->simulation->meals_required)
//             {
//                 all_philosophers_have_eaten = false;
//                 break;
//             }
//         }

//         if (all_philosophers_have_eaten)
//             stop_simulation(philosopher->simulation);
//     }

//     if (pthread_mutex_unlock(philosopher->right_fork) != 0 || pthread_mutex_unlock(philosopher->left_fork) != 0)
//         return false;

//     return true;
// }



// bool check_death(t_philosopher *philosopher)
// {
//     if (get_timestamp() - philosopher->last_meal >= philosopher->simulation->time_to_die)
//     {
//         philosopher->is_dead = true;
//         print_status(philosopher->simulation, philosopher->id, "died");
//         return true;
//     }
//     return false;
// }

// void update_last_meal(t_philosopher *philosopher)
// {
//     philosopher->last_meal = get_timestamp();
// }

// void update_meals_eaten(t_philosopher *philosopher)
// {
//     philosopher->meals_eaten++;
// }

// void *philosopher_routine(void *arg)
// {
//     t_philosopher *philosopher = (t_philosopher *)arg;

//     while (!philosopher->is_dead && !philosopher->simulation->simulation_ended)
//     {
//         if (!eat(philosopher))
//             break;

//         if (philosopher->meals_eaten == philosopher->simulation->meals_required)
//             break;

//         sleep_philosopher(philosopher);
//         think(philosopher);
//     }

//     return NULL;
// }
