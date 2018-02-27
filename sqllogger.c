#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int params_are_ok(int argc);
int file_is_available(char* filename);

int main(int argc, char* argv[]) {

    int params_result = params_are_ok(argc);
    if (params_result != EXIT_SUCCESS){
        printf("Error: %s\n", strerror(params_result));
        return EXIT_FAILURE;
    }
    if (file_is_available(argv[1]) != EXIT_SUCCESS) {
        perror("Error");
        return EXIT_FAILURE;
    }
    
}

int params_are_ok(argc) {
    // do more checking here
    if (argc > 2) {
        return EINVAL;    
    }
    return EXIT_SUCCESS;
}

int file_is_available(char* filename) {

    struct stat *statbuf;
    errno = 0;
    statbuf = malloc(sizeof(struct stat));    
    int exists = stat(filename, statbuf);
    free(statbuf);

    if (exists != 0) {
        return errno;
    }
    return EXIT_SUCCESS;
}