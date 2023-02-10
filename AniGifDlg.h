#pragma once

#include <deque>
#include "../../Common/Functions.h"
#include "../../Common/GdiPlusBitmap.h"

// CAniGifDlg 대화 상자

class CAniGifDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAniGifDlg)

public:
	CAniGifDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAniGifDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIGIF };
#endif

protected:
	enum TIMER
	{
		timer_animate = 0,
	};

	void	render();
	CGdiplusBitmap	m_img;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
