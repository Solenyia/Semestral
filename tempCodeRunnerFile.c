#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){

    char* fname = malloc(1024 * sizeof(char));
    char* message;

    printf("Enter filename: ");
    scanf("%s", fname);
    fname = realloc(fname, strlen(fname) + 1);

    int fw = open(fname, O_WRONLY | O_CREAT);
    if(fw == -1){
        perror("Error opening file");
        free(fname);
        return 1;
    }

    // clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // // message logic
    // message = malloc(1024 * sizeof(char));
    // printf("Enter message: ");
    // fgets(message, MAX_MSG_SIZE, stdin);
    // message[strcspn(message, "\n")] = '\0';         // remove newline character
    // message = realloc(message, strlen(message) + 1);
    // write(fw, message, strlen(message));

    // // cleanup
    // free(message);
    free(fname);
    close(fw);
}