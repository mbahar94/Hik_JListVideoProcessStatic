#include "stdafx.h"
#include "resource.h"
#include "ReceiveVideoData.h"

VideoDataBuffer *g_pVideoBuffer,*g_pVideoBuffer2,*g_pVideoBuffer3;//�������ݵ���������
LONG g_CurrentImageLocation=0,g_CurrentImageLocation2=0,g_CurrentImageLocation3=0;
LONG nPort=-1;LONG nPort2=-1;LONG nPort3=-1;
int g_Width=0,g_Height=0,g_Size=0,g_Width2=0,g_Height2=0,g_Size2=0,g_Width3=0,g_Height3=0,g_Size3=0;

	
//�������ݻص�����
void CALLBACK DecCBFun(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2)
{
	long lFrameType = pFrameInfo->nType;	
	g_Height=pFrameInfo->nHeight;g_Width=pFrameInfo->nWidth;
	if(lFrameType ==T_YV12)
	{	
		//ReceiveVideoData *CB_ReceiveBuffer=((ReceiveVideoData *)nReserved1);
		int BufferDeep=g_pVideoBuffer->GetDeep();
		if (g_pVideoBuffer->m_VideoBuffer[g_CurrentImageLocation].m_bProcessing==true)//������ڴ���д����һ֡
		{
			g_CurrentImageLocation=(g_CurrentImageLocation+1)%BufferDeep;
		}
		g_pVideoBuffer->m_VideoBuffer[g_CurrentImageLocation].m_bWriting=true;//��������д����ֹ����
		g_pVideoBuffer->m_VideoBuffer[(g_CurrentImageLocation-1+BufferDeep)%BufferDeep].m_bWriting=false;//�ָ�ǰһ֡
		memcpy(g_pVideoBuffer->m_VideoBuffer[g_CurrentImageLocation].m_pImage,((UCHAR*)pBuf),nSize);//д��
		g_CurrentImageLocation = (g_CurrentImageLocation + 1)%BufferDeep;
		

		//BYTE *data=NULL,*pBufTemp=NULL;
		//data=new BYTE[pFrameInfo->nWidth*pFrameInfo->nHeight*3];
		
		//YV12_to_RGB24((unsigned char*)pBuf/*pBufTemp*/,data,pFrameInfo->nWidth,pFrameInfo->nHeight);
		//IplImage *test=cvCreateImageHeader(cvSize(pFrameInfo->nWidth,pFrameInfo->nHeight), IPL_DEPTH_8U,3);
		//cvSetData(test,data,pFrameInfo->nWidth*3);
		//
		///*cvNamedWindow("Image",1);      //opencv��ʾ
		//cvShowImage("Image",test);
		//cvWaitKey(1);*/

		//
		//CRect rect;
		//h_screenpost=cpost->GetDC();
		//HDC hDC = h_screenpost ->GetSafeHdc();                // ��ȡ HDC(�豸���) �����л�ͼ����
		//cpost->GetClientRect(&rect);

		//
		//cimg.CopyOf( test );                            // ����ͼƬ
		//cimg.DrawToHDC( hDC, &rect );                // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
		//

		////�ͷ���Դ
		//delete data;
		//cvReleaseImageHeader(&test);
		//data=nullptr,pBufTemp=nullptr;
		//cimg.Destroy();

	}
	else
	{
		/*if(lFrameType ==T_UYVY)
		{

		}*/
	}

}
//�������ݻص�����2
void CALLBACK DecCBFun2(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2)
{
	long lFrameType2 = pFrameInfo->nType;	
	g_Height2=pFrameInfo->nHeight;g_Width2=pFrameInfo->nWidth;
	if(lFrameType2 ==T_YV12)
	{	
		//ReceiveVideoData *CB_ReceiveBuffer=((ReceiveVideoData *)nReserved1);
		int BufferDeep2=g_pVideoBuffer2->GetDeep();

		if (g_pVideoBuffer2->m_VideoBuffer[g_CurrentImageLocation2].m_bProcessing==true)//������ڴ���д����һ֡
		{
			g_CurrentImageLocation2=(g_CurrentImageLocation2+1)%BufferDeep2;
		}

		g_pVideoBuffer2->m_VideoBuffer[g_CurrentImageLocation2].m_bWriting=true;//�������ڴ�����ֹ����
		g_pVideoBuffer2->m_VideoBuffer[(g_CurrentImageLocation2-1+BufferDeep2)%BufferDeep2].m_bWriting=false;//�ָ�ǰһ֡
		memcpy(g_pVideoBuffer2->m_VideoBuffer[g_CurrentImageLocation2].m_pImage,((UCHAR*)pBuf),nSize);//д��
		g_CurrentImageLocation2 = (g_CurrentImageLocation2 + 1)%BufferDeep2;
		

	
	}
	

}
//�������ݻص�����3
void CALLBACK DecCBFun3(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2)
{
	long lFrameType3 = pFrameInfo->nType;	
	g_Height3=pFrameInfo->nHeight;g_Width3=pFrameInfo->nWidth;
	if(lFrameType3 ==T_YV12)
	{	
		//ReceiveVideoData *CB_ReceiveBuffer=((ReceiveVideoData *)nReserved1);
		int BufferDeep3=g_pVideoBuffer3->GetDeep();

		if (g_pVideoBuffer3->m_VideoBuffer[g_CurrentImageLocation3].m_bProcessing==true)//������ڴ���д����һ֡
		{
			g_CurrentImageLocation3=(g_CurrentImageLocation3+1)%BufferDeep3;
		}

		g_pVideoBuffer3->m_VideoBuffer[g_CurrentImageLocation3].m_bWriting=true;//�������ڴ�����ֹ����
		g_pVideoBuffer3->m_VideoBuffer[(g_CurrentImageLocation3-1+BufferDeep3)%BufferDeep3].m_bWriting=false;//�ָ�ǰһ֡
		memcpy(g_pVideoBuffer3->m_VideoBuffer[g_CurrentImageLocation3].m_pImage,((UCHAR*)pBuf),nSize);//д��
		g_CurrentImageLocation3 = (g_CurrentImageLocation3 + 1)%BufferDeep3;



	}


}
//ʵʱ���ص�
void CALLBACK fRealDataCallBack(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,void *pUser)
{
	DWORD dRet;
	//g_pVideoBuffer=((ReceiveVideoData*)pUser)->m_pVideoBuffer;
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:
		if (!PlayM4_GetPort(&nPort))
		{
			break;
		}
		if (!PlayM4_OpenStream(nPort,pBuffer,dwBufSize,1024*1024))
		{
			dRet=PlayM4_GetLastError(nPort);
			break;
		}
		
		//���ý���ص����� ֻ���벻��ʾ
		 		/*if (!PlayM4_SetDecCallBack(nPort,DecCBFun))
		 		{
		 			dRet=PlayM4_GetLastError(nPort);
		 			break;
		 		}*/

		//���ý���ص����� ��������ʾ
		if (!PlayM4_SetDecCallBackEx(nPort,DecCBFun,NULL,NULL))
		{
			dRet=PlayM4_GetLastError(nPort);
			break;
		}

		//����Ƶ����
		if (!PlayM4_Play(nPort,((ReceiveVideoData*)pUser)->m_hscreen))
		{
			dRet=PlayM4_GetLastError(nPort);
			break;
		}

		////����Ƶ����, ��Ҫ�����Ǹ�����
		if (!PlayM4_PlaySound(nPort))
		{
		dRet=PlayM4_GetLastError(nPort);
		break;
		}
		break;

	case NET_DVR_STREAMDATA:
		BOOL inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
		while (!inData)
		{
			Sleep(10);
			inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
			//OutputDebugString("PlayM4_InputData failed \n");	
		}
		
	}		
}

