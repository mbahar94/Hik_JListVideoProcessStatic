#include "stdafx.h"
#include "CamShift.h"
#include "ctype.h"

CamShift::CamShift(void)
{
	m_selectObject=0;
	m_trackObject=0;
	m_curImage=0;
	m_dims=48;//�ֳ�16��bins
	m_hranges_arr[0]=0,m_hranges_arr[1]=180;//= {1,180};
	m_ranges=m_hranges_arr;
;
}


CamShift::~CamShift(void)
{
	if (m_curImage)
	{
		cvReleaseImage(&m_curImage);
		cvReleaseImage(&m_hsv);
		cvReleaseImage(&m_hue);
		cvReleaseImage(&m_mask);
		cvReleaseImage(&m_backProject);
		cvReleaseHist(&m_hist);
	}
}
CvPoint origin;
void on_mouse( int event, int x, int y, int flags, void* param )
	//���ص�����,�ú����������и���Ŀ���ѡ��
{
	CamShift *pCamShift=(CamShift*)(param);
	if( !pCamShift->m_curImage )
		return;

	if( pCamShift->m_curImage->origin )
		y = pCamShift->m_curImage->height - y;
	//���ͼ��ԭ������������,�����Ϊ����

	if( pCamShift->m_selectObject )
		//select_objectΪ1,��ʾ����������Ŀ��ѡ��
			//��ʱ�Ծ�����selection�õ�ǰ�����λ�ý�������
	{
		pCamShift->m_selectedArea.x = MIN(x,origin.x);
		pCamShift->m_selectedArea.y = MIN(y,origin.y);
		pCamShift->m_selectedArea.width = pCamShift->m_selectedArea.x + CV_IABS(x - origin.x);
		pCamShift->m_selectedArea.height = pCamShift->m_selectedArea.y + CV_IABS(y - origin.y);
		//һ����Լ��
		pCamShift->m_selectedArea.x = MAX( pCamShift->m_selectedArea.x, 0 );
		pCamShift->m_selectedArea.y = MAX( pCamShift->m_selectedArea.y, 0 );
		pCamShift->m_selectedArea.width = MIN( pCamShift->m_selectedArea.width, pCamShift->m_curImage->width );
		pCamShift->m_selectedArea.height = MIN( pCamShift->m_selectedArea.height, pCamShift->m_curImage->height );
		pCamShift->m_selectedArea.width -= pCamShift->m_selectedArea.x;
		pCamShift->m_selectedArea.height -= pCamShift->m_selectedArea.y;
	}

	switch( event )
	{
	case CV_EVENT_LBUTTONDOWN:
		//��갴��,��ʼ���ѡ���������
		origin = cvPoint(x,y);
		pCamShift->m_selectedArea = cvRect(x,y,0,0);
		pCamShift->m_selectObject = 1;
		break;
	case CV_EVENT_LBUTTONUP:
		//����ɿ�,���ѡ���������
		pCamShift->m_selectObject = 0;
		if( pCamShift->m_selectedArea.width > 0 && pCamShift->m_selectedArea.height > 0 )
			//���ѡ��������Ч����򿪸��ٹ���
				pCamShift->m_trackObject = -1;
		break;
	}
}
bool CamShift::CamShiftProcess(IplImage *crtImage,CvRect srctw,CvRect newtw)
{
	if (!crtImage)
	return false;
	//cvSetMouseCallback( "CamShiftDemo", on_mouse, (void*)this);//�������ص�����
	if (m_trackObject==0)
	{
		m_selectedArea.x=240;
		m_selectedArea.y=150;
		m_selectedArea.width=200;
		m_selectedArea.height=100;
	}
	
	//m_trackObject=1;
	if (!m_curImage)//����ռ�
	{
		m_curImage=cvCreateImage(cvGetSize(crtImage),8,3);
		m_curImage->origin=crtImage->origin;
		m_hsv = cvCreateImage( cvGetSize(crtImage), 8, 3 );
		m_hue = cvCreateImage( cvGetSize(crtImage), 8, 1 );
		m_mask = cvCreateImage( cvGetSize(crtImage), 8, 1 );//������Ĥͼ��ռ�

		m_backProject = cvCreateImage( cvGetSize(crtImage), 8, 1 );//���䷴��ͶӰͼ�ռ�,��Сһ��,��ͨ��
		m_hist = cvCreateHist( 1, &m_dims, CV_HIST_ARRAY, &m_ranges, 1 );//����ֱ��ͼ�ռ�

	}
	cvCopy(crtImage,m_curImage,0);
	cvCvtColor(m_curImage,m_hsv,CV_BGR2HSV);//��ͼ���RGB��ɫϵתΪHSV��ɫϵ

	//if (m_trackObject)
	{
		//������Ĥ�壬ֻ��������ֵΪH��0~180��S��smin~256��V��vmin~vmax֮��Ĳ���
		cvInRangeS( m_hsv, cvScalar(0,30,10,0),cvScalar(180,256,256,0), m_mask );
		cvSplit( m_hsv, m_hue, 0, 0, 0 );//����H����
		//m_trackObject=-1;
		if (m_trackObject==0)//�����Ҫ���ٵ����廹û�н���������ȡ�������ѡȡ�����ͼ��������ȡ
		{
			float max_val = 0.f;
			cvSetImageROI( m_hue, m_selectedArea);//����ԭѡ���ΪROI
			cvSetImageROI( m_mask, m_selectedArea );//������Ĥ��ѡ���ΪROI
			cvCalcHist( &m_hue, m_hist, 0, m_mask );//�õ�ѡ�������������Ĥ���ڵ�ֱ��ͼ
			cvGetMinMaxHistValue( m_hist, 0, &max_val, 0, 0 );
			cvConvertScale( m_hist->bins, m_hist->bins, max_val ? 255. / max_val : 0.5, 0 );// ��ֱ��ͼ����ֵתΪ0~255
			cvResetImageROI( m_hue );//ȥ��ROI
			cvResetImageROI( m_mask );//ȥ��ROI

			m_trackWindow=m_selectedArea;
			m_trackObject=1;//��track_objectΪ1,����������ȡ���

		}
		cvCalcBackProject( &m_hue, m_backProject, m_hist );//����hue�ķ���ͶӰͼ
		cvAnd( m_backProject, m_mask, m_backProject, 0 );//�õ���Ĥ�ڵķ���ͶӰ
		if(cvCamShift( m_backProject, m_trackWindow,cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1.1 ),
			&m_trackComp, &m_trackBox )<=1)//ʹ��MeanShift�㷨��backproject�е����ݽ�������,���ظ��ٽ��
		return false;
			m_trackWindow = m_trackComp.rect;//�õ����ٽ���ľ��ο�
		//if( backproject_mode )
			cvCvtColor( m_backProject, m_curImage, CV_GRAY2BGR );
		if( m_curImage->origin )
				m_trackBox.angle = -m_trackBox.angle;
		cvEllipseBox( m_curImage, m_trackBox, CV_RGB(255,0,0), 3, CV_AA, 0 );

	}
	return true;
}