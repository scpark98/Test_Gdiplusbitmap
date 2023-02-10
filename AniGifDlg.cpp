// AniGifDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Test_Gdiplusbitmap.h"
#include "AniGifDlg.h"
#include "afxdialogex.h"


// CAniGifDlg 대화 상자

IMPLEMENT_DYNAMIC(CAniGifDlg, CDialogEx)

CAniGifDlg::CAniGifDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANIGIF, pParent)
{

}

CAniGifDlg::~CAniGifDlg()
{
}

void CAniGifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAniGifDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CAniGifDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAniGifDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAniGifDlg 메시지 처리기


BOOL CAniGifDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_img.load(_T("c:\\scpark\\media\\test_image\\24.gif"));
	//m_img.back_color(Gdiplus::Color::Transparent);
	m_img.set_animation(m_hWnd);
	render();

	SetTimer(timer_animate, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAniGifDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == timer_animate)
	{
		render();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CAniGifDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CAniGifDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
	m_img.stop_animation();
	Wait(500);
	CDialogEx::OnCancel();
}

void CAniGifDlg::render(void)
{
	if (!IsWindow(m_hWnd) || m_img.empty())
		return;

	int width = m_img.width;
	int height = m_img.height;
	RECT rc;
	::GetWindowRect(m_hWnd, &rc);
	POINT ptSrc = { 0, 0 };
	POINT ptWinPos = { rc.left, rc.top };
	SIZE szWin = { width, height };
	BLENDFUNCTION stBlend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };


	HDC hDC = ::GetDC(m_hWnd);
	HDC hdcMemory = ::CreateCompatibleDC(hDC);

	BITMAPINFOHEADER bmih = { 0 };
	int nBytesPerLine = ((width * 32 + 31) & (~31)) >> 3;
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = width;
	bmih.biHeight = height;
	bmih.biPlanes = 1;
	bmih.biBitCount = 32;
	bmih.biCompression = BI_RGB;
	bmih.biClrUsed = 0;
	bmih.biSizeImage = nBytesPerLine * height;

	PVOID pvBits = NULL;
	HBITMAP hbmpMem = ::CreateDIBSection(NULL, (PBITMAPINFO)&bmih, DIB_RGB_COLORS, &pvBits, NULL, 0);
	ASSERT(hbmpMem != NULL);
	memset(pvBits, 0, width * 4 * height);
	if (hbmpMem)
	{
		HGDIOBJ hbmpOld = ::SelectObject(hdcMemory, hbmpMem);
		Graphics g(hdcMemory);

		g.SetPageScale(1.0);
		g.SetPageUnit(UnitPixel);
		g.SetSmoothingMode(SmoothingModeNone);

		g.DrawImage(m_img, 0, 0, width, height);

		::UpdateLayeredWindow(m_hWnd
			, hDC
			, &ptWinPos
			, &szWin
			, hdcMemory
			, &ptSrc
			, 0
			, &stBlend
			, ULW_ALPHA
		);


		g.ReleaseHDC(hdcMemory);
		::SelectObject(hdcMemory, hbmpOld);
		::DeleteObject(hbmpMem);
	}

	::DeleteDC(hdcMemory);
	::DeleteDC(hDC);
}
