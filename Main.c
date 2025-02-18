#include <stdio.h>
#include <stdlib.h>

int main(void){

    size_t input_size = 0;
    char* input_line = NULL;

    if (getline(&input_line, &input_size, stdin) == -1) {
        free(input_line);
        perror("Failed to read input");
        return 0;
    }

    printf("Got input: '%s'\n", input_line);
    free(input_line);
}