#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10
#define STRING_SIZE 50

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed int int32_t;
int8_t insertionSort(int32_t *array, uint8_t arraySize);
void printArray(int32_t *array, uint8_t arraySize);
int8_t lcsGetSize(int32_t *array, uint8_t arraySize, uint8_t *sizeofLCS);
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

   // if(i>MAX_SIZE)printf("ERROORROVERFLOW\n");

    returned_val = lcsGetSize(arr,i,&lcs);
   // printArray(arr,MAX_SIZE);

   //* Return:
   //returns -1 if the array is empty
   //returns -2 if the array size is 0 or >10
   //returns -3 if there is no LCS,
   // 0therwise 0
    if(returned_val == -1) printf("Empty Array\n");
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

/* Description:
 * - This function takes a reference to an array of integers
 * - Sorts the array in ascending order
 * - Using the insertion sort algorithm
 * Return:
 * - returns -1 if the array is empty
 * - returns -2 if the array size is 0 or >10
 * - returns 0 if sorting is done without errors
 */
int8_t insertionSort(int32_t *array, uint8_t arraySize){
   int8_t i,j;
   for(i=0;i<arraySize;i++){
    if(array[i]!=0)break;
   }
   if(i==arraySize && array[i-1]==0)return -1;
   if(arraySize>10 || arraySize<1)return -2;
   int32_t temp;
   for(i=1;i<arraySize;i++){
    j=i;
    while(j>0 && array[j-1]>array[j]){
        temp=array[j];
        array[j]=array[j-1];
        array[j-1] = temp;

        j--;
    }

   }

   return 0;
}


/* Description:
 * - This function takes a reference to an array of integers
 * - Prints all array elements
 * Return:
 * - Nothing to return
 */
void printArray(int32_t *array, uint8_t arraySize){
int8_t i;
printf("Printing Array\n\n");
for(i=0;i<arraySize;i++)printf("%d\t",array[i]);
printf("\n");

}

/* Description:
 * - This function takes a reference to an array,
 * - array size, and
 * - reference to store the size of the LCS
 * - Using the insertion sort algorithm
 * - The function will search for the LCS in the array and
 * - stores its size
 * Return:
 * - returns -1 if the array is empty
 * - returns -2 if the array size is 0 or >10
 * - returns -3 if there is no LCS,
 * (i.e all array elements are not consecutive at all)
 * - returns 0 otherwise
 */
int8_t lcsGetSize(int32_t *array, uint8_t arraySize, uint8_t *sizeofLCS){

  uint8_t returnedValue = insertionSort(array,arraySize);
  if(returnedValue)return returnedValue;
   int8_t i,temp=1;
   *sizeofLCS = 1 ;
   for(i=0;i<arraySize;i++){
    if(array[i]==(array[i+1])-1){
            *sizeofLCS+=1;
    }
    else{
        if(temp<*sizeofLCS)temp = *sizeofLCS;
        *sizeofLCS=1;
    }
   }
   if(temp>*sizeofLCS)*sizeofLCS = temp;
   if(*sizeofLCS==1)return -3;
   return 0;


}

