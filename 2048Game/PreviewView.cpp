// PreviewView.cpp : implementation file
//

#include "stdafx.h"
#include "2048Game.h"
#include "PreviewView.h"
#include "MainFrm.h"

// PreviewView

IMPLEMENT_DYNCREATE(PreviewView, CView)

PreviewView::PreviewView() :
	m_startButton(new Button(IDS_START_GAME, RGB(246, 132, 96), RGB(255, 255, 255), CPoint(), CSize())),
	m_aboutButton(new Button(IDS_ABOUT, RGB(144, 122, 102), RGB(255, 255, 255), CPoint(), CSize())),
	m_titleFont(FontFactory::CreateFont(100))
{
}

PreviewView::~PreviewView()
{
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
	m_startButton->position.SetPoint(rect.Width() * .2, rect.Height() * .5);
	m_startButton->size.SetSize(rect.Width() * .8, rect.Height() * .57);
	m_aboutButton->position.SetPoint(rect.Width() * .2, rect.Height() * .6);
	m_aboutButton->size.SetSize(rect.Width() * .8, rect.Height() * .67);

	m_startButton->OnDraw(pDC);
	m_aboutButton->OnDraw(pDC);

	CFont font;
	CFont* font_st;

	font_st = pDC->SelectObject(&font);

	font.CreateFontIndirect(m_titleFont.get());
	pDC->SelectObject(&font);
	pDC->DrawTextW(L"2048", rect, DT_CENTER | DT_SINGLELINE);

	pDC->SelectObject(font_st);
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
	if (!m_startButton || !m_aboutButton) return;

	if (m_startButton->PtInRect(point))
		((CMainFrame*)AfxGetMainWnd())->StartGame();
	else if (m_aboutButton->PtInRect(point)) {
		// show about
	}
}
