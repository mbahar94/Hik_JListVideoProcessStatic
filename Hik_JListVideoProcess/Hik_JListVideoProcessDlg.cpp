
// Hik_JListVideoProcessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Hik_JListVideoProcess.h"
#include "Hik_JListVideoProcessDlg.h"
#include "ReceiveVideoData.h"
#include "VideoDataBuffer.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 //bool flagThreadExit = false;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHik_JListVideoProcessDlg �Ի���



CHik_JListVideoProcessDlg::CHik_JListVideoProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHik_JListVideoProcessDlg::IDD, pParent)
	, m_bisNetOpen(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHik_JListVideoProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHik_JListVideoProcessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Login, &CHik_JListVideoProcessDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_Start, &CHik_JListVideoProcessDlg::OnBnClickedButtonStart)
//	ON_BN_CLICKED(IDCANCEL, &CHik_JListVideoProcessDlg::OnBnClickedCancel)
ON_BN_CLICKED(IDC_BUTTON_ShowRGB, &CHik_JListVideoProcessDlg::OnBnClickedButtonShowrgb)
ON_BN_CLICKED(IDC_BUTTON_GaussBK, &CHik_JListVideoProcessDlg::OnBnClickedButtonGaussbk)
ON_BN_CLICKED(IDC_BUTTON_Capture, &CHik_JListVideoProcessDlg::OnBnClickedButtonCapture)
ON_BN_CLICKED(IDC_BUTTON_Open, &CHik_JListVideoProcessDlg::OnBnClickedButtonOpen)
ON_BN_CLICKED(IDC_BUTTON_CLIMBdet, &CHik_JListVideoProcessDlg::OnBnClickedButtonClimbdet)
ON_BN_CLICKED(IDC_BUTTON_GaussBK2, &CHik_JListVideoProcessDlg::OnBnClickedButtonGaussbk2)
ON_BN_CLICKED(IDC_BUTTON_GaussBK3, &CHik_JListVideoProcessDlg::OnBnClickedButtonGaussbk3)
ON_BN_CLICKED(IDC_BUTTON_AreaDet, &CHik_JListVideoProcessDlg::OnBnClickedButtonAreadet)
ON_BN_CLICKED(IDC_BUTTON_Open2s, &CHik_JListVideoProcessDlg::OnBnClickedButtonOpen2s)
 ON_MESSAGE(WM_USER_THREADEND, OnUserThreadend) 
  ON_MESSAGE(WM_USER_THREADEND2, OnUserThreadend2) 
END_MESSAGE_MAP()


// CHik_JListVideoProcessDlg ��Ϣ�������

BOOL CHik_JListVideoProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_hwndclimb=GetSafeHwnd();
	m_hscreen=GetDlgItem(IDC_STATIC_hscreen)->GetSafeHwnd();
	m_hscreen2=GetDlgItem(IDC_STATIC_hscreen2)->GetSafeHwnd();
	m_hscreen3=GetDlgItem(IDC_STATIC_hscreen3)->GetSafeHwnd();
	m_cWnd=GetDlgItem(IDC_STATIC_PostScreen);
	m_winThread=NULL;
	SetDlgItemText(IDC_EDIT_ClimbDet1,"�޾�����Ϣ��"); 
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHik_JListVideoProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHik_JListVideoProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHik_JListVideoProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHik_JListVideoProcessDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_ReceiveData.InitHKNET_DVR();//��ʼ����������
	if (!m_ReceiveData.login())
	{
		//AfxMessageBox("¼���ļ����ڲ��ţ�����ͣ��");
		//NET_DVR_Cleanup();
		return ;
	}
	m_bisNetOpen=true;
}
LRESULT CHik_JListVideoProcessDlg::OnUserThreadend(WPARAM wParam, LPARAM lParam) //�Զ�����Ϣ��Ӧ
{
	SetDlgItemText(IDC_EDIT_ClimbDet1,"��ע�⣬���ʸ߿����ԣ����棡��");//UpdateData(false);//TRACE("WM_USER_THREADEND message /n");
	
	return 0;
}
LRESULT CHik_JListVideoProcessDlg::OnUserThreadend2(WPARAM wParam, LPARAM lParam) //�Զ�����Ϣ��Ӧ2 ��ʾ�޾���
{
	SetDlgItemText(IDC_EDIT_ClimbDet1,"�޾�����Ϣ����");//UpdateData(false);//TRACE("WM_USER_THREADEND message /n");

	return 0;
}      

