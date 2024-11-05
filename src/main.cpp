#include <Arduino.h>
#include <Mouse.h>
#include <Keyboard.h>

#define TopLeft 2
#define TopMiddle 3
#define TopRight 4
#define LowerLeft 5
#define LowerMiddle 6
#define LowerRight 7
#define JOY_V_PIN A0
#define JOY_H_PIN A1

#define MOUSECLICK1 MOUSE_LEFT
#define MOUSECLICK2 MOUSE_RIGHT

#define BUTTON1 'c'
#define BUTTON2 'z'
#define BUTTON3 'v'
#define BUTTON4 's'

#define BUTTON_DEBUG 0

#define SCROLL_SPEED_DELAY 300.0
#define MIN_SCROLL_SPEED_DELAY 30


// put function declarations here:
void pollButtons();
void pollScrolls();
void buttonActions();
void scrollActions();

int buttons[8];
int lastButtons[4] = {1,1,1,1};
int scrolls[2];
unsigned long nextMillisH = 0;
unsigned long nextMillisV = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(JOY_H_PIN, INPUT);
  pinMode(JOY_V_PIN, INPUT);
  pinMode(TopLeft, INPUT_PULLUP);
  pinMode(TopMiddle, INPUT_PULLUP);
  pinMode(TopRight, INPUT_PULLUP);
  pinMode(LowerLeft, INPUT_PULLUP);
  pinMode(LowerMiddle, INPUT_PULLUP);
  pinMode(LowerRight, INPUT_PULLUP);
  if(BUTTON_DEBUG){
      Serial.begin(9600);
  }
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  pollButtons();
  pollScrolls();
  
  buttonActions();
  scrollActions();
}

void pollScrolls(){
  scrolls[0] = analogRead(JOY_V_PIN);
  scrolls[1] = analogRead(JOY_H_PIN);
}

void pollButtons(){
  for(int i = 2; i <= 7; i++){
    buttons[i - 2] = digitalRead(i);
  }
}

void buttonActions(){
  if(!buttons[0]){
    Mouse.press(MOUSECLICK1);
    if(BUTTON_DEBUG){
      Serial.println("MOUSE1");
    }
  }
  else{Mouse.release(MOUSECLICK1);}

  if(!buttons[1]){
    Mouse.press(MOUSECLICK2);
    if(BUTTON_DEBUG){
      Serial.println("MOUSE2");
    }
  }
  else{Mouse.release(MOUSECLICK2);}

  if(!buttons[2] && lastButtons[0]){ //  if button 2 is pressed, and its last state was unpressed
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(BUTTON1);
    Keyboard.releaseAll();
    if(BUTTON_DEBUG){
      Serial.println("BUTTON1");
    }
    lastButtons[0] = 0;
  }
  else if(buttons[2]){ // if button is unpressed, reset lastButtons
    lastButtons[0] = 1;
  }

  if(!buttons[3] && lastButtons[1]){ //  if button 2 is pressed, and its last state was unpressed
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(BUTTON2);
    Keyboard.releaseAll();    
    if(BUTTON_DEBUG){
      Serial.println("BUTTON2");
    }
    lastButtons[1] = 0;
  }
  else if(buttons[3]){ // if button is unpressed, reset lastButtons
    lastButtons[1] = 1;
  }

  if(!buttons[4] && lastButtons[2]){ //  if button 2 is pressed, and its last state was unpressed
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(BUTTON3);
    Keyboard.releaseAll();
    if(BUTTON_DEBUG){
      Serial.println("BUTTON3");
    }
    lastButtons[2] = 0;
  }
  else if(buttons[4]){ // if button is unpressed, reset lastButtons
    lastButtons[2] = 1;
  }
  
  if(!buttons[5] && lastButtons[3]){ //  if button 2 is pressed, and its last state was unpressed
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(BUTTON4);
    Keyboard.releaseAll();
    if(BUTTON_DEBUG){
      Serial.println("BUTTON4");
    }
    lastButtons[3] = 0;
  }
  else if(buttons[5]){ // if button is unpressed, reset lastButtons
    lastButtons[3] = 1;
  }
}

void scrollActions(){
  if(scrolls[0] < 475 && nextMillisV < millis()){ // Vertical potentiometer
      delay(1);
      Mouse.move(0, 0, -1);
      delay(1);
      nextMillisV = millis() + MIN_SCROLL_SPEED_DELAY + (int)(SCROLL_SPEED_DELAY * ((float)scrolls[0] / 475.0));
  }
  else if(scrolls[0] > 650 && nextMillisV < millis()){
      delay(1);
      Mouse.move(0, 0, 1);
      delay(1);
      nextMillisV = millis() + MIN_SCROLL_SPEED_DELAY + (int)(SCROLL_SPEED_DELAY * ((1024.0 - (float)scrolls[0]) / 374.0));
  }
  
  if(scrolls[1] < 475 && nextMillisH < millis()){ // Horizontal potentiometer
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(1);
      Mouse.move(0, 0, 1);
      delay(1);
      Keyboard.release(KEY_LEFT_SHIFT);
      nextMillisH = millis() + MIN_SCROLL_SPEED_DELAY + (int)(SCROLL_SPEED_DELAY * ((float)scrolls[1] / 475.0));
  }
  else if(scrolls[1] > 650 && nextMillisH < millis()){
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(1);
      Mouse.move(0, 0, -1);
      delay(1);
      Keyboard.release(KEY_LEFT_SHIFT);
      nextMillisH = millis() + MIN_SCROLL_SPEED_DELAY + (int)(SCROLL_SPEED_DELAY * ((1024.0 - (float)scrolls[1]) / 374.0));
  }
}