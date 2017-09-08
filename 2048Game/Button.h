#pragma once

#include "Container.h"

class Button : public Container
{
	CString text;
	CBrush brush;
	CPen pen;
	COLORREF textColor;

public:
	Button(int textId, COLORREF backgrounColor, COLORREF textColor, CPoint position, CSize size);
	~Button();

	void OnDraw(CDC* pDC);
};

