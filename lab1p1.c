#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 8
#define MAX_COMMANDS 100

int main(int argc, char *argv[], char *envp[])
{
    char *commands[MAX_COMMANDS][MAX_ARGS + 1]; // +1 for NULL termination
    int cmd_index = 0;
    int arg_index = 0;

    // Initialize all pointers to NULL
    for (int i = 0; i < MAX_COMMANDS; i++) {
        for (int j = 0; j < MAX_ARGS + 1; j++) {
            commands[i][j] = NULL;
        }
    }

    for (int i = 1; i < argc; i++) {
        // seperate command line arguments seperated by "+" to different arrays 
        if (strcmp(argv[i], "+") != 0) { // not +
            commands[cmd_index][arg_index] = argv[i];
            arg_index++;
        } else { // +
            if (arg_index == 0) { // Empty argument, use /bin/true
                commands[cmd_index][0] = "/bin/true";
                commands[cmd_index][1] = NULL;
            } else { // adding NULL terminator
                commands[cmd_index][arg_index] = NULL;
            }
            arg_index = 0;
            cmd_index++;
        }
    }

                    
    if (arg_index == 0) {
        // Handle the empty command
        commands[cmd_index][0] = "/bin/true";
        commands[cmd_index][1] = NULL;
    } else {
        // Add NULL terminator to the last command
        commands[cmd_index][arg_index] = NULL;
    }

    // Execute each cammand
    for (int i = 0; i <= cmd_index; i++) {

        pid_t pid = fork();

        if (pid < 0) { //error
            fprintf(stderr, "Fork failed\n");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execve(commands[i][0], commands[i], envp) == -1) {
                perror("execve");
                fprintf(stderr, "error = %d\n", errno);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i <= cmd_index; i++) {
        if (wait(NULL) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
