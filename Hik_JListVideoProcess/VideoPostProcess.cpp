#include "stdafx.h"
#include "VideoPostProcess.h"
#include "ReceiveVideoData.h"

VideoPostProcess::VideoPostProcess(void)
{
	m_pGaussBuffer = nullptr;
	m_pGaussBuffer2 = nullptr;
}


VideoPostProcess::~VideoPostProcess(void)
{
}
//��ʼ��
bool VideoPostProcess::initVPP(GaussTargetBuffer *GaussBuffer,GaussTargetBuffer *GaussBuffer2)//��ʼ��"��Ƶ����"Ŀ��ֵ
{
	m_pGaussBuffer = GaussBuffer;
	m_pGaussBuffer2 = GaussBuffer2;
	return true;
}
bool VideoPostProcess::initVPP(GaussTargetBuffer *GaussBuffer,GaussTargetBuffer *GaussBuffer2,HWND hwndClimb)//��ʼ��"��Ƶ����"Ŀ��ֵ,�Զ����ʸ���Ϣ��Ӧ
{
	m_pGaussBuffer = GaussBuffer;
	m_pGaussBuffer2 = GaussBuffer2;
	m_hwndClimb=hwndClimb;
	return true;
}
//��ʼ��
bool VideoPostProcess::initVPP(GaussTargetBuffer *GaussBuffer,GaussTargetBuffer *GaussBuffer2,GaussTargetBuffer *GaussBuffer3)//��ʼ��"��Ƶ����"Ŀ��ֵ��������
{
	m_pGaussBuffer = GaussBuffer;
	m_pGaussBuffer2 = GaussBuffer2;
	m_pGaussBuffer3 = GaussBuffer3;
	return true;
}
bool VideoPostProcess::ClimbDetect()
{
	MSG msg;//��Ϣ��Ϣ
	int t_ndeep=m_pGaussBuffer->GetDeep();
	int t_nTargetLocation=0;
	bool t_isClimb1=false,t_isClimb2=false;//�ж��Ƿ��ʸ�
	int t_width1,t_width2,t_height1,t_height2;//ͨ��һ���Ŀ��
	int t_numCountTime=0;//�ʸ�ʱ��������ͳ�ƴ�����
	FILE *t_fclimb;
	t_fclimb=fopen("..\\Log\\climbDet.txt","at+");
	while (true)
	{
		//ͨ��һ
		if (m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_bWriting==false)//��ǰ֡������д��
		{
			m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_bProcessing=true;//�õ�ǰ֡���ڴ���
			//����ģ��
			int t_SArea=0;
			t_width1=m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->width;
			t_height1=m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->height;
			for (int i=0;i<100;i++)
			{
				for(int j=0;j<t_width1;j++)
				{
					if (m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->imageData[i*t_width1+j])
					{
						t_SArea++;
					}
				}
			}
			if (t_SArea>100)
			{
				t_isClimb1=true;

			}
			else
			{
				t_isClimb1=false;
			}
			//m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_pCurrentImage;
			
			//CString str;//="save";str=str+num;
			//static int num2=0;
			//str.Format("..\\CaptureImage\\save%d.bmp",num2++);
			//cvSaveImage(str,m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_pCurrentImage);

			Sleep(100);//�Ӹ���ʱ

			m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_bProcessing=false;//�õ�ǰ֡���ڴ���
		}
		//ͨ����
		if (m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_bWriting==false)//��ǰ֡������д��
		{
			m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_bProcessing=true;//�õ�ǰ֡���ڴ���
			//����ģ��
			//m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_pCurrentImage;

			//CString str2;//="save";str=str+num;
			//static int num3=0;
			//str2.Format("..\\CaptureImage\\save2%d.bmp",num3++);
			//cvSaveImage(str2,m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_pCurrentImage);
			if (t_isClimb1)
			{
				int t_SArea2=0;
				t_width2=m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->width;
				t_height2=m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->height;
				for (int i=0;i<100;i++)
				{
					for(int j=0;j<t_width2;j++)
					{
						if (m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->imageData[i*t_width2+j])
						{
							t_SArea2++;
						}
					}
				}
				if (t_SArea2>100)
				{
					t_isClimb2=true;
				}
				else
				{
					t_isClimb2=false;
				}
			}
			else
				t_isClimb2=false;
			
			Sleep(100);//�Ӹ���ʱ(��ʱ��)
			m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_bProcessing=false;//�õ�ǰ֡���ڴ���
			
		}
		if (t_isClimb2)
		{
			t_numCountTime++;
			if (t_numCountTime>4)
			{
				char tmp[64];	
				LPNET_DVR_TIME mytime=new NET_DVR_TIME;mytime->dwDay=0;
				if (!NET_DVR_GetDVRConfig(0,NET_DVR_GET_TIMECFG,0xFFFFFFFF,mytime,sizeof(NET_DVR_TIME),LPDWORD(mytime)))
				{
					time_t t = time(0);
					strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A �����%j�죺",localtime(&t) ); 
				}
				else
				{
					sprintf(tmp,"%d/%d/%d %d:%d:%d: ",mytime->dwYear,mytime->dwMonth,mytime->dwDay,mytime->dwHour,mytime->dwMinute,mytime->dwSecond);
				}
				fwrite(tmp,strlen(tmp),1,t_fclimb);
				char l_c[]="�ʸ߾��棡\n";		
				fwrite(l_c,strlen(l_c),1,t_fclimb);
				//GetSafeHwnd();
				//UpdateData();
				PostMessage(m_hwndClimb,WM_USER_THREADEND, 0, 0);
				t_numCountTime=0;
				t_isClimb2=false;
				t_isClimb1=false;
				delete mytime;
			}
		}
		else
		{
			PostMessage(m_hwndClimb,WM_USER_THREADEND2, 0, 0);
			t_numCountTime=0;
			//t_isClimb2=false;
			t_isClimb1=false;
		}
		if (PeekMessage(&msg,0,0,0,0))
		{
			fclose(t_fclimb);
			AfxEndThread(0);//����յ���Ϣ�˳��߳�
			return true;
		}
		t_nTargetLocation++;//��ȡ��һ��Ŀ��
		t_nTargetLocation%=t_ndeep;
	}
	return true;
}
//������
bool VideoPostProcess::AreaDetect()
{
	MSG msg;//��Ϣ��Ϣ
	int t_ndeep=m_pGaussBuffer->GetDeep();
	int t_nTargetLocation=0;
	int t_width3,t_height3;//ͨ��3�Ŀ��
	int t_numCountFrameq=0,t_numCountFramer=0;
	FILE *t_fileArea;
	t_fileArea=fopen("..\\Log\\AreaDet.txt","at+");
	LPNET_DVR_TIME mytime=new NET_DVR_TIME;mytime->dwDay=0;
	while (true)
	{
		//ͨ��3
		if (m_pGaussBuffer3->m_gaussTargetBuffer[t_nTargetLocation].m_bWriting==false)//��ǰ֡������д��
		{
			m_pGaussBuffer3->m_gaussTargetBuffer[t_nTargetLocation].m_bProcessing=true;//�õ�ǰ֡���ڴ���
			//����ģ��
			
			//m_pGaussBuffer->m_gaussTargetBuffer[t_nTargetLocation].m_pCurrentImage;

			//CString str;//="save";str=str+num;
			//static int num2=0;
			//str.Format("..\\CaptureImage\\save%d.bmp",num2++);
			//cvSaveImage(str,m_pGaussBuffer3->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage);
			int t_SArea3=0;
			t_width3=m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->width;
			t_height3=m_pGaussBuffer2->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->height;
			for (int i=t_height3/3;i<t_height3/3*2;i++)
			{
				for(int j=t_width3/3;j<t_width3/3*2;j++)
				{
					if (m_pGaussBuffer3->m_gaussTargetBuffer[t_nTargetLocation].m_pForeGroundImage->imageData[i*t_width3+j])
					{
						t_SArea3++;
					}
				}
			}
			if (t_SArea3>600)
			{
				t_numCountFramer=0;
				t_numCountFrameq++;
				if (t_numCountFrameq>4)
				{
					char tmp[64];	
					
					if (!NET_DVR_GetDVRConfig(0,NET_DVR_GET_TIMECFG,0xFFFFFFFF,mytime,sizeof(NET_DVR_TIME),LPDWORD(mytime)))
					{
						time_t t = time(0);
						strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A �����%j�죺",localtime(&t) ); 
					}
					else
					{
						sprintf(tmp,"%d/%d/%d %d:%d:%d: ",mytime->dwYear,mytime->dwMonth,mytime->dwDay,mytime->dwHour,mytime->dwMinute,mytime->dwSecond);
					}
					fwrite(tmp,strlen(tmp),1,t_fileArea);
					char l_c[]="�г����룡\n";		
					fwrite(l_c,strlen(l_c),1,t_fileArea);
					t_numCountFrameq=0;
					
				}
			}
			else if(t_SArea3>100)
			{
				t_numCountFrameq=0;
				t_numCountFramer++;
				if (t_numCountFramer>4)
				{
					char tmp[64];	
					//LPNET_DVR_TIME mytime=new NET_DVR_TIME;mytime->dwDay=0;
					if (!NET_DVR_GetDVRConfig(0,NET_DVR_GET_TIMECFG,0xFFFFFFFF,mytime,sizeof(NET_DVR_TIME),LPDWORD(mytime)))
					{
						time_t t = time(0);
						strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A �����%j�죺",localtime(&t) ); 
					}
					else
					{
						sprintf(tmp,"%d/%d/%d %d:%d:%d: ",mytime->dwYear,mytime->dwMonth,mytime->dwDay,mytime->dwHour,mytime->dwMinute,mytime->dwSecond);
					}
					fwrite(tmp,strlen(tmp),1,t_fileArea);
					char l_c[]="���˴��룡\n";		
					fwrite(l_c,strlen(l_c),1,t_fileArea);
					t_numCountFramer=0;
				}
			}
			else
			{
				t_numCountFrameq=0;t_numCountFramer=0;
			}



			Sleep(100);//�Ӹ���ʱ

			m_pGaussBuffer3->m_gaussTargetBuffer[t_nTargetLocation].m_bProcessing=false;//�õ�ǰ֡���ڴ���
		}
		if (PeekMessage(&msg,0,0,0,0))
		{
			//fclose(t_fclimb);
			delete mytime;
			AfxEndThread(0);//����յ���Ϣ�˳��߳�
			return true;
		}
		t_nTargetLocation++;//��ȡ��һ��Ŀ��
		t_nTargetLocation%=t_ndeep;
	}
	return true;
}