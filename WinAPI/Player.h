#pragma once
#include "GameNode.h"
#include "Observer.h"

class Player : public Character::Observer
{
	private:

		// 입력 
		void _inputKey();
		
		// 명령어
		void _funcCollision();
		void _funcImage();
		
	public:
		POINT cameraPoint;

		HRESULT init();
		void release(void) { };
		void update();
		void render(void);

		Player();
		~Player() {};
};
