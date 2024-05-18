#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_WORDS 100
#define MAX_LENGTH 1000

int main() {
    char input[MAX_LENGTH];
    char *words[MAX_WORDS];
    int word_count = 0;

    
    
    fgets(input, MAX_LENGTH, stdin);

    
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }

    
    char *token = strtok(input, " ");
    while (token != NULL) {
        words[word_count++] = token;
        token = strtok(NULL, " ");
    }

    
    
    for (int i = 0; i < word_count; i += 2) {
        printf("%s ", words[i]);
    }
    printf("\n");

    return 0;
}

