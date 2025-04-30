
// Test_GdiplusbitmapDlg.h: 헤더 파일
//

#pragma once

#include <vector>
#include "../../Common/GdiplusBitmap.h"
#include "AniGifDlg.h"
#include "../../Common/CStatic/SCParagraphStatic/SCParagraphStatic.h"

// CTestGdiplusbitmapDlg 대화 상자
class CTestGdiplusbitmapDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestGdiplusbitmapDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CAniGifDlg	m_aniGifDlg;

	CRect m_r;
	CRect m_rotated;
	std::vector<CPoint> m_pts;
	CGdiplusBitmap m_img_back;
	CGdiplusBitmap m_img_cream;
	CGdiplusBitmap m_copied;
	CGdiplusBitmap m_gif;
	CGdiplusBitmap m_img_ico;

	bool m_closed = false;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_GDIPLUSBITMAP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CSCParagraphStatic m_static_para;
};
