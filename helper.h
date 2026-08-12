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
    int             simulazione_finita;
} t_config;

typedef struct s_dongle{
    int             used;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    struct timeval  last_release;
    
} t_dongle;

typedef struct s_coder{
    t_config        *config;
    t_dongle        *dongles;
    int             id;
} t_coder;

int     is_valid_number(char *str);
int parsing(int argc, char *argv[], t_config *config);
void set_config(t_config *config, char *str[]);
void    print_config(t_config *config);
void start_coders(t_coder *coders, pthread_t *threads);
void wait_coders (t_coder *coders, pthread_t *threads);
long get_time_ms(void);
void init_dongles(t_config *config, t_dongle *dongles);
void take_dongles(t_dongle *dongles, int left, int right);
void leave_dongles(t_dongle *dongles, int left, int right);
void init_coders(t_config *config, t_dongle *dongles, t_coder *coders);

#endif