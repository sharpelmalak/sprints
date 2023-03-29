#include "main.h"
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

