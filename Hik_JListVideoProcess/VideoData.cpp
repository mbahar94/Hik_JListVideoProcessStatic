#include "stdafx.h"
#include "VideoData.h"


VideoData::VideoData(void)
{
	m_pImage=NULL;
	m_bProcessing = false;
	m_bWriting = true;			//Ϊ�˷�ֹ�����δд���ͼ�����Կ�ʼ������д����״̬��
}


VideoData::~VideoData(void)
{
}
