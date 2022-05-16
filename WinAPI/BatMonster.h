#pragma once

class BatMonster : public Character::Observer
{
	class datas
	{
		public:
			int astar = 0;
			int length;
			POINT point = { 0, 0};
			bool isStop = false;
			bool isLote = false;

			datas()
			{
				astar = point.x = point.y = 0;
				isStop = false;
			};

			datas(POINT point,int state, bool isStop = false)
			{
				astar = state;
				this->point = point;
				this->isStop = isStop;
			};
	};

private:
	vector<datas> roet;

	int fps;
	RECT _detect;
	
	int isdown;

	bool _isDetect;
	void patternMove();
	void _funcCollision();

public:
	BatMonster(RECT);
	~BatMonster() { };
	//HRESULT init();
	void release(void) { };
	void update();
	void render(void);
};

