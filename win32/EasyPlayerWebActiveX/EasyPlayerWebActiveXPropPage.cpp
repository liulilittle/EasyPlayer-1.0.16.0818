// EasyPlayerWebActiveXPropPage.cpp : CEasyPlayerWebActiveXPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "EasyPlayerWebActiveX.h"
#include "EasyPlayerWebActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEasyPlayerWebActiveXPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CEasyPlayerWebActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CEasyPlayerWebActiveXPropPage, "EASYPLAYERWEBA.EasyPlayerWebAPropPage.1",
	0xf594479c, 0x1a17, 0x49c7, 0xae, 0xf8, 0x86, 0x7a, 0x93, 0x2c, 0x20, 0xa2)



// CEasyPlayerWebActiveXPropPage::CEasyPlayerWebActiveXPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CEasyPlayerWebActiveXPropPage ��ϵͳע�����

BOOL CEasyPlayerWebActiveXPropPage::CEasyPlayerWebActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EASYPLAYERWEBACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CEasyPlayerWebActiveXPropPage::CEasyPlayerWebActiveXPropPage - ���캯��

CEasyPlayerWebActiveXPropPage::CEasyPlayerWebActiveXPropPage() :
	COlePropertyPage(IDD, IDS_EASYPLAYERWEBACTIVEX_PPG_CAPTION)
{
}



// CEasyPlayerWebActiveXPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CEasyPlayerWebActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CEasyPlayerWebActiveXPropPage ��Ϣ�������
