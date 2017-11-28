

#include <main.h>
//#include "lcd16216.c"

#define PWM_PERIOD_VAL 199   //250   // Calculated
#define PWM_DUTY_MIN 0
#define PWM_DUTY_MAX 800 //change

int pwm_count = 0;
int servo_angle = 0;


#int_ccp1
void ccp1_int(){
//   output_toggle(PIN_D0);
   
   if(pwm_count++ == 200){
      pwm_count = 0;
   }
   
   if(pwm_count <= 19){ //servo_angle
      output_high(PIN_D0);      
   }else{
      output_low(PIN_D0);
   } 
}


void main()
{
   

   setup_oscillator(OSC_8MHZ,2);
   CCP_1 = 25;
   setup_ccp1(CCP_COMPARE_RESET_TIMER|CCP_COMPARE_INT);
//   setup_ccp1(CCP_COMPARE_RESET_TIMER); 
//   setup_ccp1(CCP_COMPARE_INT); 
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   
   enable_interrupts(INT_CCP1);
   enable_interrupts(GLOBAL);

   while(TRUE){
      
      while(servo_angle < 19){
         servo_angle++;
         delay_ms(50);
      }
      while(servo_angle > 9){
         servo_angle--;
         delay_ms(50);
      }
   }

   
   
   
   
   while(1){
   
   }
   
   
}




