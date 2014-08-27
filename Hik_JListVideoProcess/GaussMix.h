
#pragma once

#include "cv.h"
#include <vector>
using namespace std;


class GaussMix
{
public:
	GaussMix(void);
	~GaussMix(void);


//���к���
public:
	int Init( IplImage* m_pFrame, IplImage* m_pBkImg, IplImage* m_pFrImg );		//��ʼ������
	int UpdateRGB( IplImage* m_pFrame, IplImage* m_pBkImg, IplImage* m_pFrImg, int m_dCurrentFrameNumber );		//���±���
	int UpdateYUV( IplImage* m_pFrame, IplImage* m_pBkImg, IplImage* m_pFrImg, int m_dCurrentFrameNumber );
	int UpdateHSV( IplImage* m_pFrame, IplImage* m_pBkImg, IplImage* m_pFrImg, int m_dCurrentFrameNumber );
	int UpdateGray( IplImage* m_pFrame, IplImage* m_pBkImg, IplImage* m_pFrImg, int m_dCurrentFrameNumber );

//��˹ģ�ͻ��������趨
private:
	double m_dStdThreshold;				//�жϷ��ϵ�ǰ��ģ�͵ķ���ı��� /* lambda=2.5 is 99% */
	double m_dBackgroundThreshold;		//�ж�Ϊǰ���Ľ��ձ��� /* threshold sum of weights for background test */
	double m_dUpdataRateWeight;				//����Ȩ�صı���
	double m_dUpdataRateWeight2;	//Ϊ������ٶȣ������ظ������������
	double m_dUpdataRateMean;
	double m_dUpdataRateSigma;
	double m_dUpdataRateSigma2;
	double m_dWeightInit;				//��ʼȨ��
	int m_nGaussians;					//��˹ģ�͵Ĳ���
	double m_nSigmaInit;					//��ʼ����
	int m_nRefreshPercent;				//ÿ֡���µı���

//˽�к���
	public:
	int Update1( IplImage* m_pFrame, IplImage* m_pBkImg, int m_dCurrentFrameNumber );	//���ɱ��������������ָ��·�����״����

	int CountFrImage1( IplImage* m_pFrame, IplImage* m_pFrImg, int t_nOffset );	//����ǰ��ͼ��

//˽��������
private:
	int m_nImageWidth;			//ͼ����
	int m_nImageHeight;			//ͼ��߶�
	int m_nPixNumber;			//ͼ��������Ŀ
	int m_nDataSize;			//ͼ�����ݴ�С
	int m_nLineExpand;			//ͼ��ÿ�к������
	int m_nLineSize;			//ͼ��ÿ�е��ֽ���
	int m_nChannels;			//ͨ����

	vector <double *> m_pfBkMean;		//����ͼ���ֵ
	
	vector <double *> m_pfBkWeight;		//����ͼ��Ȩֵ

	vector <double *> m_pfBkSigma;		//����ͼ�񷽲�
};
