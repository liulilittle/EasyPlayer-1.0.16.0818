#pragma once

// EasyPlayerWebActiveXPropPage.h : CEasyPlayerWebActiveXPropPage ����ҳ���������


// CEasyPlayerWebActiveXPropPage : �й�ʵ�ֵ���Ϣ������� EasyPlayerWebActiveXPropPage.cpp��

class CEasyPlayerWebActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEasyPlayerWebActiveXPropPage)
	DECLARE_OLECREATE_EX(CEasyPlayerWebActiveXPropPage)

// ���캯��
public:
	CEasyPlayerWebActiveXPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_EASYPLAYERWEBACTIVEX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

