#include "helper.h"

int main (int argc, char *argv[]){
    t_config config;
    if (parsing(argc, argv, &config)){
        t_coder coders[config.number_of_coders];
        pthread_t threads[config.number_of_coders];
        t_dongle dongles[config.number_of_coders];
        init_dongles(&config, dongles);
        init_coders(&config, dongles, coders);
        start_coders(coders, threads);
        wait_coders(coders, threads);
    }

    return 0;
}