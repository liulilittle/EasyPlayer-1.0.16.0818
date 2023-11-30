/*
	Copyright (c) 2013-2014 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
// RTSP������(����)�����࣬��������Ƶ�� [11/8/2015 Dingshuai]
// Add by SwordTwelve

#pragma once

#include "./Win/libEasyPlayer/EasyRTSPClient/EasyTypes.h"
#include "./Win/libEasyPlayer/libEasyPlayerAPI.h"

//Gavin's Source Struct����Ϣ�ṹ
typedef struct __EASY_LOCAL_SOURCE_T
{	
	int		rtspSourceId;
	Easy_Pusher_Handle	pusherHandle;

	char	pushServerAddr[128];
	int		pushServerPort;
	char	sdpName[64];
	void* pMaster;
}EASY_LOCAL_SOURCE_T;

class EasyPlayerManager
{
public:
	EasyPlayerManager(void);
	~EasyPlayerManager(void);

	//Member Function
public:
	//��ʼ��
	static int Init()
	{
		return EasyPlayer_Init();
	}

	// �ͷ�
	static void UnInit()
	{
		EasyPlayer_Release();
	}

	//����
	int Start(char* szURL, HWND hShowWnd, RENDER_FORMAT eRenderFormat, int rtpovertcp, const char *username, const char *password, MediaSourceCallBack callback=NULL, void *userPtr=NULL) ;
	//���ò���
	void Config(int nFrameCache,  BOOL bPlaySound, BOOL bShowToScale = TRUE, BOOL  bShowStatisticInfo = FALSE);
	//�ر���
	void	Close();
	int InRunning();

	//Member Var
private:
	//���յ�����Ϣ
	EASY_LOCAL_SOURCE_T		m_sSourceInfo;
};

