#pragma once

#include "ImageEx.h"

// CMainVideoWnd �Ի���

class CMainVideoWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CMainVideoWnd)

public:
	CMainVideoWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainVideoWnd();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

private:
	//IDB_PNG_EASYLOGO
	CImageEx	* m_pEasyLogo;

public:
	virtual BOOL OnInitDialog();
};
