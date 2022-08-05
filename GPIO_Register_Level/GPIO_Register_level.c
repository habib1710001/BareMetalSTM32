/**************************INFROMATIONS FROM DOCUMENTATIONS******************************/

/************STM32 Nucleo-64 User Manual****************/

//OUTPUT PIN
//PIN : PC10
//PORT: C
//Pin : 10

//INPUT PIN
//PIN  : PD2
//PORT : D
//PIN  : 2

/****************Stm32 Datasheet************************/
//Block Diagram
//PORT C BUS : AHB1 180MHz
//Memory Block : Peripherals Block
//AHB1 Bus connected registers
//AHB1 Base    : 0x4002 0000
//Register Boundary Address
//Reset and clock control Regiters(RCC)  :  0x4002 3800 - 0x4002 3BFF 
//GPIOC :  0x4002 0800 - 0x4002 0BFF 
//GPIOD :  0X4002 0C00 - 0x4002 0FFF


/***********Stm32 Reference manual***********************/

//Reset and clock control Regiters:

//RCC AHB1 peripheral clock enable register(RCC_AHB1ENR)
//Address offset: 0x30 -> 0x4002 3830
//GPIOCEN: IO port C clock enabled for 1
//GPIODEN: IO port C clock enabled for 1


// GPIOC Registers:

// GPIOC port mode register (GPIOC_MODER):
// Address offset: 0x00     -> 0x4002 0800
// Register Bits (MODER10) : Bit 21 20
// 01: General purpose output mode

// GPIOD Registers:

// GPIOD port mode register (GPIOD_MODER):
// Address offset: 0x00     -> 0x4002 0C00
// Register Bits (MODER2) : Bit 5 4
// 00: General purpose input mode


// GPIOC port output data register (GPIOC_ODR):
// Offset Address: 0x14     -> 0x4002 0814
// Register Bit: Bit  10
// Set 1 Clear 0

// GPIOD port input data register (GPIOD_IDR):
// Offset Address: 0x10     -> 0X4002 0C10
// Register Bit: Bit  3
 
 
#include <stdint.h>


#define MASK(x)((uint32_t)1 << x)

#define PERIPH_BASE   0x40000000

#define AHB1_OFFSET   0x00020000
#define AHB1_BASE     (PERIPH_BASE + AHB1_OFFSET)

#define GPIOC_OFFSET  0x00000800
#define GPIOC_BASE    (GPIOC_OFFSET + AHB1_BASE)

#define GPIOD_OFFSET  0x00000C00
#define GPIOD_BASE    (GPIOD_OFFSET + AHB1_BASE)

#define RCC_OFFSET    0x00003800
#define RCC_BASE      (RCC_OFFSET + AHB1_BASE)


//MISRAC Style
#define __IO volatile 


//unnammed structure aliased to GpioTypedef 
typedef struct{  
	__IO uint32_t MODER;
	__IO uint32_t DUMMY[3];
	__IO uint32_t IDR ;
  __IO uint32_t ODR ; 
} GpioTypedef;


//unnammed structure aliased to RccTypedef 
typedef struct{
	__IO uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR; 
} RccTypedef;

//Base address of Registers are converted from a number to a pointer(address) of GPIO_TypeDef type.
//Named corresponding GPIO, such as GPIOA

#define RCC    ((RccTypedef *) RCC_BASE)
#define GPIOC  ((GpioTypedef *)GPIOC_BASE)
#define GPIOD  ((GpioTypedef *)GPIOD_BASE)


int main()
{
	RCC-> AHB1ENR |= MASK(2);
  RCC-> AHB1ENR |= MASK(3);
	
	//big endian
	GPIOC -> MODER |= MASK(20);
	GPIOC -> MODER &= ~MASK(21); //just for clearity
	
	GPIOD -> MODER &= ~MASK(5); //just for clearity
	GPIOD -> MODER &= ~MASK(4); //just for clearity
	  
	while(1)  
	{
	 if((GPIOD->IDR)& MASK(2))
	 {
    GPIOC->ODR |= MASK(10);
	 }
	 else
	 {
    GPIOC -> ODR &= ~MASK(10);
	 } 
}
}
