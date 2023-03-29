#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "sort.h"
#include "lcs.h"




int main()
{

    int8_t i=0,returned_val;
    uint8_t lcs;
    int32_t arr[MAX_SIZE]={};
    char str[STRING_SIZE];
    printf("Enter Elements : ");
    fgets(&str,STRING_SIZE,stdin);
    if(strlen(str)==1);
    else{
         char *token = strtok(str," ");
    while (token != NULL)
    {

    arr[i]=atoi(token);
    token = strtok(NULL," ");
    i++;

    }

    }

    returned_val = lcsGetSize(arr,i,&lcs);

   //* Return:
   //returns -1 if the array is empty
   //returns -2 if the array size is 0 or >10
   //returns -3 if there is no LCS,
   // otherwise 0

    if(returned_val == -1){printf("Empty Array\n"); printArray(arr,i);}
    else if(returned_val == -2) printf("Size Error\n");
    else if(returned_val == -3){
           printf("there is no LCS\n");
            printArray(arr,i);
    }
    else {
         printArray(arr,i);
         printf("Longest Consecutive %d\n",lcs);

    }
    system("pause");
    return 0;
}

