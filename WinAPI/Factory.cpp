#include "Stdafx.h"
#include "Factory.h"

void Factory::produce(Tag tag,RECT rect,int direction)
{
	switch (tag)
	{
		case Factory::SNAKE: // �Ϸ� 
		{ 
			OBSERVER->character.setObserver(new SnakeMonster(rect));
			OBSERVER->grvity.setObserver(OBSERVER->character.getObserver().back());
		} break;
		case Factory::BAT: // �Ϸ� 
		{
			OBSERVER->character.setObserver(new BatMonster(rect));
			OBSERVER->grvity.setObserver(OBSERVER->character.getObserver().back());
		} break;
		case Factory::THORN: // �Ϸ�
		{
			MAP->_item.push_back(new Thorn(rect));
		}break;
		case Factory::PROJECTILE: // �Ϸ� 
		{
			OBSERVER->character.setObserver(new Projectile(rect, direction));
		}break;
	}
}
