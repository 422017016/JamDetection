
// Car_DetectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Car_Detection.h"
#include "Car_DetectionDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//�����ַ�ʽ������Ϊ1
#define PICTUREOPERATION_CANNY 1
#define PICTUREOPERATION_FT 0



#if PICTUREOPERATION_FT
#define M_NUMOFPARA 3
CString m_AllPara_String[M_NUMOFPARA]={//Ҫ���õĲ�����ʾ
	"Harris�ǵ�ӵ����ֵ<Ŀǰ�ֶ�>",
	"Harris��С�ǵ���",
	"Harris���С"
};
int m_AllPara_Int[M_NUMOFPARA];//���ò�����ֵ
int m_AllPara_Int_Default[M_NUMOFPARA]={400,1,3};

#define M_NUMOFRECORD 1
CString m_AllRecord_String[M_NUMOFRECORD]={//Ҫ��¼�Ĳ���
	"Harris�ǵ����",
	/*"��¼2",
	"��¼3",
	"��¼4",
	"��¼5"*/
};
int m_AllRecord_Int[M_NUMOFRECORD];//���ò�����ֵ
#endif

#if PICTUREOPERATION_CANNY
#define M_NUMOFPARA 3//9
CString m_AllPara_String[M_NUMOFPARA]={//Ҫ���õĲ�����ʾ
	/*"ģ��������С<����>",
	"��Ե������С<����1������>",
	"ģ������Sigma",
	"��Ե��������ֵ<С>",
	"��Ե��������ֵ<��>",
	"����ռ����������<1/n>",*/
	"ˮƽͶӰ�������",
	"��Ч�߰ٷֱ���ֵ",
	"ӵ���жϰٷֱ���ֵ"
};
int m_AllPara_Int[M_NUMOFPARA];//���ò�����ֵ
int m_AllPara_Int_Default[M_NUMOFPARA]={20,40,70};//{7,3,15,30,50,5,20,40,70};

#define M_NUMOFRECORD 2
CString m_AllRecord_String[M_NUMOFRECORD];//Ҫ��¼�Ĳ���
int m_AllRecord_Int[M_NUMOFRECORD];
#endif



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCar_DetectionDlg �Ի���




CCar_DetectionDlg::CCar_DetectionDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CCar_DetectionDlg::IDD, pParent)
	, m_Edit_Para_Val(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CCar_DetectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VideoAddr, m_Edit_Route_Ctl);
	DDX_Control(pDX, IDC_Switch_OpenVideo, m_Switch_ROUTE);
	DDX_Control(pDX, ID_STOPSTART_BTN, m_VIDEO_OpenBTN);
	DDX_Control(pDX, ID_STOPSTART_BTN_PRE, m_VIDEO_OpenBTN_Pre);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_Para_CTL);
	DDX_Text(pDX, IDC_EDIT1, m_Edit_Para_Val);
	DDX_Control(pDX, IDC_BTN_SAVE_Record, m_BTN_CTL_SAVE);
	DDX_Control(pDX, IDC_BTN_PARA_Default, m_BTN_CTL_DEFAULT);
}

