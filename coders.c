#include "helper.h"

void *routine(void * arg){
    t_coder *coder = (t_coder *)arg;
    int     i;
    i = 0;
    while(i < (*(*coder).config).number_of_compiles_required){
        printf("I'm taking the dongles: left: %d, right: %d ",(*coder).id, ((*coder).id + 1) % (*coder).config -> number_of_coders );
        take_dongles((*coder).dongles, (*coder).id, ((*coder).id + 1) % (*coder).config -> number_of_coders);
        
        printf("I'm coder: %d, I'm compiling : ", (*coder).id + 1);
        printf("I wait %.2f s\n", (float)(*coder).config -> time_to_compile /1000);
        usleep((*coder).config -> time_to_compile * 1000);
        
        printf("I'm leaving the dongles: left: %d, right: %d ",(*coder).id, ((*coder).id + 1) % (*coder).config -> number_of_coders );
        leave_dongles((*coder).dongles, (*coder).id, ((*coder).id + 1) % (*coder).config -> number_of_coders);
        printf("I'm debugging : ");
        printf("I wait %.2f s\n", (float)(*coder).config -> time_to_debug /1000);
        usleep(coder -> config -> time_to_debug * 1000);

        printf("I'm refactoring : ");
        printf("I wait %.2f s\n", (float)(*coder).config -> time_to_refactor /1000);
        printf("\n");
        usleep( coder -> config -> time_to_refactor * 1000);

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