#include <Keyboard.h>
#include <Mouse.h>
#define BAUD_RATE 115200

#define PuertoSerie Serial1

String bufferStr = "";
String ultimo = "";
String movimientoRaton = "10";
int movimientoRatonInt = movimientoRaton.toInt();

void Linea(String _linea)
{
  int primerEspacio = _linea.indexOf(" ");
  if(primerEspacio == -1) Pulsar(_linea);
  else{
      String resto = _linea;
      while(resto.length() > 0){
        int ultimoEspacio = resto.indexOf(" ");
        if (ultimoEspacio == -1){
          Pulsar(resto);
          resto = "";
        }
        else{
          Pulsar(resto.substring(0, ultimoEspacio));
          resto = resto.substring(ultimoEspacio + 1);
        }
        delay(5);
      }
  }
  Keyboard.releaseAll();
}


void Pulsar(String b){
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
      Mouse.begin();
      Mouse.move(0, 0);
      Mouse.move(0, movimientoRatonInt*-1);
      Mouse.end();
  }else if(b.equals("MouseMoveDown")) {
      Mouse.begin();
      Mouse.move(0, 0);
      Mouse.move(0, movimientoRatonInt);
      Mouse.end();
  }else if(b.equals("MouseMoveLeft")) {
      Mouse.begin();
      Mouse.move(0, 0);
      Mouse.move(movimientoRatonInt*-1, 0);
      Mouse.end();
  }else if(b.equals("MouseMoveRight")) {
      Mouse.begin();
      Mouse.move(0, 0);
      Mouse.move(movimientoRatonInt, 0);
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
  PuertoSerie.begin(BAUD_RATE);
  Keyboard.begin();
}

void loop() {
  if(PuertoSerie.available()) {
    bufferStr = PuertoSerie.readString();
  }
  
  if(bufferStr.length() > 0){
    bufferStr.replace("\r","\n");
    bufferStr.replace("\n\n","\n");
    while(bufferStr.length() > 0){
      int latest_return = bufferStr.indexOf("\n");
      if(latest_return == -1){
        Linea(bufferStr);
        bufferStr = "";
      } else{
        if(bufferStr.substring(0, latest_return)==(" ")){
          Linea("SPACE");
        }else{
          Linea(bufferStr.substring(0, latest_return));
        }
        ultimo=bufferStr.substring(0, latest_return);
        bufferStr = bufferStr.substring(latest_return + 1);
      }
    }
    
    bufferStr = "";
    PuertoSerie.write(0x99);
  }
}
