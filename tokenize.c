#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_tokens(const char *input);
int tokenize(char *input, int *token_count, char ***token_vector);
void print_tokens(int token_count, char **token_vector);

int main(int argc, char **argv) {
    char line[1024];
    int tokenc;
    char **tokenv;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        tokenc = count_tokens(line);
        tokenize(line, &tokenc, &tokenv);
        print_tokens(tokenc, tokenv);

        // Free memory allocated for tokens
        for (int i = 0; i < tokenc; i++) {
            free(tokenv[i]);
        }
        free(tokenv);
    }

    return 0;
}

int count_tokens(const char *input) {
    int token_count = 0;
    const char *delimiter = " \t"; 
    char *copy = strdup(input);     // Create a copy of input
    char *saveptr;                  

    
    char *token = strtok_r(copy, delimiter, &saveptr);

    while (token != NULL) {
        token_count++;
        token = strtok_r(NULL, delimiter, &saveptr);
    }

    free(copy);  // Free memory

    return token_count;
}

int tokenize(char *input, int *token_count, char ***token_vector) {
    const char *delimiter = " \t";
    char **tokens = NULL;
    char *token;
    char *saveptr;
    int count = 0;

    // Allocate memory
    tokens = (char **)malloc((*token_count) * sizeof(char *));
    if (tokens == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Tokenization using strtok_r
    token = strtok_r(input, delimiter, &saveptr);
    while (token != NULL) {
        tokens[count] = strdup(token);
        if (tokens[count] == NULL) {
            perror("Failed to allocate memory for token");
            exit(EXIT_FAILURE);
        }
        count++;
        token = strtok_r(NULL, delimiter, &saveptr);
    }

    *token_vector = tokens;
    return count;
}

void print_tokens(int token_count, char **token_vector) {
    for (int i = 0; i < token_count; i++) {
        printf("%s\n", token_vector[i]);
    }
}
