#ifndef PHILO_H
#define PHILO_H

#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_philosopher t_philosopher;
typedef struct s_simulation t_simulation;

struct s_philosopher
{
    int id;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long last_meal;
    int meals_eaten;
    bool is_dead;
    t_simulation *simulation;
};

struct s_simulation
{
    int num_philosophers;
    unsigned long long time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_required;
    bool simulation_ended;
    pthread_mutex_t *forks;
    pthread_mutex_t state_mutex;
    t_philosopher *philosophers;
};

// main.c
int main(int argc, char **argv);
bool parse_arguments(t_simulation *simulation, int argc, char **argv);
bool validate_arguments(t_simulation *simulation);

// philosopher.c
void *philosopher_routine(void *arg);
void think(t_philosopher *philosopher);
void sleep_philosopher(t_philosopher *philosopher);
bool eat(t_philosopher *philosopher);
bool check_death(t_philosopher *philosopher);
void update_last_meal(t_philosopher *philosopher);
void update_meals_eaten(t_philosopher *philosopher);

// simulation.c
bool init_simulation(t_simulation *simulation);
void run_simulation(t_simulation *simulation);
void stop_simulation(t_simulation *simulation);
void cleanup_simulation(t_simulation *simulation);

// utils.c
unsigned long get_timestamp(void);
void ms_sleep(unsigned int ms);
int ft_atoi(const char *str);
void print_status(t_simulation *simulation, int philosopher_id, const char *status);
void write_logs(t_simulation *simulation, int philosopher_id,const char *message);

#endif // PHILO_H

