#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private : 
	
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

public :

	KeyManager() {}
	~KeyManager() {}
	HRESULT init(void);

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }
	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }


};

