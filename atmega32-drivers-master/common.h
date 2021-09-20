/*
 * common.h
 *
 *  Created on: Jul 14, 2018
 *      Author: dardeery
 */

#ifndef COMMON_H_
#define COMMON_H_
/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#define NULL (void *) 0


typedef unsigned char                       uint8;
typedef signed char                         sint8;
typedef unsigned short                     uint16;
typedef signed short                       sint16;
typedef unsigned int                       uint32;
typedef signed int                         sint32;
typedef unsigned long                      uint64;
typedef signed long                        sint64;



typedef  enum
{
	E_FALSE =0,
	E_TRUE ,
}bool_t;

typedef enum
{
	IN=0,
	OUT,
}DIRECTION;

#endif /* COMMON_H_ */
