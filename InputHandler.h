#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

//---------------------------------------------------------------------------
//InputHandler.h, InputHandler.cpp
//
//Handles inputs from the user and acts accordingly
//
//
//---------------------------------------------------------------------------

#include <iostream>
#include <vector>
//#include "globals.h"

using namespace std;

class InputHandler; // Declaration so that the function pointers can adress the input handler.

//   function(key, specialKey, c, r, InputHandler)
typedef void (*keyboardFunction)(unsigned char, int, int , int, InputHandler*);             // Functions that run when the right keyboard event is triggerd.
typedef bool (*keyboardActivationFunction)(unsigned char, int, int, int, InputHandler*);    // Determines if a keyboard function should run or not, depending on the current state.

//   function(Button, state, specialKey, c, r, InputHandler)
typedef void (*mouseFunction)(int, int, int, int, int, InputHandler*);                     // Functions that run when the right mouse event is triggerd.
typedef bool (*mouseActivationFunction)(int, int, int, int, int, InputHandler*);            // Determines if a mouse function should run or not, depending on the current state.

//   function(c, r, InputHandler)
typedef void (*motionFunction)(int, int, InputHandler*);                               // Functions that run when the right motion event is triggerd.
typedef bool (*motionActivationFunction)(int, int, InputHandler*);                     // Determines if a motion function should run or not, depending on the current state.

//   function(c, r, InputHandler)
typedef void (*scrollFunction)(int, InputHandler*);
typedef bool (*scrollActivationFunction)(int, InputHandler*);

//Holds the event functions.
struct keyboardEvent
{
    keyboardFunction function;
    keyboardActivationFunction activation;
};

struct mouseEvent
{
    mouseFunction function;
    mouseActivationFunction activation;
};

struct motionEvent
{
    motionFunction function;
    motionActivationFunction activation;
};

struct scrollEvent
{
    scrollFunction function;
    scrollActivationFunction activation;
};

class InputHandler
{
	public:
		InputHandler();
		~InputHandler();

		void handleKeyboard(unsigned char key, int c, int r);
		void handleMouse(int button, int state, int c, int r);
		void handleMotion(int c, int r);
		void handleScroll(int dir);

        // Add an event function.
        // fn runs every time the criteriumFn returns true in an event.
		void addKeyboardFunction(keyboardFunction   fn, keyboardActivationFunction  criteriumFn);
		void addMouseFunction(mouseFunction      fn, mouseActivationFunction     criteriumFn);
		void addMotionFunction(motionFunction     fn, motionActivationFunction    criteriumFn);
		void addScrollFunction(scrollFunction     fn, scrollActivationFunction    criteriumFn);

        // Vectors of events.
        vector<keyboardEvent>   keyboardFunctions;
        vector<mouseEvent>      mouseFunctions;
        vector<motionEvent>     motionFunctions;
        vector<scrollEvent>     scrollFunctions;

		bool mouseLeftDown, mouseMiddleDown;
		bool altDown;
		int cStart, rStart;
};

#endif
