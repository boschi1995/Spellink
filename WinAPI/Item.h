#pragma once
#include "Observer.h"

class Whip : public Item::Observer
{
	public:
		Whip(Character::Observer*);
		~Whip() { };
		void update() override;
		void render() override;
		void Interaction() override;
};

class Lope : public Item::Observer
{
	// 땅에 잇을경우만. 
	private:
		int _distance;
		int tail;
		RECT* collider;
	public:
		Lope(Character::Observer*);
		~Lope() { };
		void update() override;
		void render() override;
		void Interaction() override;
		bool swap() override;
}; 

class LopeTile : public ItemTile
{
	private:
		bool attach;
	public:
		LopeTile(RECT, bool, int = 0);
		~LopeTile() { };
		void update(Character::Observer*) override;
		void update() override;
		void rander() override;
};

// 타일로 스왑 
class Boom : public Item::Observer
{
	private:
		pair<int,int> fps;
		int move;
		bool shoot;
		queue<float> _keeping;
		float second;
	public:
		Boom();
		Boom(Character::Observer*);
		~Boom() { };

		void update() override;
		void render() override;
		void Interaction() override;
		bool swap() override;
};

class BoomTile : public ItemTile, public Gravity::Observer
{
private:
	pair<int, int> fps;
	float speed;
	int move;
	RECT blasting;
	queue<float> _keeping;
public:
	BoomTile(RECT);
	BoomTile(RECT,int);
	BoomTile(RECT,int, queue<float>,pair<int,int>);
	~BoomTile() {};
	void update() override;
	void rander() override;
};

class Arrow : public Item::Observer
{
	private:
		int direction;

	public:
		Arrow(Character::Observer*);
		~Arrow() { };
		void update() override;
		void render() override;
		void Interaction() override;
};

class ArrowTile : public ItemTile, public Gravity::Observer
{
	private:
		float speed;
		int move;
	public:
		ArrowTile(RECT,int);
		void update() override;
		void update(Character::Observer*) override;
		void rander() override;
		~ArrowTile() { };
};

class Rock : public Item::Observer
{
	private:
		int direction;

	public:
		Rock(Character::Observer*);
		~Rock() { };
		void update() override;
		void render() override;
		void Interaction() override;
};

class RockTile : public ItemTile, public Gravity::Observer
{
	private:
		float speed;
		int move;
	public:
		RockTile(RECT, int =0);
		void update() override;
		void update(Character::Observer*) override;
		void rander() override;
		~RockTile() { };
};

class GoldTile : public ItemTile, public Gravity::Observer
{
	private:
		int gold;
	public:
		GoldTile(RECT,int);
		~GoldTile() { };
		void update() override;
		void update(Character::Observer*) override;
		void rander() override;
};