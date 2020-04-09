#include <Keyboard.h>
#include <Mouse.h>
#define BAUD_RATE 115200

#define ExternSerial Serial1

String bufferStr = "";
String last = "";

void Line(String _line)
{
  int firstSpace = _line.indexOf(" ");
  if(firstSpace == -1) Press(_line);
  else{
      String remain = _line;

      while(remain.length() > 0){
        int latest_space = remain.indexOf(" ");
        if (latest_space == -1){
          Press(remain);
          remain = "";
        }
        else{
          Press(remain.substring(0, latest_space));
          remain = remain.substring(latest_space + 1);
        }
        delay(5);
      }
  }

  Keyboard.releaseAll();
}


void Press(String b){
  //if(b.length() == 1) Keyboard.press(char(b[0]));
  if(b.length() == 1) Keyboard.print(b);
  else if (b.equals("Enter")) Keyboard.press(KEY_RETURN);
  else if (b.equals("Control")) Keyboard.press(KEY_LEFT_CTRL);
  else if (b.equals("Shift")) Keyboard.press(KEY_LEFT_SHIFT);
  else if (b.equals("AltGraph")) Keyboard.press(KEY_RIGHT_ALT);
  else if (b.equals("Alt")) Keyboard.press(KEY_LEFT_ALT);
  else if (b.equals("Control")) Keyboard.press(KEY_LEFT_GUI);
  else if (b.equals("ArrowUp")) Keyboard.press(KEY_UP_ARROW);
  else if (b.equals("ArrowDown")) Keyboard.press(KEY_DOWN_ARROW);
  else if (b.equals("ArrowLeft")) Keyboard.press(KEY_LEFT_ARROW);
  else if (b.equals("ArrowRight")) Keyboard.press(KEY_RIGHT_ARROW);
  else if (b.equals("Delete")) Keyboard.press(KEY_DELETE);
  else if (b.equals("PageUp")) Keyboard.press(KEY_PAGE_UP);
  else if (b.equals("PageDown")) Keyboard.press(KEY_PAGE_DOWN);
  else if (b.equals("Meta")) Keyboard.press(KEY_HOME);
  else if (b.equals("Escape")) Keyboard.press(KEY_ESC);
  else if (b.equals("Backspace")) Keyboard.press(KEY_BACKSPACE);
  else if (b.equals("Insert")) Keyboard.press(KEY_INSERT);
  else if (b.equals("Tab")) Keyboard.press(KEY_TAB);
  else if (b.equals("End")) Keyboard.press(KEY_END);
  else if (b.equals("CapsLock")) Keyboard.press(KEY_CAPS_LOCK);
  else if (b.equals("F1")) Keyboard.press(KEY_F1);
  else if (b.equals("F2")) Keyboard.press(KEY_F2);
  else if (b.equals("F3")) Keyboard.press(KEY_F3);
  else if (b.equals("F4")) Keyboard.press(KEY_F4);
  else if (b.equals("F5")) Keyboard.press(KEY_F5);
  else if (b.equals("F6")) Keyboard.press(KEY_F6);
  else if (b.equals("F7")) Keyboard.press(KEY_F7);
  else if (b.equals("F8")) Keyboard.press(KEY_F8);
  else if (b.equals("F9")) Keyboard.press(KEY_F9);
  else if (b.equals("F10")) Keyboard.press(KEY_F10);
  else if (b.equals("F11")) Keyboard.press(KEY_F11);
  else if (b.equals("F12")) Keyboard.press(KEY_F12);
  else if (b.equals(" ")) Keyboard.press(' ');
  else if(b.equals("MouseMoveUp")) {
      String mousemove = "10";
      int mousemoveamt = mousemove.toInt();
      delay(25);
      Mouse.begin();
      Mouse.move(0, 0);
      Mouse.move(0, mousemoveamt*-1);
      Mouse.end();
  }else if(b.equals("MouseMoveDown")) {
      String mousemove = "10";
      int mousemoveamt = mousemove.toInt();
      delay(25);
      Mouse.begin();
      Mouse.move(0, 0);
      Mouse.move(0, mousemoveamt);
      Mouse.end();
  }else if(b.equals("MouseMoveLeft")) {
      String mousemove = "10";
      int mousemoveamt = mousemove.toInt();
      delay(25);
      Mouse.begin();
      Mouse.move(0, 0);
      Mouse.move(mousemoveamt*-1, 0);
      Mouse.end();
  }else if(b.equals("MouseMoveRight")) {
      String mousemove = "10";
      int mousemoveamt = mousemove.toInt();
      delay(25);
      Mouse.begin();
      Mouse.move(0, 0);
      Mouse.move(mousemoveamt, 0);
      Mouse.end();
  }else if(b.equals("MouseClickRIGHT")) {
      Mouse.begin();
      Mouse.click(MOUSE_RIGHT);
      Mouse.end();
  }else if(b.equals("MouseClickLEFT")) {
      Mouse.begin();
      Mouse.click(MOUSE_LEFT);
      Mouse.end();
  }else if(b.equals("MouseClickMIDDLE")) {
      Mouse.begin();
      Mouse.click(MOUSE_MIDDLE);
      Mouse.end();
  }
}

void setup() {
  
  Serial.begin(BAUD_RATE);
  ExternSerial.begin(BAUD_RATE);

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  Keyboard.begin();
}

void loop() {
  if(ExternSerial.available()) {
    bufferStr = ExternSerial.readString();
  }
  
  if(bufferStr.length() > 0){
    Serial.println("hola "+ bufferStr);
    bufferStr.replace("\r","\n");
    bufferStr.replace("\n\n","\n");
    
    while(bufferStr.length() > 0){
      int latest_return = bufferStr.indexOf("\n");
      if(latest_return == -1){
        Serial.println("run: "+bufferStr);
        Line(bufferStr);
        bufferStr = "";
      } else{
        Serial.println("run: '"+bufferStr.substring(0, latest_return)+"'");
        if(bufferStr.substring(0, latest_return)==(" ")){
          Line("SPACE");
        }else{
          Line(bufferStr.substring(0, latest_return));
        }
        
        last=bufferStr.substring(0, latest_return);
        bufferStr = bufferStr.substring(latest_return + 1);
      }
    }
    
    bufferStr = "";
    ExternSerial.write(0x99);
    Serial.println("done");
  }
}
