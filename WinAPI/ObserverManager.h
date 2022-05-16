#pragma once
#include "Stdafx.h"
#include "SingletonBase.h"
#include "Observer.h"

class ObserverManager : public SingletonBase<ObserverManager>
{
	public:
		Character::Nexus character;
		Gravity::Nexus grvity;
		Item::Nexus item;
		Effect::Nexus effect;

		void update()
		{
			grvity.reading();
			character.reading();
			item.reading();
			effect.reading();
		}
};

