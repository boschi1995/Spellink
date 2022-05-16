#include "Stdafx.h"
#include "UiScene.h"

HRESULT UiScene::init(void)
{
	heartNum.init("Resources/Ui/number.bmp", 640, 64,10,1, true, RGB(255, 0, 255));
	boomNum.init("Resources/Ui/number.bmp", 640, 64, 10, 1, true, RGB(255, 0, 255));
	ropeNum.init("Resources/Ui/number.bmp", 640, 64, 10, 1, true, RGB(255, 0, 255));
	//heartNum.init("Resources/Ui/number.bmp", 64, 64, 10, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void UiScene::render(void)
{
	for (int i = 0; i < OBSERVER->character.getObserver().size(); i++)
	{
		if (OBSERVER->character.getObserver(i)->tag != Character::PLAYER) { return; }

		char str[256];
		IMAGEMANAGER->findImage("Ui_Heart")->render(getMemDC(), 25, 25);
		IMAGEMANAGER->findImage("Ui_Boom")->render(getMemDC(), 175, 25);
		IMAGEMANAGER->findImage("Ui_Rope")->render(getMemDC(), 325, 25);
		//IMAGEMANAGER->findImage("Ui_Gold")->render(getMemDC(), 475, 25);

		heartNum.setFrameX(OBSERVER->character.getObserver(i)->hp);
		heartNum.frameRender(getMemDC(), 25 + 59, 25);



		//sprintf_s(str, "%d", OBSERVER->character.getObserver(i)->gold);
		//TextOut(getMemDC(), 475 + 57, 25, str, strlen(str));




		Item::Tag find;
		int count = 0;
		for (int h = 0; h < 2; h++)
		{
			if (h == 0) { find = Item::BOOM; } else { find = Item::LOPE; }

			if (OBSERVER->character.getObserver(i)->items.find(find) != OBSERVER->character.getObserver(i)->items.end())
			{
				count = OBSERVER->character.getObserver(i)->items[find]->count;
			}

			if (find == Item::BOOM)
			{
				boomNum.setFrameX(count);
				boomNum.frameRender(getMemDC(), 175 + 57, 25);
			}
			else
			{ 
				ropeNum.setFrameX(count);
				ropeNum.frameRender(getMemDC(), 325 + 57, 25);
			}
		}
		break;
	}
}
