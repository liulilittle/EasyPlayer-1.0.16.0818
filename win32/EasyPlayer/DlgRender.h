#pragma once



typedef struct __CHANNEL_STATUS
{
	
	int			recording;

}CHANNELSTATUS;
// CDlgRender �Ի���

class CDlgRender : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRender)

public:
	CDlgRender(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRender();

	void	SetChannelId(int _channelId)	{mChannelId = _channelId;}

	int		mChannelId;
	CHANNELSTATUS	channelStatus;
	HMENU	hMenu;
	void	ClosePopupMenu();

// �Ի�������
	enum { IDD = IDD_DIALOG_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

private:
	CImageEx	* m_pEasyLogo;

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
