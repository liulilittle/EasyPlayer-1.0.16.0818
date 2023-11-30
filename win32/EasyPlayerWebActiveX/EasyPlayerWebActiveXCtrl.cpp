// EasyPlayerWebActiveXCtrl.cpp : CEasyPlayerWebActiveXCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "EasyPlayerWebActiveX.h"
#include "EasyPlayerWebActiveXCtrl.h"
#include "EasyPlayerWebActiveXPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEasyPlayerWebActiveXCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CEasyPlayerWebActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CEasyPlayerWebActiveXCtrl, COleControl)
	DISP_FUNCTION_ID(CEasyPlayerWebActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEasyPlayerWebActiveXCtrl, "Start", dispidStart, Start, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPlayerWebActiveXCtrl, "Config", dispidConfig, Config, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPlayerWebActiveXCtrl, "Close", dispidClose, Close, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CEasyPlayerWebActiveXCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CEasyPlayerWebActiveXCtrl, 1)
	PROPPAGEID(CEasyPlayerWebActiveXPropPage::guid)
END_PROPPAGEIDS(CEasyPlayerWebActiveXCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CEasyPlayerWebActiveXCtrl, "EASYPLAYERWEBACT.EasyPlayerWebActCtrl.1",
	0x1ee1c648, 0xf4a9, 0x42f9, 0x9a, 0xa7, 0x2c, 0x8e, 0x3a, 0xf7, 0xb7, 0xfd)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CEasyPlayerWebActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID IID_DEasyPlayerWebActiveX = { 0xFB5E35A6, 0x2538, 0x47C4, { 0x9B, 0x40, 0xB0, 0xFB, 0x6A, 0x0, 0xDE, 0xA0 } };
const IID IID_DEasyPlayerWebActiveXEvents = { 0x66887A6D, 0xC75B, 0x48B8, { 0xB5, 0xE1, 0xBD, 0x72, 0x2D, 0x87, 0x59, 0x23 } };


// �ؼ�������Ϣ

static const DWORD _dwEasyPlayerWebActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEasyPlayerWebActiveXCtrl, IDS_EASYPLAYERWEBACTIVEX, _dwEasyPlayerWebActiveXOleMisc)



// CEasyPlayerWebActiveXCtrl::CEasyPlayerWebActiveXCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CEasyPlayerWebActiveXCtrl ��ϵͳע�����

BOOL CEasyPlayerWebActiveXCtrl::CEasyPlayerWebActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegInsertable | afxRegApartmentThreading ��Ϊ afxRegInsertable��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_EASYPLAYERWEBACTIVEX,
			IDB_EASYPLAYERWEBACTIVEX,
			afxRegInsertable | afxRegApartmentThreading,
			_dwEasyPlayerWebActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// ��Ȩ�ַ���

static const TCHAR _szLicFileName[] = _T("EasyPlayerWebActiveX.lic");

static const WCHAR _szLicString[] = L"Copyright (c) 2016 ";



// CEasyPlayerWebActiveXCtrl::CEasyPlayerWebActiveXCtrlFactory::VerifyUserLicense -
// ����Ƿ�����û����֤

BOOL CEasyPlayerWebActiveXCtrl::CEasyPlayerWebActiveXCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}



// CEasyPlayerWebActiveXCtrl::CEasyPlayerWebActiveXCtrlFactory::GetLicenseKey -
// ��������ʱ��Ȩ��Կ

BOOL CEasyPlayerWebActiveXCtrl::CEasyPlayerWebActiveXCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR *pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}



// CEasyPlayerWebActiveXCtrl::CEasyPlayerWebActiveXCtrl - ���캯��

CEasyPlayerWebActiveXCtrl::CEasyPlayerWebActiveXCtrl()
{
	InitializeIIDs(&IID_DEasyPlayerWebActiveX, &IID_DEasyPlayerWebActiveXEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CEasyPlayerWebActiveXCtrl::~CEasyPlayerWebActiveXCtrl - ��������

CEasyPlayerWebActiveXCtrl::~CEasyPlayerWebActiveXCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CEasyPlayerWebActiveXCtrl::OnDraw - ��ͼ����

void CEasyPlayerWebActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
// 	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
// 	pdc->Ellipse(rcBounds);

	DoSuperclassPaint(pdc, rcBounds);

	//if (!m_pActiveDlg.IsFullScreen())
	{
		m_pActiveDlg.MoveWindow(rcBounds, TRUE);
	}

	CBrush brBackGnd(TranslateColor(AmbientBackColor()));
	pdc->FillRect(rcBounds, &brBackGnd);

}



// CEasyPlayerWebActiveXCtrl::DoPropExchange - �־���֧��

void CEasyPlayerWebActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CEasyPlayerWebActiveXCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CEasyPlayerWebActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CEasyPlayerWebActiveXCtrl::AboutBox - ���û���ʾ�����ڡ���

void CEasyPlayerWebActiveXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_EASYPLAYERWEBACTIVEX);
	dlgAbout.DoModal();
}



