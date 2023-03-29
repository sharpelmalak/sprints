#include "main.h"
#include "stack.h"



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
