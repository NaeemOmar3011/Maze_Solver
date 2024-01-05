/*
 * Servo_Motor.c
 *
 * Created: 12/30/2023 3:34:19 PM
 *  Author: N A E E M
 */ 

#include "Servo_Motor.h"

/*****************************************************************************
* Function Name: Servo_Motor_init
* Purpose      : initialize servo motor
* Parameters   : void
* Return value : void
*****************************************************************************/
void Servo_Motor_init(void){
	//Timer equation ==>  Fclk(PWM) = Fclk(UC) / prescalar*(1+TOP)
	//For Servo motor we need 50HZ frequency
	//50 = (16M) / 8*(1+TOP)  ----->  TOP=39,999
	//50HZ ==> 20ms
	
	SETBIT(DDRD,PD4); //output for OCR1B
	
	TCCR1A=0;
	TCCR1B=0;
	
	SETBIT(TCCR1A,COM1B1); //non_inverting mode OCR1B
	
	//Fast PWM ---> TOP=OCR1A
	SETBIT(TCCR1A,WGM10);
	SETBIT(TCCR1A,WGM11);
	SETBIT(TCCR1B,WGM13);
	SETBIT(TCCR1B,WGM12);
	
	//prescalar 8
	SETBIT(TCCR1B,CS11);
	
	//TOP
	OCR1A=39999;
	TCNT1=0;
	
}

/*****************************************************************************
* Function Name: Servo_Motor_Rotate
* Purpose      : Rotate servo motor
* Parameters   : uint16_t
* Return value : void
*****************************************************************************/
void Servo_Motor_Rotate(uint16_t Angle){
	Servo_Motor_init();
	  //90* --> (2ms/20ms)*39,999  **From data sheet**
	 //0* --> (1.5ms/20ms)*39,999  **From data sheet**
	//-90* --> (1ms/20ms)*39,999  **From data sheet**
	
	// 1ms-->2ms == 0* --> 180*  so; 1ms/180 (time per angle)
	//((1ms+((1ms/180)*Angle))/20ms)*39,999
	
	OCR1B = 850 + Angle*21.5 ;  //there are error that we handeled
}