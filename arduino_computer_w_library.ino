#include <LiquidCrystal.h>
#include <arduino_computer.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int arrowButtons[] = {9, 8, 7, 10};
int selectButton = 6;

arduino_computer OS(lcd, arrowButtons, selectButton);

void Options() { OS.Options(); }
void CMD()     { OS.CMD(); }
void Restart() { OS.Restart(); }

void setup() {
  OS.setupOS();
}

void loop() {
  OS.loopOS();
}
