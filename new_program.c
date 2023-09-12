#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program_path> [arguments...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *program_path = argv[1];
    char **program_args = &argv[1];  // Arguments for the new program

    // Execute the new program
    if (execv(program_path, program_args) == -1) {
        perror("execv");  // Report error with perror
        exit(EXIT_FAILURE);
    }

    return 0;  // This line should never be reached if execv is successful
}

