#pragma once
#include "MapAlorithm.h"

namespace Item
{
	enum Tag
	{
		WHIP, LOPE, BOOM, ARROW, GOLD, ROCK, END
	};

	class Observer
	{
		public:
			RECT rect;
			Tag tag;
			int count;
			int damage;
			Character::Observer* user;
			bool button;
			bool _isdelete;
			virtual void update() { }
			virtual void render() { }
			virtual void Interaction() { }
			virtual bool swap() { return true; }

			Image* image;
			Animation* Anime;
			POINT imagePoint;
	};

	class Nexus
	{
		private:
			vector<Observer*> _observer;
		public:
			void setObserver(Observer*,bool=false);
			void clearObserver();
			void reading();
	};
}

namespace Gravity
{
	class Observer
	{
		public:
			RECT rect;
			pair<bool, float> isJump;
			vector<pair<bool, int >> _collider;
			//vector<pair<bool, int >> _collider;
			void _funcJump();
			bool _isdelete;
	};

	class Nexus
	{
		private:
			RECT comparison[8];
			vector<Observer*> _observer;	
		public:
			void setObserver(Observer*);
			void clearObserver();
			void reading();
	};
}


namespace Character
{
	enum Tag
	{
		PLAYER, MONSTER, TRAP
	};

	class Observer : public GameNode, public Gravity::Observer
	{
		public:
			Tag tag;
			int gold;
			int hp;
			pair<int, int> move;
			int _isDown;
			bool _isUp = false;
			queue<Item::Tag> useItem;
			map<Item::Tag,Item::Observer*> items;

			pair<string,string>state;
			pair<string, string> subState;
			Image* image;
			Animation* Anime;
			POINT imagePoint;
	};

	class Nexus
	{
		private:
			vector<Observer*> _observer;
		public:
			void setObserver(Observer*);
			vector<Observer*> getObserver();
			Observer* getObserver(int);
			void clearObserver();
			void clearObserver(int);
			void reading();
	};
}

namespace Effect
{
	class Observer : public GameNode
	{
		public:
			Image* image;
			Animation* anime;
	};

	class Nexus
	{
		private:
			vector<Observer*> _observer;
		public:
			void reading();
			void setObserver(Observer*);
			Observer* getBack();
	};

}