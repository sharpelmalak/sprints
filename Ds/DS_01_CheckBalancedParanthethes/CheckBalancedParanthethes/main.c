#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef struct stack {
uint8_t elements[STACK_SIZE];
int8_t top;
}ST_stack_t;


void createEmptyStack(ST_stack_t *stack);
int8_t push(ST_stack_t *stack, uint8_t data);
int8_t pop(ST_stack_t *stack, uint8_t *data);
int8_t printStack(ST_stack_t *stack);
int8_t getStackTop(ST_stack_t *stack, uint8_t *topData);
int8_t isFull(ST_stack_t *stack);
int8_t isEmpty(ST_stack_t *stack);
int8_t isBalancedParanthethes(uint8_t *expression);

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

void createEmptyStack(ST_stack_t *stack){
  uint8_t i;
  for(i=0;i<STACK_SIZE;i++)
  stack->elements[i]=0;
  stack->top=-1;
}

int8_t push(ST_stack_t *stack, uint8_t data){
if(stack->top==STACK_SIZE-1)return -1;
stack->top++;
stack->elements[stack->top]=data;
return 0;
}

int8_t pop(ST_stack_t *stack, uint8_t *data){
if(stack->top==-1)return -2;
*data = stack->elements[stack->top];
 stack->top--;
 return 0;
}

int8_t printStack(ST_stack_t *stack){
int8_t i;
if(stack->top == -1 )return -2;
for(i=(stack->top);i>=0;i--)printf("%d\n",stack->elements[i]);
if(stack->top == STACK_SIZE-1)return -1 ;
return 0;
}

int8_t getStackTop(ST_stack_t *stack, uint8_t *topData){
if(stack->top == -1)return -2;
*topData = stack->elements[stack->top];
return 0;
}

int8_t isFull(ST_stack_t *stack){
if(stack->top == STACK_SIZE-1)return -1;
return 0;
}
int8_t isEmpty(ST_stack_t *stack){
if(stack->top == -1)return -2;
return 0;
}

int8_t isBalancedParanthethes(uint8_t *expression){

    uint8_t i,chek=0,popedData;
    int8_t return_value;
    ST_stack_t s;
    createEmptyStack(&s);
    for(i=0;expression[i]!= NULL ; i++)
    {
        switch(expression[i])
        {
           case '(' :
                chek=1;
                return_value = push(&s,expression[i]);
                //return_value = printStack(&s);

               /* if(!return_value)break;
                else {
                    printf("STACK OVERFLOW\n");
                     } */
                  break;

           case '{' :
               chek=1;
               return_value = push(&s,expression[i]);
               // printf("%d",return_value);
               /* if(!return_value)break;
                else {
                    printf("STACK OVERFLOW\n");
                     } */
                  break;
            case ')' :
                chek=1;
                return_value = pop(&s,&popedData);
                //printf("%c",popedData);
                if(return_value == -2 || popedData != '(')return -1 ;
                break;

            case '}' :
                chek=1;
                return_value = pop(&s,&popedData);
                if(return_value == -2 || popedData != '{')return -1 ;
                  break;


            default:break;

        }

    }

     if(!chek)return -2;
     else if (isEmpty(&s)==-2)return 0 ;


}
