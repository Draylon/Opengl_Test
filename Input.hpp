#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include<map>
#include<thread>
#include<vector>
#include <list>
#include <GL/freeglut.h>

bool input_stop_all = false;
class Input {
private:

	static Input* instance;
	Input() {
		keys_thread = std::thread(persistKey);
	}
	~Input() {
		input_stop_all = true;
		if (keys_thread.joinable())
			keys_thread.join();
		printf("Input thread has been stopped\n");
	}

	static void (*keydown_pointer)(unsigned char);
	static void (*keyup_pointer)(unsigned char);
	static void (*spcdown_pointer)(int);
	static void (*spcup_pointer)(int);

	static void persistKey();

public:
	static unsigned int pressed_keys;
	static unsigned int pressed_spc;
	static std::thread keys_thread;
	static std::map<unsigned char, bool> key_press;
	static std::map<unsigned char, bool> spc_press;
	static std::map<unsigned char, bool> key_last;
	static std::map<unsigned char, bool> spc_last;

	static Input* getInstance();

	//static void initKeys(std::list<int>);

	static void keyDownReceiver(unsigned char key, int,int);
	static void keyUpReceiver(unsigned char key, int,int);
	static void spcDownReceiver(int key, int,int);
	static void spcUpReceiver(int key, int,int);

	static void keyDownCallback(void (*callback)(unsigned char));
	static void keyUpCallback(void (*callback)(unsigned char));
	static void spcDownCallback(void (*callback)(int));
	static void spcUpCallback(void (*callback)(int));

	static void Stop();
};


#endif