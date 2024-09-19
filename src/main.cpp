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


// put function declarations here:
void pollButtons();
void pollScrolls();
void buttonActions();
void scrollActions();

int buttons[8];
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

  if(!buttons[2]){
    Mouse.press(MOUSE_LEFT);
    Mouse.release(MOUSE_LEFT);
    Mouse.press(MOUSE_LEFT);
    }
  else{Mouse.release(MOUSE_LEFT);}

  if(!buttons[3]){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.write('c');
    Keyboard.releaseAll();
  }

  if(!buttons[4]){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.write('v');
    Keyboard.releaseAll();
  }
  
  if(!buttons[5]){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.write('z');
    Keyboard.releaseAll();
  }
}

void scrollActions(){
  if(scrolls[0] < 400){
    if(nextMillisV < millis()){
      Mouse.move(0, 0, -1);
      nextMillisV = millis() + 150;
    }
  }
  else if(scrolls[0] > 625){
    if(nextMillisV < millis()){
      Mouse.move(0, 0, 1);
      nextMillisV = millis() + 150;
    }
  }
  
  if(scrolls[1] < 400){
    if(nextMillisH < millis()){
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(1);
      Mouse.move(0, 0, 1);
      delay(1);
      Keyboard.release(KEY_LEFT_SHIFT);
      nextMillisH = millis() + 150;
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