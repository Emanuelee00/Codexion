#include "helper.h"

void init_dongles(t_config *config, t_dongle *dongles){
    int     i;
    i = 0;
    while (i < (*config).number_of_coders){
        dongles[i].used = 0;
        pthread_mutex_init(&dongles[i].mutex, NULL);
        pthread_cond_init(&dongles[i].cond, NULL);
        gettimeofday(&dongles[i].last_release, NULL);
        i ++;
    }

}

void take_dongle(t_dongle *dongles, int index){
    pthread_mutex_lock(&dongles[index].mutex);
    while(dongles[index].used == 1){
        pthread_cond_wait(&dongles[index].cond,
            &dongles[index].mutex);
        }
    dongles[index].used = 1;
    pthread_mutex_unlock(&dongles[index].mutex);
}

void take_dongles(t_dongle *dongles, int left, int right){
    if (left < right){
        take_dongle(dongles, left);
        take_dongle(dongles, right);
    }
    else{
        take_dongle(dongles, right);
        usleep(10000);
        take_dongle(dongles, left);
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