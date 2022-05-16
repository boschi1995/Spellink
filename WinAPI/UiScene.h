#pragma once
#include "GameNode.h"

class UiScene : public GameNode
{
	private:
		Image heartNum;
		Image boomNum;
		Image ropeNum;
		//Image goldNum;



	public:
		HRESULT init(void);
		void release(void) { }
		void render(void);
};

