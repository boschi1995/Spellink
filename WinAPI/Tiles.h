#pragma once
#include "SingletonBase.h"
#include "MapAlorithm.h"

class Tile
{
	public:
		enum class Type
		{
			WALL, IMPOSSIBLE, BACK,
			ENTRANCE, EXIT,
			LOPE,
		};

		RECT object;
		Image image;
		int gold;
		Type type;
		Tile() { };
		~Tile() { };
};


namespace Character { class Observer; }
namespace Item { enum Tag; }
class ItemTile
{
	public:
		bool _isdelete;
		bool _capsule;
		Item::Tag tag;
		RECT object;
		virtual void rander() { };
		virtual void update() { };
		virtual void update(Character::Observer*) {};

		Image* image;
};
 
class MapManager : public SingletonBase<MapManager>
{
	private:
		vector<pair<POINT, int>> _spon;

	public:
		// 지형
		Image backGround;
		vector<vector<Tile>> _tiles;
		vector<POINT> _angleTiles;
		vector<POINT> _door;
		
		// 아이템 
		vector<ItemTile*> _item;
		vector<int> _angleItem;

		void init();
		void relese();
		void render();
		void update();
		void clearItem();
		void TileImage(Tile* tile);
};


