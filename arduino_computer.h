#ifndef arduino_computer_h
#define arduino_computer_h

#include <LiquidCrystal.h>
#include <Arduino.h>

struct menuItemStruct
{
	String name;
	void (*action)();
};

struct menuStruct
{
	String name;
	int currentItemIndex;
	menuItemStruct* items;
	int numberOfItems;
};

class arduino_computer
{
	public:
		void setupOS();
		void loopOS();

		arduino_computer(LiquidCrystal& lcdRef, int* buttonArrows, int selectButton);

		void DisplayMenu(menuStruct* menuPointer);
		void PrintToScreen(String line1, String line2);

		void Options();
		void Restart();
		void CMD();

	private:
		LiquidCrystal& _lcd;
		int* _buttonArrows;
		int _selectButton;

		menuStruct* currentMenu;
};

#endif