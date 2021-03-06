#pragma once

class Animation
{
private:
	// 프레임 리스트
	typedef vector <POINT> _vFrameList;

	// 프레임 플레이 리스트
	typedef vector <INT> _vPlayList;

private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameNum;			// 프레임 번호
	int _frameWidth;		// 프레임 가로
	int _frameHeight;		// 프레임 세로 
	int _frameNumWidth;		// 프레임 가로번호
	int _frameNumHeight;	// 프레임 세로번호

	float _frameUpdateSec;	// 초당 프레임 업데이트 수 
	float _elapsedSec;		// 프레임과 프레임 사이의 시간

	bool _isPlay;
	bool _loop;
	DWORD _nowPlayIdx;

public:

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);


	void setDefPlayFrame(bool reverse = false, bool loop = false);
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0, bool loop = false);
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	void setPlayReverseFrame(int start, int end, int framX, bool loop);


	// 초당 프레임 갱신 횟수
	void setFPS(int framePerSec);
	void setFPS(int framePerSec, int maxSec);

	// 프레임 업데이트 
	void frameUpdate(float elpasedTime);
	void AniStart(void);
	void AniStop(void);
	void AniPause(void);
	void AniResume(void);

	// 플레이 중?
	inline bool isPlay(void) { return _isPlay; }

	inline POINT getFramePos(void) 
	{ 
		if (0 > _nowPlayIdx || _nowPlayIdx >= size(_playList)) 
			return POINT{ 0,0 };
		int frameListIndex = _playList[_nowPlayIdx];
		if (0 > frameListIndex || frameListIndex >= size(_frameList))
			return POINT{ 0,0 };

		return _frameList[_playList[_nowPlayIdx]]; 
	}
	
	//inline int getFrame(void) { return _nowPlayIdx; }

	// 현재 에니메이션의 프레임 위치 순서 얻기
	inline int getFrameIdx(void)
	{
		POINT ptPOS = getFramePos();
		int frameX = ptPOS.x / _frameWidth;
		int frameY = ptPOS.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	//프레임 가로 세로 크기를 얻어온다
	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }

	Animation();
	~Animation() {};
};



