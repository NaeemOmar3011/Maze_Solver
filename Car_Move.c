/*
 * Car_Move.c
 *
 * Created: 12/31/2023 10:58:55 PM
 *  Author: N A E E M
 */ 
#include "Car_Move.h"
#include "Car_Move_cfg.h"

/*****************************************************************************
* Function Name: Car_init
* Purpose      : Sets car configuration
* Parameters   : void
* Return value : void
*****************************************************************************/
void Car_init(void){
	Car_cfg();
}
/*****************************************************************************
* Function Name: Move_Forward
* Purpose      : Makes car moves forward
* Parameters   : void
* Return value : void
*****************************************************************************/
void Move_Forward(void){
	PWM_Timer2_set_duty_cycle(45); //tire one(left)
	Timer0_PWM_OCR0_DC(50); //tire two(right)
	tire_two_front();
	tire_one_front();
}
/*****************************************************************************
* Function Name: Move_Back
* Purpose      : Makes car moves back
* Parameters   : void
* Return value : void
*****************************************************************************/
void Move_Back(void){
	PWM_Timer2_set_duty_cycle(50); //tire one(left)
	Timer0_PWM_OCR0_DC(50); //tire two(right)
	tire_one_back();
	tire_two_back();
}
/*****************************************************************************
* Function Name: Move_Right
* Purpose      : Makes car moves right
* Parameters   : void
* Return value : void
*****************************************************************************/
void Move_Right(void){
	PWM_Timer2_set_duty_cycle(75); //tire one(left)
	Timer0_PWM_OCR0_DC(60); //tire two(right)
	tire_one_front();
	tire_two_front();
}
/*****************************************************************************
* Function Name: Move_Left
* Purpose      : Makes car moves left
* Parameters   : void
* Return value : void
*****************************************************************************/
void Move_Left(void){
	PWM_Timer2_set_duty_cycle(50); //tire one(left)
	Timer0_PWM_OCR0_DC(75); //tire two(right)
	tire_two_front();
	_delay_ms(150);
	tire_one_front();
	
}
/*****************************************************************************
* Function Name: Move_Stop
* Purpose      : Makes car stop
* Parameters   : void
* Return value : uint16_t
*****************************************************************************/
void Move_Stop(void){
	PWM_Timer2_set_duty_cycle(45); //tire one(left)
	Timer0_PWM_OCR0_DC(50); //tire two(right)
	if(tire_one_is_front()){
		tire_one_back();
	}
	else if(tire_one_is_back()){
		tire_one_front();
	}
	if(tire_two_is_front()){
		tire_two_back();
	}
	else if(tire_two_is_back()){
		tire_two_front();
	}
	_delay_ms(100);
	tire_stop();
}