#pragma once
class VideoData
{
public:
	VideoData(void);
	~VideoData(void);
public:
	UCHAR *m_pImage;
	bool m_bProcessing;		//�Ƿ��ڴ�����
	bool m_bWriting;		//�Ƿ��ڽ�����������
};

