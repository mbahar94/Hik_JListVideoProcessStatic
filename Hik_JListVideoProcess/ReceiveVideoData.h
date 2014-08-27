#pragma once

#include "VideoDataBuffer.h"
#include "HCNetSDK.h"
#include "PlayM4.h"
#pragma comment(lib,"C:/Hik_lib/lib/HCNetSDK.lib")
#pragma comment(lib,"C:/Hik_lib/lib/PlayCtrl.lib")



class ReceiveVideoData
{
public:
	VideoDataBuffer *m_pVideoBuffer;
	VideoDataBuffer *m_pVideoBuffer2;
	VideoDataBuffer *m_pVideoBuffer3;

	LONG m_userID;
	LONG lRealPlayHandle;
	LONG lRealPlayHandle2;//��ȡ�����
	LONG lRealPlayHandle3;//��ȡ�����
	bool m_startRecordPlay;
	bool m_startRecordPlay2;
	HWND m_hscreen;//��ʾ���ھ��
	HWND m_hscreen2;//��ʾ���ھ��2
	HWND m_hscreen3;//��ʾ���ھ��3
	int m_nWidth;
	int m_nHeight;
	int m_nChannel;
	int m_nSize;
	
public:
	ReceiveVideoData(void);
	~ReceiveVideoData(void);
	//bool YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight);
	bool ShowOriginalVideo(HWND hscreen,HWND hscreen2,HWND hscreen3,bool isOpenType,CString mpath);
	bool ShowOriginalVideo(HWND hscreen,HWND hscreen2,HWND hscreen3,bool isOpenType,CString mpath,CString mpath2);
	int InitVideoBuffer( VideoDataBuffer * t_pVideoDataBuffer );	//��ʼ��
	int InitVideoBuffer( VideoDataBuffer * t_pVideoDataBuffer ,VideoDataBuffer * t_pVideoDataBuffer2);	//��ʼ��
	int InitVideoBuffer( VideoDataBuffer * t_pVideoDataBuffer ,VideoDataBuffer * t_pVideoDataBuffer2,VideoDataBuffer * t_pVideoDataBuffer3);	//��ʼ��
	bool InitHKNET_DVR(void);
	bool login();
	bool Open();
	int GetWidth(){return m_nWidth;}
	int GetHeight(){return m_nHeight;}
	int GetChannel(){return m_nChannel;}
	int GetSize(){return m_nSize;}
	bool CloseVideo(void);
	bool m_bisOpenType;
	CString m_sPath;
	CString m_sPath2;//����·��2
};
extern VideoDataBuffer *g_pVideoBuffer;
