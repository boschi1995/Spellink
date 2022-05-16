#pragma once
class Thorn : public ItemTile
{
	Image* image;

	public:
		Thorn(RECT);
		~Thorn() { };

		void release(void) { };
		void update(Character::Observer*) override;
		void rander(void) override;
};

