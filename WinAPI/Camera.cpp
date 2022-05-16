#include "Stdafx.h"
#include "Camera.h"

Camera::Camera() { init(POINT{ 0,0 }); }

HRESULT Camera::init(POINT point)
{
	if (point.x == 0 && point.y == 0) { _follow = { WINSIZE_X/2, WINSIZE_Y/2 }; } else { _follow = point; }
	_screen = RECT{ 0,0,WINSIZE_X,WINSIZE_Y };
	return S_OK; 
}

void Camera::release(void) { }

void Camera::update(POINT point)
{ 
	_follow = point; 
	_screen = RECT{ _follow.x,_follow.y,WINSIZE_X + _follow.x ,WINSIZE_Y + _follow.y };
}

bool Camera::inTheAngle(RECT rect)
{ 
	RECT temp; if (IntersectRect(&temp, &rect, &_screen)) { return true; } else { return false; }
}

void Camera::setRender(bool relative, int zoder, RECT* rect, Image* image, Animation* animation)
{ 
	_zoder.insert({ zoder,Camera::Stack{relative,rect,0,0,image,animation } }); 
}

void Camera::setRender(bool relative, int zoder, RECT* rect, COLORREF outLine, bool IsSideColor, COLORREF inSide, Image* image, Animation* animation)
{
	if (IsSideColor)
	{
		_zoder.insert({ zoder,Camera::Stack{relative,rect,CreatePen(PS_SOLID,3,outLine), CreateSolidBrush(inSide),image,animation}});
	}
	else
	{
		_zoder.insert({ zoder,Camera::Stack{relative,rect,CreatePen(PS_SOLID,3,outLine), 0,image,animation} });
	}
}

queue<Camera::Stack> Camera::_zoderSort()
{
	int maxOder = 0;
	queue<Camera::Stack>  result;
	
	_iZoder = _zoder.begin();
	for (; _iZoder != _zoder.end(); _iZoder++) { if (_iZoder->first > maxOder) { maxOder = _iZoder->first; } }
	maxOder++;

	for (int i = 0; i < maxOder; i++)
	{
		_iZoder = _zoder.begin();
		for (_iZoder = _zoder.begin(); _iZoder != _zoder.end(); _iZoder++)
		{ if (_iZoder->first == i) { result.push(_iZoder->second); } }
	}
	_zoder.clear();
	return result;
}

void Camera::render(void)
{
	queue<Camera::Stack> object = _zoderSort();
	vector<int> rect;

	while (object.empty() == false)
	{
		if (object.front().rect != nullptr) // 렉트가 있을 경우 
		{
			rect.push_back(object.front().rect->left);
			rect.push_back(object.front().rect->top);
			rect.push_back(object.front().rect->right);
			rect.push_back(object.front().rect->bottom);
			if (object.front().relative == true)
			{
				rect[0] -= _follow.x; rect[2] -= _follow.x;
				rect[1] -= _follow.y; rect[3] -= _follow.y;
			}
		}

		if (object.front().image != nullptr) // 이미지가 있을경우.
		{
			rect.push_back(object.front().image->getX());
			if (object.front().relative == true) { rect.back() -= _follow.x; }
			rect.push_back(object.front().image->getY());
			if (object.front().relative == true) { rect.back() -= _follow.y; }
		}

		if (object.front().rect != nullptr) // 렉트가 있을 경우 
		{
			if (object.front().pen == 0)
			{
				Rectangle(getMemDC(), rect[0], rect[1], rect[2], rect[3]);
			}
			else
			{
				oldPen = (HPEN)::SelectObject(getMemDC(), object.front().pen);
				if (object.front().brush == 0) { Rectangle(getMemDC(), rect[0], rect[1], rect[2], rect[3]); }
				else
				{
					oldBrush = (HBRUSH)SelectObject(getMemDC(), object.front().brush);
					Rectangle(getMemDC(), rect[0], rect[1], rect[2], rect[3]);
					SelectObject(getMemDC(), oldBrush);
					DeleteObject(object.front().brush);
				}
				(HPEN)::SelectObject(getMemDC(), oldPen);
				DeleteObject(object.front().pen);
			}

			for (int i = 0; i < 4; i++) { rect.erase(rect.begin()); }
		}

		if(rect.size() != 0)
		{
			if (object.front().animation != nullptr)
			{ object.front().image->aniRender(getMemDC(), rect[0], rect[1], object.front().animation); }
			else
			{
				if(object.front().image->isFrame())
				{
					object.front().image->frameRender(getMemDC(), rect[0], rect[1]);
				}
				else if (object.front().image->isClipping())
				{
					object.front().image->render(getMemDC(), rect[0], rect[1],
						object.front().image->getClippingX(), object.front().image->getClippingY(),
						object.front().image->getClippingW(), object.front().image->getClippingH());
				}
				else
				{
					object.front().image->render(getMemDC(), rect[0], rect[1]);
				}

			}
		}

		rect.clear();
		object.pop();
	}
}