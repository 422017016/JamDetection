
// Car_DetectionDlg.h : ͷ�ļ�
//

#pragma once
#include "CvvImage.h"
#include "afxwin.h"
#include "math.h"
#include <cv.h>
#include <highgui.h>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/opencv.hpp" 
#include "Markup.h"
// CCar_DetectionDlg �Ի���
using namespace cv;
using namespace std;

#define FRAME_WIDTH 230*2//480
#define FRAME_HEIGHT 168*2//360

class CCar_DetectionDlg : public CBCGPDialog
{
// ����
public:
	CCar_DetectionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CAR_DETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnGaugeClick(WPARAM wp, LPARAM lp);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedStopstartBtn();
	afx_msg void OnBnClickedStopstartBtn2();
	afx_msg void OnBnClickedBtnSaveRecord();
	afx_msg void OnBnClickedBtnParaDefault();
	afx_msg void OnBnClickedBtnStartall();
	afx_msg void OnBnClickedBtnallcam();
	DECLARE_MESSAGE_MAP()
public:
	//ͨ�ú���
	float P2PDistance(Point P1, Point P2);//�㵽��ľ���
	float TriangleArea(Point P1, Point P2, Point P3);//�������������
	int PointInRect(Point p, Point ps[4]);//�жϵ��Ƿ����ı�����
	Point RectCenter(Rect rect);//���ؾ��ε����ĵ�����
	CString m_GetStringBy2Sign(CString,char,char);//��ȡ�����ַ��е��ַ���
	
	//MFC�����ϵı���������
	void BCGPInit(void);//�ؼ���ʼ������
	void VideoInit(void);//��ʾ�ؼ���ʼ��
	CBCGPButton m_VIDEO_OpenBTN;//��һ�Ű�ť
	CBCGPButton m_VIDEO_OpenBTN_Pre;//��һ�Ű�ť
	bool Flag_OfStartAll;//��������ı�־
	bool Flag_OfStartAllCam;//�����������ı�־
	CvvImage m_ShowArea_Prime;//ԭʼ������ʾ����
	CBCGPEdit m_Edit_Route_Ctl;//��Ƶ·��
	CBCGPSwitchCtrl m_Switch_ROUTE;//��Ƶ�򿪿���
	BOOL m_switch_ROUTE_State;//��ʾ·�����ر�־λ
	Mat m_PrimeFrame;//ԭʼ֡����
	Mat m_PrimeFrame_WithROIEdge;//����ROI�߿��ԭʼ����

	//·������
	CString m_PrimePicture_Route;//����ͼƬ��ԭʼ·��
	CString m_PrimePicture_Route_SubNum;//����ͼƬ��ԭʼ·����ȥ���ż�����
	CString m_PrimePicture_Route_Format;//����ͼƬ�ļ���ʽ
	CString m_PrimePicture_CAMName;//����ͼƬ�������
	int m_PrimePicture_Route_Num;//����ͼƬ��·��С��
	//int m_PrimePicture_Route_FileName;//·�����ļ���

	// ��·�����ܶȱ�Ե��ⷽ��
	Mat Picture_CANNY_ROAD(Mat src);
	Mat m_projection_transfer(Mat src);// ͶӰ��ת����ͳ��
	int m_trans_Rect_Height;
	int m_trans_Rect_Width;
	vector<Mat> m_transform_Mat_vector;

	//�����㷨��·�����ܶ�
	Mat Picture_FT_ROAD(Mat src);

	//�����༭����صı���
	CEdit m_Edit_Para_CTL;
	CString m_Edit_Para_Val;
	CString m_Para_String;
	void m_SumRecordToPara(void);// �����¼��ߵĲ���
	void m_RecordParaInit(void);// �����ĳ�ʼ��
	bool m_IfCleanRecordWhenParaInit;//��������ʼʱ�Ƿ�������м�¼
	void m_RecordUpdate(void);// ��¼����
	CButton m_BTN_CTL_SAVE;
	CButton m_BTN_CTL_DEFAULT;
	
	//ROI��ر���������
	Point MeasureLine_Start;//��Ƶ����������ʼ��
	Point MeasureLine_End;//��Ƶ���������յ�
	int m_RectPoint_Flag;//��Ч���������ı�־λ��-1������Ч
	void m_DrawLaneRect();//����������
	
	vector<vector<Point>> ROIS_4Point;//ROI����������
	vector<Mat> m_Mat_ROI_vector;
	vector<vector<Point>> m_trans_ROI_Points;//�任���ROI������
	Mat m_Mat_ROI;//��Ч����ͼƬ	
	CString m_ROI_Path;//��������·��
	CString m_ROI_XML_Path;//��������·��  
	void m_CreatROI();// ������Ч����

	//XML��ر���������
	CMarkup xml_ROI;
	void Init_ROI_XML(void);
	bool m_ReadCamROI_Info(CString);
	void m_WriteCamROI_Info(CString);	
	
	//ͳ���ж��Ƿ���ȷ�ı���
	int m_ReadJamFromPic(Mat src);// ��ͼƬ�ж�ȡ�Ƿ�ӵ��
	int m_NumOfPic_num_true;
	int m_NumOfPic_num_false;
	int m_NumOfPic_num;
};
