
// myPuzzleView.h: CmyPuzzleView 클래스의 인터페이스
//

#pragma once
#include "afxwin.h"
//#include "Game.h"
//#include "Board.h"

#include <time.h>
#include <stdlib.h>
//#include "board.h"
#include "gameManager.h"

class CmyPuzzleView : public CView
{
protected: // serialization에서만 만들어집니다.
	CmyPuzzleView() noexcept;
	DECLARE_DYNCREATE(CmyPuzzleView)

protected:
	gameManager gm;
	
public:
	CButton btModeUp;
	CButton btModeDown;
	CButton btnUp;
	CButton btnDown;
	CButton btStart;
	CButton btDiffEasy;
	CButton btDiffNormal;
	CButton btDiffHard;
	CButton btGroupBox;
	CImage m_title;

	void SetActiveBts(int n);
	void SetActiveDiffBts(int n);
	void CreateBts();
	void ShowMenuWnd(CDC *pDC);
	void Show1PWnd(CDC* pDC);
	void Show2PWnd(CDC* pDC);

public:
	CmyPuzzleDoc* GetDocument() const;

public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

// 구현입니다.
public:
	virtual ~CmyPuzzleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnStartButtonCliked();
	afx_msg void OnnUpButtonCliked();
	afx_msg void OnnDownButtonCliked();
	afx_msg void OnmodeUpButtonCliked();
	afx_msg void OnmodeDownButtonCliked();
	afx_msg void RadioCtrl(UINT radioNum);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // myPuzzleView.cpp의 디버그 버전
inline CmyPuzzleDoc* CmyPuzzleView::GetDocument() const
   { return reinterpret_cast<CmyPuzzleDoc*>(m_pDocument); }
#endif