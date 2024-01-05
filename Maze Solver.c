/*
 * Obstacle_Avoid.c
 *
 * Created: 12/30/2023 1:39:27 PM
 * Author: N A E E M
 */ 
#include "generic_macros_header.h"
#include "Servo_Motor.h"
#include "Ultra-Sonic.h"
#include "LCD.h"
#include "Car_Move.h"
#include "Timer.h"

void LCD_type_distance(uint8_t dist , uint8_t dir){
	LCD_write_command(First_Line(0));
	LCD_write_string(dir);
	LCD_write_string(": ");
	LCD_write_num(dist);
	LCD_write_string("cm");
	LCD_write_string("      ");
}
void LCD_type_car_state(uint8_t Stat){
	LCD_write_command(Second_Line(0));
	LCD_write_string(Stat);
	LCD_write_string("     ");
}

int main(void)
{	
	uint8_t dist,dist_right,dist_left;
	
	SETBIT(DDRC,PC0); //red_light
	SETBIT(DDRC,PC1); //white_light
	
	CLRBIT(DDRA,PA7); //Start_button
	SETBIT(PORTA,PA7); //white_light
	
	Timer0_PWM_OC0_init();
	PWM_Timer2_init();
	LCD_init();
	Car_init();
	Ultra_Sonic_init();
	Servo_Motor_init();
	
	LCD_write_command(First_Line(1));
	LCD_write_string("Press to start!");
	while(READBIT(PINA,PA7));
	
    while (1) 
    {
		Servo_Motor_Rotate(90);
		dist= Ultra_Sonic_get_distance();
		LCD_type_distance(dist,"Front");
		LCD_type_car_state("Car goes forward");
		Move_Forward();
		
		while(dist>12){
			dist= Ultra_Sonic_get_distance();
			LCD_type_distance(dist,"Front");
		}
			
			SETBIT(PORTC,PC1);//turn_on white_led
			
			Move_Stop();
			LCD_type_car_state("Car stopped");
			_delay_ms(100);
			
			Servo_Motor_Rotate(25);
			_delay_ms(250);
			dist_right= Ultra_Sonic_get_distance();
			LCD_type_distance(dist_right,"Right");
			_delay_ms(500);

			
			Servo_Motor_Rotate(160);
			_delay_ms(500);
			dist_left= Ultra_Sonic_get_distance();
			LCD_type_distance(dist_left,"Left");
			_delay_ms(500);
			
			Servo_Motor_Rotate(90);
			_delay_ms(200);
			dist= Ultra_Sonic_get_distance();
			LCD_type_distance(dist,"Front");
			
			CLRBIT(PORTC,PC1); //turn_off white_led
			
			if(dist_right>dist_left && dist_right>15){
				LCD_type_car_state("Car moves right");
				Move_Right();
				_delay_ms(200);
				LCD_type_car_state("Car stopped");
				Move_Stop();
				_delay_ms(100);
				
			}
			else if(dist_left>dist_right && dist_left>15){
				LCD_type_car_state("Car moves left");
				Move_Left();
				_delay_ms(200);
				LCD_type_car_state("Car stopped");
				Move_Stop();
				_delay_ms(100);
			}
			else{
				LCD_write_command(1);
				LCD_write_command(First_Line(2));
				LCD_write_string("Maze Solved!");
				while(1){
					TOGBIT(PORTC,PC0);//turn_on red_led
					_delay_ms(500);
				}
			}
			
    }
}



