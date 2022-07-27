
// BombingDlg.h : ͷ�ļ�
//

#pragma once


// CBombingDlg �Ի���
class CBombingDlg : public CDialogEx
{
// ����
public:
	CBombingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BOMBING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//����bool����
	struct mybools
	{
		bool main;//������
		bool end;//�Ƿ����
		bool fen;//�÷�
		bool translation;//�ж��Ƿ�ת��
		bool loading;//�ж��Ƿ����
		bool quitdialog;//�ж��뿪�Ի����Ƿ��
		bool click;//�ж��������Ƿ����
		bool Misioncompleted;///�ж��Ƿ�ͨ��
		bool dialogopen;//�ж϶Ի����Ƿ��
		bool startdialog;//�жϽ�����Ϸ�Ի����Ƿ��
		bool game;//�ж��Ƿ������Ϸ
	}bools;
	//����
	struct words
	{
		struct object
		{
			int frame;
			CImage pic;
		};
		object begin;  // ��ʼ
		object end;  //����
		object mod;  //ģʽ
		object comfirm;  //ȷ��
		object cancel;  //ȡ��
		object rand;   //�����С
		object bom;   ///��ը
		object release;  //�ͷ�
		object perfect;   //�����ķ���
		object great;   ///����
		object good;   //��
		object bad;   //����
		object goal[10];   //�ӷ���
		object plus;    //�Ӻ�

		int pointer;
		int mousepoint;
	}w;
	//����
	struct window
	{
		struct object
		{
			CImage pic;
		};
		object start;
		object dialog;
		object back;
	}c;
	//����
	struct item
	{
		struct object
		{
			CImage pic;
			int frame;
			int x;
			int y;
			CString load;
		};
		int ball;
		bool showball;
		bool showbomb;
		object bottom;//��ť
		object balloon[6];//����
		object bomb;//��ը����
		object gas;//����
		object aro;//��ͷ
		CString goal;
		int score;
		int fen;
		int feny;
		int maxx;
		int times;
		bool keydown;
	}i;
	//************************************DC��ʼ��***************
	CRect m_client;    //����ͻ�����С

	CDC m_cacheDC;   //����DC
	CBitmap m_cacheCBitmap;//����λͼ

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
