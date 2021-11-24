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

void Input::initKeys(std::list<char>charlist) {
	for (char c : charlist) {
		key_press[c] = false;
		key_threads[c] = std::thread(persistKey,c);
		key_threads[c].join();
	}
}
void Input::initSpcKeys(std::list<int>charlist) {
	for (char c : charlist) {
		spc_press[c] = false;
		spc_threads[c] = std::thread(persistSpc,c);
		spc_threads[c].join();
	}
}

void Input::persistKey(unsigned char key) {
	while (!input_stop_all && key_press[key] == true){
		Input::keydown_pointer(key, 0, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
void Input::persistSpc(int key) {
	while (!input_stop_all && spc_press[key] == true) {
		Input::spcdown_pointer(key, 0, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}


void Input::keyDownReceiver(unsigned char key, int x, int y) {
	//create thread
	if (key_press[key]) return;
	key_press[key] = true;
	if (key_threads[key].joinable()) return;
	Input::keydown_pointer(key, 0, 0);
	key_threads[key]= std::thread(persistKey, key);
}

void Input::keyUpReceiver(unsigned char key, int x, int y) {
	key_press[key] = false;
	Input::keyup_pointer(key, 0, 0);
	if(key_threads[key].joinable())key_threads[key].join();
}

void Input::specialKeyDownReceiver(int key, int x, int y) {
	//create thread
	if (spc_press[key]) return;
	spc_press[key] =true;
	if (spc_threads[key].joinable()) return;
	Input::spcdown_pointer(key, 0, 0);
	spc_threads[key]=std::thread(persistSpc, key);
}
void Input::specialKeyUpReceiver(int key, int x, int y) {
	spc_press[key] = false;
	Input::spcup_pointer(key, 0, 0);
	if(spc_threads[key].joinable())spc_threads[key].join();
}

void Input::keyUpCallback(void (*callback)(unsigned char, int, int)) { keyup_pointer = callback; }
void Input::keyDownCallback(void (*callback)(unsigned char, int, int)) { keydown_pointer = callback; }
void Input::specialKeyDownCallback(void (*callback)(int, int, int)) { spcdown_pointer = callback; }
void Input::specialKeyUpCallback(void (*callback)(int, int, int)) { spcup_pointer = callback; }