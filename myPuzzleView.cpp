
// myPuzzleView.cpp: CmyPuzzleView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
//#include "myPuzzle.h"
#include "myPuzzle.h"
#include "myPuzzleDoc.h"
#include "myPuzzleView.h"
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//출력 좌표
#define CRD_BT_DOWNRIGHT 400
#define CRD_BT_UPLEFT 604
#define CRD_BT_STARTRIGHT 594
#define CRD_BT_STARTLEFT 410
#define CRD_SINGLEMODE_LTX

//버튼 사이즈
#define SZ_BT_WIDTH 120
#define SZ_BT_HEIGHT 60

// CmyPuzzleView

IMPLEMENT_DYNCREATE(CmyPuzzleView, CView)

BEGIN_MESSAGE_MAP(CmyPuzzleView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_BN_CLICKED(2000, OnStartButtonCliked)
	ON_BN_CLICKED(2001, OnmodeDownButtonCliked)
	ON_BN_CLICKED(2002, OnmodeUpButtonCliked)
	ON_BN_CLICKED(2003, OnnDownButtonCliked)
	ON_BN_CLICKED(2004, OnnUpButtonCliked)
	ON_CONTROL_RANGE(BN_CLICKED, 2007, 2009, RadioCtrl)
	
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CmyPuzzleView 생성/소멸

CmyPuzzleView::CmyPuzzleView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CmyPuzzleView::~CmyPuzzleView()
{
}

BOOL CmyPuzzleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CmyPuzzleView 그리기


void CmyPuzzleView::OnStartButtonCliked()
{
	gm.SetInGame(true);
	SetActiveBts(SW_HIDE);
	SetActiveDiffBts(SW_HIDE);
	gm.initBrds();
	Invalidate();
}

void CmyPuzzleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_title.Load(L"title.png");
	CreateBts();
}

void CmyPuzzleView::OnDraw(CDC* pDC)
{
	if (!gm.InGame())
	{
		ShowMenuWnd(pDC);
	}
	else if (gm.GetGameMode() == _1P)
	{
		Show1PWnd(pDC);
		if (gm.brds[_1P].isSolve())
		{
			AfxMessageBox(_T("You solved the puzzle!"));
			gm.SetInGame(false);
			Invalidate();
		}
	}
	else if (gm.GetGameMode() == _2P)
	{
		Show2PWnd(pDC);
		if (gm.brds[_1P].isSolve())
		{
			AfxMessageBox(_T("1P solved the puzzle!"));
			gm.SetInGame(false);
			Invalidate();
		}
		if (gm.brds[_2P].isSolve())
		{
			AfxMessageBox(_T("2P solved the puzzle!"));
			gm.SetInGame(false);
			Invalidate();
		}
	}
	/*CmyPuzzleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc)
		return;*/

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

}
// CmyPuzzleView 진단

#ifdef _DEBUG
void CmyPuzzleView::AssertValid() const
{
	CView::AssertValid();
}

void CmyPuzzleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmyPuzzleDoc* CmyPuzzleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmyPuzzleDoc)));
	return (CmyPuzzleDoc*)m_pDocument;
}
#endif //_DEBUG