BEGIN_MESSAGE_MAP(CCar_DetectionDlg, CBCGPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_REGISTERED_MESSAGE(BCGM_ON_GAUGE_CLICK, OnGaugeClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(ID_STOPSTART_BTN, &CCar_DetectionDlg::OnBnClickedStopstartBtn)
	ON_BN_CLICKED(ID_STOPSTART_BTN_PRE, &CCar_DetectionDlg::OnBnClickedStopstartBtn2)
	ON_BN_CLICKED(IDC_BTN_SAVE_Record, &CCar_DetectionDlg::OnBnClickedBtnSaveRecord)
	ON_BN_CLICKED(IDC_BTN_PARA_Default, &CCar_DetectionDlg::OnBnClickedBtnParaDefault)
	ON_BN_CLICKED(IDC_BTN_STARTALL, &CCar_DetectionDlg::OnBnClickedBtnStartall)
	ON_BN_CLICKED(IDC_BTNALLCAM, &CCar_DetectionDlg::OnBnClickedBtnallcam)
END_MESSAGE_MAP()


// CCar_DetectionDlg ��Ϣ�������
BOOL CCar_DetectionDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	BCGPInit();//���ƿؼ���ʼ
	VideoInit();
	Init_ROI_XML();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CCar_DetectionDlg::BCGPInit(void)
{
	//switch init
	CBCGPSwitchColors colorsVert;
	colorsVert.m_brFillOn = CBCGPBrush(CBCGPColor::Green, CBCGPColor::YellowGreen, CBCGPBrush::BCGP_GRADIENT_HORIZONTAL);
	colorsVert.m_brFillOff = CBCGPBrush(CBCGPColor::DarkRed, CBCGPColor::Red, CBCGPBrush::BCGP_GRADIENT_HORIZONTAL);
	colorsVert.m_brFillThumb = CBCGPBrush(CBCGPColor::LightGray, CBCGPColor::White, CBCGPBrush::BCGP_GRADIENT_RADIAL_TOP_LEFT);
	colorsVert.m_brLabelOff = CBCGPBrush(CBCGPColor::White);

	m_switch_ROUTE_State=FALSE;
	m_Switch_ROUTE.GetSwitch()->SetID(IDC_Switch_OpenVideo);
	m_Switch_ROUTE.GetSwitch()->SetColors(colorsVert);
	m_Switch_ROUTE.GetSwitch()->EnableOnOffLabels();
	m_Switch_ROUTE.GetSwitch()->SetStyle(CBCGPSwitchImpl::BCGP_SWITCH_CIRCLE);

	m_VIDEO_OpenBTN.SetImage(IDB_VIDEO_START);
	m_VIDEO_OpenBTN_Pre.SetImage(IDB_VIDEO_STOP);
	
}
void CCar_DetectionDlg::VideoInit(void)
{
	

	CString VideoAddrStr;
	VideoAddrStr=theApp.GetString(L"VideoAddress");
	m_Edit_Route_Ctl.EnableFileBrowseButton (NULL,L"(*.jpg;*.png;*.bmp;*.jpeg;)|*.jpg;*.png;*.bmp;*jpeg||");//��ȡ·����ʽ����
	m_Edit_Route_Ctl.SetWindowTextW(VideoAddrStr);
	m_ShowArea_Prime.m_LockRect(GetDlgItem(IDC_VideoRect));//�󶨵�Picture�ؼ�
	m_PrimeFrame.create(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC3);

	m_RectPoint_Flag=-1;
	Flag_OfStartAll=false;
	Flag_OfStartAllCam=false;

	CString Para;
	for(int i=0;i<M_NUMOFPARA;i++)
	{
		Para.Format(L"M_Para_%d",i);
		m_AllPara_Int[i]=theApp.GetInt(Para);//��ȡ����Ĳ���
	}
	m_RecordParaInit();
	m_BTN_CTL_SAVE.EnableWindow(FALSE);
	m_BTN_CTL_DEFAULT.EnableWindow(TRUE);
	
}
void CCar_DetectionDlg::Init_ROI_XML(void)
{
	GetCurrentDirectory(MAX_PATH,m_ROI_Path.GetBuffer(MAX_PATH));//��¼��ǰӦ�ó����·��
	m_ROI_Path.Format(L"%s\\ROI_Info",m_ROI_Path);//��ǰĿ¼�µ�ROI_Info�ļ�����Ϊ��Ŀ¼
	m_ROI_XML_Path.Format(L"%s\\ROI_Info.xml",m_ROI_Path);//ROI_InfoĿ¼�µ�XML�ļ�Ŀ¼

	bool ifLoad=xml_ROI.Load(m_ROI_XML_Path);//����xml�ĵ������û��������һ����׼��
	if(!ifLoad){
		xml_ROI.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
		xml_ROI.AddElem(L"CAM_ID");
		xml_ROI.IntoElem();

		//û������ŵĳ�ʼΪ�߿�֮��5���ص��
		xml_ROI.AddElem(L"DEFAULT");
		xml_ROI.AddAttrib(L"ROI_NUM",1);
		xml_ROI.AddAttrib(L"T_Width",100);
		xml_ROI.AddAttrib(L"T_Height",100);
		xml_ROI.IntoElem();

		CString strROI;
		xml_ROI.AddElem(L"Points_0");
		xml_ROI.AddAttrib(L"P0.x",5);xml_ROI.AddAttrib(L"P0.y",5);
		xml_ROI.AddAttrib(L"P1.x",5);xml_ROI.AddAttrib(L"P1.y",FRAME_HEIGHT-5);
		xml_ROI.AddAttrib(L"P2.x",FRAME_WIDTH-5);xml_ROI.AddAttrib(L"P2.y",FRAME_HEIGHT-5);
		xml_ROI.AddAttrib(L"P3.x",FRAME_WIDTH-5);xml_ROI.AddAttrib(L"P3.y",5);

		xml_ROI.AddAttrib(L"TP0.x",5);xml_ROI.AddAttrib(L"TP0.y",5);
		xml_ROI.AddAttrib(L"TP1.x",5);xml_ROI.AddAttrib(L"TP1.y",FRAME_HEIGHT-5);
		xml_ROI.AddAttrib(L"TP2.x",FRAME_WIDTH-5);xml_ROI.AddAttrib(L"TP2.y",FRAME_HEIGHT-5);
		xml_ROI.AddAttrib(L"TP3.x",FRAME_WIDTH-5);xml_ROI.AddAttrib(L"TP3.y",5);

		system("md ROI_Info");//���ROI�ļ������ڣ�����ROI�ļ���

		xml_ROI.Save(m_ROI_XML_Path);
	}
	m_PrimePicture_CAMName="";
}
void CCar_DetectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBCGPDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCar_DetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBCGPDialog::OnPaint();
		//�ڴ����ػ�ʱ����ǰ·����ͼƬ���ؽ���

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCar_DetectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CCar_DetectionDlg::OnGaugeClick(WPARAM wp, LPARAM /*lp*/)
{
	int nID = (int)wp;
	switch (nID)
	{
		case IDC_Switch_OpenVideo:
			{
				if(m_switch_ROUTE_State){
					//�ر�ͼƬ,���Խ��в������ã�ROI������£��������
					m_switch_ROUTE_State=FALSE;
					m_Edit_Route_Ctl.EnableWindow(TRUE);
					m_Edit_Para_CTL.EnableWindow(TRUE);
					m_BTN_CTL_SAVE.EnableWindow(FALSE);
					m_BTN_CTL_DEFAULT.EnableWindow(TRUE);
				}
				else{
					//��ֹ��·�����ROI���������ܲ��
					

					m_switch_ROUTE_State=TRUE;
					m_BTN_CTL_SAVE.EnableWindow(TRUE);
					m_BTN_CTL_DEFAULT.EnableWindow(FALSE);
					m_Edit_Route_Ctl.EnableWindow(FALSE);
					m_Edit_Para_CTL.EnableWindow(FALSE);
					
					m_Edit_Route_Ctl.GetWindowTextW(m_PrimePicture_Route);
					theApp.WriteString (L"VideoAddress",m_PrimePicture_Route);
					
					String VideoAddress=CT2A(m_PrimePicture_Route.GetBuffer());
					Mat Input=imread(VideoAddress);

					if(!Input.data)
					{
						BCGPMessageBox(L"��ַ��Ч��\r\n������ѡ��ͼƬ");
						return 0;
					}

					m_SumRecordToPara();//�����������¼
					m_RecordParaInit();//��¼��ʼ�������������ԭ��¼
					m_SumRecordToPara();//�����������¼
					m_RecordUpdate();//���¼�¼		

					//���û��ID�ĵ�ַ�±�
					int IndexTemp=m_PrimePicture_Route.Find('(');
					m_PrimePicture_Route_SubNum=m_PrimePicture_Route.Left(IndexTemp);
					//���ͼƬ�ĸ�ʽ
					CString InsideSubNum=m_PrimePicture_Route.Right(m_PrimePicture_Route.GetLength()-IndexTemp);
					IndexTemp=InsideSubNum.Find(')');
					m_PrimePicture_Route_Format=InsideSubNum.Right(InsideSubNum.GetLength()-IndexTemp-1);
					//���ͼƬ��ID����int��ʽ
					InsideSubNum=InsideSubNum.Left(IndexTemp);
					InsideSubNum=InsideSubNum.Right(1);
					m_PrimePicture_Route_Num=_ttoi(InsideSubNum);
					//���������֣����û�й涨���ʶΪDEFAULT
					CString cam=m_GetStringBy2Sign(m_PrimePicture_Route,'#','#');

					if(cam!=m_PrimePicture_CAMName)
					{
						m_ReadCamROI_Info(cam);
					}
					m_PrimePicture_CAMName=cam;
					m_CreatROI();
					m_WriteCamROI_Info(m_PrimePicture_CAMName);

					if(FRAME_WIDTH>0&&FRAME_HEIGHT>0)//���������Ч���������
						resize(Input,m_PrimeFrame,Size(FRAME_WIDTH,FRAME_HEIGHT));//����
					
					m_DrawLaneRect();//���ƾ���
					m_ShowArea_Prime.m_Mat2Rect(m_PrimeFrame_WithROIEdge);//��ʾ�ڿؼ���
				}
			}
		break;
	}
	return 0L;
}

/****************************************
* ������һ����Ƭ
* ����ַ���зֽⲢ���ۼӣ����ڵ����֣�������ɵ�·�������ڣ����ȡ��NUM=1����Ƭ
****************************************/
void CCar_DetectionDlg::OnBnClickedStopstartBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��û����������ʱ���ܽ����������
	if(!m_switch_ROUTE_State)return;
	
	if(!Flag_OfStartAll)
		m_AllRecord_String[1].Empty();//����������ǰ����ռ�¼1

	m_PrimePicture_Route.Format(L"%s(%d)%s",m_PrimePicture_Route_SubNum,m_PrimePicture_Route_Num,m_PrimePicture_Route_Format);
	String addr=CT2A(m_PrimePicture_Route.GetBuffer());
	Mat Input=imread(addr); 
	if(!Input.data)
	{//���ͼƬ�����������¶�ȡ���
		m_PrimePicture_Route_Num=1;
		m_PrimePicture_Route.Format(L"%s(%d)%s",m_PrimePicture_Route_SubNum,m_PrimePicture_Route_Num,m_PrimePicture_Route_Format);
		addr=CT2A(m_PrimePicture_Route.GetBuffer());
		Flag_OfStartAll=false;
		if(!Flag_OfStartAllCam)
		{
			m_NumOfPic_num--;//�������һ��
			return;
		}
		else
		{
			Flag_OfStartAll=true;
			CString fileName=m_GetStringBy2Sign(m_PrimePicture_Route,'&','&');
			int fileNum=_ttoi(fileName);
			fileNum++;

			int index=m_PrimePicture_Route.Find('&');
			CString temp=m_PrimePicture_Route.Left(index);
			m_PrimePicture_Route.Format(L"%s\&%d\&\\\#Cam%d\#(1)%s",temp,fileNum,fileNum,m_PrimePicture_Route_Format);

			//���û��ID�ĵ�ַ�±�
			int IndexTemp=m_PrimePicture_Route.Find('(');
			m_PrimePicture_Route_SubNum=m_PrimePicture_Route.Left(IndexTemp);
			//���ͼƬ�ĸ�ʽ
			CString InsideSubNum=m_PrimePicture_Route.Right(m_PrimePicture_Route.GetLength()-IndexTemp);
			IndexTemp=InsideSubNum.Find(')');
			m_PrimePicture_Route_Format=InsideSubNum.Right(InsideSubNum.GetLength()-IndexTemp-1);
			//���ͼƬ��ID����int��ʽ
			InsideSubNum=InsideSubNum.Left(IndexTemp);
			InsideSubNum=InsideSubNum.Right(1);
			m_PrimePicture_Route_Num=_ttoi(InsideSubNum);
			//���������֣����û�й涨���ʶΪDEFAULT
			m_PrimePicture_CAMName=m_GetStringBy2Sign(m_PrimePicture_Route,'#','#');
			addr=CT2A(m_PrimePicture_Route.GetBuffer());
			Input=imread(addr);
			if(!Input.data)
			{
				Flag_OfStartAllCam=false;
				Flag_OfStartAll=false;
				m_NumOfPic_num--;
				return;
			}
			m_ReadCamROI_Info(m_PrimePicture_CAMName);
		}
	}

	m_PrimePicture_Route_Num++;

	if(FRAME_WIDTH>0&&FRAME_HEIGHT>0)//���������Ч���������
		resize(Input,m_PrimeFrame,Size(FRAME_WIDTH,FRAME_HEIGHT));//����
	
	if(PICTUREOPERATION_FT==1)
		Picture_FT_ROAD(m_PrimeFrame);//��ͼƬ���������㴦��ĳ����ܶ�����
	else 
		Picture_CANNY_ROAD(m_PrimeFrame);//��ͼƬ���б�Ե��⴦��ĳ����ܶ�����
	
	if(!Flag_OfStartAll)
		m_RecordUpdate();//������¼����
	m_DrawLaneRect();//���ƾ���
	m_ShowArea_Prime.m_Mat2Rect(m_PrimeFrame_WithROIEdge);//��ʾ�ڿؼ���

}
/****************************************
* ��������������Ƭ
* ����������һ����ᣬ��һ��ͼƬ��ֱ������
****************************************/
void CCar_DetectionDlg::OnBnClickedBtnallcam()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_switch_ROUTE_State)return;

	Flag_OfStartAllCam=true;
	Flag_OfStartAll=true;
	m_AllRecord_String[1].Empty();//����������ǰ����ռ�¼1

	m_NumOfPic_num_true=0;
	m_NumOfPic_num_false=0;
	m_NumOfPic_num=0;

	clock_t start,finish;
	double totaltime;
	start=clock();
	while(Flag_OfStartAllCam)
	{
		OnBnClickedStopstartBtn();
		m_NumOfPic_num++;
		//int c=waitKey(1000);
	}
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	double averagetime=totaltime/m_NumOfPic_num*1000;
	float correct_rate_all=100*m_NumOfPic_num_true/m_NumOfPic_num;//������Ƭ����ȷ��
	float error_rate_all=100*m_NumOfPic_num_false/m_NumOfPic_num;//������Ƭ�Ĵ�����

	m_AllRecord_String[0].Format(L"����ͼƬ�жϵ���ȷ��Ϊ��%f\r\n�ܴ�����Ƭ����%d\r\n�ж���ȷ��%d\r\n�жϴ���%d",correct_rate_all,m_NumOfPic_num,m_NumOfPic_num_true,m_NumOfPic_num_false);
	CString str;
	str.Format(L"ͼƬ����Ϊ��%d\r\n�ܹ�����ʱ��Ϊ��%fs\r\n����ƽ������ʱ��Ϊ��%fms\r\n\r\n",m_NumOfPic_num,totaltime,averagetime);
	BCGPMessageBox(L"ͼƬ�������\r\n"+str);
	m_AllRecord_String[1]=str+m_AllRecord_String[1];

	m_RecordUpdate();
}
/****************************************
* �������е�ǰ������Ƭ
* ����������һ��ͼƬ��ֱ������
****************************************/
void CCar_DetectionDlg::OnBnClickedBtnStartall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_switch_ROUTE_State)return;
	Flag_OfStartAll=true;
	m_AllRecord_String[1].Empty();//����������ǰ����ռ�¼1
	
	m_NumOfPic_num_true=0;
	m_NumOfPic_num_false=0;
	m_NumOfPic_num=0;

	clock_t start,finish;
	double totaltime;
	start=clock();
	while(Flag_OfStartAll){
		OnBnClickedStopstartBtn();
		m_NumOfPic_num++;
	}
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	double averagetime=totaltime/m_NumOfPic_num*1000;
	
	float correct_rate_all=100*m_NumOfPic_num_true/m_NumOfPic_num;//������Ƭ����ȷ��
	float error_rate_all=100*m_NumOfPic_num_false/m_NumOfPic_num;//������Ƭ�Ĵ�����
	
	m_AllRecord_String[0].Format(L"����ͼƬ�жϵ���ȷ��Ϊ��%f\r\n�ܴ�����Ƭ����%d\r\n�ж���ȷ��%d\r\n�жϴ���%d",correct_rate_all,m_NumOfPic_num,m_NumOfPic_num_true,m_NumOfPic_num_false);
	CString str;
	str.Format(L"ͼƬ����Ϊ��%d\r\n�ܹ�����ʱ��Ϊ��%fs\r\n����ƽ������ʱ��Ϊ��%fms\r\n\r\n",m_NumOfPic_num,totaltime,averagetime);
	BCGPMessageBox(L"ͼƬ�������\r\n"+str);
	m_AllRecord_String[1]=str+m_AllRecord_String[1];
	m_RecordUpdate();
}

