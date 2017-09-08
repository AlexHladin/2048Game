#include "stdafx.h"
#include "Button.h"


Button::Button(int textId, COLORREF backgrounColor, COLORREF textColor, CPoint position, CSize size)
	: Container(position, size)
{
	this->text.LoadStringW(textId);
	this->brush.CreateSolidBrush(backgrounColor);
	this->pen.CreatePen(PS_SOLID, 0, backgrounColor);
	this->textColor = textColor;
}

Button::~Button()
{
}

void Button::OnDraw(CDC * pDC)
{
	// set params
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldFrColor = pDC->SetTextColor(textColor);
	CBrush* oldBrush = pDC->SelectObject(&brush);
	CPen* oldPen = pDC->SelectObject(&pen);
	CRect rect(position.x, position.y, size.cx, size.cy);

	// draw
	pDC->RoundRect(rect, CPoint(5, 5));
	pDC->DrawTextW(text, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// restore
	pDC->SetTextColor(oldFrColor);
	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}
