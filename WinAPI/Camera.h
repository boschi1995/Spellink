#pragma once
#include "GameNode.h"
#include "SingletonBase.h"
#include "Animation.h"

class Camera : public SingletonBase<Camera> , public GameNode
{
	struct Stack
	{
		bool relative;
		RECT* rect;
		HPEN pen;
		HBRUSH brush;
		Image* image;
		Animation* animation;
	};

	private:
		POINT _follow;
		RECT _screen;
		//multimap<int, Stack> _zoder;
		multimap<int, Stack>::iterator _iZoder;
		queue<Stack> _zoderSort();

		HPEN oldPen;
		HBRUSH oldBrush;

	public:
		multimap<int, Stack> _zoder;
		HRESULT init(POINT point);
		void release(void);
		void update(POINT);
		void render(void);
		Camera();
		~Camera() { };

		void setRender(bool,int, RECT*, Image* = nullptr, Animation* = nullptr);
		void setRender(bool, int, RECT*, COLORREF, bool, COLORREF = NULL_BRUSH, Image* = nullptr, Animation* = nullptr);

		bool inTheAngle(RECT);
};