
// EasyPlayerDlg.h : ͷ�ļ�
//

#pragma once

#include "DlgVideo.h"
#include ".\EasySkinUI\skindialog.h"


#define	_SURV_MAX_WINDOW_NUM		16

typedef struct __VIDEO_NODE_T
{
	bool		fullscreen;
	int			maximizedId;
	int			selectedId;
	int			channels;
	CDlgVideo	*pDlgVideo;
}VIDEO_NODE_T;

// CEasyPlayerDlg �Ի���
class CEasyPlayerDlg : public CSkinDialog
{
// ����
public:
	CEasyPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��


public:
	CComboBox		*pComboxSplitScreen;
	CComboBox		*pComboxRenderFormat;	//IDC_COMBO_RENDER_FORMAT
	VIDEO_NODE_T	*pVideoWindow;		//��Ƶ����
	CSkinButton			pChkShownToScale;	//��������ʾ
	CStatic			*pStaticCopyright;	//IDC_STATIC_COPYRIGHT

	void	InitialComponents();
	void	CreateComponents();
	void	UpdateComponents();
	void	DeleteComponents();
	void	UpdateVideoPosition(LPRECT lpRect);

// �Ի�������
	enum { IDD = IDD_EASYPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	LRESULT OnWindowMaximized(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL DestroyWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnCbnSelchangeComboSplitScreen();
	afx_msg void OnCbnSelchangeComboRenderFormat();
	afx_msg void OnBnClickedCheckShowntoscale();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
