#pragma once

#include "Button.h"

// PreviewView view

class PreviewView : public CView
{
	DECLARE_DYNCREATE(PreviewView)

	Button* startButton;
	Button* aboutButton;

protected:
	PreviewView();           // protected constructor used by dynamic creation
	virtual ~PreviewView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


