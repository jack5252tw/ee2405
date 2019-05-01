#include "mbed.h"
#include "math.h"

BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,0xBF};

DigitalIn  DR(D2);
PwmOut PWM1(D3);

int main(){
  
  int tmp1 = 0;       //Compare tmp1 & tmp2 to trigger start
  int tmp2 = 0;
  int start = 0;

  int cnt0 = 0;       //counters for 0 & 1
  int cnt1 = 0;
  int ratio = 0;      //duty ratio = floor(100*(1's/0's + 1's))
  PWM1.period(0.5);
  PWM1.write (0.74);  //set the duty ratio

  while(1){
    cnt0 = 0;
    cnt1 = 0;
    start = 0;
    tmp1 = DR;
    //////////////////////Idle
    if(tmp1){
      tmp2 = tmp1;
      tmp1 = DR;
      while(tmp1 == tmp2){
        tmp2 = tmp1;
        tmp1 = DR;
      }
      start = 1;  
    }
    /////////////////////Start
    if(start){
      tmp2 = tmp1;
      tmp1 = DR;
      cnt0++;
         
      while(tmp1 == tmp2){
        cnt0 ++;
        tmp2 = tmp1;
        tmp1 = DR;
      }
      while(tmp1 != 0){
        cnt1 ++;
        tmp1 = DR;
      }
      /*          ////////////// Another way to count/////////
      while(tmp1 >= tmp2 ){
        tmp2 =tmp1;
        tmp1 = DR;
        if(tmp1){
          cnt1++;
        }
        else{
          cnt0++;
        }
      }
      start = 0;
      */      
    }

    if(cnt1 != 0)         ///prevent from the missing error
      ratio = floor(((100*cnt1)/( cnt0 + cnt1)));
    
    //Display 0.XY
    display = table[10];  //0.
    wait(0.5);
    display = table[ratio/10]; //X
    wait(0.5);
    display = table[ratio%10]; //Y
    wait(0.5);
    
  }
}
  
