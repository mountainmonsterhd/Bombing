
// BombingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bombing.h"
#include "BombingDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include <MMSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBombingDlg �Ի���
#define NONE -1
#define START 1
#define QUIT 3
#define YES 4
#define NO 5
#define CONFIRM 6
#define CANCEL 7
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
//�ػ�ʱ��
#define TIMER_PAINT 1001
#define TIMER_BOMB 1002
#define TIMER_BALLOON 1003
#define TIMER_FEN 1004

//***************�Զ��庯��
void TransparentPNG(CImage *png)
{
    for(int i = 0; i <png->GetWidth(); i++)
    {
        for(int j = 0; j <png->GetHeight(); j++)
        {
            unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i , j));
            pucColor[0] = pucColor[0] *pucColor[3] / 255;
            pucColor[1] = pucColor[1] *pucColor[3] / 255;
            pucColor[2] = pucColor[2] *pucColor[3] / 255;
        }
    }
}

int random(int a,int b)
{
	return rand()%(b-a+1)+a;
}

CBombingDlg::CBombingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBombingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBombingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBombingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CBombingDlg ��Ϣ�������

BOOL CBombingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBombingDlg::OnPaint()
{
	//******************����DC*****************
	
	CDC *cDC=this->GetDC();//��ȡ����DCָ��
	
	GetClientRect(&m_client);//��ȡ���ڴ�С
	
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(cDC,m_client.Width(),m_client.Height());//��������DC
	m_cacheDC.SelectObject(&m_cacheCBitmap);
	
	
//**************************����ͼ�����*******************
	c.back.pic.Draw(m_cacheDC,0,0,1280,720,0,0,1280,720);
	if(bools.main)
	{
		switch(w.pointer)
		{
		case START:
			{
				w.begin.frame = 1;
				w.end.frame = 0;
			}
			break;
		case QUIT:
			{
				w.begin.frame = 0;
				w.end.frame = 1;
			}
			break;
		}
		w.begin.pic.Draw(m_cacheDC,300,250,570,120,0,w.begin.frame*120,570,120);
		w.end.pic.Draw(m_cacheDC,300,420,570,120,0,w.end.frame*120,570,120);
		CFont font;
		font.CreateFontW(20,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("����"));
		m_cacheDC.SelectObject(&font);
		SetTextColor(m_cacheDC,RGB(0,0,0));
		SetBkMode(m_cacheDC,TRANSPARENT);
		m_cacheDC.TextOutW(10,690,_T("version:demo�汾1.0   ���ߣ��������  ������"));
	}
	if(bools.game)
	{
		CFont font;
		font.CreateFontW(40,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("��Բ"));
		m_cacheDC.SelectObject(&font);
		SetTextColor(m_cacheDC,RGB(100,79,89));
		SetBkMode(m_cacheDC,TRANSPARENT);
		m_cacheDC.TextOutW(20,20,_T("�����ո����������������ٰ�һ��ֹͣ����"));//
		m_cacheDC.TextOutW(50,650,_T("С������ըŶ����"));
		font.DeleteObject();
		font.CreateFontW(30,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("��Բ"));
		m_cacheDC.SelectObject(&font);
		SetTextColor(m_cacheDC,RGB(0,100,220));
		SetBkMode(m_cacheDC,TRANSPARENT);
		i.goal.Format(_T("��ǰ�÷֣�%d"),i.score);
		m_cacheDC.TextOutW(1030,80,i.goal);
		CString text;
		text.Format(_T("������%d�λ���"),10-i.times);
		m_cacheDC.TextOutW(1030,130,text);
		font.DeleteObject();
		if(i.showball)
		{
			i.balloon[i.ball].pic.Draw(m_cacheDC,WINDOW_WIDTH/2-i.balloon[i.ball].x/2,WINDOW_HEIGHT/2-i.balloon[i.ball].y+200,i.balloon[i.ball].x,i.balloon[i.ball].y,0,0,100,137);
		}
		else if(i.showbomb)
		{
			i.bomb.pic.Draw(m_cacheDC,WINDOW_WIDTH/2-i.balloon[i.ball].x/2,WINDOW_HEIGHT/2-i.balloon[i.ball].y+200,i.balloon[i.ball].x,i.balloon[i.ball].y,0,0,492,435);
		}
		if(bools.fen)
		{
			font.CreateFontW(50,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("��Բ"));
			m_cacheDC.SelectObject(&font);
			SetTextColor(m_cacheDC,RGB(0,100,220));
			text.Format(_T("+%d"),i.fen);
			m_cacheDC.TextOutW(800,i.feny,text);
			font.DeleteObject();
		}
	}
	if(bools.end)
	{
		CFont font;
		font.CreateFontW(100,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("��Բ"));
		m_cacheDC.SelectObject(&font);
		SetTextColor(m_cacheDC,RGB(random(0,255),random(0,255),random(0,255)));
		SetBkMode(m_cacheDC,TRANSPARENT);
		m_cacheDC.TextOutW(280,180,_T("��Ϸ����"));
		i.goal.Format(_T("���յ÷֣�%d"),i.score);
		m_cacheDC.TextOutW(280,380,i.goal);
		font.DeleteObject();
		font.CreateFontW(30,0,0,0,FW_BLACK,FALSE,FALSE,FALSE,GB2312_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,VARIABLE_PITCH|PROOF_QUALITY,FIXED_PITCH | FF_MODERN,_T("��Բ"));
		m_cacheDC.SelectObject(&font);
		SetTextColor(m_cacheDC,RGB(100,79,89));
		SetBkMode(m_cacheDC,TRANSPARENT);
		m_cacheDC.TextOutW(20,680,_T("���ո���ص���ʼ����"));
		font.DeleteObject();
	}

	//*********�ڴ�DC������DC****************
	//��󽫻���DC�������������DC��

	cDC->BitBlt(0,0,m_client.Width(),m_client.Height(),&m_cacheDC,0,0,SRCCOPY);
	
	

	

	//�ڻ�����ͼ��,ʹ��������Ч
	ValidateRect(&m_client);
	//�ͷŻ���DC
	m_cacheDC.DeleteDC();
	//�ͷŶ���
	m_cacheCBitmap.DeleteObject();
	//�ͷŴ���DC
	ReleaseDC(cDC);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBombingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




int CBombingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//i.bomb.load.Format("b%d",i.bomb.frame);
	// TODO:  �ڴ������ר�õĴ�������
	MoveWindow(320,180,1280,720);
	SetTimer(TIMER_PAINT,10,NULL);
	//���ر���ͼƬ
	c.back.pic.Load(_T("res\\res\\start"));
	//����ͼƬ
	w.begin.pic.Load(_T("res\\res\\startgame"));
	w.end.pic.Load(_T("res\\res\\endgame"));
	i.balloon[0].pic.Load(_T("res\\res\\red"));
	i.balloon[1].pic.Load(_T("res\\res\\blue"));
	i.balloon[2].pic.Load(_T("res\\res\\yellow"));
	i.balloon[3].pic.Load(_T("res\\res\\green"));
	i.balloon[4].pic.Load(_T("res\\res\\purple"));
	i.balloon[5].pic.Load(_T("res\\res\\orange"));
	i.bomb.pic.Load(_T("res\\res\\b1"));
	//�Ż�ͼƬ����
	TransparentPNG(&w.begin.pic);
	TransparentPNG(&w.end.pic);
	TransparentPNG(&i.balloon[1].pic);
	TransparentPNG(&i.balloon[2].pic);
	TransparentPNG(&i.balloon[3].pic);
	TransparentPNG(&i.balloon[4].pic);
	TransparentPNG(&i.balloon[5].pic);
	TransparentPNG(&i.balloon[0].pic);
	TransparentPNG(&i.bomb.pic);

	//��ʼ��ͼƬ֡
	w.begin.frame = 0;
	w.end.frame = 0;
	i.bomb.frame = 1;
	//��ʼ������
	for(int t = 0;t<6;t++)
	{
		i.balloon[t].x = 35;
		i.balloon[t].y = 48;
	}
	w.pointer = START;
	bools.main = 1;
	bools.game = 0;
	bools.end = 0;
	bools.fen = 0;
	i.showball = 0;
	i.showbomb = 0;
	i.score = 0;
	i.maxx = random(300,500);
	i.keydown = 0;
	i.times = 0;
	i.feny = 400;
	
	//SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|0x80000);
	i.ball = random(0,5);
	sndPlaySound(_T("res\\res\\bgm.wav"),SND_ASYNC | SND_LOOP);
	return 0;
}


void CBombingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case TIMER_PAINT:
		{
			CBombingDlg::OnPaint();
		}
		break;
	case TIMER_BALLOON:
		{
			i.balloon[i.ball].x++;
			i.balloon[i.ball].y++;
			if(i.balloon[i.ball].x==i.maxx)
			{
				i.showball = 0;
				i.showbomb = 1;
				KillTimer(TIMER_BALLOON);
				SetTimer(TIMER_BOMB,40,NULL);
			}
		}
		break;
	case TIMER_BOMB:
		{
			i.bomb.frame ++;
			if(i.bomb.frame == 11)
			{
				i.bomb.frame = 1;
				KillTimer(TIMER_BOMB);
				i.showbomb = 0;
				i.showball = 1;
				i.keydown = 0;
				i.ball = random(0,5);
				i.balloon[i.ball].x = 35;
				i.balloon[i.ball].y = 48;
				i.maxx = random(300,500);
			}
			i.bomb.load.Format(_T("res\\res\\b%d"),i.bomb.frame);
			i.bomb.pic.Destroy();
			i.bomb.pic.Load(i.bomb.load);
		}
		break;
	case TIMER_FEN:
		{
			i.feny--;
			if(i.feny==350)
			{
				i.ball = random(0,5);
				i.balloon[i.ball].x = 35;
				i.balloon[i.ball].y = 48;
				i.maxx = random(300,500);
				if(i.times == 10)
				{
					bools.end = 1;
					bools.game = 0;
				}
				bools.fen = 0;
				i.feny = 400;
				KillTimer(TIMER_FEN);
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CBombingDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//***************��������Ϣ��Ӧ
	/*w.begin.pic.Draw(m_cacheDC,300,250,570,120,0,w.begin.frame*120,570,120);
		w.end.pic.Draw(m_cacheDC,300,420,570,120,0,w.begin.frame*120,570,120);*/
	if(bools.main)
	{
		if(point.x>300&&point.x<870&&point.y>250&&point.y<370)
		{
			w.pointer = START;
			w.mousepoint = START;
		}
		else if(point.x>300&&point.x<870&&point.y>420&&point.y<540)
		{			
			w.pointer = QUIT;
			w.mousepoint = QUIT;
		}
		else
		{
			w.mousepoint = NONE;
		}
	}
	/*if(bools.quitdialog&&!bools.translation)
	{
		if(point.x>490&&point.x<653&&point.y>370&&point.y<445)
		{
			
			w.pointer = CONFIRM;
			w.mousepoint = CONFIRM;
		}
		else if(point.x>490&&point.x<672&&point.y>480&&point.y<560)
		{
			
			w.pointer = CANCEL;
			w.mousepoint = CANCEL;
		}
		else
		{
			w.mousepoint = NONE;
		}
	}
	else if(bools.startdialog&&!bools.translation)
	{
		if(point.x>490&&point.x<660&&point.y>370&&point.y<445)
		{
			
			w.pointer = CONFIRM;
			w.mousepoint = CONFIRM;
		}
		else if(point.x>490&&point.x<658&&point.y>480&&point.y<554)
		{
			
			w.pointer = CANCEL;
			w.mousepoint = CANCEL;
		}
		else
		{
			w.mousepoint = NONE;
		}
	}*/
	CDialogEx::OnMouseMove(nFlags, point);
}


void CBombingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(bools.main)
	{
		
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CBombingDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(bools.main)
	{
		if(w.pointer == START)//��ʼ
		{
			bools.main = 0;
			bools.game = 1;
			c.back.pic.Destroy();
			c.back.pic.Load(_T("res\\res\\gamebg"));
			i.showball = 1;
		}
		else if(w.pointer == QUIT)//����
		{			
			CDialogEx::OnOK();
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CBombingDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CBombingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			{
				if(bools.main)
				{
					switch(w.pointer)
					{
					case START:
						{
							bools.main = 0;
							bools.game = 1;
							c.back.pic.Destroy();
							c.back.pic.Load(_T("res\\res\\gamebg"));
							i.showball = 1;
						}
						break;
					case QUIT:
						{
							CDialogEx::OnOK();
							return TRUE;
						}
					}
				}
				return TRUE;
			}
			break;
		case VK_ESCAPE:{return TRUE;}break;
		case VK_UP:
			{
				if(w.pointer == QUIT)
					w.pointer=START;
				else if(w.pointer == START)
					w.pointer=QUIT;
			}
			break;
		case VK_DOWN:
			{
				if(w.pointer == QUIT)
					w.pointer=START;
				else if(w.pointer == START)
					w.pointer=QUIT;
			}
			break;
		case VK_SPACE:
			{
				if(bools.game&&i.showball)
				{
					if(!i.keydown&&!bools.fen)
					{
						SetTimer(TIMER_BALLOON,10,NULL);
						i.keydown = 1;
						i.times++;
					}
					else if(i.keydown&&!bools.fen)
					{
						KillTimer(TIMER_BALLOON);
						i.keydown = 0;
						i.fen = 10000/(i.maxx-i.balloon[i.ball].x);
						i.score = i.score + i.fen;
						bools.fen = 1;
						SetTimer(TIMER_FEN,20,NULL);
					}
				}
				if(bools.end)
				{
					bools.end = 0;
					bools.main = 1;
					i.showball = 0;
					c.back.pic.Destroy();
					c.back.pic.Load(_T("res\\res\\start"));
					//��ʼ��ͼƬ֡
					w.begin.frame = 0;
					w.end.frame = 0;
					i.bomb.frame = 1;
					//��ʼ������
					for(int t = 0;t<6;t++)
					{
						i.balloon[t].x = 35;
						i.balloon[t].y = 48;
					}
					w.pointer = START;
					bools.main = 1;
					bools.game = 0;
					bools.end = 0;
					bools.fen = 0;
					i.showball = 0;
					i.showbomb = 0;
					i.score = 0;
					i.maxx = random(300,500);
					i.keydown = 0;
					i.times = 0;
					i.feny = 400;
				}
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
