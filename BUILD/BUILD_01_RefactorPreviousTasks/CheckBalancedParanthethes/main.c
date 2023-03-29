#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "stack.h"
#include "balanced.h"

int main()
{

    // initialize stack
    ST_stack_t s;
    // vars for pop , push , and returned values
    uint8_t datapoped,dataTop;
    int8_t var_return;

    //Create an empty stack
    createEmptyStack(&s);
   // printf("%d\n",s.top);

/*
    //Push 5 different characters to the stack
     var_return = push(&s,1);
     var_return = push(&s,2);
     var_return = push(&s,3);
     var_return = push(&s,4);
     var_return = push(&s,5);





     //Print all stack data
   //  var_return = printStack(&s);


     //Pop one character from the stack
     var_return = pop(&s,&datapoped);
    // printf("%d\n",s.top);

     //Print the stack's top
     var_return = getStackTop(&s,&dataTop);
   //  printf("Stack Top is %d\n\n",dataTop);

     //Print all stack data
   //  var_return = printStack(&s);

     // Push another 7 different characters to the stack
     var_return = push(&s,10);
     var_return = push(&s,20);
     var_return = push(&s,30);
     var_return = push(&s,40);
     var_return = push(&s,50);
     var_return = push(&s,60);
     //overflow
     var_return = push(&s,70);

     //printf("%d",var_return);

     //Print the stack's top
     var_return = getStackTop(&s,&dataTop);
    // printf("Stack Top is %d\n\n",dataTop);

     //Print all stack data
    // var_return = printStack(&s);


      //Pop 4 character from the stack
     var_return = pop(&s,&datapoped);
     var_return = pop(&s,&datapoped);
     var_return = pop(&s,&datapoped);
     var_return = pop(&s,&datapoped);


     //Print the stack's top
     var_return = getStackTop(&s,&dataTop);
    // printf("Stack Top is %d\n\n",dataTop);



     //Print all stack data
    // var_return = printStack(&s);

     // Pop 7 more times from the stack
     var_return = pop(&s,&datapoped);
     var_return = pop(&s,&datapoped);
     var_return = pop(&s,&datapoped);
     var_return = pop(&s,&datapoped);
     var_return = pop(&s,&datapoped);
     var_return = pop(&s,&datapoped);

     var_return = pop(&s,&datapoped); //Empty Stack var_return will = -2
      //printf("\n\n%d",var_return);


     //Print the stack's top
    // var_return = getStackTop(&s,&dataTop);//Empty Stack var_return will = -2
    // printf(" %d\n\n",dataTop);

     //Print all stack data
     var_return = printStack(&s); //Empty Stack var_return will = -2
     printf("\n\n%d",var_return); */

    printf("ENTER THE EXPRESSION\n\n");
    uint8_t exp[50];
    gets(exp);
    int8_t return_val = isBalancedParanthethes(&exp);
    //printf("--------%d-------\n\n",return_val);
    if(!return_val)printf("the parentheses are balanced\n");
    else if (return_val == -1)printf("the parentheses are not balanced\n");
    else{
       printf("the neither of paranthethes is used\n");

     }

    system("pause");
    return 0;
}

