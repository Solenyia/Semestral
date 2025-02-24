#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(void){

    char* fname = malloc(1024 * sizeof(char));
    char* message;
    srand(time(NULL));
    int r = rand();

    printf("Enter filename: ");
    scanf("%s", fname);
    fname = realloc(fname, strlen(fname) + 1);

    int fw = open(fname, O_CREAT | O_WRONLY | O_APPEND,0644) ;
    if(fw == -1){
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
    message = realloc(message, strlen(message) + 2);
    message[strlen(message)] = '\n';
    
    char* reformed = malloc(sizeof(message) + 10);
    sprintf(reformed, "%d: %s\n",r, message);
    write(fw, reformed, strlen(reformed));

    // cleanup
    free(message);
    free(fname);
    free(reformed);

    int is_success = close(fw);
    printf("File closed with status: %d\n", is_success);
}