/****************************************
* �����һ�Ű�ť
* ʵ����������һ�ţ���·����ߣ����е����ּ�С����
****************************************/
void CCar_DetectionDlg::OnBnClickedStopstartBtn2()
{//
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_switch_ROUTE_State)return;
	Flag_OfStartAll=false;//��һ�ſ��Ե���ͣʹ��
	m_PrimePicture_Route_Num=m_PrimePicture_Route_Num-2;
	OnBnClickedStopstartBtn();
}

/****************************************
* ��ͼƬ�ж�ȡ�Ƿ�ӵ��
* ����ֵΪ0�����·��ӵ����Point(0,0)==0��
*		Ϊ1�����·ӵ����Point(0,0)==255��
*		Ϊ2����δ֪��ͼƬû�о������ã�
****************************************/
int CCar_DetectionDlg::m_ReadJamFromPic(Mat src)
{
	int src_gray_level=(int)src.at<unsigned char>(Point(0,0));
	if(src_gray_level==0)
		return 0;
	else if(src_gray_level=255)
		return 1;
	else return 2;
}
//�����㷽����·�����ܶ�
Mat CCar_DetectionDlg::Picture_FT_ROAD(Mat src)
{
	Mat src_gray;//�Ҷȴ���
	Mat src_gray_roi(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC1);//ROI����
	Mat src_gray_roi_changes;//ROI�����ϵĸ��ֱ�����ʾ
	Mat goodFT;
	vector<KeyPoint> m_Keypoints;

	int FastThreshold=m_AllPara_Int[0];
	int minDistance=m_AllPara_Int[1];
	int blockSize=m_AllPara_Int[2];

	//�Ҷȴ���
	//������Ҷȵ�ROI
	cvtColor( src, src_gray, CV_BGR2GRAY );
	src_gray_roi=src_gray&m_Mat_ROI;//ֻ��ע��Ч����

	/*imshow("ROI",src_gray_roi);

	FASTX(src_gray_roi,m_Keypoints,FastThreshold,true,FastFeatureDetector::TYPE_7_12);
	drawKeypoints (src_gray_roi,m_Keypoints,src_gray_roi_changes,Scalar::all (255),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS); 
	imshow( "FAST_KeyPoint", src_gray_roi_changes );*/

	// Parameters for Shi-Tomasi algorithm
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	bool useHarrisDetector = false;
	double k = 0.04;
	// Apply corner detection
	goodFeaturesToTrack( src_gray_roi,corners,10000,qualityLevel,minDistance,Mat(),blockSize,useHarrisDetector,k );
	int r = 2;
	m_AllRecord_Int[0]=0;//�ǵ������ʼΪ0
	for( int i = 0; i < corners.size(); i++ )
	{ 
		//if(PointInRect(corners[i],m_SubROIEdgePoint)==1)
		{	
			circle( src_gray_roi,corners[i],r,Scalar::all (255), -1, 8, 0 ); 
			m_AllRecord_Int[0]++;
		}
	}
	imshow("GoodFeature",src_gray_roi);

	return src;
}
//��Ե��ⷽ����·�����ܶ�
Mat CCar_DetectionDlg::Picture_CANNY_ROAD(Mat src)
{
	//����
	Mat src_gray;
	Mat src_gray_roi(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC1);
	Mat gaussblur;
	Mat edges;

	int BlurBlob=7;
	int EdgesBlob=3;
	int Sigma=15;
	int ThresholdLow=30;
	int ThresholdHigh=50;

	//������Ҷȵ�ROI
	cvtColor( src, src_gray, CV_BGR2GRAY );
	src_gray_roi=src_gray&m_Mat_ROI;//ֻ��ע��Ч����
	
	//imshow("src_gray_roi",src_gray_roi);
	
	Mat perspective_Mat=Mat(Size(m_trans_Rect_Width,m_trans_Rect_Height),CV_8UC1,Scalar::all(0));
	Mat temp_Mat;
	for(int i=0;i<ROIS_4Point.size();i++){
		src_gray_roi=src_gray&m_Mat_ROI_vector[i];
		warpPerspective( src_gray_roi, temp_Mat, m_transform_Mat_vector[i],Size(m_trans_Rect_Width,m_trans_Rect_Height),0,0,Scalar::all(255));
		perspective_Mat=perspective_Mat|temp_Mat;
	}
	//imshow("perspective_Mat",perspective_Mat);
	
	GaussianBlur(perspective_Mat, gaussblur, Size(BlurBlob,BlurBlob), Sigma/10, Sigma/10);
	imshow("GaussianBlur",gaussblur);

	Canny(gaussblur, edges, ThresholdLow, ThresholdHigh, EdgesBlob);
	//�߽����Ԥ����
	for(int i=0;i<ROIS_4Point.size();i++)
	{
		cv::line(edges,m_trans_ROI_Points[i][0],m_trans_ROI_Points[i][3],Scalar::all(0),3);//�ϱ߽���ƺ��ߣ�����ȥ����ROI�ӷ촦Ӱ��
		cv::line(edges,m_trans_ROI_Points[i][0],m_trans_ROI_Points[i][1],Scalar::all(100),2);//��߽��Ϊ100
		cv::line(edges,m_trans_ROI_Points[i][2],m_trans_ROI_Points[i][3],Scalar::all(100),2);//�ұ߽��Ϊ100
	}
	if(!Flag_OfStartAll)//���Ŵ���ʱ��ʾ
		imshow("Edges", edges);
	Mat projection_transfer=m_projection_transfer(edges);
	if(!Flag_OfStartAll)
		imshow("����ͶӰ", projection_transfer);
	return src;
}

