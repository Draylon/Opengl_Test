#include "Input.hpp"

std::map<unsigned char, std::thread> Input::key_threads;
std::map<unsigned char, bool> Input::key_press;
std::map<int, std::thread> Input::spc_threads;
std::map<int, bool> Input::spc_press;

Input* Input::instance;

void (*Input::keydown_pointer)(unsigned char, int, int);
void (*Input::keyup_pointer)(unsigned char, int, int);
void (*Input::spcdown_pointer)(int, int, int);
void (*Input::spcup_pointer)(int, int, int);

//======

Input& Input::getInstance() {
	input_stop_all = false;
	if (!instance) {
		instance = new Input();
	}
	return *instance;
}

void Input::persistKey(unsigned char key) {
	
	while (!input_stop_all && key_press[key] == true) {
		Input::keydown_pointer(key, 0, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	Input::keyup_pointer(key, 0, 0);
}
void Input::persistSpc(unsigned char key) {
	
	while (!input_stop_all && spc_press[key] == true) {
		Input::spcdown_pointer(key, 0, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	Input::spcup_pointer(key, 0, 0);
}


void Input::keyDownReceiver(unsigned char key, int x, int y) {
	//create thread
	if(key_press.find(key) != key_press.end())
		if (key_press[key] == true)
			return;
	if(key_threads.find(key) != key_threads.end())
		if (key_threads[key].joinable())
			key_threads[key].join();

	key_press.insert_or_assign(key, true);
	key_threads.insert_or_assign(key, std::thread(persistKey, key) );
}

void Input::keyUpReceiver(unsigned char key, int x, int y) {
	key_press[key] = false;
}

void Input::specialKeyDownReceiver(int key, int x, int y) {
	//create thread
	if (spc_press.find(key) != spc_press.end())
		if (spc_press[key] == true)
			return;
	if (spc_threads.find(key) != spc_threads.end())
		if (spc_threads[key].joinable())
			spc_threads[key].join();

	spc_press.insert_or_assign(key, true);
	spc_threads.insert_or_assign(key, std::thread(persistSpc, key));
}
void Input::specialKeyUpReceiver(int key, int x, int y) {
	spc_press[key] = false;
}

void Input::keyUpCallback(void (*callback)(unsigned char, int, int)) { keydown_pointer = callback; }
void Input::keyDownCallback(void (*callback)(unsigned char, int, int)) { keyup_pointer = callback; }
void Input::specialKeyDownCallback(void (*callback)(int, int, int)) { spcdown_pointer = callback; }
void Input::specialKeyUpCallback(void (*callback)(int, int, int)) { spcup_pointer = callback; }