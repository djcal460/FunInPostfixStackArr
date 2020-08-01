/*
 * Author: Derek Calzadillas
 * Purpose: To demonstrate knowledge of infix to postfix using an array stack
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

struct Stack
{
    int size;
    int top;
    char *s;
};

//just pass as local stack since we're not changing anything
void display(struct Stack st)
{
    //display from top of stack (end of array)
    for (int i = st.top; i >= 0; i--)
        printf("%d ", st.s[i]); //s ptr is pts to array and arrays are addr
    printf("\n");
}

//need a ptr because we are changing the stack
void push(struct Stack *st, int x)
{
    if (st->top == st->size - 1)
        printf("The Stack is Full");
    else
    {
        st->top++;          //increase top ptr
        st->s[st->top] = x; //add x to top of stack
    }
}

//need a ptr because we are changing the stack
int pop(struct Stack *st)
{
    int x = -1;
    if (st->top == -1)
        printf("The Stack is Empty");
    else
    {
        x = st->s[st->top]; // save top var
        st->top--;          //decrease top ptr
    }
    return x;
}

int stackTop(struct Stack st)
{
    if (st.top == -1)
        return -1;
    else
        return st.s[st.top];
}

int isEmpty(struct Stack st)
{
    if (st.top == -1)
        return 1;
    else
        return 0;
}

int isFull(struct Stack st)
{
    if (st.top == st.size - 1)
        return 1;
    else
        return 0;
}

//peek down into stack
int peek(struct Stack st, int pos)
{

    int x = -1;
    if (st.top - pos + 1 <= 0) //from top peak down to pos
        printf("Invalid Position");
    else
        x = st.s[st.top - pos + 1];
    return x;
}
int isOperand(char x)
{
    if (x == '+' || x == '-' || x == '*' || x == '/')
    {
        return 0;
    }
    else
        return 1;
}
int preced(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    else
        return 0;
}
char *convert(char *infix)
{

    struct Stack st;
    st.top = -1;
    st.size = strlen(infix);
    st.s = (char *)malloc((strlen(infix) + 1) * sizeof(char));

    char *postfix = (char *)malloc((strlen(infix) + 1) * sizeof(char)); //add one for null term

    int i = 0, j = 0;
    while (infix[i] != '\0')
    {
        if (isOperand(infix[i]))
            //if it's a blank space skip it
            if (infix[i] == ' ')
            {
                infix[i++];
            }
            else
                postfix[j++] = infix[i++]; //if operand add to postfix right away
        else
        {
            if (preced(infix[i]) > preced(stackTop(st)))
            {                          //if char prec > stackTop prec
                push(&st, infix[i++]); //push to stack then increment char ptr
            }
            else
            {
                postfix[j++] = pop(&st); //if char prec is lower or equal then pop and add to postfix
            }
        }
    }
    //empty out remaining stack operators
    while (!isEmpty(st))
    {
        postfix[j++] = pop(&st);
    }

    postfix[j] = '\0'; //add null term at end
    return postfix;
}

int evalPostfix(char *postfix)
{

    //create a stack to use
    struct Stack st;
    st.top = -1;
    st.size = strlen(postfix);
    st.s = (char *)malloc((strlen(postfix) + 1) * sizeof(char));

    int x1, x2, r;
    for (int i = 0; postfix[i] != '\0'; i++)
    {
        if (isOperand(postfix[i]))
        {
            push(&st, postfix[i] - '0'); //subtract char by 0 char, get actual int for that char
            printf("Pushed %c\n", postfix[i]);
        }
        else
        {
            //first pop is right operand, second is left operand
            x2 = pop(&st);
            x1 = pop(&st);
            //current postfix is operator, find operation to do and push result to stack
            switch (postfix[i])
            {
            case '+':
                r = x1 + x2;
                push(&st, r);
                printf("%d+%d\n", x1, x2);
                break;
            case '-':
                r = x1 - x2;
                push(&st, r);
                printf("%d-%d\n", x1, x2);
                break;
            case '*':
                r = x1 * x2;
                push(&st, r);
                printf("%d*%d\n", x1, x2);
                break;
            case '/':
                r = x1 / x2;
                push(&st, r);
                printf("%d/%d\n", x1, x2);
                break;
            }
        }
    }
    return pop(&st);
}

int reprompt()
{
    int fixin, input, ret = 0;
    //check valid size
    while (ret != 1 || input > 11 || input < 1)
    {
        printf("Enter a valid size: ");
        while ((fixin = getchar()) != EOF && fixin != '\n')
            ; // fix stdin
        fflush(stdin);
        ret = scanf("%d", &input);
    }
    return input;
}

void resolve(char *infix)
{
    //convert infix to postfix
    char *postfix = convert(infix);
    printf("Postfix was computed as: %s\n", postfix);
    //evaluate postfix
    printf("Postfix was computed and the result was: %d\n", evalPostfix(postfix));
}

int main()
{
    int ret, input;
    //prompt user to choose an equation
    do
    {
        printf("\nBelow are some simple infix math equations.\n");
        printf("Choose an equation to convert from infix to postfix.\n");
        printf("And let the program solve the equation.\n");
        printf("1.  8 + 3 * 9 - 6\n");
        printf("2.  5 * 4 / 9 + 1\n");
        printf("3.  6 + 6 + 7 * 2\n");
        printf("4.  8 / 2 / 2 + 9 \n");
        printf("5.  2 * 2 * 2 / 2 + 2 + 2\n");
        printf("6.  7 / 3 * 2 + 5 / 2\n");
        printf("7.  3 * 9 + 3 / 3 + 3\n");
        printf("8.  4 * 4 * 4 / 4 + 8\n");
        printf("9.  9 / 1 / 1 + 9 / 9\n");
        printf("10.  9 + 8 + 7 / 6 - 5 + 4 + 3\n");
        printf("11. Exit Program.\n");

        //validate input

        printf("\nEnter your choice: ");
        ret = scanf("%d", &input);
        if (ret != 1 || input > 11 || input < 1)
            input = reprompt();

        //set the infix string
        switch (input)
        {
        case 1:
            printf("\n");
            char *infix1 = "8 + 3 * 9 - 6";
            resolve(infix1);
            break;
        case 2:
            printf("\n");
            char *infix2 = "5 * 4 / 9 + 1";
            resolve(infix2);
            break;
        case 3:
            printf("\n");
            char *infix3 = "6 + 6 + 7 * 2";
            resolve(infix3);
            break;
        case 4:
            printf("\n");
            char *infix4 = "8 / 2 / 2 + 9 ";
            resolve(infix4);
            break;
        case 5:
            printf("\n");
            char *infix5 = "2 * 2 * 2 / 2 + 2 + 2";
            resolve(infix5);
            break;
        case 6:
            printf("\n");
            char *infix6 = "7 / 3 * 2 + 5 / 2";
            resolve(infix6);
            break;
        case 7:
            printf("\n");
            char *infix7 = "3 * 9 + 3 / 3 + 3";
            resolve(infix7);
            break;
        case 8:
            printf("\n");
            char *infix8 = "4 * 4 * 4 / 4 + 8";
            resolve(infix8);
            break;
        case 9:
            printf("\n");
            char *infix9 = "9 / 1 / 1 + 9 / 9";
            resolve(infix9);
            break;
        case 10:
            printf("\n");
            char *infix10 = "9 + 8 + 7 / 6 - 5 + 4 + 3";
            resolve(infix10);
            break;
        case 11:
            printf("Exiting Program\n");
            exit(0);
        default:
            printf("Invalid option.\n");
        }
    } while (input != 11);

    return 0;
}
