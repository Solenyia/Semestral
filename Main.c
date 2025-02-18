#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

    char *s;
    s = malloc(1024 * sizeof(char));    // allocate memory for 1024 characters
    
    // filename logic
    printf("Enter filename: ");
    scanf("%s", s);
    s = realloc(s, strlen(s) + 1);      // reallocate memory to fit the exact number of characters
    printf("%s\n", s);

    // message logic
    printf("Enter message: ");
    scanf("%s", s);
    s = realloc(s, strlen(s) + 1);
    printf("%s\n", s);

    free(s);

    return 0;
}