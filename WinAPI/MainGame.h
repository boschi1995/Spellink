#pragma once
#include "GameNode.h"
#include "GameScene.h"

class MainGame : public GameNode
{
private:
	GameScene scene;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
public:
    MainGame() {}
    ~MainGame() {}
};
