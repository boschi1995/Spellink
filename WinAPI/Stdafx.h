#pragma once
#include <sdkddkver.h>

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외
#define WIN32_LEAN_AND_MEAN 

// 형변환 데이터 손실 
#pragma warning(disable:4244)

//! Windows 헤더 파일
#include <Windows.h>

// 디버깅용 콘솔창
//!라이브러리
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")
// 알파 블렌드를 사용하기 위한 라이브러리 추가 
#pragma comment (lib,"msimg32.lib")

//! C 런타임 헤더 파일
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// 윈도우 내장 재생 라이브러리 
// PlaySound()를 사용하기 위해 
#include <mmsystem.h>

// Media Control Interface(장치관리자) API 
// mciSendString()을 사용하기 위해 
#include <mciapi.h>

//! C++ 런타임 헤더 파일
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <queue>
#include <tuple>
#include <cassert>
#include <algorithm>
// bind 함수 기능 묶어주는
#include <functional>
using namespace std;

//===================================
// # 내가 만든 헤더파일을 이곳에 추가 #
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
// # 싱글톤을 이곳에 추가 #
//========================
#define IMAGEMANAGER ImageManager::getSingleton()
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()

//============================
// # 매크로 # (윈도우창 초기화)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

#define WINSTART_X	 200
#define WINSTART_Y	 0
#define WINSIZE_X	 960
#define WINSIZE_Y	 736
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU

//===============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # 전역변수 #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;



// 이거 어떻게해야되는지 나중에 물어보기
#include "Camera.h"
#include "ObserverManager.h"
#include "Tiles.h"
#include "Factory.h"
#define CAMAERA Camera::getSingleton()
#define OBSERVER ObserverManager::getSingleton()
#define MAP MapManager::getSingleton()
#define FACTORY Factory::getSingleton()

static int gameSpeed = 4;