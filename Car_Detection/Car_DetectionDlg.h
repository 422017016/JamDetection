
// Car_DetectionDlg.h : 头文件
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
// CCar_DetectionDlg 对话框
using namespace cv;
using namespace std;

#define FRAME_WIDTH 230*2//480
#define FRAME_HEIGHT 168*2//360

class CCar_DetectionDlg : public CBCGPDialog
{
// 构造
public:
	CCar_DetectionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CAR_DETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	//通用函数
	float P2PDistance(Point P1, Point P2);//点到点的距离
	float TriangleArea(Point P1, Point P2, Point P3);//运算三角形面积
	int PointInRect(Point p, Point ps[4]);//判断点是否在四边形内
	Point RectCenter(Rect rect);//返回矩形的中心点坐标
	CString m_GetStringBy2Sign(CString,char,char);//提取两个字符中的字符串
	
	//MFC界面上的变量及方法
	void BCGPInit(void);//控件初始化函数
	void VideoInit(void);//显示控件初始化
	CBCGPButton m_VIDEO_OpenBTN;//下一张按钮
	CBCGPButton m_VIDEO_OpenBTN_Pre;//上一张按钮
	bool Flag_OfStartAll;//连续处理的标志
	bool Flag_OfStartAllCam;//连续处理相册的标志
	CvvImage m_ShowArea_Prime;//原始数据显示区域
	CBCGPEdit m_Edit_Route_Ctl;//视频路径
	CBCGPSwitchCtrl m_Switch_ROUTE;//视频打开开关
	BOOL m_switch_ROUTE_State;//表示路径开关标志位
	Mat m_PrimeFrame;//原始帧数据
	Mat m_PrimeFrame_WithROIEdge;//带有ROI边框的原始数据

	//路径变量
	CString m_PrimePicture_Route;//读入图片的原始路径
	CString m_PrimePicture_Route_SubNum;//读入图片的原始路径减去括号及数字
	CString m_PrimePicture_Route_Format;//读入图片文件格式
	CString m_PrimePicture_CAMName;//读入图片的相册名
	int m_PrimePicture_Route_Num;//读入图片的路径小标
	//int m_PrimePicture_Route_FileName;//路径的文件名

	// 道路车辆密度边缘检测方法
	Mat Picture_CANNY_ROAD(Mat src);
	Mat m_projection_transfer(Mat src);// 投影的转换与统计
	int m_trans_Rect_Height;
	int m_trans_Rect_Width;
	vector<Mat> m_transform_Mat_vector;

	//特征点法道路车辆密度
	Mat Picture_FT_ROAD(Mat src);

	//参数编辑栏相关的变量
	CEdit m_Edit_Para_CTL;
	CString m_Edit_Para_Val;
	CString m_Para_String;
	void m_SumRecordToPara(void);// 计算记录里边的参数
	void m_RecordParaInit(void);// 参数的初始化
	bool m_IfCleanRecordWhenParaInit;//当参数初始时是否清空所有记录
	void m_RecordUpdate(void);// 记录更新
	CButton m_BTN_CTL_SAVE;
	CButton m_BTN_CTL_DEFAULT;
	
	//ROI相关变量及方法
	Point MeasureLine_Start;//视频界面点击的起始点
	Point MeasureLine_End;//视频界面点击的终点
	int m_RectPoint_Flag;//有效区域点坐标的标志位，-1代表无效
	void m_DrawLaneRect();//画车道矩形
	
	vector<vector<Point>> ROIS_4Point;//ROI区域的坐标点
	vector<Mat> m_Mat_ROI_vector;
	vector<vector<Point>> m_trans_ROI_Points;//变换后的ROI的坐标
	Mat m_Mat_ROI;//有效区域图片	
	CString m_ROI_Path;//程序所在路径
	CString m_ROI_XML_Path;//程序所在路径  
	void m_CreatROI();// 创建有效区域

	//XML相关变量及方法
	CMarkup xml_ROI;
	void Init_ROI_XML(void);
	bool m_ReadCamROI_Info(CString);
	void m_WriteCamROI_Info(CString);	
	
	//统计判断是否正确的变量
	int m_ReadJamFromPic(Mat src);// 从图片中读取是否拥塞
	int m_NumOfPic_num_true;
	int m_NumOfPic_num_false;
	int m_NumOfPic_num;
};
