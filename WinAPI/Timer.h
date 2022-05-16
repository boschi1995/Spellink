#pragma once
/*
Ÿ�̸��� ���� ���ڰ� ������ ���ػ� vs ���ػ�
������ �����  API ���� �Լ�
GetTickCount(); -> 1000 1��
�� ��������
GetTickCount64(); ->
���׷��� �̰� ����
//���� Ÿ�̸Ӵ� ���鸸���� 1�ʷ� ��
*/
/*
Timer
- �ð��� �����ϴ� �Լ����� ������ ���� �⺻������ �����찡 ���۵� ���� ���� �ð��� Milli Second ������ ��ȯ
- ���� Ÿ�̸Ӹ� �����Ҷ� �˾Ƶ־� �� ������ �ػ󵵿� Ŭ��

�ػ�?
-�پ��� �ð� �Լ����� �ð��� �����ϱ� ���� �������� tick ��� ������ �մ�.
	�� 1���� �������� �󸶳� ���� ���������� ���� �� �ִ����� ���Ѵ�
	��1�е��� �󸶳� ���� tick���� ������ �ð��� ��Ȯ���� ���̴��Ŀ� ���� ���ػ󵵿� ���ػ󵵷� ������.

Clock(������)
- Ÿ�̸ӿ��� �ֱ��ϴ� Ŭ���� CPUŬ��(clock)�� �ǹ��Ѵ�.
- Ŭ�� ��ü�� ������ ȸ���� ������ ���� ���̸� Hz�� ǥ���Ѵ�.
	�� 1Hz : 1�ʶ�� �����Ͽ� ��ȣ(0or1)�� �� �� �ش�.
								�� 1��Ʈ�� �ѹ� �ű��.
	i5-4690 CPU @ 3.50GHz   3.50 GHz
	�� 1GHz 1�Ⱑ�츣�� : 10�� 9���� -> 10���
	�� 3GHz 3�Ⱑ �츣�� : 30���
							�� 1�ʿ� 30�ﰳ�� ��Ʈ�� �ű� �� �ִ�.

# ���� Ÿ�̸��� ��� ���� ��� ��Ű�� ���ؼ��� ��ø�� �ʿ��ϴ�. - cpu�� �δ��� �޸𸮷� �ٲٴ�...
	�� �뷫 9�鸸���� 1�ʱ��� ����
- �⺻������ �����ϰ� ����� �� �鸸���� 1�ʱ��� ���� ����

-�ٵ� ���ڴٰ� �ؼ� os�� �����ִ��� ���θ� �Ǵ��� (�ź��Ҽ�������)
�� üũ�ؼ� ���ܸ� �����
*/
class Timer
{
private:
	float _timeScale; //����ð� üũ
	float _timeElapsed; // ������ �ð��� ����ð��� ��������� FPS���� ����
	bool _isHardware; // ���� Ÿ�̸� ���� ���� Ȯ��

	// __int64 == INT64_MAX;
	__int64 _curTime;		//���� �ð�
	__int64 _lastTime;			//���� �ð�
	__int64 _periodFrequency;	//�ð� �ֱ�

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init(void);
	//���� �ð��� �������;
	void tick(float lockFPS = 0.0f);

	//���� FPS
	unsigned long getFrameRate(char* str = nullptr) const;
	//������ �ð��� ���� �ð��� �����
	inline float getElapsedTime(void) const { return _timeElapsed; }
	// ��ü ��� �ð�
	inline float getWorldTime(void) const { return _worldTime; }
public:
	Timer() {}
	~Timer() {}
};

