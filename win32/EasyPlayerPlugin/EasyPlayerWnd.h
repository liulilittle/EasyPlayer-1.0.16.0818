/*
	Copyright (c) 2013-2014 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
// ���Ŵ��ڽ����� [11/8/2015 Dingshuai]
// Add by SwordTwelve

#pragma once


#include "Win/PluginWindowWin.h"
#include <gdiplus.h>
#include "../../build\projects\EasyPlayerPlugin\gen\global\resource.h"

FB_FORWARD_PTR(EasyPlayerWnd)

class EasyPlayerWnd : public FB::PluginWindowWin
{
public:
	EasyPlayerWnd(const FB::WindowContextWin& ctx);
	~EasyPlayerWnd(void);
	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam);
	typedef std::map<void*,EasyPlayerWnd*> PluginWindowMap;


	//Member Function
protected:
	static PluginWindowMap m_windowMap;
	//���ڻ��ƺ���
	virtual void DrawClientArea(HDC hdc,int nWidth,int nHeight);

};

