#pragma once
#include "SingletonBase.h"
#include "Timer.h"
//Ÿ�̸Ӵ� �߻����丮�� ���� �� ������ �ϴ� �̷��� ����
class TimeManager : public SingletonBase <TimeManager>
{
private:
	Timer* _timer;
public:
	//���� ���� ������� ������ ��ü�� �����ϰڴ�
	//�ð��� �׻� �귯���°Ŵϱ�
	//�׷��� ���� �߻����丮�� ���ٰ� �Ѱ�
	HRESULT init(void);
	void release(void);
	void update(float lock = 0.0f);
	void render(HDC hdc);

	//��ü �ð�
	inline float getWorldTime(void) const { return _timer->getWorldTime(); }
	//������ ��� �ð�
	inline float getElapsedTime(void) const { return _timer->getElapsedTime(); }
public:
	TimeManager() {}
	~TimeManager() {}
};

