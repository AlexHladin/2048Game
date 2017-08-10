
// 2048GameView.h : interface of the CMy2048GameView class
//

#pragma once

#include "StringContainer.h"

class CMy2048GameView : public CView
{
private:
	StringContainer* pointsContainer;

protected: // create from serialization only
	CMy2048GameView();
	DECLARE_DYNCREATE(CMy2048GameView)

// Attributes
public:
	CMy2048GameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
protected:

// Implementation
public:
	virtual ~CMy2048GameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in 2048GameView.cpp
inline CMy2048GameDoc* CMy2048GameView::GetDocument() const
   { return reinterpret_cast<CMy2048GameDoc*>(m_pDocument); }
#endif

