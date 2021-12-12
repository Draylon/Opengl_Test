#include "Input.hpp"

unsigned int Input::pressed_keys;
unsigned int Input::pressed_spc;
std::thread Input::keys_thread;
std::map<unsigned char, bool> Input::key_press;
std::map<unsigned char, bool> Input::spc_press;
std::map<unsigned char, bool> Input::key_last;
std::map<unsigned char, bool> Input::spc_last;

Input* Input::instance;

void (*Input::keydown_pointer)(unsigned char);
void (*Input::keyup_pointer)(unsigned char);
void (*Input::spcdown_pointer)(int);
void (*Input::spcup_pointer)(int);

//======

Input* Input::getInstance() {
	input_stop_all = false;
	if (!instance) {
		pressed_keys = 0;
		pressed_spc= 0;
		instance = new Input();
	}
	return instance;
}


/*void Input::initKeys(std::list<int>charlist) {
	for (char c : charlist) {
		key_press[c] = false;
		key_last[c] = false;
	}
}*/


void Input::persistKey(){
	while (!input_stop_all) {
		if (pressed_keys != 0){
			for (std::pair<unsigned char, bool> e : key_press) {
				//printf("K-%c -> %i\n", e.first, e.second);
				if (e.second) {
					if (key_last[e.first] == false) key_last[e.first] = true;
					Input::keydown_pointer(e.first);
				} else {
					if (key_last[e.first] == true) {
						pressed_keys--;
						key_last[e.first] = false;
						Input::keyup_pointer(e.first);
					}
				}
			}
		}
		if (pressed_spc != 0){
			for (std::pair<int, bool> e : spc_press) {
				//printf("S-%u -> %i\n", e.first, e.second);
				if (e.second) {
					if (spc_last[e.first] == false) spc_last[e.first] = true;
					Input::spcdown_pointer(e.first);
				} else {
					if (spc_last[e.first] == true) {
						pressed_spc--;
						spc_last[e.first] = false;
						Input::spcup_pointer(e.first);
					}
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}


void Input::keyDownReceiver(unsigned char key, int, int){
	if (spc_press[GLUT_KEY_CTRL_L]) key += 96;
	else if (spc_press[GLUT_KEY_SHIFT_L]) 
		if(key != 32) key += 32;
	//create thread
	//if (key_press.find(key) == key_press.end()) return;
	if (key_press[key]) return;
	key_press[key] = true;
	key_last[key] = false;
	pressed_keys++;
	// else GLFW_REPEAT GLFW_UNKNOWN?
}
void Input::keyUpReceiver(unsigned char key, int, int) {
	if (spc_press[GLUT_KEY_CTRL_L]) key += 96;
	else if (spc_press[GLUT_KEY_SHIFT_L])
		if (key != 32) key += 32;
	key_press[key] = false;
}

void Input::spcDownReceiver(int key, int, int) {
	//create thread
	//if (key_press.find(key) == key_press.end()) return;
	if (spc_press[key]) return;
	spc_press[key] = true;
	spc_last[key] = false;
	pressed_spc++;
	// else GLFW_REPEAT GLFW_UNKNOWN?
}
void Input::spcUpReceiver(int key, int, int) {
	spc_press[key] = false;
}


void Input::keyDownCallback(void (*callback)(unsigned char)) { keydown_pointer= callback; }
void Input::keyUpCallback(void (*callback)(unsigned char)) { keyup_pointer= callback; }
void Input::spcDownCallback(void (*callback)(int)) { spcdown_pointer= callback; }
void Input::spcUpCallback(void (*callback)(int)) { spcup_pointer= callback; }


void Input::Stop() {
	delete instance;
}