void CHik_JListVideoProcessDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!flagThreadExit)//�ͷ��߳�
	{
		flagThreadExit=true;
		//m_winThread=nullptr;
	}
	else
		flagThreadExit=false;
	if(m_winThread!=NULL) 
	{
		PostThreadMessage(m_winThread->m_nThreadID,WM_QUIT,0,0);
		m_winThread=nullptr;
	}
	if (m_VideoBuffer.GetDeep()<0)
	{
		m_VideoBuffer.Initial(704,576,704*576*3,10);//�̶�����
		m_VideoBuffer2.Initial(704,576,704*576*3,10);//�̶�����
		m_VideoBuffer3.Initial(704,576,704*576*3,10);//�̶�����
		m_GaussVideoBuffer.Initial(704,576,704*576,10);//��ʼ����˹
		m_GaussVideoBuffer2.Initial(704,576,704*576,10);//��ʼ����˹
		m_GaussVideoBuffer3.Initial(704,576,704*576,10);//��ʼ����˹
		m_ReceiveData.InitVideoBuffer(&m_VideoBuffer,&m_VideoBuffer2,&m_VideoBuffer3);//��ʼ��
	}
	//else flagThreadExit=true;
	//else m_winThread->ExitInstance();
	//else AfxEndThread(m_winThread->m_nThreadID);
	else 
		{
			/*if (!flagThreadExit)
			{
				flagThreadExit=true;
			}
			else
				flagThreadExit=false;*/
		
		}
	m_ReceiveData.ShowOriginalVideo(m_hscreen,m_hscreen2,m_hscreen3,m_bisNetOpen,m_spath,m_spath2);
}


//void CHik_JListVideoProcessDlg::OnBnClickedCancel()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDialogEx::OnCancel();
//}


