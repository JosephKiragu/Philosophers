#include "philo.h"

int main(int argc, char **argv)
{
    t_simulation simulation;

    // Check if the correct number of command-line arguments is provided
    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    // Parse and store command-line arguments in the simulation struct
    if (!parse_arguments(&simulation, argc, argv) || !validate_arguments(&simulation))
    {
        printf("Invalid arguments\n");
        return 1;
    }
	printf("PROGRAM VALIDATES AND SIMULATION IS TO BE INITIALIZED \n");

    // Initialize the simulation (create philosophers, forks, etc.)
    if (!init_simulation(&simulation))
    {
        printf("Failed to initialize simulation\n");
        return 1;
    }

    // Run the simulation (start philosopher threads)
    run_simulation(&simulation);

    // Clean up resources used by the simulation (free memory, destroy mutexes, etc.)
    cleanup_simulation(&simulation);

    return 0;
}

bool parse_arguments(t_simulation *simulation, int argc, char **argv)
{
    // Store the command-line arguments in the simulation struct
    simulation->num_philosophers = ft_atoi(argv[1]);
    simulation->time_to_die = ft_atoi(argv[2]);
    simulation->time_to_eat = ft_atoi(argv[3]);
    simulation->time_to_sleep = ft_atoi(argv[4]);
    simulation->meals_required = (argc == 6) ? ft_atoi(argv[5]) : -1; /* check if optional 6th command has been included.
	if so assign the value in argv[5] else assign -1*/ 

    return true;
}

bool validate_arguments(t_simulation *simulation)
{
    // Check if the provided arguments are valid (positive values)
    if (simulation->num_philosophers <= 0 || simulation->time_to_die <= 0 || simulation->time_to_eat <= 0 || simulation->time_to_sleep <= 0)
        return false;

    // If the number of required meals is specified, check if it's a non-zero value
    if (simulation->meals_required == 0)
        return false;

    return true;
}
