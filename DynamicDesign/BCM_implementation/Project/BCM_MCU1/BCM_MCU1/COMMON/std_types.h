/**************************************************************************
 Author        				: Sherif Ashraf Ali                      
 Date         				: 11 Feb 2023
 Project Name _ File Name   : AVR_DRIVER _ STD_Types.h
 Version       				: V-01                                   
 GitHub       				: https://github.com/sherifkhadr         
**************************************************************************/


#ifndef COMMON_STD_TYPES_H_
#define COMMON_STD_TYPES_H_


typedef signed char  						sint8_t;
typedef unsigned char 						uint8_t;


typedef signed short int 					sint16_t;
typedef unsigned short int 					uint16_t;
typedef signed int 							sint32_t;
typedef unsigned int 						uint32_t;
typedef signed long long int  				sint64_t;
typedef unsigned long long int  			uint64_t;



typedef signed char  						vsint8_t;
typedef unsigned char 						vuint8_t;
typedef volatile signed short int 			vsint16_t;
typedef volatile unsigned short int 		vuint16_t;
typedef volatile signed int 				vsint32_t;
typedef volatile unsigned int 				vuint32_t;
typedef volatile signed long long int  		vsint64_t;
typedef volatile unsigned long long int  	vuint64_t;

typedef float								float32_t;
typedef double								float64_t;
typedef long double 						float96_t;




 #ifndef TRUE
 #define TRUE   1
 #endif
 
 
 #ifndef FALSE
 #define FALSE 	0
 #endif


#ifndef	NULL
#define NULL	'\0'
#endif



#endif /* COMMON_STD_TYPES_H_ */