/////////////////////////////////////////////////////////�߳�
UINT ThreadProcessRGB(LPVOID pParam)//�����̣߳���ʾRGB
{
	CHik_JListVideoProcessDlg *l_pVPD=(CHik_JListVideoProcessDlg *)pParam;
	l_pVPD->m_VideoProcess.Initiate(704,576,704*576*3,&l_pVPD->m_VideoBuffer,l_pVPD->m_cWnd);
	l_pVPD->m_VideoProcess.ShowVideoRGB();
	//l_pVPD->m_VideoProcess.ShowGaussBG();
	return 0;
}
//ͨ��һ
UINT ThreadProcessGauss(LPVOID pParam)//�����̣߳������˹����ʾ��˹���
{
	CHik_JListVideoProcessDlg *l_pVPD=(CHik_JListVideoProcessDlg *)pParam;
	//l_pVPD->m_VideoProcess.Initiate(704,576,704*576*3,&l_pVPD->m_VideoBuffer,l_pVPD->m_cWnd);//ԭ������
	l_pVPD->m_VideoProcess.Initiate(704,576,704*576*3,&l_pVPD->m_VideoBuffer,&l_pVPD->m_VideoBuffer2,&l_pVPD->m_GaussVideoBuffer,&l_pVPD->m_GaussVideoBuffer2,l_pVPD->m_cWnd,l_pVPD->m_bisNetOpen);//���صļӸ�˹Ŀ�걣�溯��
	//l_pVPD->m_VideoProcess.ShowVideoRGB();
	//l_pVPD->m_VideoProcess.ShowGaussBG();
	l_pVPD->m_VideoProcess.SaveGaussResults();//Ŀǰ���漰չʾ������ģ
	return 0;
}
//ͨ��2
UINT ThreadProcessGauss2(LPVOID pParam)//�����̣߳������˹����ʾ��˹���
{
	CHik_JListVideoProcessDlg *l_pVPD=(CHik_JListVideoProcessDlg *)pParam;
	//l_pVPD->m_VideoProcess.Initiate(704,576,704*576*3,&l_pVPD->m_VideoBuffer,l_pVPD->m_cWnd);//ԭ������
	l_pVPD->m_VideoProcess.Initiate(704,576,704*576*3,&l_pVPD->m_VideoBuffer,&l_pVPD->m_VideoBuffer2,&l_pVPD->m_GaussVideoBuffer,&l_pVPD->m_GaussVideoBuffer2,l_pVPD->m_cWnd,l_pVPD->m_bisNetOpen);//���صļӸ�˹Ŀ�걣�溯��
	//l_pVPD->m_VideoProcess.ShowVideoRGB();
	//l_pVPD->m_VideoProcess.ShowGaussBG();
	l_pVPD->m_VideoProcess.SaveGaussResults2();//Ŀǰ���漰չʾ������ģ
	return 0;
}
//ͨ��3�ص�����
UINT ThreadProcessGauss3(LPVOID pParam)//�����̣߳������˹����ʾ��˹���
{
	CHik_JListVideoProcessDlg *l_pVPD=(CHik_JListVideoProcessDlg *)pParam;
	//l_pVPD->m_VideoProcess.Initiate(704,576,704*576*3,&l_pVPD->m_VideoBuffer,l_pVPD->m_cWnd);//ԭ������
	l_pVPD->m_VideoProcess.Initiate(704,576,704*576*3,&l_pVPD->m_VideoBuffer,&l_pVPD->m_VideoBuffer2,&l_pVPD->m_VideoBuffer3,&l_pVPD->m_GaussVideoBuffer,&l_pVPD->m_GaussVideoBuffer2,&l_pVPD->m_GaussVideoBuffer3,l_pVPD->m_cWnd,l_pVPD->m_bisNetOpen);//���صļӸ�˹Ŀ�걣�溯��
	//l_pVPD->m_VideoProcess.ShowVideoRGB();
	//l_pVPD->m_VideoProcess.ShowGaussBG();
	l_pVPD->m_VideoProcess.SaveGaussResults3();//Ŀǰ���漰չʾ������ģ
	return 0;
}
//�����̣߳������ʸ�
UINT ThreadProcessClimbDet(LPVOID pParam)//�����߳�
{
	CHik_JListVideoProcessDlg *l_pVPD2=(CHik_JListVideoProcessDlg *)pParam;
	
	l_pVPD2->m_VideoPostProcess.initVPP(&l_pVPD2->m_GaussVideoBuffer,&l_pVPD2->m_GaussVideoBuffer2,l_pVPD2->m_hwndclimb);//��ʼ��������
	//l_pVPD->m_VideoProcess.ShowVideoRGB();
	//l_pVPD->m_VideoProcess.ShowGaussBG();
	l_pVPD2->m_VideoPostProcess.ClimbDetect();//�ʸ߼��
	return 0;
}
//�����̣߳�������
UINT ThreadProcessAreaDet(LPVOID pParam)//�����߳�
{
	CHik_JListVideoProcessDlg *l_pVPD2=(CHik_JListVideoProcessDlg *)pParam;

	l_pVPD2->m_VideoPostProcess.initVPP(&l_pVPD2->m_GaussVideoBuffer,&l_pVPD2->m_GaussVideoBuffer2,&l_pVPD2->m_GaussVideoBuffer3);///��ʼ��������
	//l_pVPD->m_VideoProcess.ShowVideoRGB();
	//l_pVPD->m_VideoProcess.ShowGaussBG();
	l_pVPD2->m_VideoPostProcess.AreaDetect();//������
	return 0;
}
void CHik_JListVideoProcessDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	/*NET_DVR_Logout_V30(userID);

	NET_DVR_Cleanup();	*/
	//g_pVideoBuffer=NULL;
	//m_winThread->ExitInstance();
	//_CrtDumpMemoryLeaks();
	//m_winThread->m_bAutoDelete=false;//�ֶ�ɾ��
	//
	//if (m_winThread)
	//{
	//	
	//	delete m_winThread;
	//	m_winThread=NULL;
	//}
	//AfxEndThread(m_winThread->m_nThreadID);
	
	if(m_ReceiveData.CloseVideo())
	{
		
		CDialogEx::OnCancel();
	}
	else
	{
		return;
	}
}


void CHik_JListVideoProcessDlg::OnBnClickedButtonShowrgb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_winThread!=NULL) 
	{
		PostThreadMessage(m_winThread->m_nThreadID,WM_QUIT,0,0);
		m_winThread=nullptr;
	}
	else

		//m_winThread=new CWinThread;
	/*if (m_winThread)
	{
		if (!flagThreadExit)
		{
			flagThreadExit=true;
		}
		else
		{flagThreadExit=false;AfxBeginThread(ThreadProcessRGB,this);}
	}
	else*/
		m_winThread=AfxBeginThread(ThreadProcessRGB,this);
	
	/*m_VideoProcess.Initiate(704,576,704*576*3,&m_VideoBuffer,m_cWnd);
	m_VideoProcess.ShowVideoRGB();*/
}