//ͶӰ��ת����ͳ��
Mat CCar_DetectionDlg::m_projection_transfer(Mat src)
{
	Mat projection(Size(2*m_trans_Rect_Width+100,m_trans_Rect_Height),CV_8UC1,Scalar::all(0));
	
	vector<Point> val_f;//���˺����Чֵ��xΪֵ�Ĵ�С��yΪrow
	Point val_point(0,0);//ͳ�ƹ��˺���Ч�����
	
	int road_num=m_AllPara_Int_Default[0];//���˼��
	if(m_AllPara_Int[0]!=0)
			road_num=m_AllPara_Int[0];
	int threshold_single=m_AllPara_Int[1];
	int threshold_all=m_AllPara_Int[2];
	
	int line_num=0;//�������Ч�ߵĸ���
	int line_num_value=0;//��Ч�ߵ�����

	int f_fliter=road_num;//m_trans_Rect_Width/(road_num*car_road);
	

	for(int row=0;row<m_trans_Rect_Height;row++)
	{
		int col=0;

		int f_dis=row%f_fliter;//��ɨ����fliter���һ��ʱ����ͳ�ƻ���
		bool flag_fliter_draw=false;
		if((f_fliter-f_dis)==1)flag_fliter_draw=true;

		int f_mid=row/f_fliter;
		int f_row=f_mid*f_fliter;//�������

		while(src.at<unsigned char>(Point(col,row))!=100)
			col++;

		int val_all=m_trans_Rect_Width-2*col;//��ǰ�е���Ч�ܳ���
		int val_null=col;//��ǰ�е���Ч����

		float col_k=(float)m_trans_Rect_Width/(float)val_all;//col����ʹ�õ�ϵ��

		for(col;col<m_trans_Rect_Width-val_null;col++)
		{//ɨ�赽�ұ߽�Ϊֹ
			if(src.at<unsigned char>(Point(col,row))==255)
			{
				int x=(int)((col-val_null)*col_k);//��������
				projection.at<unsigned char>(Point(x,row))=255;

				if(projection.at<unsigned char>(Point(x+m_trans_Rect_Width,f_row))!=255)
				{
					projection.at<unsigned char>(Point(x+m_trans_Rect_Width,f_row))=255;//���˹���ͼ
					val_point.x++;
				}				
			}
		}
		if(flag_fliter_draw)
		{
			val_point.y=f_row;
			val_point.x=val_point.x*100/m_trans_Rect_Width;
			val_f.push_back(val_point);
			
			line_num++;//ͳ�������ۼ�

			if(val_point.x>=threshold_single)//��Ч
			{
				line_num_value++;//��Ч��ͳ�������ۼ�
				line(projection,Point(2*m_trans_Rect_Width,f_row),Point(2*m_trans_Rect_Width+val_point.x,f_row),Scalar::all(255));
			}
			else//��Ч
				line(projection,Point(2*m_trans_Rect_Width,f_row),Point(2*m_trans_Rect_Width+val_point.x,f_row),Scalar::all(100));
			
			val_point=Point(0,0);//����
		}		
	}
	cv::line(projection,Point(m_trans_Rect_Width,0),Point(m_trans_Rect_Width,m_trans_Rect_Height-1),Scalar::all(255));
	cv::line(projection,Point(2*m_trans_Rect_Width,0),Point(2*m_trans_Rect_Width,m_trans_Rect_Height-1),Scalar::all(255));
	cv::line(projection,Point(2*m_trans_Rect_Width+threshold_single,0),Point(2*m_trans_Rect_Width+threshold_single,m_trans_Rect_Height-1),Scalar::all(100));

	int precent_line_value=line_num_value*100/line_num;
	int JamFlag=m_ReadJamFromPic(m_PrimeFrame);//��¼ͼƬʵ���Ƿ�ӵ��
	
	if(precent_line_value>=threshold_all){//�ж�Ϊӵ��
		CString str;
		if(JamFlag==0)//ʵ�ʲ�ӵ�¡����жϴ���
		{
			m_NumOfPic_num_false++;
			str.Format(m_PrimePicture_CAMName+L"\tID:%d�ж�Ϊӵ�£� ����\r\n",m_PrimePicture_Route_Num-1);
		}
		else if(JamFlag==1)//ʵ��ӵ�¡����ж���ȷ
		{
			m_NumOfPic_num_true++;
			str.Format(m_PrimePicture_CAMName+L"\tID:%d�ж�Ϊӵ�£� ��ȷ\r\n",m_PrimePicture_Route_Num-1);
		}
		m_AllRecord_String[1]+=str;//��¼1�ۼ�
		if(!Flag_OfStartAll)//����������ʱ��¼
			m_AllRecord_String[0].Format(L"��ǰ��·�ж�Ϊӵ�£�������������\r\n������=%d\r\n�ж�Ϊ��Ч������=%d\r\n��Ч�ٷֱ�=%d",line_num,line_num_value,precent_line_value);
	}
	else{//�ж�Ϊ��ӵ��
		CString str;
		if(JamFlag==0)//ʵ�ʲ�ӵ�¡����ж���ȷ�������м�¼��
		{
			m_NumOfPic_num_true++;
			if(!Flag_OfStartAll)//����������ʱ��¼
			{
				str.Format(m_PrimePicture_CAMName+L"\tID:%d�ж�Ϊ��ӵ�£� ��ȷ\r\n",m_PrimePicture_Route_Num-1);
			}
		}
		else if(JamFlag==1)//ʵ��ӵ�¡����жϴ���
		{
			m_NumOfPic_num_false++;
			str.Format(m_PrimePicture_CAMName+L"\tID:%d�ж�Ϊ��ӵ�£� ����\r\n",m_PrimePicture_Route_Num-1);
		}
		m_AllRecord_String[1]+=str;//��¼1�ۼ�
		if(!Flag_OfStartAll)//����������ʱ��¼
			m_AllRecord_String[0].Format(L"������=%d\r\n�ж�Ϊ��Ч������=%d\r\n��Ч�ٷֱ�=%d",line_num,line_num_value,precent_line_value);
	}

	return projection;
}

