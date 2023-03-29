#include "main.h"
#include "stack.h"




int8_t isBalancedParanthethes(uint8_t *expression){

    uint8_t i,chek=0,popedData;
    int8_t return_value;
    ST_stack_t s;
    createEmptyStack(&s);
    for(i=0;expression[i]!= 0 ; i++)
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
