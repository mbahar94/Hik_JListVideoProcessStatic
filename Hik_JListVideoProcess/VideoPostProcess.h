#pragma once
//��ȡ�ĵ�ǰ��������ǰ��ͼ����д���
#include "GaussTargetBuffer.h"
class VideoPostProcess
{
public:
	VideoPostProcess(void);
	~VideoPostProcess(void);
	bool initVPP(GaussTargetBuffer *GaussBuffer,GaussTargetBuffer *GaussBuffer2);//��ʼ����Ƶ����Ŀ��ֵ
	bool initVPP(GaussTargetBuffer *GaussBuffer,GaussTargetBuffer *GaussBuffer2,HWND hwndClimb);//��ʼ����Ƶ����Ŀ��ֵ
	bool initVPP(GaussTargetBuffer *GaussBuffer,GaussTargetBuffer *GaussBuffer2,GaussTargetBuffer *GaussBuffer3);//��ʼ����Ƶ����Ŀ��ֵ
	//bool ClimbDetect(GaussTargetBuffer *GaussBuffer,GaussTargetBuffer *GaussBuffer2);
	bool ClimbDetect();//�ʸ߼��
	bool AreaDetect();//������
private:
	GaussTargetBuffer *m_pGaussBuffer,*m_pGaussBuffer2,*m_pGaussBuffer3;
	HWND m_hwndClimb;
};