//��ԭͼ�ϻ���ROI����
void CCar_DetectionDlg::m_DrawLaneRect()
{
	m_PrimeFrame.copyTo(m_PrimeFrame_WithROIEdge);
	CString str;
	for(int num=0;num<ROIS_4Point.size();num++)
	{
		vector<Point> Points_vector=ROIS_4Point[num];
		Point Points_4[4];
		for(int i=0;i<4;i++)
		{
			Points_4[i]=Points_vector[i];
		}
		for(int i=0;i<4;i++)
		{
			circle(m_PrimeFrame_WithROIEdge,Points_4[i],1,Scalar( 0, 255, 0 ),2);
			line( m_PrimeFrame_WithROIEdge,Points_4[i],Points_4[(i+1)%4],Scalar( 255, 0, 0 ),1,1 );
		}
		
		str.Format(L"%d",num);
		string str1=CT2A(str.GetBuffer(0));
		putText(m_PrimeFrame_WithROIEdge,str1,Points_4[0],FONT_ITALIC,0.3 ,Scalar(0,0,255),1);
	}
}

//���ؾ��ε����ĵ�����
Point CCar_DetectionDlg::RectCenter(Rect rect)
{
	return(Point(rect.x+rect.width/2,rect.y+rect.height/2));
}

// ������Ч����
void CCar_DetectionDlg::m_CreatROI()
{
	//����͸��
	m_transform_Mat_vector.clear();//�任�������
	m_trans_ROI_Points.clear();//�任�����
	m_Mat_ROI_vector.clear();//ROI���
	m_trans_Rect_Height=0;	

	vector<vector<int>> ROIS_info;//ROI���µף��ϱߣ���߸ߣ�����߽ϳ���һ����
	for(int i=0;i<ROIS_4Point.size();i++)
	{
		vector<int> Temp_int_vector;
		int c1=(int)P2PDistance(ROIS_4Point[i][0],ROIS_4Point[i][1]);
		int c2=(int)P2PDistance(ROIS_4Point[i][2],ROIS_4Point[i][3]);
		int up=(int)P2PDistance(ROIS_4Point[i][0],ROIS_4Point[i][3]);
		int down=(int)P2PDistance(ROIS_4Point[i][1],ROIS_4Point[i][2]);
		Temp_int_vector.push_back(down);
		Temp_int_vector.push_back(up);
		if(c1>c2)
		{
			Temp_int_vector.push_back(c1);
			m_trans_Rect_Height+=c1;
		}
		else 
		{
			Temp_int_vector.push_back(c2);
			m_trans_Rect_Height+=c2;
		}
		ROIS_info.push_back(Temp_int_vector);
	}
	if(ROIS_4Point.size()==0)
	{
		//BCGPMessageBox(L"û��ѡ��ROI����");
		return;
	}
	m_trans_Rect_Width=ROIS_info[0][0];//ת���Ŀ�
	
	int tempHeight=m_trans_Rect_Height;
	int tempWidth_2=m_trans_Rect_Width/2;//1/2�Ŀ���ʾ������
	for(int i=0;i<ROIS_4Point.size();i++)
	{
		vector<Point2f> corners(4);  
		corners[0] = ROIS_4Point[i][0];  
		corners[1] = ROIS_4Point[i][1];  
		corners[2] = ROIS_4Point[i][2];  
		corners[3] = ROIS_4Point[i][3];  

		vector<Point2f> corners_trans(4);
		tempHeight-=ROIS_info[i][2];

		int upx1=tempWidth_2-ROIS_info[i][1]/2;
		int upx2=tempWidth_2+ROIS_info[i][1]/2-1;
		int upy=tempHeight;
		int downx1=tempWidth_2-ROIS_info[i][0]/2;
		int downx2=tempWidth_2+ROIS_info[i][0]/2-1;
		int downy=tempHeight+ROIS_info[i][2]-1;
		
		vector<Point> points;

		corners_trans[0] = Point2f(upx1,upy);points.push_back(Point(upx1,upy));
		corners_trans[1] = Point2f(downx1,downy);points.push_back(Point(downx1,downy));
		corners_trans[2] = Point2f(downx2,downy);points.push_back(Point(downx2,downy));
		corners_trans[3] = Point2f(upx2,upy);points.push_back(Point(upx2,upy));

		m_trans_ROI_Points.push_back(points);
		Mat trans = getPerspectiveTransform(corners,corners_trans);  
		m_transform_Mat_vector.push_back(trans);
	}

	//����ROI
	
	for(int i=0;i<ROIS_4Point.size();i++)
	{
		m_Mat_ROI_vector.push_back(Mat(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC1,Scalar::all(0)));
	}
	m_Mat_ROI=Mat(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC1,Scalar::all(0));//����һ����ԭͼͬ����С��MAT����ΪROI���ø�ʽ
	Mat Mat_temp(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC1);
	for(int num=0;num<ROIS_4Point.size();num++)
	{
		
		vector<Point> Points_vector=ROIS_4Point[num];
		Point Points_4[4];
		for(int i=0;i<4;i++)
		{
			Points_4[i]=Points_vector[i];
		}

		for(int i=0;i<FRAME_WIDTH;i++)
		{	
			for(int j=0;j<FRAME_HEIGHT;j++)
			{
				if(PointInRect(Point(i,j),Points_4)==1)
				{
					Mat_temp.at<unsigned char>(Point(i,j))=255;
				}
				else 
				{
					Mat_temp.at<unsigned char>(Point(i,j))=0;
				}
			}
		}
		Mat_temp.copyTo(m_Mat_ROI_vector[num]);
		m_Mat_ROI=m_Mat_ROI|Mat_temp;
	}
}
//������
float CCar_DetectionDlg::P2PDistance(Point P1, Point P2)
{
	float x=P1.x-P2.x;
	float y=P1.y-P2.y;
	float c=sqrt(x*x+y*y);
	return c;
}
//���������
float CCar_DetectionDlg::TriangleArea(Point P1, Point P2, Point P3)
{
	float a,b,c,s,Area;
	a=P2PDistance(P1,P2);
	b=P2PDistance(P2,P3);
	c=P2PDistance(P3,P1);
	s=(a+b+c)/2;
	Area=sqrt(s*(s-a)*(s-b)*(s-c));
	return Area;
}
//�жϵ��Ƿ����ı�����
int CCar_DetectionDlg::PointInRect(Point p, Point ps[4])
{
	float A,A1,A2;
	float B,B1,B2,B3,B4;
	A1=TriangleArea(ps[0],ps[1],ps[2]);
	A2=TriangleArea(ps[2],ps[3],ps[0]);
	A=A1+A2;

	B1=TriangleArea(p,ps[0],ps[1]);
	B2=TriangleArea(p,ps[1],ps[2]);
	B3=TriangleArea(p,ps[2],ps[3]);
	B4=TriangleArea(p,ps[3],ps[0]);
	B=B1+B2+B3+B4;

	if(A<B-20)return 0;//ȥ��С�����Ӱ��
	else return 1;
}


