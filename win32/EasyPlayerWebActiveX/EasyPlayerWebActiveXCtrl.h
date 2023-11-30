#pragma once

#include "MainVideoWnd.h"
// ����EasyPlayer������ [3/6/2016 dingshuai]
#include "EasyPlayerManager.h"

// EasyPlayerWebActiveXCtrl.h : CEasyPlayerWebActiveXCtrl ActiveX �ؼ����������

// CEasyPlayerWebActiveXCtrl : �й�ʵ�ֵ���Ϣ������� EasyPlayerWebActiveXCtrl.cpp��

class CEasyPlayerWebActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEasyPlayerWebActiveXCtrl)

// ���캯��
public:
	CEasyPlayerWebActiveXCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CEasyPlayerWebActiveXCtrl();

	BEGIN_OLEFACTORY(CEasyPlayerWebActiveXCtrl)        // �๤���� guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR *);
	END_OLEFACTORY(CEasyPlayerWebActiveXCtrl)

	DECLARE_OLETYPELIB(CEasyPlayerWebActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEasyPlayerWebActiveXCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CEasyPlayerWebActiveXCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidClose = 3L,
		dispidConfig = 2L,
		dispidStart = 1L
	};

private:
	CMainVideoWnd m_pActiveDlg; 
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
protected:
	LONG Start(LPCTSTR sURL, LPCTSTR sRenderFormat, LPCTSTR sUserName, LPCTSTR sPassword);
	void Config(LPCTSTR sFrameCache, LPCTSTR sPlaySound, LPCTSTR sShowToScale, LPCTSTR sShowStatisticInfo);
	void Close(void);

private:
	EasyPlayerManager m_player;
};

