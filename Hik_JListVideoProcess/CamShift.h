#pragma once
#include "cv.h"
#include "highgui.h"
class CamShift
{
public:
	CamShift(void);
	~CamShift(void);
public:
	//ѡ�������Ƿ�
	int m_selectObject,m_trackObject;
	int m_dims;
	IplImage *m_curImage,*m_hsv,*m_hue,*m_mask;
	CvRect m_selectedArea;
	CvRect m_trackWindow;//�ó��Ĵ���
	CvHistogram *m_hist;//ֱ��ͼ
	CvConnectedComp m_trackComp;//���Ӳ���
	IplImage *m_backProject;//����ͶӰͼ
	//CHistogram *hist;

	float m_hranges_arr[2]; //= {0,180};
	//����ֵ�ķ�Χ
	float* m_ranges ;//= hranges_arr;
	CvBox2D m_trackBox;
public:
	bool CamShiftProcess(IplImage *crtImage,CvRect srctw,CvRect newtw);
};

