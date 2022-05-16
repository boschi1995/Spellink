#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"
//������Ʈ ���������� �˾ƾ���
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

DWORD CALLBACK loadingThread(LPVOID prc)
{
	// ��ü�� ���� �Լ� ����
	SceneManager::_readyScene->init();

	// ���� ���� ��ü�� ������ ����
	SceneManager::_currentScene = SceneManager::_readyScene;

	// �ε� �� ����
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;
	// �ε�Ŭ������ ����� �ε����� ���� �ʿ�
	return 0;
}
HRESULT SceneManager::init(void)
{
	 SceneManager::_currentScene = nullptr;
	 SceneManager::_loadingScene = nullptr;
	 SceneManager::_readyScene = nullptr;
	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	// �ε� �� >> ��ü ��� ���� �� >> ���� ��
	//4���̻�(��ŸƮ��,���Ӿ�,������,������,������,,,,,)
	//���Ƶ� 10��?�ϰű� ������
	//for ���� ���°� �´��� while���� �´����� ����ϴ°ͺ���
	//�ݺ�Ƚ���� ���� �ʱ⶧���� �ݺ������ٴ� do while�� �ϴ°� ����
	//����� �̰� ���� �����ϰڴ�!
	for (; miSceneList != _mSceneList.end();)
	{	
		//������ ���� ���߹���
		if (miSceneList->second != nullptr)
		{
			if(miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
	/*
	for each(auto scene in _mSceneList)
	{

	}
	SAFE_DELETE(miSceneList->second);
	miSceneList = _mSceneList.erase(miSceneList);
	*/
}

void SceneManager::update(void)
{
	// ���� ���� �����ϸ� ���� ���� ����
	if(_currentScene)_currentScene->update();
}

void SceneManager::render(void)
{
	// ���� ���� �����ϸ� ���� ���� ����
	if (_currentScene)_currentScene->render();
}
// �� �߰�
GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	//�ϴ� �����
	//���� ���ٸ� ����
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}

GameNode * SceneManager::addLoadingScene(string loadingSceneName, GameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(loadingSceneName, scene));
	return nullptr;
}
//�� ����
HRESULT SceneManager::changeScene(string sceneName)
{
	//�����Ϸ��� �ϴ� ���� ã�´�.
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;
	//���� �ʱ�ȭ�� �ϰ� �ٲ��ְ��ִ�.
	//�������� �����ٰ� �ٽ� ������ ������ ���� �����̾��µ� 0���ϼ���?
	//������ �ʱ�ȭ�� �߻������ʵ��� ����ó���ϴ� ���������� �ϴ� �� ¥��
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

