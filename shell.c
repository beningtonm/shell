#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void print_prompt();
void display_banner();
int count_tokens(const char *input);
int tokenize(char *input, int *token_count, char ***token_vector);
void print_tokens(int token_count, char **token_vector);

int main(int argc, char **argv)
{
    char line[1024];
    int tokenc;
    char **tokenv;
    char input[1024];
    display_banner();

    while (1)
    {
        print_prompt();

        if (fgets(input, sizeof(input), stdin) == NULL){
            // End of user input
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        // Exit on "exit"
        if (strcmp(input, "exit") == 0){
            printf("Exiting terminal...\nHAVE A GOOD DAY!\n");
            break;
        }

        pid_t pid = fork();

        if (pid == -1){
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0){ 
            // Child 
            tokenize(input, &tokenc, &tokenv);

            char *program_path = tokenv[0]; // Get program name

            // Count the number of arguments
            int num_args = tokenc - 1;

            char **program_args = (char **)malloc((num_args + 2) * sizeof(char *));
            if (program_args == NULL)
            {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }

            // Set the first element as program name
            program_args[0] = program_path;

            // Copy the arguments, skip first elem
            for (int i = 1; i <= num_args; i++)
            {
                program_args[i] = tokenv[i];
            }

            // The last element must be NULL
            program_args[num_args + 1] = NULL;

            // Execute the command using execvp
            int ret = execvp(program_path, program_args);

            if (ret == -1)
            {
                perror("Exec failed");
                exit(EXIT_FAILURE);
            }
            // Free allocated memory for program_args
            free(program_args);
        }

        else
        { // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

void print_prompt()
{
    printf("MMUX> ");
}

void display_banner()
{
    printf("\n\n\n");
    printf("WELCOME TO: ...\n\n\n");
    printf("███    ███ ██  ██████ ██   ██  █████  ███████ ██      ███████     ███    ███ ██ ███    ██ ██     ██    ██ ███    ██ ██ ██   ██     ███████ ██   ██ ███████ ██      ██     \n");
    printf("████  ████ ██ ██      ██   ██ ██   ██ ██      ██      ██          ████  ████ ██ ████   ██ ██     ██    ██ ████   ██ ██  ██ ██      ██      ██   ██ ██      ██      ██     \n");
    printf("██ ████ ██ ██ ██      ███████ ███████ █████   ██      ███████     ██ ████ ██ ██ ██ ██  ██ ██     ██    ██ ██ ██  ██ ██   ███       ███████ ███████ █████   ██      ██     \n");
    printf("██  ██  ██ ██ ██      ██   ██ ██   ██ ██      ██           ██     ██  ██  ██ ██ ██  ██ ██ ██     ██    ██ ██  ██ ██ ██  ██ ██           ██ ██   ██ ██      ██      ██     \n");
    printf("██      ██ ██  ██████ ██   ██ ██   ██ ███████ ███████ ███████     ██      ██ ██ ██   ████ ██      ██████  ██   ████ ██ ██   ██     ███████ ██   ██ ███████ ███████ ███████\n");
    printf("\n\n\n");
}

int count_tokens(const char *input)
{
    int token_count = 0;
    const char *delimiter = " \t";
    char *copy = strdup(input); // copy input
    char *saveptr;              // Save pointer for strtok_r

    char *token = strtok_r(copy, delimiter, &saveptr);

    while (token != NULL)
    {
        token_count++;
        token = strtok_r(NULL, delimiter, &saveptr);
    }

    free(copy); // Free memory allocated for string copy

    return token_count;
}

int tokenize(char *input, int *token_count, char ***token_vector)
{
    const char *delimiter = " \t";
    char **tokens = NULL;
    char *token;
    char *saveptr;
    int count = 0;

    // Allocate memory for array
    tokens = (char **)malloc((*token_count) * sizeof(char *));
    if (tokens == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    token = strtok_r(input, delimiter, &saveptr);
    while (token != NULL)
    {
        tokens[count] = strdup(token);
        if (tokens[count] == NULL)
        {
            perror("Failed to allocate memory for token");
            exit(EXIT_FAILURE);
        }
        count++;
        token = strtok_r(NULL, delimiter, &saveptr);
    }

    *token_vector = tokens;
    return count;
}

void print_tokens(int token_count, char **token_vector)
{
    for (int i = 0; i < token_count; i++)
    {
        printf("%s\n", token_vector[i]);
    }
}