//����������������������Ч��������ı任*********************************************************
void CCar_DetectionDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBCGPDialog::OnLButtonDown(nFlags, point);

	if(m_switch_ROUTE_State)return;//��ͼƬ��ʱ��ֹ�ı�����

	CRect VideoCTLRect;
	GetDlgItem(IDC_VideoRect)->GetClientRect(VideoCTLRect);//�õ���Ƶ���ſؼ�

	GetDlgItem(IDC_VideoRect)->ClientToScreen(VideoCTLRect);//����ת������Ļ����
	ClientToScreen(&point);//���������Ҳת������Ļ����

	if(VideoCTLRect.PtInRect(point))//�������������
	{
		//����Ļ�ϵ��������õ�Mat�ϵ�����λ��
		int VideoRect_X=(point.x-VideoCTLRect.left)*FRAME_WIDTH/VideoCTLRect.Width();
		int VideoRect_Y=(point.y-VideoCTLRect.top)*FRAME_HEIGHT/VideoCTLRect.Height();
		for(int i=0;i<ROIS_4Point.size();i++)
		{
			for(int j=0;j<4;j++){
				if(abs((ROIS_4Point[i][j].x-VideoRect_X))<4&&abs((ROIS_4Point[i][j].y-VideoRect_Y))<4)
				{
					m_RectPoint_Flag=4*i+j;//��¼��־λ
					return;
				}
			}
		}
		{//���û�е���궨�㣬����о������
			MeasureLine_Start=Point(VideoRect_X,VideoRect_Y);//��¼���������ʼ����
			m_RectPoint_Flag=-2;//����û�в���
		}
	}
}

