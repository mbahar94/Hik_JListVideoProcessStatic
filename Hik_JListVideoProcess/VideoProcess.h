#pragma once
//#include "VideoDataBuffer.h"
//class VideoDataBuffer;
#include "GaussTargetBuffer.h"
#include "ReceiveVideoData.h"
//class ReceiveVideoData;
#include "GaussMix.h"
#include "CamShift.h"
class VideoProcess  //��Ҫ����չʾЧ��
{
public:
	VideoProcess(void);
	~VideoProcess(void);
	bool YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight);
	bool Initiate( int nWidth, int nHeight, int nSize, VideoDataBuffer * t_VideoDataBuffer, CWnd  * t_pThis );	//��ʼ������ģ��
	bool Initiate( int nWidth, int nHeight, int nSize, VideoDataBuffer * t_VideoDataBuffer, GaussTargetBuffer *t_GaussBuffer,CWnd  * t_pThis );	//���س�ʼ������ģ��
	bool Initiate( int nWidth, int nHeight, int nSize, VideoDataBuffer * t_VideoDataBuffer,VideoDataBuffer * t_VideoDataBuffer2, 
		             GaussTargetBuffer *t_GaussBuffer,GaussTargetBuffer *t_GaussBuffer2,CWnd  * t_pThis ,bool opennNetType);	//���س�ʼ������ģ��2
	bool Initiate( int nWidth, int nHeight, int nSize, VideoDataBuffer * t_VideoDataBuffer,VideoDataBuffer * t_VideoDataBuffer2, VideoDataBuffer * t_VideoDataBuffer3,
		GaussTargetBuffer *t_GaussBuffer,GaussTargetBuffer *t_GaussBuffer2,GaussTargetBuffer *t_GaussBuffer3,CWnd  * t_pThis ,bool opennNetType);	//���س�ʼ������ģ��3
	bool ShowVideoRGB();//չʾRGB
	bool ShowGaussBG();//��ʾ��˹���
	bool SaveGaussResults();//�����˹���
	bool SaveGaussResults2();//�����˹��� ͨ��2
	bool SaveGaussResults3();//�����˹��� ͨ��3
	//��֤���Ժ���
	bool IntrusionDetection(IplImage *pForeImage,FILE *pfile);//�ж�������Ϣ
	bool SaveAnalylizeData(IplImage *pCurrentImage,IplImage *pBackImage);//����Դͼ�񡢱���ͼ���ݶȣ����ȱ仯
	bool FindGradient(IplImage *src,uchar *dst);//�����ݶ�
	bool AnalyzeLightData(IplImage *pCurrentImage,IplImage *pBackImage);//ͳ�ƿ������ȱ仯��������
public:
	int m_nWidth;
	int m_nHeight;
	int m_nSize;
	CWnd *m_pCwnd;//��ʾ��ָ��
	VideoDataBuffer *m_pVideoBuffer,*m_pVideoBuffer2,*m_pVideoBuffer3;//���ݻ�����
	GaussTargetBuffer *m_pGaussBuffer,*m_pGaussBuffer2,*m_pGaussBuffer3;//Ŀ�껺����
public://gauss funtion
	GaussMix m_MixGauss,m_MixGauss2,m_MixGauss3;
	CamShift m_camShift;
	int m_nImageNumber,m_nImageNumber2,m_nImageNumber3;	//��ǰ֡��
	IplImage * m_pFrountImage,*m_pFrountImage2,*m_pFrountImage3;//ǰ��ͼ��
	IplImage * m_pCurrentImage;//��ǰͼ��
	//IplImage * m_pLastImage;
	IplImage * m_pBackGroundImage,*m_pBackGroundImage2,*m_pBackGroundImage3;//����ͼ��
private:
	int m_openType; //���ļ�����
};

