/*
 * usart_private.h
 *
 * Created: 5/23/2023 6:29:50 PM
 *  Author: Sharpel
 */ 


#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_


// registers

#define UDR     (*(vuint8_t*)(0x2C))
#define UCSRA   (*(vuint8_t*)(0x2B))
#define UCSRB   (*(vuint8_t*)(0x2A))
#define UCSRC   (*(vuint8_t*)(0x40))
#define UBRRH   (*(vuint8_t*)(0x40))
#define UBRRL   (*(vuint8_t*)(0x29))


// UCSRA bitS nameS

#define MPCM     0
#define U2X      1
#define PE       2
#define DOR      3
#define FE       4
#define UDRE     5
#define TXC      6
#define RXC      7


// UCSRB bitS nameS

#define TXB8     0
#define RXB8     1
#define UCSZ2    2
#define TXEN     3
#define RXEN     4
#define UDRIE    5
#define TXCIE    6
#define RXCIE    7




// UCSRC bitS nameS

#define UCPOL    0
#define UCSZ0    1
#define UCSZ1    2
#define USBS     3
#define UPM0     4
#define UPM1     5
#define UMSEL    6
#define URSEL    7


#define EMPTY_POSITOIN  -1

#endif /* USART_PRIVATE_H_ */