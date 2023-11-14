/**
 * The given template is a guideline for your coursework only.
 * You are free to edit/create any functions and variables.
 * You can add extra C files if required.
*/


#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"

#define BUTTON_PIN			16	// Pin 21 (GPIO 16)

// declare global variables e.g., the time when the button is pressed 
int dotsAndDashes[] = {0,0,0,0};	// Where a 2 = dash, 1 = dot, 0 = nothing
int pointer = 0;	// Determines which index of buttonDown to put next dot/ dash into
int timerButtonDown = 0;
int timerButtonUp = 0;

// --------------------------------------------------------------------
// declare the function definitions, e.g, decoder(...); and ther functions
// given the user input, you can decode if the input is a character
void decoder();

void notCharacter();

void clearDotsAndDashes();

void notCharacter();

// check if the button press is a dot or a dash
void checkButton();

void showLetter(char letter);


int main() {
	stdio_init_all();

	// Initialise the seven segment display.
	seven_segment_init();
	
	// Turn the seven segment display off when the program starts.
	seven_segment_off();

	
	// ---- REQUIREMENT 1 ----
	// Display welcome msg
	printf("%s", "Welcome to our morse code decipherer! When the display stops flashing, press/hold button to display different aphabet letters, where: \nA: .-\nB: -...\nC: -.-.\nD: -..\nE: .\nF: ..-.\nG: --.\nH: ....\nI: ..\nJ: .---\nK: -.-\nL: .-..\nM: --\nN: -.\nO: ---\nP: .--.\nQ: --.-\nR: .-.\nS: ...\nT: -\nU: ..-\nV: ...-\nW: .--\nX: -..-\nY:-.--\nZ: --..");

	// Flash on and off 7-segment display
	for(int i = 0; i < 8; i++){
		gpio_put(9,0);
		sleep_ms(250);
		gpio_put(9,1);
		sleep_ms(250);
	}

	// Initialize the button's GPIO pin.
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).

	while (true) {
		
		while (gpio_get(BUTTON_PIN)){	
            // record how long the button is pressed
            timerButtonDown += 25;
			timerButtonUp = 0;
			sleep_ms(25); // adjust the sleep_ms as required
		} 

		if(timerButtonDown >= 25){		// Check if button has been pressed
			checkButton();				// check if the button press is a dot or a dash
			timerButtonDown = 0;
		}
		
		// If the user has waited 400ms and the array isn't empty
		if(timerButtonUp > 400 && dotsAndDashes[0] != 0){
			decoder();		// Checks all dots and dashes array to display corresponding letter
			timerButtonUp = 0;
			timerButtonDown = 0;
		}

        timerButtonUp += 25;
		sleep_ms(25);
	}
}



void showLetter(char letter){
	// Nazarii here. 
	printf("%c", letter);
}

void checkButton(){
    // Check if dot or dash
	if (pointer <= 3){
		if (timerButtonDown >= 25 && timerButtonDown <= 250){
			// Dot
			dotsAndDashes[pointer] = 1;
			pointer++;
		} else if (timerButtonDown > 250){
			// Dash
			dotsAndDashes[pointer] = 2;
			pointer++;
		}
	} else{
		notCharacter();
	}
}

void decoder() {
	// Takes the dotsAndDashes array and determines letter, then displays
	if(dotsAndDashes[0] == 1){		// Dot, ...
		if(dotsAndDashes[1] == 0){
			// Letter E
			showLetter('E');
		}

		else if(dotsAndDashes[1] == 1){			// Dot, dot, ...
			if(dotsAndDashes[2] == 0){
				// Letter I
				showLetter('I');
			} else if(dotsAndDashes[2] == 1){		// Dot, dot, dot, ...
				if(dotsAndDashes[3] == 0){
					// Letter S
					showLetter('S');
				} else if(dotsAndDashes[3] == 1){
					// Letter H
					showLetter('H');
				} else{
					// Letter V
					showLetter('V');
				}
			} else{								// Dot, dot, dash, ...
				if(dotsAndDashes[3] == 0){
					// Letter U
					showLetter('U');
				} else if(dotsAndDashes[3] == 1){
					// Letter F
					showLetter('F');
				} else{
					notCharacter();
				}
			}
		} else if (dotsAndDashes[1] == 2){		// Dot, dash, ... 
			if( dotsAndDashes[2] == 0){
				// Letter A
				showLetter('A');
			} else if(dotsAndDashes[2] == 1){		// Dot, dash, dot, ...
				if(dotsAndDashes[3] == 0){
					// Letter R
					showLetter('R');
				} else if(dotsAndDashes[3] == 1){
					// Letter L
					showLetter('L');
				} else{
					notCharacter();
				}
			} else if(dotsAndDashes[2] == 2){		// Dot, dash, dash, ...
				if (dotsAndDashes[3] == 0){
					// Letter W
					showLetter('W');
				} else if(dotsAndDashes[3] == 1){
					// Letter P
					showLetter('P');
				} else{
					// Letter J
					showLetter('J');
				}
			}
		}
	} else if (dotsAndDashes[0] == 2) {			// Dash, ...
		if (dotsAndDashes[1] == 0){
			// Letter T
			showLetter('T');
		} else if (dotsAndDashes[1] == 1){		// Dash, dot, ...
			if (dotsAndDashes[2] == 0){
				// Letter N
				showLetter('N');
			} else if (dotsAndDashes[2] == 1){	// Dash, dot, dot, ...
				if (dotsAndDashes[3] == 0){
					// Letter D
					showLetter('D');
				} else if (dotsAndDashes[3] == 1){
					// Letter B
					showLetter('B');
				} else{
					// Letter X
					showLetter('X');
				}
			} else{								// Dash, dot, dash, ...
				if (dotsAndDashes[3] == 0){
					// Letter K
					showLetter('K');
				} else if (dotsAndDashes[3] == 1){
					// Letter C
					showLetter('C');
				} else {
					// Letter Y
					showLetter('Y');
				}
			}
		} else{									// Dash, dash, ...
			if (dotsAndDashes[2] == 0){
				// Letter M
				showLetter('M');
			} else if (dotsAndDashes[2] == 1){		// Dash, dash, dot, ...
				if(dotsAndDashes[3] == 0){
					// Letter G
					showLetter('G');
				} else if(dotsAndDashes[3] == 1){
					// Letter Z
					showLetter('Z');
				} else{
					// Letter Q
					showLetter('Q');
				}
			} else{		// Dash, dash, dash, ...
				if(dotsAndDashes[3] == 0){
					// Letter O
					showLetter('O');
				}
				else{
					notCharacter();
				}
			}
		}
	}

	// Reset dots and dashes array (fill with 0s)
	clearDotsAndDashes();
}

void clearDotsAndDashes(){
	// Reset dots and dashes array (fill with 0s)
	for(int i = 0; i < 4; i++){
		dotsAndDashes[i] = 0;
	}
	pointer = 0;
}

void notCharacter() {
	// Display error msg
	printf("%s", "Character is not in morse code, please re-enter");

	// Reset dots and dashes array (fill with 0s)
	clearDotsAndDashes();
}