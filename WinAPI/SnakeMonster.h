#pragma once

class SnakeMonster : public Character::Observer
{
	private:
		enum Pattern
		{
			IDLE, MOVE, END
		};

		int fps;

		// ∆–≈œ 
		Pattern pattern;
		void inputPattern();
		function<void()> patternFunc;
		float limit;
		void patternIdle();
		void patternMove();

		void _funcCollision();

	public:
		SnakeMonster(RECT);
		~SnakeMonster() { };
		//HRESULT init();
		void release(void) { };
		void update();
		void render(void);
};