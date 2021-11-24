#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include<map>
#include<thread>
#include<vector>
#include <list>

static bool input_stop_all = false;
class Input {
private:
	
	static std::map<unsigned char, std::thread> key_threads;
	static std::map<unsigned char, bool> key_press;
	static std::map<int, std::thread> spc_threads;
	static std::map<int, bool> spc_press;
	
	static Input* instance;
	Input() {}

	static void (*keydown_pointer)(unsigned char, int, int);
	static void (*keyup_pointer)(unsigned char, int, int);
	static void (*spcdown_pointer)(int, int, int);
	static void (*spcup_pointer)(int, int, int);

	static void persistKey(unsigned char);
	static void persistSpc(int);

public:
	static Input& getInstance();

	static void initKeys(std::list<char>);
	static void initSpcKeys(std::list<int>);

	static void keyUpReceiver(unsigned char, int, int);
	static void keyDownReceiver(unsigned char, int, int);
	static void specialKeyDownReceiver(int, int, int);
	static void specialKeyUpReceiver(int, int, int);

	static void keyUpCallback(void (*callback)(unsigned char, int, int));
	static void keyDownCallback(void (*callback)(unsigned char, int, int));
	static void specialKeyDownCallback(void (*callback)(int, int, int));
	static void specialKeyUpCallback(void (*callback)(int, int, int));


	~Input(){
		input_stop_all = true;
		for (std::pair<const unsigned char,std::thread> & e : key_threads) {
			if (e.second.joinable())
				e.second.join();
		}
		for (std::pair<const int,std::thread> & e : spc_threads) {
			if (e.second.joinable())
				e.second.join();
		}
	}
};


#endif