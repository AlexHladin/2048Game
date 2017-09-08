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
	startButton = new Button(IDS_START_GAME, RGB(246, 132, 96), RGB(255, 255, 255), CPoint(), CSize());
	aboutButton = new Button(IDS_ABOUT, RGB(144, 122, 102), RGB(255, 255, 255), CPoint(), CSize());
}

PreviewView::~PreviewView()
{
	if (startButton) delete startButton;
	if (aboutButton) delete aboutButton;
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

	// recalc button size
	startButton->position.SetPoint(rect.Width() * .2, rect.Height() * .6);
	startButton->size.SetSize(rect.Width() * .8, rect.Height() * .67);
	aboutButton->position.SetPoint(rect.Width() * .2, rect.Height() * .7);
	aboutButton->size.SetSize(rect.Width() * .8, rect.Height() * .77);

	startButton->OnDraw(pDC);
	aboutButton->OnDraw(pDC);
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
	if (!startButton || !aboutButton) return;

	if (startButton->PtInRect(point))
		((CMainFrame*)AfxGetMainWnd())->StartGame();
	else if (aboutButton->PtInRect(point)) {
		// show about
	}
}
