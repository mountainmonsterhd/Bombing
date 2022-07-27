
// BombingDlg.h : 头文件
//

#pragma once


// CBombingDlg 对话框
class CBombingDlg : public CDialogEx
{
// 构造
public:
	CBombingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BOMBING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//各种bool变量
	struct mybools
	{
		bool main;//主界面
		bool end;//是否结束
		bool fen;//得分
		bool translation;//判断是否转场
		bool loading;//判断是否加载
		bool quitdialog;//判断离开对话框是否打开
		bool click;//判断鼠标左键是否点下
		bool Misioncompleted;///判断是否通关
		bool dialogopen;//判断对话框是否打开
		bool startdialog;//判断进入游戏对话框是否打开
		bool game;//判断是否进入游戏
	}bools;
	//文字
	struct words
	{
		struct object
		{
			int frame;
			CImage pic;
		};
		object begin;  // 开始
		object end;  //结束
		object mod;  //模式
		object comfirm;  //确定
		object cancel;  //取消
		object rand;   //随机大小
		object bom;   ///爆炸
		object release;  //释放
		object perfect;   //完美的分数
		object great;   ///不错
		object good;   //好
		object bad;   //坏的
		object goal[10];   //加分数
		object plus;    //加号

		int pointer;
		int mousepoint;
	}w;
	//背景
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
	//物体
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
		object bottom;//按钮
		object balloon[6];//气球
		object bomb;//爆炸动画
		object gas;//气体
		object aro;//箭头
		CString goal;
		int score;
		int fen;
		int feny;
		int maxx;
		int times;
		bool keydown;
	}i;
	//************************************DC初始化***************
	CRect m_client;    //保存客户区大小

	CDC m_cacheDC;   //缓冲DC
	CBitmap m_cacheCBitmap;//缓冲位图

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
