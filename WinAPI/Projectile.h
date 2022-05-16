#pragma once
class Projectile : public Character::Observer
{
	private:

	public:
		Projectile(RECT,int);
		~Projectile() { };
		void release(void) { };
		void update();
		void render(void);
};

