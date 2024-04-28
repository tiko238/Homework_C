#include <stdio.h>
#include <ctype.h>
#include <string.h>

int getPriority(char c) {
    switch (c) {
        case '&':
            return 1;
        case '^':
            return 2;
        case '|':
            return 3;
        default:
            return 0; 
    }
}


int isOperator(char c) {
    return (c == '&' || c == '^' || c == '|');
}


void infixToRPN(char *infix, char *rpn) {
    char stack[100];
    int top = -1;

   
    for (int i = 0; infix[i] != '\0'; ++i) {
        char c = infix[i];
        
        if (isdigit(c)) {
            while (isdigit(infix[i])) {
                *rpn++ = infix[i++];
            }
            *rpn++ = ' '; 
            --i; 
        }
        
        else if (isOperator(c)) {
            
            while (top >= 0 && getPriority(stack[top]) >= getPriority(c)) {
                *rpn++ = stack[top--];
                *rpn++ = ' '; 
            }
            
            stack[++top] = c;
        }
        
        else if (c == '(') {
            stack[++top] = c;
        }
        
        else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                *rpn++ = stack[top--];
                *rpn++ = ' '; 
            }
            top--;
        }
    }

    
    while (top >= 0) {
        *rpn++ = stack[top--];
        *rpn++ = ' '; 
    }
    *rpn = '\0';
}

int main() {
    char infix[100], rpn[100];
    printf("Input: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strlen(infix) - 1] = '\0'; 

    
    infixToRPN(infix, rpn);

    printf("Output: %s\n", rpn);

    return 0;
}