void CCar_DetectionDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CBCGPDialog::OnMouseMove(nFlags, point);
	if(m_RectPoint_Flag==-1)return;

	m_DrawLaneRect();//���ƾ���
	m_ShowArea_Prime.m_Mat2Rect(m_PrimeFrame_WithROIEdge);//��ʾ�ڿؼ���

	CRect VideoCTLRect;
	GetDlgItem(IDC_VideoRect)->GetClientRect(VideoCTLRect);//�õ���Ƶ���ſؼ�

	GetDlgItem(IDC_VideoRect)->ClientToScreen(VideoCTLRect);//����ת������Ļ����
	ClientToScreen(&point);//���������Ҳת������Ļ����
	
	int VideoRect_X=(point.x-VideoCTLRect.left)*FRAME_WIDTH/VideoCTLRect.Width();
	int VideoRect_Y=(point.y-VideoCTLRect.top)*FRAME_HEIGHT/VideoCTLRect.Height();
	MeasureLine_End=Point(VideoRect_X,VideoRect_Y);

	if(VideoCTLRect.PtInRect(point)&&m_RectPoint_Flag!=-2)
	{//��ROI�������ĵ���
		ROIS_4Point[m_RectPoint_Flag/4][m_RectPoint_Flag%4]=MeasureLine_End;
	}
	else if(m_RectPoint_Flag==-2)
	{//�������߻���ROI
		int ctrl_State=GetKeyState(VK_CONTROL);
		if(ctrl_State<0)
		{//����ROI
			rectangle(m_PrimeFrame_WithROIEdge,MeasureLine_Start,MeasureLine_End,Scalar(0,0,255));

			m_ShowArea_Prime.m_Mat2Rect(m_PrimeFrame_WithROIEdge);//��ʾ�ڿؼ���
		}
		else{
			//û�а���Ctrl������
			Mat VIDEO_SHOW_MAT(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC3,Scalar(255,255,255));
			line(VIDEO_SHOW_MAT,MeasureLine_Start,Point(VideoRect_X,VideoRect_Y),Scalar(255,0,0),2);
			CString strtemp;
			strtemp.Format(L"(%d,%d)",MeasureLine_Start.x,MeasureLine_Start.y);
			string str=CT2A(strtemp.GetBuffer(0));
			putText(VIDEO_SHOW_MAT,str,MeasureLine_Start,FONT_ITALIC,0.5 ,Scalar(255,0,255),1);

			strtemp.Format(L"(%d,%d)",VideoRect_X,VideoRect_Y);
			str=CT2A(strtemp.GetBuffer(0));
			putText(VIDEO_SHOW_MAT,str,Point(VideoRect_X,VideoRect_Y),FONT_ITALIC,0.5 ,Scalar(0,0,255),1);

			strtemp.Format(L"D=%f",P2PDistance(MeasureLine_Start,Point(VideoRect_X,VideoRect_Y)));
			str=CT2A(strtemp.GetBuffer(0));
			putText(VIDEO_SHOW_MAT,str,Point(0,FRAME_HEIGHT-20),FONT_ITALIC,0.5 ,Scalar(255,0,0),1);

			addWeighted(VIDEO_SHOW_MAT,0.5,m_PrimeFrame_WithROIEdge,0.5,0,VIDEO_SHOW_MAT);
			m_ShowArea_Prime.m_Mat2Rect(VIDEO_SHOW_MAT);//��ʾ�ڿؼ���
		}
	}
}

void CCar_DetectionDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_RectPoint_Flag==-2)
	{
		int ctrl_State=GetKeyState(VK_CONTROL);
		if(ctrl_State<0)
		{//������Ctrl
			vector<Point> rect_4Points;
			rect_4Points.push_back(MeasureLine_Start);
			rect_4Points.push_back(Point(MeasureLine_Start.x,MeasureLine_End.y));
			rect_4Points.push_back(MeasureLine_End);
			rect_4Points.push_back(Point(MeasureLine_End.x,MeasureLine_Start.y));
			ROIS_4Point.push_back(rect_4Points);
		}	
		m_DrawLaneRect();//���ƾ���
		m_ShowArea_Prime.m_Mat2Rect(m_PrimeFrame_WithROIEdge);//��ʾ�ڿؼ���
	}
	m_RectPoint_Flag=-1;
	CBCGPDialog::OnLButtonUp(nFlags, point);
}

void CCar_DetectionDlg::OnDestroy()
{
	CBCGPDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	//m_RecordROI_4point();

	CString Para;
	for(int i=0;i<M_NUMOFPARA;i++)//�������
	{
		Para.Format(L"M_Para_%d",i);
		theApp.WriteInt(Para,m_AllPara_Int[i]);
	}
}

void CCar_DetectionDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_RectPoint_Flag=-1;

	int ctrl_State=GetKeyState(VK_CONTROL);
	if(ctrl_State<0)
	{//������Ctrl
		ROIS_4Point.resize(ROIS_4Point.size());
		ROIS_4Point.pop_back();

		m_DrawLaneRect();//���ƾ���
		m_ShowArea_Prime.m_Mat2Rect(m_PrimeFrame_WithROIEdge);//��ʾ�ڿؼ���
	}

	CBCGPDialog::OnRButtonDown(nFlags, point);
}

// ��¼�����ͽ��
void CCar_DetectionDlg::m_SumRecordToPara(void)
{
	UpdateData(true);
	CString temp=m_Edit_Para_Val;
	m_Para_String=m_Edit_Para_Val;//ֻ��¼��������ַ���
	CString temp1;
	int Index;
	for(int i=0;i<M_NUMOFPARA;i++)
	{
		Index=temp.Find('(');
		temp=temp.Right(temp.GetLength()-Index-1);
		
		Index=temp.Find(')');
		temp1=temp.Left(Index);
		m_AllPara_Int[i]=_ttoi(temp1);
	}
	UpdateData(false);
}
// �����ĳ�ʼ��
void CCar_DetectionDlg::m_RecordParaInit(void)
{
	CString temp="�������ã�\r\n";
	CString temp1;

	for(int i=0;i<M_NUMOFPARA;i++)
	{
		temp1.Format(L"=(%d)",m_AllPara_Int[i]);
		temp=temp+m_AllPara_String[i]+temp1+"\r\n";
	}
	m_Edit_Para_Val=temp;
	if(m_IfCleanRecordWhenParaInit)
	{
		for(int i=0;i<M_NUMOFRECORD;i++)
		{
			m_AllRecord_String[i].Empty();
		}
	}
	m_IfCleanRecordWhenParaInit=false;
	UpdateData(false);
}

// ��¼����
void CCar_DetectionDlg::m_RecordUpdate(void)
{
	m_Edit_Para_Val=m_Para_String+"\r\n���ݼ�¼��\r\nͼƬ��ַ��"+m_PrimePicture_Route+"\r\n";
	CString temp;
	for(int i=0;i<M_NUMOFRECORD;i++)
	{
		temp.Format(L"\r\n��¼%d:\r\n",i+1);
		m_Edit_Para_Val=m_Edit_Para_Val+temp+m_AllRecord_String[i]+"\r\n";
	}
	UpdateData(false);
}

//�����¼
void CCar_DetectionDlg::OnBnClickedBtnSaveRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter=L"(*.txt)|*.txt||";
	CFileDialog dlg(false,NULL,NULL,OFN_EXPLORER|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_FILEMUSTEXIST,strFilter);
	dlg.DoModal();
	strFilter=dlg.GetPathName();
	CStdioFile savefile(strFilter+L".txt",CFile::modeCreate|CFile::typeBinary|CFile::modeWrite);
	WORD unicodeFlag = 0xFEFF;
	savefile.Write((void*)&unicodeFlag, sizeof(WORD));
	savefile.WriteString(m_Edit_Para_Val);
	savefile.Close();
}


void CCar_DetectionDlg::OnBnClickedBtnParaDefault()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i=0;i<M_NUMOFPARA;i++)
	{
		m_AllPara_Int[i]=m_AllPara_Int_Default[i];
	}
	m_RecordParaInit();
}

