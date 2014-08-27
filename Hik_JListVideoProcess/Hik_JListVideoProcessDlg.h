
// Hik_JListVideoProcessDlg.h : ͷ�ļ�
//

#pragma once
#include "receivevideodata.h"
#include "VideoProcess.h"
#include "VideoPostProcess.h"
//class VideoProcess;


// CHik_JListVideoProcessDlg �Ի���
class CHik_JListVideoProcessDlg : public CDialogEx
{
// ����
public:
	CHik_JListVideoProcessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HIK_JLISTVIDEOPROCESS_DIALOG };

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
public:
	CWinThread *m_winThread,*m_winThread2,*m_winThread3/*����Ԥ�����߳�*/,*m_winThreadClimbDet,*m_winThreadAreaDet;
	CWnd *m_cWnd;
	HWND m_hwndclimb;//�ʸ߾�����Ϣ��Ӧ���ھ��
	HWND m_hscreen;
	HWND m_hscreen2;//��ʾͨ��2
	HWND m_hscreen3;//��ʾͨ��3
	bool m_bisNetOpen;//��ģʽ���Ƿ���������
	CString m_spath;//���ļ�·��
	CString m_spath2;//���ļ�·��2
	VideoDataBuffer m_VideoBuffer,m_VideoBuffer2,m_VideoBuffer3;
	ReceiveVideoData m_ReceiveData;
	VideoProcess m_VideoProcess;
	GaussTargetBuffer m_GaussVideoBuffer,m_GaussVideoBuffer2,m_GaussVideoBuffer3;
	VideoPostProcess m_VideoPostProcess;
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonStart();
//	afx_msg void OnBnClickedCancel();	
	afx_msg void OnBnClickedButtonShowrgb();
	afx_msg void OnBnClickedButtonGaussbk();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonCapture();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClimbdet();//�ʸ߼��
	afx_msg void OnBnClickedButtonGaussbk2();//ͨ������˹ģ��
	afx_msg void OnBnClickedButtonGaussbk3();
	afx_msg void OnBnClickedButtonAreadet();//������
	afx_msg void OnBnClickedButtonOpen2s();
	afx_msg LRESULT OnUserThreadend(WPARAM wParam, LPARAM lParam);//�Զ�����Ϣ��Ӧ�����ʸ߼�⣬��ʾ������Ϣ
	afx_msg LRESULT OnUserThreadend2(WPARAM wParam, LPARAM lParam);//�Զ�����Ϣ��Ӧ�����ʸ߼�⣬��ʾ������Ϣ
};
