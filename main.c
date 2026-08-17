#include "helper.h"

int main (int argc, char *argv[]){
    t_config config;
    if (parsing(argc, argv, &config)){
        t_coder coders[config.number_of_coders];
        pthread_t coders_threads[config.number_of_coders];
        pthread_t monitor_thread;
        t_dongle dongles[config.number_of_coders];
        t_monitor monitor;
        init_dongles(&config, dongles);
        init_coders(&config, dongles, coders);
        init_monitor(&monitor, &config, coders);
        start_coders(coders, coders_threads);
        start_monitor(&monitor, &monitor_thread);
        wait_coders(coders, coders_threads);
        wait_monitor(&monitor_thread);
    }

    return 0;
}