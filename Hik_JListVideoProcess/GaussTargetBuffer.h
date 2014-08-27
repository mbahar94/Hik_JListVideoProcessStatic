#pragma once
#include "GaussTargetFrame.h"
#include <vector>
using namespace std;
class GaussTargetBuffer
{
public:
	GaussTargetBuffer(void);
	~GaussTargetBuffer(void);
public://����
	int m_nWidth;
	int m_nHeight;
	int m_nSize;//ͼ���С	
	int m_nChannel;
	int m_ndeepDegree;//���
	vector <GaussTargetFrame> m_gaussTargetBuffer;
	unsigned int writeTargetLocation;
public:
	bool Initial( int nWidth, int nHeight, int nSize, int nFrameDeep );		//��ʼ������
	int GetDeep(){return m_ndeepDegree;}
};

