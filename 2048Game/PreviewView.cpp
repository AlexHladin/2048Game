// PreviewView.cpp : implementation file
//

#include "stdafx.h"
#include "2048Game.h"
#include "PreviewView.h"
#include "MainFrm.h"

// PreviewView

IMPLEMENT_DYNCREATE(PreviewView, CView)

PreviewView::PreviewView()
{
	startButtonRect = 0;
	aboutButtonRect = 0;
}

PreviewView::~PreviewView()
{
	if (startButtonRect) delete startButtonRect;
	if (aboutButtonRect) delete aboutButtonRect;
}

BEGIN_MESSAGE_MAP(PreviewView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// PreviewView drawing

void PreviewView::OnDraw(CDC* pDC)
{
	// prepare objects
	CRect rect;
	GetClientRect(rect);

	CBrush orangeBrush(RGB(246, 132, 96));
	CBrush grayBrush(RGB(144, 122, 102));
	CPen orangePen(PS_SOLID, 0, RGB(246, 132, 96));
	CPen grayPen(PS_SOLID, 0, RGB(144, 122, 102));

	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldFrColor = pDC->SetTextColor(RGB(255, 255, 255));
	CBrush* oldBrush = pDC->SelectObject(&orangeBrush);
	CPen* oldPen = pDC->SelectObject(&orangePen);

	// start playing button
	CString startPlayString;
	startPlayString.LoadStringW(IDS_START_GAME);

	startButtonRect = new CRect(
		rect.Width() * .2, 
		rect.Height() * .6, 
		rect.Width() * .8, 
		rect.Height() * .67);
	pDC->RoundRect(startButtonRect, CPoint(5, 5));
	pDC->DrawTextW(startPlayString, startButtonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// about button
	CString aboutString;
	aboutString.LoadStringW(IDS_ABOUT);

	pDC->SelectObject(&grayBrush);
	pDC->SelectObject(&grayPen);

	aboutButtonRect = new CRect(startButtonRect);
	aboutButtonRect->OffsetRect(0, rect.Height() * .1);
	pDC->RoundRect(aboutButtonRect, CPoint(5, 5));
	pDC->DrawTextW(aboutString, aboutButtonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// restore objects
	pDC->SetTextColor(oldFrColor);
	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}


// PreviewView diagnostics

#ifdef _DEBUG
void PreviewView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void PreviewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// PreviewView message handlers


void PreviewView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!startButtonRect || !aboutButtonRect) return;

	if (startButtonRect->PtInRect(point)) {
		((CMainFrame*)AfxGetMainWnd())->StartGame();
		return;
	}
	else if (aboutButtonRect->PtInRect(point)) {
		// show about
	}

	CView::OnLButtonDown(nFlags, point);
}