void CmyPuzzleView::ShowMenuWnd(CDC* pDC)
{
	SetActiveBts(SW_SHOW);
	if (gm.GetGameMode() == VSCOMPUTER)
		SetActiveDiffBts(SW_SHOW);
	else
		SetActiveDiffBts(SW_HIDE);

	m_title.Draw(pDC->GetSafeHdc(), 235, 50);

	CString mode, brdSize;
	switch (gm.GetGameMode())
	{
	case _1P:
		mode = L"        1 Player        ";
		break;
	case _2P:
		mode = L"        2 Player        ";
		break;
	case VSCOMPUTER:
		mode = L"    VS. COMPUTER    ";
		break;
	case SIMULATION:
		mode = L"     SIMULATION     ";
		break;
	default:
		break;
	}
	brdSize.Format(_T("%d X %d"), gm.GetSize(), gm.GetSize());
	pDC->DrawText(mode, CRect(CRD_BT_DOWNRIGHT, 360, CRD_BT_UPLEFT, 420), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	pDC->DrawText(brdSize, CRect(CRD_BT_DOWNRIGHT, 460, CRD_BT_UPLEFT, 520), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void CmyPuzzleView::Show1PWnd(CDC* pDC)
{
	const int SMLTX = 290, SMLTY = 100; //Single Mode Left Top Coordinate;
	const CPoint leftTop(SMLTX, SMLTY);
	gm.brds[_1P].DrawBrd(pDC, CELLSIZE, leftTop);
}

void CmyPuzzleView::Show2PWnd(CDC* pDC)
{
	const int P2LTX = 50, P2LTY = 100, P1LTX = 519, P1LTY = 100;
	const CPoint leftTop1P(P1LTX, P1LTY), leftTop2P(P2LTX, P2LTY);
	gm.brds[_1P].DrawBrd(pDC, CELLSIZE, leftTop1P);
	gm.brds[_2P].DrawBrd(pDC, CELLSIZE, leftTop2P);
}

void CmyPuzzleView::CreateBts()
{
	btStart.Create(_T("START"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CRD_BT_STARTLEFT, 230, CRD_BT_STARTRIGHT, 300), this, 2000);
	btModeDown.Create(_T("◀"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CRD_BT_DOWNRIGHT - SZ_BT_WIDTH, 360, CRD_BT_DOWNRIGHT, 420), this, 2001);
	btModeUp.Create(_T("▶"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CRD_BT_UPLEFT, 360, CRD_BT_UPLEFT + SZ_BT_WIDTH, 420), this, 2002);
	btnDown.Create(_T("◀"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CRD_BT_DOWNRIGHT - SZ_BT_WIDTH, 460, CRD_BT_DOWNRIGHT, 520), this, 2003);
	btnUp.Create(_T("▶"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CRD_BT_UPLEFT, 460, CRD_BT_UPLEFT + SZ_BT_WIDTH, 520), this, 2004);
	btDiffEasy.Create(_T("EASY"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, CRect(345, 630, 445, 665), this, 2007);
	btDiffNormal.Create(_T("NORMAL"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(460, 630, 560, 665), this, 2008);
	btDiffHard.Create(_T("HARD"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(590, 630, 675, 665), this, 2009);
	btGroupBox.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, CRect(330, 620, 680, 670), this, 2010);
	btDiffEasy.SetCheck(BST_CHECKED);
}

void CmyPuzzleView::SetActiveBts(int n)
{
	btStart.ShowWindow(n);
	btModeUp.ShowWindow(n);
	btModeDown.ShowWindow(n);
	btnUp.ShowWindow(n);
	btnDown.ShowWindow(n);
}

void CmyPuzzleView::SetActiveDiffBts(int n)
{
	btDiffEasy.ShowWindow(n);
	btDiffNormal.ShowWindow(n);
	btDiffHard.ShowWindow(n);
	btGroupBox.ShowWindow(n);
}

// CmyPuzzleView 메시지 처리기
void CmyPuzzleView::OnnUpButtonCliked() { if (gm.GetSize() < 5) gm.SetSizeUp();	Invalidate(false); }
void CmyPuzzleView::OnnDownButtonCliked() { if (gm.GetSize() > 3) gm.SetSizeDown();	Invalidate(false); }
void CmyPuzzleView::OnmodeUpButtonCliked() { if (gm.GetGameMode() < 3)gm.SetGameMode(gm.GetGameMode()+ 1);	Invalidate(false); }
void CmyPuzzleView::OnmodeDownButtonCliked() { if (gm.GetGameMode() > 0) gm.SetGameMode(gm.GetGameMode() - 1);	Invalidate(false); }
void CmyPuzzleView::RadioCtrl(UINT radioNum)
{
	UpdateData(true);
	switch (radioNum)
	{
	case 1007:
		gm.SetDiff(EASY);
		AfxMessageBox(L"DIFFICULTY : EASY");
		break;
	case 1008:
		gm.SetDiff(NORM);
		AfxMessageBox(L"DIFFICULTY : NORMAL");
		break;

	case 1009:
		gm.SetDiff(HARD);
		AfxMessageBox(L"DIFFICULTY : HARD");
		break;

	defalut:
		break;
	}
	UpdateData(false);
}

void CmyPuzzleView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!gm.InGame())
		return;
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	if (gm.GetGameMode() == _1P)
	{
		gm.brds[_1P].MoveTile(nChar);
	}
	else if (gm.GetGameMode() == _2P)
	{
		gm.brds[_1P].MoveTile(nChar);
		gm.brds[_2P].MoveTile2p(nChar);
	}
	Invalidate(false);
}