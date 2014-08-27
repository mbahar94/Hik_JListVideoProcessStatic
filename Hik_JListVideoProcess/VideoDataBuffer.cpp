#include "stdafx.h"
#include "VideoDataBuffer.h"


VideoDataBuffer::VideoDataBuffer(void)
{
	m_nWidth = 0;
	m_nHeight = 0;
	m_nSize = 0;
	m_nChannel=1;
	m_nChannel2=2;
	m_nChannel3=3;
	m_nBufferDeep = -1;
}


VideoDataBuffer::~VideoDataBuffer(void)
{
	int i;
	for ( i = 0; i < m_nBufferDeep; i++ )
	{
		if ( m_VideoBuffer[i].m_pImage != NULL )
		{
			delete m_VideoBuffer[i].m_pImage;
			m_VideoBuffer[i].m_pImage=NULL;
		}
	}

	m_VideoBuffer.clear();
}
bool VideoDataBuffer::Initial( int nWidth, int nHeight, int nSize, int nFrameDeep )
{	
	//ͼ�����
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nSize = nSize;

	//���������
	m_nBufferDeep = nFrameDeep;

	VideoData t_VideoDataPerFrame;		//��֡ͼ������

	int i;
	for ( i = 0; i < m_nBufferDeep; i++ )
	{
		//t_VideoDataPerFrame.m_nFrameNumber = i;			//���

		m_VideoBuffer.push_back( t_VideoDataPerFrame );			//���

		m_VideoBuffer[i].m_pImage = new UCHAR[ m_nSize ];		//���ٿռ�

		memset( m_VideoBuffer[i].m_pImage, 0, m_nSize );		//��ʼ���ռ�
	}

	return true;
}