//ʵʱ���ص�2
void CALLBACK fRealDataCallBack2(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,void *pUser)
{
	DWORD dRet;
	//g_pVideoBuffer=((ReceiveVideoData*)pUser)->m_pVideoBuffer;
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:
		if (!PlayM4_GetPort(&nPort2))
		{
			break;
		}
		if (!PlayM4_OpenStream(nPort2,pBuffer,dwBufSize,1024*1024))
		{
			dRet=PlayM4_GetLastError(nPort2);
			break;
		}
		
		//���ý���ص����� ֻ���벻��ʾ
		 		/*if (!PlayM4_SetDecCallBack(nPort,DecCBFun))
		 		{
		 			dRet=PlayM4_GetLastError(nPort);
		 			break;
		 		}*/

		//���ý���ص����� ��������ʾ
		if (!PlayM4_SetDecCallBackEx(nPort2,DecCBFun2,NULL,NULL))
		{
			dRet=PlayM4_GetLastError(nPort2);
			break;
		}

		//����Ƶ����
		if (!PlayM4_Play(nPort2,((ReceiveVideoData*)pUser)->m_hscreen2))
		{
			dRet=PlayM4_GetLastError(nPort2);
			break;
		}

		////����Ƶ����, ��Ҫ�����Ǹ�����
		if (!PlayM4_PlaySound(nPort2))
		{
		dRet=PlayM4_GetLastError(nPort2);
		break;
		}
		break;

	case NET_DVR_STREAMDATA:
		BOOL inData=PlayM4_InputData(nPort2,pBuffer,dwBufSize);
		while (!inData)
		{
			Sleep(10);
			inData=PlayM4_InputData(nPort2,pBuffer,dwBufSize);
			//OutputDebugString("PlayM4_InputData failed \n");	
		}
		
	}		
}
//ʵʱ���ص�
void CALLBACK fRealDataCallBack3(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,void *pUser)
{
	DWORD dRet;
	//g_pVideoBuffer=((ReceiveVideoData*)pUser)->m_pVideoBuffer;
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:
		if (!PlayM4_GetPort(&nPort3))
		{
			break;
		}
		if (!PlayM4_OpenStream(nPort3,pBuffer,dwBufSize,1024*1024))
		{
			dRet=PlayM4_GetLastError(nPort3);
			break;
		}
		
		//���ý���ص����� ֻ���벻��ʾ
		 		/*if (!PlayM4_SetDecCallBack(nPort,DecCBFun))
		 		{
		 			dRet=PlayM4_GetLastError(nPort);
		 			break;
		 		}*/

		//���ý���ص����� ��������ʾ
		if (!PlayM4_SetDecCallBackEx(nPort3,DecCBFun3,NULL,NULL))
		{
			dRet=PlayM4_GetLastError(nPort3);
			break;
		}

		//����Ƶ����
		if (!PlayM4_Play(nPort3,((ReceiveVideoData*)pUser)->m_hscreen3))
		{
			dRet=PlayM4_GetLastError(nPort3);
			break;
		}

		////����Ƶ����, ��Ҫ�����Ǹ�����
		if (!PlayM4_PlaySound(nPort3))
		{
		dRet=PlayM4_GetLastError(nPort3);
		break;
		}
		break;

	case NET_DVR_STREAMDATA:
		BOOL inData=PlayM4_InputData(nPort3,pBuffer,dwBufSize);
		while (!inData)
		{
			Sleep(10);
			inData=PlayM4_InputData(nPort3,pBuffer,dwBufSize);
			//OutputDebugString("PlayM4_InputData failed \n");	
		}
		
	}		
}
ReceiveVideoData::ReceiveVideoData(void)
	: m_userID(-1)
	, m_bisOpenType(true)
	, m_sPath(_T("")),m_startRecordPlay(0),m_startRecordPlay2(0)
{
	m_pVideoBuffer=NULL;//new VideoDataBuffer;
	lRealPlayHandle=-1;
	lRealPlayHandle2=-1;
	lRealPlayHandle3=-1;
}


