#include "helper.h"
#include <pthread.h>


void set_config(t_config *config, char *argv[]) {
    (*config).number_of_coders = atoi(argv[1]);
    (*config).time_to_burnout = atoi(argv[2]);
    (*config).time_to_compile = atoi(argv[3]);
    (*config).time_to_debug = atoi(argv[4]);
    (*config).time_to_refactor = atoi(argv[5]);
    (*config).number_of_compiles_required = atoi(argv[6]);
    (*config).dongle_cooldown = atoi(argv[7]);
    (*config).scheduler = argv[8];
    (*config).simulation_over = 0;
    pthread_mutex_init(&(*config).print_lock, NULL);
    pthread_mutex_init(&(*config).simulation_over_lock, NULL);
}
void print_config(t_config *config) {
    printf("number_of_coders: %d\n", config->number_of_coders);
    printf("time_to_burnout: %d\n", config->time_to_burnout);
    printf("time_to_compile: %d\n", config->time_to_compile);
    printf("time_to_debug: %d\n", config->time_to_debug);
    printf("time_to_refactor: %d\n", config->time_to_refactor);
    printf("number_of_compiles_required: %d\n", config->number_of_compiles_required);
    printf("dongle_cooldown: %d\n", config->dongle_cooldown);
    printf("scheduler: %s\n", config->scheduler);
}

int is_valid_number(char *str){
    while(*str != '\0')
    {
        if (*str< '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

long get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

