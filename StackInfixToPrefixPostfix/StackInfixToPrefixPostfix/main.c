//
//  main.c
//  StackInfixToPostfix
//
//  Created by Rockabye Saw on 07/05/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MinStackSize ( 5 )

// Stack type
struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned MaxElements)
{
    struct Stack* stack;
    
    if (MaxElements < MinStackSize)
        perror("Stack Size too small !");
    
    stack = (struct Stack*)malloc(sizeof(struct Stack));
    
    if (stack == NULL)
        perror("Out of Space");
    
    stack->top = -1;
    stack->array = (int*)malloc(sizeof(int) * MaxElements);
    
    if (stack->array == NULL)
        perror("Out of Space !");
    
    stack->capacity = MaxElements;
    return stack;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ;
}

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
// peek meaning return top
char peek(struct Stack* stack)
{
    return stack->array[stack->top];
}

char pop(struct Stack* stack)
{
    if (!isEmpty(stack)) return stack->array[stack->top--];
    return '\0';
}

void push(struct Stack* stack, char op)
{
    if (!isFull(stack))
        stack->array[++stack->top] = op;
    else
        perror("Full Stack");
}

// A utility function to check if the given character is operand
int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// A utility function to return precedence of a given operator
// Higher returned value means higher precedence
int Prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
  
    case '*':
    case '/':
        return 2;
  
    case '^':
        return 3;
    }
    return -1;
}

// The main function that converts given infix expression
// to postfix expression.
char *infixToPostfix(char* exp)
{
    int i, k;
    
    // Create a stack of capacity equal to expression size
    struct Stack* stack = createStack((unsigned)strlen(exp));
    
    if (!stack) // See if stack was created successfully
        return -1 ;
    
    // k -1 mean start from top -1
    // exp[i] whole expression and its a pointer array
    for (i = 0, k = -1; exp[i]; ++i)
    {
        // If the scanned character is an operand, add it to output.
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (exp[i] == '(')
            push(stack, exp[i]);
        // If the scanned character is an ‘)’, pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (exp[i] == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1; // invalid expression
            else
                pop(stack); // pop open-bracket too
        }
        else // an operator is encountered
        {
            // an operator precedence level is lower then that operator top in
            // stack then pop out and output else push into stack
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
            {
                // right-associative
                if (exp[i] == '^' && Prec(exp[i]) == Prec(peek(stack)))
                    break;
                
                exp[++k] = pop(stack);
            }
            push(stack, exp[i]);
        }
    }
    
    // pop all the operators from the stack
    while (!isEmpty(stack))
        exp[++k] = pop(stack);
    
    exp[++k] = '\0';
    return exp;
}

char *ReverseString(char *str)
{
    if (!str || ! *str)
        return str;

    int i = (int)strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}

char *infixToPrefix(char* exp)
{
    int l = (int)strlen(exp);
    
    exp = ReverseString(exp);
    // Replace ( with ) and vice versa
    for (int i = 0; i < l; i++)
    {
        if (exp[i] == '(')
        {
            exp[i] = ')';
            i++;
        }
        else if (exp[i] == ')')
        {
            exp[i] = '(';
            i++;
        }
    }

    infixToPostfix(exp);
    
    exp = ReverseString(exp);
    
    return exp;
}

int add(int n)
{
    return n + n;
}

int multiply(int n)
{
    return n * n;
}


int main(int argc, const char * argv[]) {
    char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
    char dest[strlen(exp) + 1];
    strcpy(dest, exp);
    printf("%s\n", infixToPostfix(exp));
    printf("%s\n", infixToPrefix(dest));
    return 0;
}
