#include "stdafx.h"
#include "GaussTargetFrame.h"


GaussTargetFrame::GaussTargetFrame(void)
{
	m_pForeGroundImage=nullptr;
	m_pCurrentImage=nullptr;
	m_pBackGroundImage=nullptr;
	m_bProcessing=false;
	m_bWriting=true;//Ϊ�˷�ֹ�����δд���ͼ�����Կ�ʼ������д����״̬��
}


GaussTargetFrame::~GaussTargetFrame(void)
{

}
