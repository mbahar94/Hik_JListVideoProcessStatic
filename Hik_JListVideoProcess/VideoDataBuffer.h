#pragma once
#include "VideoData.h"

#include <vector>
using namespace std;
//class VideoData;
class VideoDataBuffer
{
public:	
	//ͼ�����
	int m_nWidth;
	int m_nHeight;
	int m_nSize;//ͼ���С	
	int m_nChannel;
	int m_nChannel2;//ͨ��2
	int m_nChannel3;//ͨ��3
	int m_nBufferDeep;		//���������
public:
	VideoDataBuffer(void);
	~VideoDataBuffer(void);
	vector<VideoData> m_VideoBuffer;//ͼ�񻺴���
public:
	bool Initial( int nWidth, int nHeight, int nSize, int nFrameDeep );		//��ʼ������
	int GetDeep(){return m_nBufferDeep;}
};

