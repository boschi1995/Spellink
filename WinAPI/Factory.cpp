#include "Stdafx.h"
#include "Factory.h"

void Factory::produce(Tag tag,RECT rect,int direction)
{
	switch (tag)
	{
		case Factory::SNAKE: // 완료 
		{ 
			OBSERVER->character.setObserver(new SnakeMonster(rect));
			OBSERVER->grvity.setObserver(OBSERVER->character.getObserver().back());
		} break;
		case Factory::BAT: // 완료 
		{
			OBSERVER->character.setObserver(new BatMonster(rect));
			OBSERVER->grvity.setObserver(OBSERVER->character.getObserver().back());
		} break;
		case Factory::THORN: // 완료
		{
			MAP->_item.push_back(new Thorn(rect));
		}break;
		case Factory::PROJECTILE: // 완료 
		{
			OBSERVER->character.setObserver(new Projectile(rect, direction));
		}break;
	}
}
