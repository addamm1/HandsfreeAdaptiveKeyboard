#include <Arduino.h>
#include <HID-Project.h>

#define TL 2
#define TM 3
#define TR 4
#define BL 5
#define BM 6
#define BR 7
#define JOY_V_PIN A0
#define JOY_H_PIN A1
#define SCROLL_SPEED_DELAY 150


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
  pinMode(TL, INPUT_PULLUP);
  pinMode(TM, INPUT_PULLUP);
  pinMode(TR, INPUT_PULLUP);
  pinMode(BL, INPUT_PULLUP);
  pinMode(BM, INPUT_PULLUP);
  pinMode(BR, INPUT_PULLUP);
  //Serial.begin(9600);
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
  if(!buttons[0]){Mouse.press(MOUSE_LEFT);}
  else{Mouse.release(MOUSE_LEFT);}

  if(!buttons[1]){Mouse.press(MOUSE_RIGHT);}
  else{Mouse.release(MOUSE_RIGHT);}

  if(!buttons[2] && lastButtons[0]){ //  if button 2 is pressed, and its last state was unpressed
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('s');
    Keyboard.releaseAll();
    lastButtons[0] = 0;
  }
  else if(buttons[2]){ // if button is unpressed, reset lastButtons
    lastButtons[0] = 1;
  }

  if(!buttons[3] && lastButtons[1]){ //  if button 2 is pressed, and its last state was unpressed
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('c');
    Keyboard.releaseAll();
    lastButtons[1] = 0;
  }
  else if(buttons[3]){ // if button is unpressed, reset lastButtons
    lastButtons[1] = 1;
  }

  if(!buttons[4] && lastButtons[2]){ //  if button 2 is pressed, and its last state was unpressed
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('x');
    Keyboard.releaseAll();
    lastButtons[2] = 0;
  }
  else if(buttons[4]){ // if button is unpressed, reset lastButtons
    lastButtons[2] = 1;
  }
  
  if(!buttons[5] && lastButtons[3]){ //  if button 2 is pressed, and its last state was unpressed
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('v');
    Keyboard.releaseAll();
    lastButtons[3] = 0;
  }
  else if(buttons[5]){ // if button is unpressed, reset lastButtons
    lastButtons[3] = 1;
  }
}

void scrollActions(){
  if(scrolls[0] < 400){
    if(nextMillisV < millis()){
      delay(1);
      Mouse.move(0, 0, -1);
      delay(1);
      nextMillisV = millis() + SCROLL_SPEED_DELAY;
    }
  }
  else if(scrolls[0] > 625){
    if(nextMillisV < millis()){
      delay(1);
      Mouse.move(0, 0, 1);
      delay(1);
      nextMillisV = millis() + SCROLL_SPEED_DELAY;
    }
  }
  
  if(scrolls[1] < 400){
    if(nextMillisH < millis()){
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(1);
      Mouse.move(0, 0, 1);
      delay(1);
      Keyboard.release(KEY_LEFT_SHIFT);
      nextMillisH = millis() + SCROLL_SPEED_DELAY;
    }
  }
  else if(scrolls[1] > 625){
    if(nextMillisH < millis()){
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(1);
      Mouse.move(0, 0, -1);
      delay(1);
      Keyboard.release(KEY_LEFT_SHIFT);
      nextMillisH = millis() + 150;
    }
  }
}