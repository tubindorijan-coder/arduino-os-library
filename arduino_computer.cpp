/*
Wire the lcd with the standard wiring scheme
and put the buttons in an arrows and a select button setup
and wire them like i refrenced in the top of the script

to make your own custom apps you can:
1. add a button into the main menu items
2. at the bottom create a function and put your code into it
3. refrence it under void Options(); and other functions so it works in the main menu decleration
4. make sure to refrence it in main menu items
*/

#include <arduino_computer.h>
#include <LiquidCrystal.h>
#include <Arduino.h>

arduino_computer::arduino_computer(LiquidCrystal& lcdRef, int* buttonArrows, int selectButton)
    : _lcd(lcdRef), _buttonArrows(buttonArrows), _selectButton(selectButton)
{
    _buttonArrows = buttonArrows;
    _selectButton = selectButton;
}

bool buttonPressed[5];

bool inMenu = true;

void Options();
void CMD();
void Restart();

char keyData[33];
char command[32];

String appRunning = "none";

//menus
menuItemStruct mainMenuItems[] =
{
  {"Options", Options},
  {"Command prompt", CMD},
  {"Reset", Restart}
};
menuStruct mainMenu =
{
  "Main menu",
  0,
  mainMenuItems,
  sizeof(mainMenuItems) / sizeof(mainMenuItems[0])
};

//current menu pointer
menuStruct* currentMenu = &mainMenu;  // start in mainMenu

void arduino_computer::setupOS()
{
    _lcd.begin(16, 2);
    _lcd.clear();
    Serial.begin(9600);

    //set pinmodes
    for (int i = 0; i < 4; i++)
    {
        pinMode(_buttonArrows[i], INPUT_PULLUP);
    }
    pinMode(_selectButton, INPUT_PULLUP);

    currentMenu = &mainMenu;

    DisplayMenu(currentMenu);
}

void arduino_computer::loopOS()
{
    if (inMenu == true)
    {
        //button logic
        if (digitalRead(_buttonArrows[0]) == LOW && buttonPressed[0] == false)
        {
            //runs only once
            buttonPressed[0] = true;
        }
        else if (digitalRead(_buttonArrows[0]) == HIGH)
            buttonPressed[0] = false;

        if (digitalRead(_buttonArrows[1]) == LOW && buttonPressed[1] == false)
        {
            //runs only once
            buttonPressed[1] = true;
            (*currentMenu).currentItemIndex++;
            DisplayMenu(currentMenu);
        }
        else if (digitalRead(_buttonArrows[1]) == HIGH)
            buttonPressed[1] = false;

        if (digitalRead(_buttonArrows[2]) == LOW && buttonPressed[2] == false)
        {
            //runs only once
            buttonPressed[2] = true;
        }
        else if (digitalRead(_buttonArrows[2]) == HIGH)
            buttonPressed[2] = false;

        if (digitalRead(_buttonArrows[3]) == LOW && buttonPressed[3] == false)
        {
            //runs only once
            buttonPressed[3] = true;
        }
        else if (digitalRead(_buttonArrows[3]) == HIGH)
            buttonPressed[3] = false;

        if (digitalRead(_selectButton) == LOW && buttonPressed[4] == false)
        {
            //runs only once
            buttonPressed[4] = true;
            (*currentMenu).items[(*currentMenu).currentItemIndex].action();
            inMenu = false;
        }
        else if (digitalRead(_selectButton) == HIGH)
            buttonPressed[4] = false;

        //stop menus overflowing
        if ((*currentMenu).currentItemIndex >= (*currentMenu).numberOfItems)
        {
            (*currentMenu).currentItemIndex = 0;
            DisplayMenu(currentMenu);
        }
    }

    //keyboard logic for cmd
    if (Serial.available() > 0)
    {
        int bytesRead = Serial.readBytes(keyData, 32);
        keyData[bytesRead] = '\0';  // Null-terminate the string

        if (bytesRead > 0 && keyData[bytesRead - 1] == '\r')
        {
            keyData[bytesRead - 1] = '\0';
        }

        Serial.print("Received: ");
        Serial.println(keyData);
    }

    //cmd logic
    if (appRunning == "cmd")
    {
        if (strncmp(keyData, "reset", 5) == 0)
        {
            strcpy(command, "reset");
        }

        if (strcmp(command, "reset") == 0)
        {

        }
    }
}

void arduino_computer::PrintToScreen(String line1, String line2)
{
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print(line1);
    _lcd.setCursor(0, 1);
    _lcd.print(line2);
}

void arduino_computer::DisplayMenu(menuStruct* menuPointer)
{
    if ((*menuPointer).currentItemIndex + 1 >= (*menuPointer).numberOfItems)
    {
        PrintToScreen((*menuPointer).items[(*menuPointer).currentItemIndex].name, "");
    }
    else
        PrintToScreen((*menuPointer).items[(*menuPointer).currentItemIndex].name, (*menuPointer).items[(*menuPointer).currentItemIndex + 1].name);
}

void arduino_computer::Options()
{
    PrintToScreen("under work", "press reset");
}

void arduino_computer::Restart()
{
    PrintToScreen("under work", "press reset");
}

void arduino_computer::CMD()
{
    appRunning = "cmd";
}