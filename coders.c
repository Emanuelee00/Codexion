#include "helper.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>

void compiling(t_coder *coder){
    printf("I'm coder: %d, I'm compiling : ", (*coder).id + 1);
    pthread_mutex_lock(&(*coder).mutex);
    coder->last_compile_start = get_time_ms();
  
    pthread_mutex_unlock(&(*coder).mutex);
    printf("I wait %.2f s\n", (float)(*coder).config -> time_to_compile /1000);
    usleep((*coder).config -> time_to_compile * 1000);

    pthread_mutex_lock(&(*coder).mutex);
    coder->number_of_compiles += 1;
    pthread_mutex_unlock(&(*coder).mutex);
}

void debugging(t_coder *coder){
  printf("I'm debugging : ");
        printf("I wait %.2f s\n", (float)(*coder).config -> time_to_debug /1000);
        usleep(coder -> config -> time_to_debug * 1000);
}
void refactoring(t_coder *coder){
  printf("I'm refactoring : ");
        printf("I wait %.2f s\n", (float)(*coder).config -> time_to_refactor /1000);
        printf("\n");
        usleep( coder -> config -> time_to_refactor * 1000);
}
void *routine(void *arg){
    t_coder *coder = (t_coder *)arg;
    int     i;
    i = 0;
    while(i < (*(*coder).config).number_of_compiles_required){
        printf("I'm taking the dongles: left: %d, right: %d ",(*coder).id, ((*coder).id + 1) % (*coder).config -> number_of_coders );
        take_dongles((*coder).config, (*coder).dongles, (*coder).id, ((*coder).id + 1) % (*coder).config -> number_of_coders);
        
        compiling(coder);
        debugging(coder);
        refactoring(coder);
        
        printf("I'm leaving the dongles: left: %d, right: %d ",(*coder).id, ((*coder).id + 1) % (*coder).config -> number_of_coders );
        leave_dongles((*coder).dongles, (*coder).id, ((*coder).id + 1) % (*coder).config -> number_of_coders);

        i ++;
    }
    return NULL;
}

void init_coders(t_config *config, t_dongle *dongles, t_coder *coders){
    int     i;
    i = 0;
    while (i < (*config).number_of_coders){
        coders[i].config = config;
        coders[i].dongles = dongles;
        coders[i].id = i;
        coders[i].number_of_compiles = 0;
        coders[i].last_compile_start = get_time_ms();
        pthread_mutex_init(&coders[i].mutex, NULL);
        i ++;
    }

}

void start_coders(t_coder *coders, pthread_t *threads) {
    int     i;
    i = 0;
    while (i < (* coders[0].config).number_of_coders){
        pthread_create(&threads[i], NULL, routine, &coders[i]);
        i ++;
    }
}

void wait_coders(t_coder *coders, pthread_t *threads) {
    int     i;
    i = 0;
    while (i < (* coders[0].config).number_of_coders) {
        pthread_join(threads[i], NULL);
        i++;
    }
}