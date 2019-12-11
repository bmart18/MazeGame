#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>
const int xpin = 23;                  // x-axis of the accelerometer
const int ypin = 24;                  // y-axis
const int zpin = 25;
#define GameButton 33  
Screen_HX8353E myScreen;
void setup() {
  // put your setup code here, to run once:
 myScreen.begin();
analogReadResolution(12);
Serial.begin(9600);
 myScreen.setFontSolid(false);
 myScreen.setFontSize(1);
myScreen.gText((myScreen.screenSizeX()-13*myScreen.fontSizeX())/2,20, "Maze Game by:");
myScreen.gText((myScreen.screenSizeX()-11*myScreen.fontSizeX())/2, 30, "Brad Martin");
myScreen.gText((myScreen.screenSizeX()-13*myScreen.fontSizeX())/2, 40, "Jakob Roberts");
myScreen.setFontSolid(true);
myScreen.gText((myScreen.screenSizeX()-19*myScreen.fontSizeX())/2, 80, "Press the top right");
myScreen.gText((myScreen.screenSizeX()-15*myScreen.fontSizeX())/2, 90, "button to begin");
while(1)
{
  if(digitalRead(GameButton) == 0)
 
  break;
}
}
void drawMap()
{
  myScreen.setPenSolid(true);
  myScreen.dRectangle(0,0,128,128, myScreen.calculateColour(255,255,255));
  myScreen.dRectangle(0,0,128,20, myScreen.calculateColour(0,0,0));//top
  myScreen.dRectangle(0,40,30,88, myScreen.calculateColour(0,0,0));// bot left
  myScreen.dRectangle(0,98,128,30, myScreen.calculateColour(0,0,0)); //bot
  myScreen.dRectangle(50,0,30,68, myScreen.calculateColour(0,0,0)); // mid
   myScreen.dRectangle(110,50,18,88, myScreen.calculateColour(0,0,0)); //right
 
}

void fellOff(){
  myScreen.clear();
  myScreen.gText((myScreen.screenSizeX()-13*myScreen.fontSizeX())/2, 30, "You fell off!");
  myScreen.gText((myScreen.screenSizeX()-19*myScreen.fontSizeX())/2, 80, "Press the top right");
  myScreen.gText((myScreen.screenSizeX()-17*myScreen.fontSizeX())/2, 90, "button to restart");


  while(1){
      if(digitalRead(GameButton) ==0)
        break;  
  }
}
void loop() {
  drawMap();
  int spotX =10;
  int spotY= 25;
  myScreen.dRectangle(spotX,spotY,10,10, myScreen.calculateColour(255,0,0));
  while(1){
    int x = (int) analogRead(xpin) - 2048;
    int y = (int) analogRead(ypin) - 2048;
    Serial.println(x);
    Serial.println(y);
   myScreen.dRectangle(spotX,spotY,10,10, myScreen.calculateColour(255,255,255));
   if(x>200){
    if(spotX < 128){
        if((spotX == 40 && spotY < 68)|| (spotX == 100 && spotY > 40)){
          fellOff();
          
          break;
        }
        spotX+=1;
      }
    }
   if(x<-200){
    if(spotX > 0){
      if((spotX==30 && spotY >40)||(spotX== 90 && spotY<88)){
          fellOff();
          break;
      }
      spotX-=1;
      }
   }
   if(y >75){
    if(spotY > 0){
      if((spotY == 20 && spotX < 40) ||  (spotY == 68 &&(spotX > 50 && spotX < 80) ||  (spotY==20 && spotX > 90))){
        fellOff();
        break;

      }
      spotY-=1;
      }
   }
   if(y <-75){
    if(spotY < 128){
      if((spotY >= 30 && spotX <=30) || (spotY == 88 &&(spotX > 30 && spotX < 100)) || (spotY == 30 && spotX > 110)){
         fellOff();
         break;
      }
      spotY+=1;
      }
    }
   myScreen.dRectangle(spotX,spotY,10,10, myScreen.calculateColour(255,0,0));
   delay(25);
   if(spotX >= 118 && spotY < 40 && spotY > 10){
      myScreen.clear();
  myScreen.dRectangle(0,0,128,128, myScreen.calculateColour(0,255,0));
  myScreen.gText((myScreen.screenSizeX()-21*myScreen.fontSizeX())/2, 30, "!! CONGRATULATIONS !!");
    myScreen.gText((myScreen.screenSizeX()-13*myScreen.fontSizeX())/2, 40, "!! YOU WIN !!");
    while(1){
      if(digitalRead(GameButton) ==0)
        break;  
  }
 break;
   }
  }
}