// CEasyPlayerWebActiveXCtrl ��Ϣ�������


int CEasyPlayerWebActiveXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	EasyPlayerManager::Init();
	// OCX���ô��ڱ�����OCX�ؼ�Ϊ���ര�ڵ��Ӵ��ڣ����������ʾ�������� [4/14/2014-10:12:38 Dingshuai]
	m_pActiveDlg.Create(CMainVideoWnd::IDD, this);

	return 0;
}


void CEasyPlayerWebActiveXCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_pActiveDlg.DestroyWindow();
	EasyPlayerManager::UnInit();

}


LONG CEasyPlayerWebActiveXCtrl::Start(LPCTSTR sURL, LPCTSTR sRenderFormat, LPCTSTR sUserName, LPCTSTR sPassword)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: �ڴ���ӵ��ȴ���������
	char szURL[512] = {0,};
	char szRenderFormat[128] = {0,};
	char szUserName[128] = {0,};
	char szPassword[128] = {0,};

	if (wcslen(sURL) < 1)		
		return -1;
	__WCharToMByte(sURL, szURL, sizeof(szURL)/sizeof(szURL[0]));
	if (wcslen(sRenderFormat) > 0)
	{
		__WCharToMByte(sRenderFormat, szRenderFormat, sizeof(szRenderFormat)/sizeof(szRenderFormat[0]));
	}
	if (wcslen(sUserName) > 0)
	{
		__WCharToMByte(sUserName, szUserName, sizeof(szUserName)/sizeof(szUserName[0]));
	}
	if (wcslen(sPassword) > 0)
	{
		__WCharToMByte(sPassword, szPassword, sizeof(szPassword)/sizeof(szPassword[0]));
	}

	int nRenderType = atoi(szRenderFormat);
	RENDER_FORMAT eRenderFormat = DISPLAY_FORMAT_YV12;
	switch (nRenderType)
	{
	case 0:
		eRenderFormat = DISPLAY_FORMAT_YV12;
		break;
	case 1:
		eRenderFormat = DISPLAY_FORMAT_YUY2;
		break;
	case 2:
		eRenderFormat = DISPLAY_FORMAT_UYVY;
		break;
	case 3:
		eRenderFormat = DISPLAY_FORMAT_A8R8G8B8;
		break;
	case 4:
		eRenderFormat = DISPLAY_FORMAT_X8R8G8B8;
		break;
	case 5:
		eRenderFormat = DISPLAY_FORMAT_RGB565;
		break;
	case 6:
		eRenderFormat = DISPLAY_FORMAT_RGB555;
		break;
	case 7:
		eRenderFormat = DISPLAY_FORMAT_RGB24_GDI;
		break;
	}

	int nRet = m_player.Start(szURL, m_pActiveDlg.GetSafeHwnd(), eRenderFormat , 1, szUserName , szPassword);
	return nRet;
}


void CEasyPlayerWebActiveXCtrl::Config(LPCTSTR sFrameCache, LPCTSTR sPlaySound, LPCTSTR sShowToScale, LPCTSTR sShowStatisticInfo )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	char szFrameCache[128] = {0,};
	char szPlaySound[128] = {0,};
	char szShowToScale[128] = {0,};
	char szShowStatisticInfo[128] = {0,};
	int nFrameCache = 3;
	BOOL bPlaySound = TRUE;
	BOOL bShowToScale = FALSE;
	BOOL bShowStatisticInfo = TRUE;

	if (wcslen(sFrameCache) > 0)
	{
		__WCharToMByte(sFrameCache, szFrameCache, sizeof(szFrameCache)/sizeof(szFrameCache[0]));
		nFrameCache = atoi(szFrameCache);
	}
	if (wcslen(sPlaySound) > 0)
	{
		__WCharToMByte(sPlaySound, szPlaySound, sizeof(szPlaySound)/sizeof(szPlaySound[0]));
		bPlaySound = atoi(szPlaySound);
	}
	if (wcslen(sShowToScale) > 0)
	{
		__WCharToMByte(sShowToScale, szShowToScale, sizeof(szShowToScale)/sizeof(szShowToScale[0]));
		bShowToScale = atoi(szShowToScale);
	}
	if (wcslen(sShowStatisticInfo) > 0)
	{
		__WCharToMByte(sShowStatisticInfo, szShowStatisticInfo, sizeof(szShowStatisticInfo)/sizeof(szShowStatisticInfo[0]));
		bShowStatisticInfo = atoi(szShowStatisticInfo);
	}

	m_player.Config(nFrameCache, bPlaySound, bShowToScale, bShowStatisticInfo );
}


void CEasyPlayerWebActiveXCtrl::Close(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	m_player.Close();
}