//��ȡ�����ROI��Ϣ ����������򷵻�false
bool CCar_DetectionDlg::m_ReadCamROI_Info(CString CamID)
{
	ROIS_4Point.clear();//ԭ�㼯���
	m_trans_ROI_Points.clear();//�任�㼯���

	m_Mat_ROI_vector.clear();//ROIͼ�����
	m_transform_Mat_vector.clear();//�任�������

	xml_ROI.ResetPos();//��λ����һ���ֵ�֮ǰ
	xml_ROI.FindElem();//CAM_ID
	xml_ROI.IntoElem();//����

	bool ifFind=false;
	while(xml_ROI.FindElem())
	{
		CString tagName=xml_ROI.GetTagName();
		if(CamID==tagName)
		{
			ifFind=true;
			break;
		}
	}
	
	if(ifFind)
	{//����ҵ�
		int roi_num=_ttoi(xml_ROI.GetAttrib(L"ROI_NUM"));
		m_trans_Rect_Width=_ttoi(xml_ROI.GetAttrib(L"T_Width"));
		m_trans_Rect_Height=_ttoi(xml_ROI.GetAttrib(L"T_Height"));

		CString save_Addr;
		string save_addr;

		for(int i=0;i<roi_num;i++)
		{//������ROI���������
			m_Mat_ROI_vector.push_back(Mat(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC1,Scalar::all(0)));
			
			CString str;
			str.Format(L"Points_%d",i);
			xml_ROI.FindChildElem(str);//�ҵ�Points_roi_num

			vector<Point> points;
			vector<Point> roi_points;
			vector<Point2f> corners(4);  
			vector<Point2f> corners_trans(4);
			int x,y;
			for(int j=0;j<4;j++)
			{//��Points_roi_num 4�������
				str.Format(L"P%d.x",j); 
				str=xml_ROI.GetChildAttrib(str);
				x=_ttoi(str);
				str.Format(L"P%d.y",j); 
				str=xml_ROI.GetChildAttrib(str);
				y=_ttoi(str);
				points.push_back(Point(x,y));
				corners[j]=Point(x,y);//ԭ

				str.Format(L"TP%d.x",j); 
				str=xml_ROI.GetChildAttrib(str);
				x=_ttoi(str);
				str.Format(L"TP%d.y",j); 
				str=xml_ROI.GetChildAttrib(str);
				y=_ttoi(str);
				roi_points.push_back(Point(x,y));
				corners_trans[j]=Point(x,y);//�� 
			}
			ROIS_4Point.push_back(points);
			m_trans_ROI_Points.push_back(roi_points);

			Mat trans = getPerspectiveTransform(corners,corners_trans);  //��ñ任����
			m_transform_Mat_vector.push_back(Mat(trans.size(),trans.type()));
			m_transform_Mat_vector[i]=trans;

			save_Addr.Format(L"%s\\%s_ROI_%d.png",m_ROI_Path,m_PrimePicture_CAMName,i);//eg: ..\Cam1_ROI_0.png
			save_addr=CT2A(save_Addr.GetBuffer());
			m_Mat_ROI_vector[i]=imread(save_addr,0);
  		}
		save_Addr.Format(L"%s\\%s_ROI_All.png",m_ROI_Path,m_PrimePicture_CAMName);//eg: ..\Cam1_ROI_0.png
		save_addr=CT2A(save_Addr.GetBuffer());
		m_Mat_ROI=imread(save_addr,0);
	}
	else
	{
		BCGPMessageBox(L"��ǰ���û������ROI");
	}
	return true;
}

void CCar_DetectionDlg::m_WriteCamROI_Info(CString CamID)
{
	xml_ROI.ResetPos();//��λ����һ���ֵ�֮ǰ
	xml_ROI.FindElem();//CAM_ID
	xml_ROI.IntoElem();//����

	while(xml_ROI.FindElem())
	{
		CString tagName=xml_ROI.GetTagName();
		if(CamID==tagName)
		{
			xml_ROI.RemoveElem();
			break;
		}
	}

	xml_ROI.AddElem(CamID);
	xml_ROI.AddAttrib(L"ROI_NUM",ROIS_4Point.size());
	xml_ROI.AddAttrib(L"T_Width",m_trans_Rect_Width);
	xml_ROI.AddAttrib(L"T_Height",m_trans_Rect_Height);
	xml_ROI.IntoElem();
	CString str;
	CString save_Addr;
	String save_addr;
	for(int i=0;i<ROIS_4Point.size();i++)
	{//��¼��ǰ����ROI�ĵ�
		str.Format(L"Points_%d",i);
		xml_ROI.AddElem(str);
		xml_ROI.AddAttrib(L"TP0.x",m_trans_ROI_Points[i][0].x);xml_ROI.AddAttrib(L"TP0.y",m_trans_ROI_Points[i][0].y);
		xml_ROI.AddAttrib(L"TP1.x",m_trans_ROI_Points[i][1].x);xml_ROI.AddAttrib(L"TP1.y",m_trans_ROI_Points[i][1].y);
		xml_ROI.AddAttrib(L"TP2.x",m_trans_ROI_Points[i][2].x);xml_ROI.AddAttrib(L"TP2.y",m_trans_ROI_Points[i][2].y);
		xml_ROI.AddAttrib(L"TP3.x",m_trans_ROI_Points[i][3].x);xml_ROI.AddAttrib(L"TP3.y",m_trans_ROI_Points[i][3].y);
		xml_ROI.AddAttrib(L"P0.x",ROIS_4Point[i][0].x);xml_ROI.AddAttrib(L"P0.y",ROIS_4Point[i][0].y);
		xml_ROI.AddAttrib(L"P1.x",ROIS_4Point[i][1].x);xml_ROI.AddAttrib(L"P1.y",ROIS_4Point[i][1].y);
		xml_ROI.AddAttrib(L"P2.x",ROIS_4Point[i][2].x);xml_ROI.AddAttrib(L"P2.y",ROIS_4Point[i][2].y);
		xml_ROI.AddAttrib(L"P3.x",ROIS_4Point[i][3].x);xml_ROI.AddAttrib(L"P3.y",ROIS_4Point[i][3].y);
		
		save_Addr.Format(L"%s\\%s_ROI_%d.png",m_ROI_Path,m_PrimePicture_CAMName,i);//eg: ..\Cam1_ROI_0.png
		save_addr=CT2A(save_Addr.GetBuffer());
		imwrite(save_addr,m_Mat_ROI_vector[i]);
	}
	save_Addr.Format(L"%s\\%s_ROI_All.png",m_ROI_Path,m_PrimePicture_CAMName);
	save_addr=CT2A(save_Addr.GetBuffer());
	imwrite(save_addr,m_Mat_ROI);

	xml_ROI.Save(m_ROI_XML_Path);
}

//�õ������ַ��е��ַ��������������ַ�
CString CCar_DetectionDlg::m_GetStringBy2Sign(CString src,char c1,char c2)
{
	int IndexTemp=src.Find(c1);
	CString str=src.Right(src.GetLength()-IndexTemp-1);
	IndexTemp=str.Find(c2);
	str=str.Left(IndexTemp);
	if(str.IsEmpty())
	{
		str="DEFAULT";
	}
	return str;
}
