#pragma once
class StringContainer
{
public:
	CString* descriptionText;
	int* value;
	CPoint* position;
	CFont descriptionTextFont;
	CFont valueTextFont;
	int margin;

	StringContainer(int msgId, int* value, CPoint* position);
	~StringContainer();

	int GetWidth();
	int GetHeight();

	void OnDraw(CDC* pDC);
};

