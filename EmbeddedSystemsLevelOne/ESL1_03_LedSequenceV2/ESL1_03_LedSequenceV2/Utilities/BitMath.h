/*
 * BitMath.h
 *
 * Created: 4/7/2023 2:17:54 PM
 *  Author: sharb
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_

#define SET_BIT(Reg,BitNumber)    (Reg|=(1<<BitNumber))
#define CLEAR_BIT(Reg,BitNumber)  (Reg&=~(1<<BitNumber))
#define TOGGLE_BIT(Reg,BitNumber) (Reg^=(1<<BitNumber))
#define GET_BIT(Reg,BitNumber)    ((Reg>>BitNumber)&1)



#endif /* BITMATH_H_ */