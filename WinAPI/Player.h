#pragma once
#include "GameNode.h"
#include "Observer.h"

class Player : public Character::Observer
{
	private:

		// �Է� 
		void _inputKey();
		
		// ��ɾ�
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