void CHik_JListVideoProcessDlg::OnBnClickedButtonGaussbk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(m_winThread!=NULL) 
	{
		PostThreadMessage(m_winThread->m_nThreadID,WM_QUIT,0,0);
		m_winThread=nullptr;
	}
	else
	/*if (m_winThread)
	{
		if (!flagThreadExit)
		{
			flagThreadExit=true;
		}
		else
		{flagThreadExit=false;AfxBeginThread(ThreadProcessRGB,this);}
	}
	else*/
		m_winThread=AfxBeginThread(ThreadProcessGauss,this);
	
	/*if (m_winThread)
	{
	if (!flagThreadExit)
	{
	flagThreadExit=true;
	m_winThread=nullptr;
	}
	else
	{flagThreadExit=false;AfxBeginThread(ThreadProcessGauss,this);}
	}
	else
	{flagThreadExit=false;m_winThread=AfxBeginThread(ThreadProcessGauss,this);}*/

}


void CHik_JListVideoProcessDlg::OnBnClickedButtonCapture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;//="save";str=str+num;
	static int num=0;
	str.Format("..\\CaptureImage\\save%d.bmp",num++);
	cvSaveImage(str,m_GaussVideoBuffer.m_gaussTargetBuffer[(m_GaussVideoBuffer.writeTargetLocation-1+m_GaussVideoBuffer.GetDeep())%m_GaussVideoBuffer.GetDeep()].m_pForeGroundImage);
}


void CHik_JListVideoProcessDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if(!m_ReceiveData.Open())
	{
		AfxMessageBox("���������ڲ��ţ�����ͣ��");
		return;
	}
	if (m_ReceiveData.m_userID>=0)
	{
		NET_DVR_Logout_V30(m_ReceiveData.m_userID);
		m_ReceiveData.m_userID=-1;
		NET_DVR_Cleanup();	
	}

	m_bisNetOpen=false;
	CFileDialog dlg(TRUE,_T("*.mp4"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST/*|OFN_HIDEREADONLY*/
		,_T("image files (*.mp4;*.jpg)|*.mp4;*.jpg|ALL Files(*.*)|*.*||"),NULL); // ѡ����Ƶ��Լ��
	dlg.m_ofn.lpstrTitle=_T("Open Image"); // ���ļ��Ի���ı�����
	if (dlg.DoModal()!=IDOK)
	{
		return; // �ж��Ƿ�����Ƶ
	}
	m_spath=dlg.GetPathName(); // ��ȡ��Ƶ·��
	

}


void CHik_JListVideoProcessDlg::OnBnClickedButtonClimbdet()//�ʸ߼��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_winThreadClimbDet!=NULL) 
	{
		PostThreadMessage(m_winThreadClimbDet->m_nThreadID,WM_QUIT,0,0);
		m_winThreadClimbDet=nullptr;
	}
	else
	
		m_winThreadClimbDet=AfxBeginThread(ThreadProcessClimbDet,this);
	
}


void CHik_JListVideoProcessDlg::OnBnClickedButtonGaussbk2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_winThread2!=NULL) 
	{
		PostThreadMessage(m_winThread2->m_nThreadID,WM_QUIT,0,0);
		m_winThread2=nullptr;
	}
	else

		m_winThread2=AfxBeginThread(ThreadProcessGauss2,this);
	

}


void CHik_JListVideoProcessDlg::OnBnClickedButtonGaussbk3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_winThread3!=NULL) 
	{
		PostThreadMessage(m_winThread3->m_nThreadID,WM_QUIT,0,0);
		m_winThread3=nullptr;
	}
	else

		m_winThread3=AfxBeginThread(ThreadProcessGauss3,this);

}


void CHik_JListVideoProcessDlg::OnBnClickedButtonAreadet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_winThreadAreaDet!=NULL) 
	{
		PostThreadMessage(m_winThreadAreaDet->m_nThreadID,WM_QUIT,0,0);
		m_winThreadAreaDet=nullptr;
	}
	else

		m_winThreadAreaDet=AfxBeginThread(ThreadProcessAreaDet,this);
}


void CHik_JListVideoProcessDlg::OnBnClickedButtonOpen2s()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_ReceiveData.Open())
	{
		AfxMessageBox("���������ڲ��ţ�����ͣ��");
		return;
	}
	if (m_ReceiveData.m_userID>=0)
	{
		NET_DVR_Logout_V30(m_ReceiveData.m_userID);
		m_ReceiveData.m_userID=-1;
		NET_DVR_Cleanup();	
	}

	m_bisNetOpen=false;
	m_spath="E:/FFOutput/ClimbDet/climb1.mp4";
	m_spath2="E:/FFOutput/ClimbDet/climb2.mp4";

}
