#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"

int main(void){

    int i = 0;
    char *fname;
    char *message;
    FILE *fptr;
    fname = malloc(1024 * sizeof(char));    // allocate memory for 1024 characters
    
    // filename logic
    printf("Enter filename: ");
    scanf("%s", fname);
    fname = realloc(fname, strlen(fname) + 1);      // reallocate memory to fit the exact number of characters
    fptr = fopen(fname, "w");
    if (fptr == NULL) {
        perror("Error opening file");
        free(fname);
        return 1;
    }
    
    // clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // message logic
    message = malloc(1024 * sizeof(char));
    printf("Enter message: ");
    fgets(message, MAX_MSG_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0';         // remove newline character
    message = realloc(message, strlen(message) + 1);
    fwrite(message, sizeof(char), strlen(message), fptr);
    
    // cleanup
    fclose(fptr);
    free(message);
    free(fname);

    return 0;
}