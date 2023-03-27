#include "philo.h"

int ft_atoi(const char *str)
{
    int result = 0;
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

unsigned long get_timestamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


// This function prints the current status of a philosopher
void print_status(t_simulation *simulation, int philosopher_id, const char *status)
{
    unsigned long timestamp;

    // Lock the state_mutex to ensure only one thread prints at a time
    pthread_mutex_lock(&simulation->state_mutex);

    // If the simulation has not ended, print the status message
    if (!simulation->simulation_ended)
    {
        timestamp = get_timestamp();
        printf("%lu %d %s\n", timestamp, philosopher_id, status);
    }

    // Unlock the state_mutex to allow other threads to print
    pthread_mutex_unlock(&simulation->state_mutex);
}

bool is_numeric(const char *str)
{
    if (*str == '\0')
        return false;

    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return false;
        str++;
    }
    return true;
}

// void write_logs(t_simulation *simulation, int philosopher_id, const char *message)
// {
//     unsigned long long timestamp;

//     if (pthread_mutex_lock(&simulation->state_mutex) != 0)
//         return;

//     timestamp = get_timestamp();
//     printf("%llu %d %s\n", timestamp, philosopher_id, message);

//     pthread_mutex_unlock(&simulation->state_mutex);
// }

