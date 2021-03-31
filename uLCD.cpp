

#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;

DigitalIn pusheenbutton_down(D8);//A1
DigitalIn pusheenbutton_up(D6);//A0
DigitalIn pusheenbutton_confirm(D5);//A2
AnalogOut  aout(PA_4);//D7
AnalogIn Ain(A0);
DigitalOut led(LED1);
uLCD_4DGL uLCD(D1, D0, D2);
Thread thread;

int x=1;

int sample = 1000;//128
int j;
float ADCdata[1000];

void pusheenbutton_thread()
{
   int y;
   y=x;
   while (true)
   {
        if(pusheenbutton_up==1 && y<5){
            y=y+1;
            uLCD.locate(1,5);
            uLCD.printf("           \n"); //If there is "Confirmed!" mark, hide/delete it
        }
        if(pusheenbutton_down==1 && y>1){
            y=y-1;
            uLCD.locate(1,5);
            uLCD.printf("           \n"); //If there is "Confirmed!" mark, hide/delete it
        }

        if(y==1){
            uLCD.filled_rectangle(5, 5, 15, 15, 0xFFFFFF);   //GUI bar
            uLCD.filled_rectangle(20, 5, 30, 15, 0x000000);  //GUI bar
            uLCD.filled_rectangle(35, 5, 45, 15, 0x000000);  //GUI bar
            uLCD.filled_rectangle(50, 5, 60, 15, 0x000000);  //GUI bar
            uLCD.filled_rectangle(65, 5, 75, 15, 0x000000);  //GUI bar
            uLCD.locate(1,3);
            uLCD.printf("Frequency =0.01Hz\n");//T=100       //To print out the frequency value on uLCD board
            uLCD.locate(0,4);
            uLCD.printf("                  \n");             //If there is "(Cutoff Frequency)" mark, hide/delete it
        }else if(y==2){
            uLCD.filled_rectangle(5, 5, 15, 15, 0xFFFFFF);
            uLCD.filled_rectangle(20, 5, 30, 15, 0xFFFFFF);
            uLCD.filled_rectangle(35, 5, 45, 15, 0x000000);
            uLCD.filled_rectangle(50, 5, 60, 15, 0x000000);
            uLCD.filled_rectangle(65, 5, 75, 15, 0x000000);
            uLCD.locate(1,3);
            uLCD.printf("Frequency = 0.1Hz\n");//T=12//0.83
            uLCD.locate(0,4);
            uLCD.printf("                  \n");
        }else if(y==3){
            uLCD.filled_rectangle(5, 5, 15, 15, 0xFFFFFF);
            uLCD.filled_rectangle(20, 5, 30, 15, 0xFFFFFF);
            uLCD.filled_rectangle(35, 5, 45, 15, 0xFFFFFF);
            uLCD.filled_rectangle(50, 5, 60, 15, 0x000000);
            uLCD.filled_rectangle(65, 5, 75, 15, 0x000000);
            uLCD.locate(1,3);
            uLCD.printf("Frequency =0.36Hz\n");
            uLCD.locate(0,4);
            uLCD.printf("(Cutoff Frequency)\n");             //To specify that this is the cut-off frequency of the RC circuit
        }else if(y==4){
            uLCD.filled_rectangle(5, 5, 15, 15, 0xFFFFFF);
            uLCD.filled_rectangle(20, 5, 30, 15, 0xFFFFFF);
            uLCD.filled_rectangle(35, 5, 45, 15, 0xFFFFFF);
            uLCD.filled_rectangle(50, 5, 60, 15, 0xFFFFFF);
            uLCD.filled_rectangle(65, 5, 75, 15, 0x000000);
            uLCD.locate(1,3);
            uLCD.printf("Frequency =0.83Hz\n");//1//0.67//0.77
            uLCD.locate(0,4);
            uLCD.printf("                  \n");
        }else if(y==5){
            uLCD.filled_rectangle(5, 5, 15, 15, 0xFFFFFF);
            uLCD.filled_rectangle(20, 5, 30, 15, 0xFFFFFF);
            uLCD.filled_rectangle(35, 5, 45, 15, 0xFFFFFF);
            uLCD.filled_rectangle(50, 5, 60, 15, 0xFFFFFF);
            uLCD.filled_rectangle(65, 5, 75, 15, 0xFFFFFF);
            uLCD.locate(1,3);
            uLCD.printf("Frequency =1.30Hz\n");//0.33//1.43
            uLCD.locate(0,4);
            uLCD.printf("                  \n");
        }

        if(pusheenbutton_confirm==1){
            x=y;
            uLCD.locate(1,5);
            uLCD.printf("Confirmed!\n");   //If we pusheen the "confirm" button, the value will be given to the flag/label x
        }

   }
}


int main()
{
      thread.start(pusheenbutton_thread);
      int k=0;
      while(true){
        int r=0;
        for (float i = 0.0f; i < 1.0f; i += 0.016667f) {
            aout = i * 0.91f;
            if(x==1){
                ThisThread::sleep_for(500ms);
            }else if(x==2){
                ThisThread::sleep_for(50ms);
            }else if(x==3){
                ThisThread::sleep_for(14ms);//14
            }else if(x==4){
                ThisThread::sleep_for(5ms);
            }else if(x==5){
                ThisThread::sleep_for(1ms);
            }
            ADCdata[r]=3.3*Ain.read();
            //printf("%f\r\n", 3.3*Ain.read());
            r=r+1;
            
        }
        
        




        for (float i = 1.0f; i > 0.0f; i -= 0.007143f) {
            aout = i * 0.91f;
            if(x==1){
                ThisThread::sleep_for(500ms);
            }else if(x==2){
                ThisThread::sleep_for(50ms);
            }else if(x==3){
                ThisThread::sleep_for(14ms);//14
            }else if(x==4){
                ThisThread::sleep_for(5ms);
            }else if(x==5){
                ThisThread::sleep_for(1ms);
            }
            ADCdata[r]=3.3*Ain.read();
            //printf("%f\r\n", 3.3*Ain.read());
            r=r+1;
        }
        
        for(k=0;k<200;k=k+1){
            printf("%f\r\n", ADCdata[k]);
        }
      
      }
}