ReceiveVideoData::~ReceiveVideoData(void)
{
	 //m_pVideoBuffer=NULL;
	/*for (int i=0;i<m_pVideoBuffer->GetDeep();i++)
	{
	m_pVideoBuffer->m_VideoBuffer[0].m_pImage=NULL;
	}*/
}


bool ReceiveVideoData::InitHKNET_DVR(void)
{
	NET_DVR_Init();
	NET_DVR_SetConnectTime(2000,1);
	NET_DVR_SetReconnect(10000, true);

	return true;
}
bool ReceiveVideoData::login()//��¼
{
	if (m_userID>=0)
	{
		AfxMessageBox("���ѵ�¼�������ظ���¼��");
		return true;
	}
	if (m_startRecordPlay)
	{
		AfxMessageBox("¼���ļ����ڲ��ţ�����ͣ��");
		return false;
	}
	InitHKNET_DVR();//��ʼ��
	NET_DVR_DEVICEINFO_V30 l_struDeviceInfo;
	char *l_Username="admin";
	short l_Port=8000;
	char *l_Password="123456";
	char *l_ctrlDeviceIP="223.3.84.222";
	//short l_Channel=1;
	m_userID=NET_DVR_Login_V30(l_ctrlDeviceIP,l_Port,/*(LPSTR)(LPCTSTR)*/l_Username,/*(LPSTR)(LPCTSTR)*/l_Password,&l_struDeviceInfo);
	if (m_userID<0)
	{
		AfxMessageBox("��¼���������µ�¼��");
		//NET_DVR_Cleanup();
		return false;
	}
	else
	{
		AfxMessageBox("��¼�ɹ�!�������");
		return true;
	}

}
bool ReceiveVideoData::Open()
{
	if (lRealPlayHandle>=0)
	{
		return false;
	}
	else
	{
		//m_userID=-1;
		return true;
	}
}
//bool ReceiveVideoData::YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight)
//{
//	//unsigned char* pRGB24x;
//	if(!pYV12 || !pRGB24)
//		return false;
//	const long nYLen = long(iHeight * iWidth);
//	const int nHfWidth = (iWidth>>1);
//	if(nYLen<1 || nHfWidth<1) 
//		return false;
//	unsigned char* yData = pYV12;
//	unsigned char* vData = &yData[nYLen];
//	unsigned char* uData = &vData[nYLen>>2];
//	if(!uData || !vData)
//		return false;
//	
//	int rgb[3];
//	int i, j, m, n, x, y;
//	m = -iWidth;
//	n = -nHfWidth;
//	for(y=0; y < iHeight; y++)//zcx
//	{
//		for(x=0; x < iWidth; x++)
//		{
//			i = y*iWidth+x;//ÿ�����ص�
//			j = (y/2*iWidth/2+x/2);//ÿ�ĸ���Ҫһ��,ע���ʽ
//			rgb[2] = int(yData[i] + /*1.370705*/1.13983 * (vData[j] - 128)); // r����ֵ
//			rgb[1] = int(yData[i] - /*0.698001*/ 0.39465* (uData[j] - 128)  - /*0.703125 */0.58060* (vData[j] - 128)); // g����ֵ
//			rgb[0] = int(yData[i] + /*1.732446*/ 2.03211* (uData[j] - 128)); // b����ֵ
//			/*j = nYLen - iWidth - m + x;
//			i = (j<<1) + j;*/
//			i=i*3;//ÿ�����ر���3���ֽ�
//			for(j=0; j<3; j++)
//			{
//				if(rgb[j]>=0 && rgb[j]<=255)
//					pRGB24[i + j] = rgb[j];
//				else
//					pRGB24[i + j] = (rgb[j] < 0) ? 0 : 255;
//			}
//		}
//	}
//	return true;
//}

