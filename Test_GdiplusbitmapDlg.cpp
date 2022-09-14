
// Test_GdiplusbitmapDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_Gdiplusbitmap.h"
#include "Test_GdiplusbitmapDlg.h"
#include "afxdialogex.h"

#include "../../Common/Functions.h"
#include "../../Common/MemoryDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestGdiplusbitmapDlg 대화 상자



CTestGdiplusbitmapDlg::CTestGdiplusbitmapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_GDIPLUSBITMAP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGdiplusbitmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestGdiplusbitmapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestGdiplusbitmapDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestGdiplusbitmapDlg::OnBnClickedCancel)
	ON_WM_ERASEBKGND()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestGdiplusbitmapDlg 메시지 처리기

BOOL CTestGdiplusbitmapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_img_back.Load(IDB_WINDOW, _T("JPG"));
	m_img_back.clone(&m_cream);
	//m_img_back.deep_copy(&m_copied);
	m_cream.Load(IDB_APPLE, _T("PNG"));
	//m_cream.save(_T("d:\\temp\\cream.jpg"));
	//m_cream.save(_T("d:\\temp\\cream.png"));
	m_cream.clone(&m_copied);
	//m_copied.set_colorkey(Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	//m_copied.set_transparent(0.5);
	//m_copied.rotate(45);
	//m_img_back.rotate(Gdiplus::Rotate90FlipY);

	int cx = 0;
	int cy = 100;
	int tx = 100;
	int ty = 100;
	m_r = CRect(200, 200, 500, 300);
	m_rotated = m_r;
	get_rotated(cx, cy, &tx, &ty, -90);
	m_pts = get_rotated(m_r.CenterPoint().x, m_r.CenterPoint().y, &m_rotated, 25);
	//TRACE()

	RestoreWindowPosition(&theApp, this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestGdiplusbitmapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestGdiplusbitmapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rc;
		CPaintDC dc1(this);

		GetClientRect(rc);

		//배경을 그려주고 이미지를 그리므로 여기서는 CMemoryDC를 이용하여 더블버퍼링을 해줘야 안깜빡인다.
		CMemoryDC	dc(&dc1, &rc, false);
		Graphics	g(dc.m_hDC, rc);

		int w = m_img_back.m_pBitmap->GetWidth();
		int h = m_img_back.m_pBitmap->GetHeight();


		//dc.FillSolidRect(rc, m_crBack);
		//g.DrawImage(m_img_back, Rect(0, 0, rc.Width(), rc.Height()), 0, 0, w, h, UnitPixel, &ia);
		g.DrawImage(m_img_back, 0, 0, rc.Width(), rc.Height());
		//g.DrawImage(m_img_back, (int)(rc.CenterPoint().x - m_img_back.m_pBitmap->GetWidth()/2), (int)(rc.CenterPoint().y - m_img_back.m_pBitmap->GetHeight()/2));

		w = m_copied.width();
		h = m_copied.height();

		g.DrawImage(m_copied, rc.CenterPoint().x - w/2, rc.CenterPoint().y - h/2, w, h);
		//ia.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		//g.DrawImage(m_copied, Rect(100, 100, m_copied.width(), m_copied.height()), 0, 0, w, h, UnitPixel, &ia);

		DrawLine(&dc, 0, 0, rc.right, rc.bottom, red);
		DrawLine(&dc, 0, rc.bottom, rc.right, 0, red);

		//DrawRectangle(&dc, m_r, blue);
		//DrawRectangle(&dc, m_rotated, violet);
		//draw_polygon(&dc, m_pts, true, lightgreen, 1);
		/*
		g.DrawImage(m_file_image,
			(int)(rc.Width() - m_file_image->GetWidth() - 20),
			(int)(rc.Height() - m_file_image->GetHeight() - 50),
			m_file_image->GetWidth(),
			m_file_image->GetHeight());
		*/
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestGdiplusbitmapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestGdiplusbitmapDlg::OnBnClickedOk()
{
	int degree = 0;

	while (!m_closed)
	{
		/*
		m_rotated = m_r;
		m_pts = get_rotated(m_r.CenterPoint().x, m_r.CenterPoint().y, &m_rotated, degree);
		*/
		long t0 = clock();
		//m_cream.deep_copy(&m_copied);
		m_cream.clone(&m_copied);
		TRACE(_T("clone  = %ld ms\n"), clock() - t0);
		t0 = clock();
		m_copied.rotate(degree, false);
		TRACE(_T("rotate = %ld ms\n"), clock() - t0);
		//CString str;
		//str.Format(_T("d:\\temp\\%03d.png"), degree);
		//m_copied.save(str);
		t0 = clock();
		Invalidate();
		TRACE(_T("Invalidate = %ld ms\n"), clock() - t0);
		Wait(10);
		degree += 1;
		if (degree > 360)
			degree = 0;
	}
}


void CTestGdiplusbitmapDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_closed = true;
	CDialogEx::OnCancel();
}


BOOL CTestGdiplusbitmapDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CTestGdiplusbitmapDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveWindowPosition(&theApp, this);
}


void CTestGdiplusbitmapDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Invalidate();
}


BOOL CTestGdiplusbitmapDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE :
			m_closed = true;
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
