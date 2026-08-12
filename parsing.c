#include "helper.h"


int parsing(int argc, char *argv[], t_config *config)
{
    int     i;
    i = 1;

    if (argc < 1){
        printf("No arguments provided");
        return 0;
    }
    if (argc != 9){
        printf("Wrong number of arguments!");
        return 0;
    }
    while (i < 8){
        printf("%d",is_valid_number(argv[i]));
        if (!is_valid_number(argv[i])) {
                printf("Number %s not valid", argv[i]);
            return 0;
        }
        printf("str : %s\n",argv[i]);
        i++;
    }
    if (strcmp(argv[i],"fifo") != 0 && strcmp(argv[i], "edf") != 0){
        printf("Scheduler name %s not valid", argv[i]);
        return 0;
    }
    set_config(config, argv);
    print_config(config);

    return 1;
}