bool ReceiveVideoData::ShowOriginalVideo(HWND hscreen,HWND hscreen2,HWND hscreen3,bool isOpenType,CString mpath)
{
	m_bisOpenType=isOpenType;
	m_sPath=mpath;
	if(isOpenType)//�Ƿ���ļ������������豸
	{  
		if (lRealPlayHandle<0)
		{
			m_hscreen=hscreen;
			m_hscreen2=hscreen2;
			m_hscreen3=hscreen3;
			//����ͷ1
			NET_DVR_CLIENTINFO ClientInfo;
			ClientInfo.lChannel = m_pVideoBuffer->m_nChannel; //ͨ��Ҫ��################
			ClientInfo.hPlayWnd = nullptr;  //����Ϊ�գ��豸SDK������ֻȡ��
			ClientInfo.lLinkMode = 0;    //Main Stream
			ClientInfo.sMultiCastIP = NULL;
			lRealPlayHandle = NET_DVR_RealPlay_V30(m_userID,&ClientInfo,fRealDataCallBack,this,TRUE);
			/*if (!NET_DVR_PlayBackSaveData(lRealPlayHandle,"jlist.mp4"))
			{
				::MessageBoxA(0,"����ʧ��",0,0);

			}*/
			//bool tep=NET_DVR_SetRealDataCallBack(lRealPlayHandle,fRealDataCallBack2,0);//������
			//lRealPlayHandle =NET_DVR_RealPlay_V40(userID,&struPlayInfo,fRealDataCallBack,NULL);
			//����ͷ2
			NET_DVR_CLIENTINFO ClientInfo2;
			ClientInfo2.lChannel = m_pVideoBuffer->m_nChannel2; //ͨ��Ҫ��################
			ClientInfo2.hPlayWnd = nullptr;  //����Ϊ�գ��豸SDK������ֻȡ��
			ClientInfo2.lLinkMode = 0;    //Main Stream
			ClientInfo2.sMultiCastIP = NULL;
			lRealPlayHandle2 = NET_DVR_RealPlay_V30(m_userID,&ClientInfo2,fRealDataCallBack2,this,TRUE);


			//����ͷ3
			NET_DVR_CLIENTINFO ClientInfo3;
			ClientInfo3.lChannel = m_pVideoBuffer->m_nChannel3; //ͨ��Ҫ��################
			ClientInfo3.hPlayWnd = nullptr;  //����Ϊ�գ��豸SDK������ֻȡ��
			ClientInfo3.lLinkMode = 0;    //Main Stream
			ClientInfo3.sMultiCastIP = NULL;
			lRealPlayHandle3 = NET_DVR_RealPlay_V30(m_userID,&ClientInfo3,fRealDataCallBack3,this,TRUE);
			if (lRealPlayHandle<0||lRealPlayHandle2<0||lRealPlayHandle3<0)
			{
				CString ErrorNum;
				ErrorNum.Format("NET_DVR_RealPlay_V30 failed! Error number: %d\n",NET_DVR_GetLastError());
				AfxMessageBox(ErrorNum);
				return false;
			}
			//GetDlgItem(IDC_BUTTON_Start)->SetWindowTextA("��ͣ");
		}
		else
		{
			NET_DVR_StopRealPlay(lRealPlayHandle);
			NET_DVR_StopRealPlay(lRealPlayHandle2);//��һ��ͨ����ֹͣ
			NET_DVR_StopRealPlay(lRealPlayHandle3);
			lRealPlayHandle=-1;
			lRealPlayHandle2=-1;
			lRealPlayHandle3=-1;
			//m_userID=-1;
			//ֹͣ����
			if (nPort>-1)
			{
				if (!PlayM4_StopSound())
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_Stop(nPort))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_CloseStream(nPort))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				PlayM4_FreePort(nPort);
				nPort=-1;
			}		
			if (nPort2>-1)
			{
				if (!PlayM4_StopSound())
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_Stop(nPort2))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_CloseStream(nPort2))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				PlayM4_FreePort(nPort2);
				nPort2=-1;
			}		
			if (nPort3>-1)
			{
				if (!PlayM4_StopSound())
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_Stop(nPort3))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_CloseStream(nPort3))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				PlayM4_FreePort(nPort3);
				nPort3=-1;
			}		
			//GetDlgItem(IDC_BUTTON_Start)->SetWindowTextA("����");
		}
	}
	else//���ļ������Ǵ��ļ�
	{
		//static int StartPlay=1;
		if(!m_startRecordPlay)
		{
			PlayM4_GetPort(&nPort);
			PlayM4_OpenFile(nPort,(LPSTR)(LPCTSTR)mpath);
			BYTE *pBuffer;DWORD dwBufSize=0;
			if (!PlayM4_SetDecCallBackEx(nPort,DecCBFun,NULL,NULL))//�ص�����
			{
				PlayM4_GetLastError(nPort);

			}
			//����Ƶ����
			if (!PlayM4_Play(nPort,hscreen))
			{
				PlayM4_GetLastError(nPort);

			}
			m_startRecordPlay=true;
		}
		else
		{
			PlayM4_Stop(nPort);
			PlayM4_CloseFile(nPort);
			PlayM4_FreePort(nPort);
			m_startRecordPlay=false;
		}
		
	}
		return true;
}
bool ReceiveVideoData::ShowOriginalVideo(HWND hscreen,HWND hscreen2,HWND hscreen3,bool isOpenType,CString mpath,CString mpath2)
{
	m_bisOpenType=isOpenType;
	m_sPath=mpath;
	m_sPath2=mpath2;
	if(isOpenType)//�Ƿ���ļ������������豸
	{  
		if (lRealPlayHandle<0)
		{
			m_hscreen=hscreen;
			m_hscreen2=hscreen2;
			m_hscreen3=hscreen3;
			//����ͷ1
			NET_DVR_CLIENTINFO ClientInfo;
			ClientInfo.lChannel = m_pVideoBuffer->m_nChannel; //ͨ��Ҫ��################
			ClientInfo.hPlayWnd = nullptr;  //����Ϊ�գ��豸SDK������ֻȡ��
			ClientInfo.lLinkMode = 0;    //Main Stream
			ClientInfo.sMultiCastIP = NULL;
			lRealPlayHandle = NET_DVR_RealPlay_V30(m_userID,&ClientInfo,fRealDataCallBack,this,TRUE);
			/*if (!NET_DVR_PlayBackSaveData(lRealPlayHandle,"jlist.mp4"))
			{
				::MessageBoxA(0,"����ʧ��",0,0);

			}*/
			//bool tep=NET_DVR_SetRealDataCallBack(lRealPlayHandle,fRealDataCallBack2,0);//������
			//lRealPlayHandle =NET_DVR_RealPlay_V40(userID,&struPlayInfo,fRealDataCallBack,NULL);
			//����ͷ2
			NET_DVR_CLIENTINFO ClientInfo2;
			ClientInfo2.lChannel = m_pVideoBuffer->m_nChannel2; //ͨ��Ҫ��################
			ClientInfo2.hPlayWnd = nullptr;  //����Ϊ�գ��豸SDK������ֻȡ��
			ClientInfo2.lLinkMode = 0;    //Main Stream
			ClientInfo2.sMultiCastIP = NULL;
			lRealPlayHandle2 = NET_DVR_RealPlay_V30(m_userID,&ClientInfo2,fRealDataCallBack2,this,TRUE);


			//����ͷ3
			NET_DVR_CLIENTINFO ClientInfo3;
			ClientInfo3.lChannel = m_pVideoBuffer->m_nChannel3; //ͨ��Ҫ��################
			ClientInfo3.hPlayWnd = nullptr;  //����Ϊ�գ��豸SDK������ֻȡ��
			ClientInfo3.lLinkMode = 0;    //Main Stream
			ClientInfo3.sMultiCastIP = NULL;
			lRealPlayHandle3 = NET_DVR_RealPlay_V30(m_userID,&ClientInfo3,fRealDataCallBack3,this,TRUE);
			if (lRealPlayHandle<0||lRealPlayHandle2<0||lRealPlayHandle3<0)
			{
				CString ErrorNum;
				ErrorNum.Format("NET_DVR_RealPlay_V30 failed! Error number: %d\n",NET_DVR_GetLastError());
				AfxMessageBox(ErrorNum);
				return false;
			}
			//GetDlgItem(IDC_BUTTON_Start)->SetWindowTextA("��ͣ");
		}
		else
		{
			NET_DVR_StopRealPlay(lRealPlayHandle);
			NET_DVR_StopRealPlay(lRealPlayHandle2);//��һ��ͨ����ֹͣ
			NET_DVR_StopRealPlay(lRealPlayHandle3);
			lRealPlayHandle=-1;
			lRealPlayHandle2=-1;
			lRealPlayHandle3=-1;
			//m_userID=-1;
			//ֹͣ����
			if (nPort>-1)
			{
				if (!PlayM4_StopSound())
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_Stop(nPort))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_CloseStream(nPort))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				PlayM4_FreePort(nPort);
				nPort=-1;
			}		
			if (nPort2>-1)
			{
				if (!PlayM4_StopSound())
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_Stop(nPort2))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_CloseStream(nPort2))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				PlayM4_FreePort(nPort2);
				nPort2=-1;
			}		
			if (nPort3>-1)
			{
				if (!PlayM4_StopSound())
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_Stop(nPort3))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				if (!PlayM4_CloseStream(nPort3))
				{
					//bRet1=PlayM4_GetLastError(nPort);
				}
				PlayM4_FreePort(nPort3);
				nPort3=-1;
			}		
			//GetDlgItem(IDC_BUTTON_Start)->SetWindowTextA("����");
		}
	}
	else//���ļ������Ǵ��ļ�
	{
		//static int StartPlay=1;
		if(!m_startRecordPlay)
		{
			PlayM4_GetPort(&nPort);
			PlayM4_OpenFile(nPort,(LPSTR)(LPCTSTR)mpath);
			BYTE *pBuffer;DWORD dwBufSize=0;
			if (!PlayM4_SetDecCallBackEx(nPort,DecCBFun,NULL,NULL))//�ص�����
			{
				PlayM4_GetLastError(nPort);

			}
			//����Ƶ����
			if (!PlayM4_Play(nPort,hscreen))
			{
				PlayM4_GetLastError(nPort);

			}
			m_startRecordPlay=true;
		}
		else
		{
			PlayM4_Stop(nPort);
			PlayM4_CloseFile(nPort);
			PlayM4_FreePort(nPort);
			m_startRecordPlay=false;
		}
		if(!m_startRecordPlay2)
		{
			PlayM4_GetPort(&nPort2);
			PlayM4_OpenFile(nPort2,(LPSTR)(LPCTSTR)mpath2);
			BYTE *pBuffer;DWORD dwBufSize=0;
			if (!PlayM4_SetDecCallBackEx(nPort2,DecCBFun2,NULL,NULL))//�ص�����
			{
				PlayM4_GetLastError(nPort2);

			}
			//����Ƶ����
			if (!PlayM4_Play(nPort2,hscreen2))
			{
				PlayM4_GetLastError(nPort2);

			}
			m_startRecordPlay2=true;
		}
		else
		{
			PlayM4_Stop(nPort2);
			PlayM4_CloseFile(nPort2);
			PlayM4_FreePort(nPort2);
			m_startRecordPlay2=false;
		}
	}
		return true;
}
int ReceiveVideoData::InitVideoBuffer( VideoDataBuffer * t_pVideoDataBuffer )
{
	m_pVideoBuffer = t_pVideoDataBuffer;//������ָ������Ŀռ�
	g_pVideoBuffer = t_pVideoDataBuffer;
	//g_pVideoBuffer =t_pVideoDataBuffer;
	m_nWidth = g_Width;		//��ȡͼ�����704
	m_nHeight = g_Height;//576
	m_nChannel = 3;
	//m_nSize = g_Size;
	//if ( m_nDataType == HKCARD )
	//{
	//	m_nState = SetImageStream( hChannelHandle, 1, 0, m_nWidth, m_nHeight, m_ImageBuf);			//�����ص�����
	//	if ( m_nState != 0 )
	//	{
	//		MessageBox( NULL, " �����ص�����ʧ�� ", " error ", MB_OKCANCEL );
	//		return 0;
	//	}
	//}

	//if ( m_nDataType == NETCLIENT )
	//{
	//	g_pVideoDataBuffer = m_pVideoDataBuffer;

	//	if ( !MP4_ClientSetCapPicCallBack(0,NetClientCallBack2) )//�����ص�����
	//	{
	//		return 0;
	//	}
	//} 
	return 1;
}
int ReceiveVideoData::InitVideoBuffer( VideoDataBuffer * t_pVideoDataBuffer ,VideoDataBuffer * t_pVideoDataBuffer2)	//��ʼ��
{
	m_pVideoBuffer = t_pVideoDataBuffer;//������ָ������Ŀռ�
	g_pVideoBuffer = t_pVideoDataBuffer;
	//g_pVideoBuffer =t_pVideoDataBuffer;
	m_nWidth = g_Width;		//��ȡͼ�����704
	m_nHeight = g_Height;//576
	m_nChannel = 3;
	m_pVideoBuffer2 = t_pVideoDataBuffer2;//������ָ������Ŀռ�
	g_pVideoBuffer2 = t_pVideoDataBuffer2;
	return 1;
}
int  ReceiveVideoData::InitVideoBuffer( VideoDataBuffer * t_pVideoDataBuffer ,VideoDataBuffer * t_pVideoDataBuffer2,VideoDataBuffer * t_pVideoDataBuffer3)	//��ʼ��
{
	m_pVideoBuffer = t_pVideoDataBuffer;//������ָ������Ŀռ�
	g_pVideoBuffer = t_pVideoDataBuffer;
	//g_pVideoBuffer =t_pVideoDataBuffer;
	m_nWidth = g_Width;		//��ȡͼ�����704
	m_nHeight = g_Height;//576
	m_nChannel = 3;
	m_pVideoBuffer2 = t_pVideoDataBuffer2;//������ָ������Ŀռ�
	g_pVideoBuffer2 = t_pVideoDataBuffer2;
	m_pVideoBuffer3 = t_pVideoDataBuffer3;//������ָ������Ŀռ�
	g_pVideoBuffer3 = t_pVideoDataBuffer3;
	return true;
}
bool ReceiveVideoData::CloseVideo(void)
{
	if(lRealPlayHandle>=0||m_startRecordPlay)
	{
		AfxMessageBox("����ͣ����!");
		return false;
	}
	//g_pVideoBuffer=NULL;
	if (m_bisOpenType)
	{
		NET_DVR_Logout_V30(m_userID);
		m_userID=-1;
		NET_DVR_Cleanup();	
	}
	else
	{
		PlayM4_Stop(nPort);
		PlayM4_CloseFile(nPort);
		PlayM4_FreePort(nPort);
	}
	
	return true;
}
