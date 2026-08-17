#ifndef HELPER_H
# define HELPER_H

# include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_config {
    int             number_of_coders;
    int             time_to_burnout;
    int             time_to_compile;
    int             time_to_debug;
    int             time_to_refactor;
    int             number_of_compiles_required;
    int             dongle_cooldown;
    char            *scheduler;
    pthread_mutex_t print_lock;
    int             simulation_over;
    pthread_mutex_t simulation_over_lock;
} t_config;

typedef struct s_dongle{
    int             used;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    long last_release;
} t_dongle;

typedef struct s_coder{
    t_config        *config;
    t_dongle        *dongles;
    int             id;
    int             number_of_compiles;
    long            last_compile_start;
    pthread_mutex_t mutex;
} t_coder;

typedef struct s_monitor{
    t_config           *config;
    t_coder            *coders;

} t_monitor;

int     is_valid_number(char *str);
int parsing(int argc, char *argv[], t_config *config);
void set_config(t_config *config, char *str[]);
void    print_config(t_config *config);
void start_coders(t_coder *coders, pthread_t *threads);
void wait_coders (t_coder *coders, pthread_t *threads);
long get_time_ms(void);
void init_dongles(t_config *config, t_dongle *dongles);
void take_dongles(t_config *confgi, t_dongle *dongles, int left, int right);
void leave_dongles(t_dongle *dongles, int left, int right);
void init_coders(t_config *config, t_dongle *dongles, t_coder *coders);
void init_monitor(t_monitor *monitor, t_config *config, t_coder *coders);
void start_monitor(t_monitor *monitor, pthread_t *thread);
void wait_monitor(pthread_t *monitor_thread);

#endif