#include "helper.h"
#include <pthread.h>
#include <threads.h>
#include <unistd.h>

int simulation_over(t_monitor *monitor){
    int over;
    pthread_mutex_lock(&monitor->config->simulation_over_lock);
    over = monitor->config->simulation_over;
    pthread_mutex_unlock(&monitor->config->simulation_over_lock);
    if (over){
        return 1;
    }
    return 0;
}

void get_compiling_info(t_coder *coder, long *last_compile_start, int *number_of_compiles){
    pthread_mutex_lock(&coder->mutex);
    *last_compile_start = coder->last_compile_start;
    *number_of_compiles = coder->number_of_compiles;
    pthread_mutex_unlock(&coder->mutex);
}
void scan_coders(t_monitor *monitor){
    int         i;
    int         all_done;
    long        last_compile_start;
    int         number_of_compiles;

    all_done = 1;
    i = 0;
    while(i < monitor -> config -> number_of_coders){
        get_compiling_info(&monitor->coders[i], &last_compile_start, &number_of_compiles);
        if (number_of_compiles < monitor ->config->number_of_compiles_required){
            all_done = 0;
            if ( get_time_ms() - last_compile_start >= monitor ->config->time_to_burnout){
            pthread_mutex_lock(&monitor->config->simulation_over_lock);
            monitor->config->simulation_over = 1;
            pthread_mutex_unlock(&monitor->config->simulation_over_lock);
            pthread_mutex_lock(&monitor->config->print_lock);
            printf("%ld %d burned out\n", get_time_ms(), monitor->coders[i].id + 1);
            pthread_mutex_unlock(&monitor->config->print_lock);

            return;
            }
        }  
        i ++;
        }
    if (all_done){
        pthread_mutex_lock(&monitor->config->simulation_over_lock);
        monitor->config->simulation_over = 1;
        pthread_mutex_unlock(&monitor->config->simulation_over_lock);
    }
}

void *monitor_routine(void *arg){
    t_monitor   *monitor;
   

    monitor = (t_monitor *)arg;

    while(1){
    
        scan_coders(monitor);
       
        
        if (simulation_over(monitor)){
            break;
        }
    usleep(1000);
    }
    return NULL;
}

void init_monitor(t_monitor *monitor, t_config *config, t_coder *coders){
    monitor->config = config;
    monitor->coders = coders;

}

void start_monitor(t_monitor *monitor, pthread_t *thread){
    pthread_create(thread, NULL, monitor_routine, monitor);

}

void wait_monitor(pthread_t *monitor_thread){
    pthread_join(*monitor_thread, NULL);
}