#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 8
#define MAX_INPUTS 100

int main(int argc, char *argv[])
{
    char *command[MAX_ARGS + 1]; // +1 for NULL termination
    int placeholder_c = 0;
    int cmd_index = 0; 

    // initilizing commands to avoid unwanted errors
    for (int j = 0; j < MAX_ARGS + 1; j++) { 
        command[j] = NULL;
    }
    
    // setting repetitive part of the command for all the processes.
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "%") != 0) {
            command[cmd_index] = argv[i];
            cmd_index++; 
        } else {
            placeholder_c++; // count number of "%"
        }
    }


    // Taking input for the remaining parts of each command
    char input[MAX_INPUTS];
    char *inputs[MAX_INPUTS];
    int input_index = 0;
    
        // Read inputs from stdin
    while (fgets(input, sizeof(input), stdin)) {
        // Strip newline character
        input[strcspn(input, "\n")] = 0;
        inputs[input_index] = strdup(input);
        input_index++;
    }


    // Execute commands for each input
    for(int i = 0; i < input_index; i++) {
        pid_t pid = fork();
        if (pid < 0) { // error
            fprintf(stderr, "Fork failed\n");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process

            // make an array from the each space separated input
            char *token = strtok(inputs[i], " ");
            int token_count = 0;
                
            while (token != NULL && token_count < placeholder_c) {
                command[cmd_index + token_count] = token; // commplete the command array by adding tokens
                token_count++;
                token = strtok(NULL, " ");
            }

            // adding null terminator
            command[cmd_index+ token_count] = NULL;

            // execute the command
            if (execvp(command[0], command) == -1) { // check for errors
                perror("execvp");
                fprintf(stderr, "error = %d\n", errno);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i < input_index; i++) {
        wait(NULL);
    }

        // Free allocated memory
    for (int i = 0; i < input_index; i++) {
        free(inputs[i]);
    }


    return 0;
}
