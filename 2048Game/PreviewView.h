#pragma once

#include <memory>

#include "Button.h"
#include "FontFactory.h"

// PreviewView view

using std::shared_ptr;

class PreviewView : public CView
{
	DECLARE_DYNCREATE(PreviewView)

	shared_ptr<Button> m_startButton;
	shared_ptr<Button> m_aboutButton;
	shared_ptr<LOGFONT> m_titleFont;

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


