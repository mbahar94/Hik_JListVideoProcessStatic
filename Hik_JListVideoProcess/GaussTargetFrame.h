#pragma once
class GaussTargetFrame
{
public:
	GaussTargetFrame(void);
	~GaussTargetFrame(void);
public:
	IplImage * m_pForeGroundImage;//ǰ��ͼ��
	IplImage * m_pCurrentImage;//��ǰͼ��
	IplImage * m_pBackGroundImage;//����ͼ��
	bool m_bProcessing;		//�Ƿ��ڴ�����
	bool m_bWriting;		//�Ƿ��ڽ�����������

};

