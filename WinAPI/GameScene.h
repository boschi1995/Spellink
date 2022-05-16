#pragma once
#include "GameNode.h"
#include "Observer.h"
#include "Player.h"
#include "UiScene.h"

class GameScene : public GameNode
{
	private:
		Player* player;
		UiScene ui;

	public:
		HRESULT init(void);
		void release(void) { };
		void update(void);
		void render(void);

		GameScene() {};
		~GameScene() {};
};