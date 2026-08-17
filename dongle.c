#include "helper.h"

void init_dongles(t_config *config, t_dongle *dongles){
    int     i;
    i = 0;
    while (i < (*config).number_of_coders){
        dongles[i].used = 0;
        pthread_mutex_init(&dongles[i].mutex, NULL);
        pthread_cond_init(&dongles[i].cond, NULL);
        dongles[i].last_release = get_time_ms();
        i ++;
    }

}

void take_dongle(t_config *config, t_dongle *dongles, int index){
    long deadline_ms = 0;
    struct timespec deadline;
    pthread_mutex_lock(&dongles[index].mutex);
    while(dongles[index].used == 1 ||
        config->dongle_cooldown > get_time_ms()-dongles[index].last_release){

        if (dongles[index].used == 1)
            pthread_cond_wait(&dongles[index].cond,
            &dongles[index].mutex);

        else if (config->dongle_cooldown > get_time_ms() - dongles[index].last_release){
            deadline_ms = dongles[index].last_release + config->dongle_cooldown;

            deadline.tv_sec = deadline_ms / 1000;
            deadline.tv_nsec = (deadline_ms % 1000) * 1000000;
    pthread_cond_timedwait(&dongles[index].cond,
    &dongles[index].mutex,
    &deadline);
    }

    }
    dongles[index].used = 1;
    pthread_mutex_unlock(&dongles[index].mutex);
}

void take_dongles(t_config *config, t_dongle *dongles, int left, int right){
    if (left < right){
        take_dongle(config, dongles, left);
        take_dongle(config, dongles, right);
    }
    else{
        take_dongle(config, dongles, right);
        usleep(10000);
        take_dongle(config, dongles, left);
    }
}


void leave_dongle(t_dongle *dongles, int index){
    pthread_mutex_lock(&dongles[index].mutex);
    dongles[index].used = 0;
    pthread_cond_broadcast(&dongles[index].cond);
    pthread_mutex_unlock(&dongles[index].mutex);
}

void leave_dongles(t_dongle *dongles, int left, int right){
    leave_dongle(dongles, left);
    leave_dongle(dongles, right);
}