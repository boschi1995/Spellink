#include "Stdafx.h"
#include "GameScene.h"
#include "Item.h"

HRESULT GameScene::init(void)
{
	player = new Player();
	MAP->init();
	player->init();
	ui.init();
	for (int i = 0; i < 60; i++)
	{
		//FACTORY->produce(Factory::SNAKE, player->rect);
	}
	return S_OK;
}

void GameScene::update(void)
{
	
}

void GameScene::render(void)
{
	MAP->render();
	CAMAERA->render();
	ui.render();
}


