#include "main.h"
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

