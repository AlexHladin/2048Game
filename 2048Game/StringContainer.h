#pragma once
class StringContainer
{
private:
	int width;
	int height;

public:
	CString* descriptionText;
	int* value;
	CPoint* position;
	CFont descriptionTextFont;
	CFont valueTextFont;
	int margin;

	StringContainer(int msgId, int* value, CPoint* position, int width = 128, int height = 128);
	~StringContainer();

	int GetWidth();
	int GetHeight();

	void OnDraw(CDC* pDC);
};

