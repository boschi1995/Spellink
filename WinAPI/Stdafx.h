#pragma once
#include <sdkddkver.h>

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN 

// ����ȯ ������ �ս� 
#pragma warning(disable:4244)

//! Windows ��� ����
#include <Windows.h>

// ������ �ܼ�â
//!���̺귯��
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")
// ���� ���带 ����ϱ� ���� ���̺귯�� �߰� 
#pragma comment (lib,"msimg32.lib")

//! C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// ������ ���� ��� ���̺귯�� 
// PlaySound()�� ����ϱ� ���� 
#include <mmsystem.h>

// Media Control Interface(��ġ������) API 
// mciSendString()�� ����ϱ� ���� 
#include <mciapi.h>

//! C++ ��Ÿ�� ��� ����
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <queue>
#include <tuple>
#include <cassert>
#include <algorithm>
// bind �Լ� ��� �����ִ�
#include <functional>
using namespace std;

//===================================
// # ���� ���� ��������� �̰��� �߰� #
//===================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"
using namespace MY_UTIL;

//========================
// # �̱����� �̰��� �߰� #
//========================
#define IMAGEMANAGER ImageManager::getSingleton()
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()

//============================
// # ��ũ�� # (������â �ʱ�ȭ)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

#define WINSTART_X	 200
#define WINSTART_Y	 0
#define WINSIZE_X	 960
#define WINSIZE_Y	 736
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU

//===============================================
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # �������� #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;



// �̰� ����ؾߵǴ��� ���߿� �����
#include "Camera.h"
#include "ObserverManager.h"
#include "Tiles.h"
#include "Factory.h"
#define CAMAERA Camera::getSingleton()
#define OBSERVER ObserverManager::getSingleton()
#define MAP MapManager::getSingleton()
#define FACTORY Factory::getSingleton()

static int gameSpeed = 4;