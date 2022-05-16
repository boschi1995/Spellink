#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init()
{
	return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
	string first="open \""; // ���丮�� ã�Ƽ� ������ ����
	string end = "\" type mpegvideo alias ";
	string finalQuery = first + fileName + end + key;

	// C++ ���ڿ��� C��Ÿ�Ϸ� ��ȯ 
	const char* str = finalQuery.c_str(); 

	// mciSendString() : ���� ��ġ�� ��ɾ �����Ͽ� �ʿ��� ��ġ�� ������Ű�� �Լ�
	// ���ڿ� ��ɾ�, ��ȯ�� ���ڿ�, ��ȯ�� ����, �ڵ� �ݹ� 
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
	string first = "open \""; // ���丮�� ã�Ƽ� ������ ����
	string end = "\" type waveaudio alias ";
	string finalQuery = first + fileName + end + key;

	// C++ ���ڿ��� C��Ÿ�Ϸ� ��ȯ 
	const char* str = finalQuery.c_str();

	// mciSendString() : ���� ��ġ�� ��ɾ �����Ͽ� �ʿ��� ��ġ�� ������Ű�� �Լ�
	// ���ڿ� ��ɾ�, ��ȯ�� ���ڿ�, ��ȯ�� ����, �ڵ� �ݹ� 
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
	// �����̸�.wave , �ڵ�(NULL -> ���ϸ��� ����Ѵ�.), sound: �ɼ� | �ɼ� | �ɼ�
	// PlaySound(fileName, NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	// ���带 ��� ����Ұ��� : ���� Ȯ�� , �ɼ� | �ݺ� | ���� ���� ��� ���(�Ⱦ�) 
	
	// ������ ����ϴ� ��� SND_ASYNC�� ������ �ݺ��ϴµ��� �����Ϸ��� �ƹ��͵� �� �� ����.
	// SND_ASYNC : ����ϸ鼭 ���� �ڵ� ����(�񵿱������� �۵��϶�� �÷���)
	// �񵿱��� -> �����尡 �۵��ϳ�? -> �����尡 �۵��Ѵٸ� ���ſ� �ڵ�ڱ�....
	PlaySound(fileName, NULL, SND_ASYNC );

}


void TempSoundManager::playSoundWithKey(string key)
{
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::stopMp3WithKey(string key)
{
	string first = "stop ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}
