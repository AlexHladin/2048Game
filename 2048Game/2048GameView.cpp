
// 2048GameView.cpp : implementation of the CMy2048GameView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "2048Game.h"
#endif

#include "2048GameDoc.h"
#include "2048GameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2048GameView

IMPLEMENT_DYNCREATE(CMy2048GameView, CView)

BEGIN_MESSAGE_MAP(CMy2048GameView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy2048GameView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy2048GameView construction/destruction

CMy2048GameView::CMy2048GameView()
{
	pointsContainer = 0;
}

CMy2048GameView::~CMy2048GameView()
{
	if (pointsContainer)
		delete pointsContainer;
}


void CMy2048GameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	pointsContainer = new StringContainer(IDS_POINTS, &GetDocument()->points, new CPoint(0, 0));
}

// CMy2048GameView drawing

void CMy2048GameView::OnDraw(CDC* pDC)
{
	CMy2048GameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc || !pDoc->cell || !pointsContainer)
		return;

	CRect rect;
	GetClientRect(&rect);

	float size = (min(rect.right, rect.bottom) - pointsContainer->GetHeight() - 10) / pDoc->size;

	float x = 0, y = 0, offset = .05f * size;

	pointsContainer->position->SetPoint(offset, offset);

	CFont font;
	CFont* font_st;

	CRect valRect;
	CBrush brush;
	brush.CreateSolidBrush(pDoc->bkColor);
	CString val;

	if (pDoc->start && pDoc->cell) {
		while (true) {
			int i = rand() % pDoc->size;
			int j = rand() % pDoc->size;
			val.Format(L"(%d, %d)", i, j);

			if (pDoc->cell[i][j] == 0) {
				pDoc->cell[i][j] = (rand() % 2) * 2;
				break;
			}
		}
	}
	else {
		if (pDoc->cell)
			AfxMessageBox(IDS_LOSE);
	}

	if (pDoc->cell) {
		font_st = pDC->SelectObject(&font);

		font.CreateFontIndirect(&pDoc->fontText);
		pDC->SetBkColor(pDoc->bkColor);
		pDC->SetTextColor(RGB(255, 255, 255));

		pDC->SelectObject(&font);

		int oldBkMode, oldBkColor;
		float startY = pointsContainer->GetHeight() + 2 * offset;

		// draw background rect		
		CBrush b(RGB(188, 176, 162));
		CPen p;
		p.CreatePen(PS_SOLID, 0, RGB(188, 176, 162));
		CBrush* oldB = pDC->SelectObject(&b);
		CPen* oldP = pDC->SelectObject(&p);

		CRect bkRect(0, startY, size * pDoc->size, startY + size * pDoc->size);
		pDC->RoundRect(bkRect, CPoint(10, 10));

		pDC->SelectObject(oldB);
		pDC->SelectObject(oldP);
		//

		for (int i = 0; i < pDoc->size; i++) {
			y = startY;
			for (int j = 0; j < pDoc->size; j++) {
				valRect.left = x + offset;
				valRect.top = y + offset;
				valRect.right = x + size - offset;
				valRect.bottom = y + size - offset;

				int color = GetColorByNumber(pDoc->cell[i][j]);

				CPen pen;
				pen.CreatePen(PS_SOLID, 0, color);
				CBrush brush(color);
				CBrush* oldBrush = pDC->SelectObject(&brush);
				CPen* oldPen = pDC->SelectObject(&pen);
				int oldBkMode = pDC->SetBkMode(TRANSPARENT);
				
				pDC->RoundRect(valRect, CPoint(10, 10));

				if (pDoc->cell[i][j]) {
					int oldTextColor = 0;
					if (pDoc->cell[i][j] < 8)
						oldTextColor = pDC->SetTextColor(RGB(126, 117, 100));

					val.Format(L"%d", pDoc->cell[i][j]);
					pDC->DrawTextW(val, valRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

					if (oldTextColor)
						pDC->SetTextColor(oldTextColor);
				}

				y += size;

				pDC->SetBkMode(oldBkMode);
				pDC->SelectObject(oldPen);
				pDC->SelectObject(oldBrush);
			}
			x += size;
		}
		
		pointsContainer->OnDraw(pDC);

		pDC->SelectObject(font_st);
	}
}


void CMy2048GameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy2048GameView diagnostics

#ifdef _DEBUG
void CMy2048GameView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2048GameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2048GameDoc* CMy2048GameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2048GameDoc)));
	return (CMy2048GameDoc*)m_pDocument;
}
#endif //_DEBUG

void CMy2048GameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMy2048GameDoc* pDoc = GetDocument();
	
	if (!pDoc->start) return;

	int plus = 0;
	int score = 0;
	if (nChar == 37) {
		for (int j = 0; j < pDoc->size; j++) {
			for (int i = 0; i < pDoc->size; i++) {
				for (int k = i + 1; k < pDoc->size; k++) {
					if (pDoc->cell[k][j] != 0) {
						if (pDoc->cell[i][j] == 0) {
							pDoc->cell[i][j] = pDoc->cell[k][j];
							pDoc->cell[k][j] = 0;
						} else {
							if (pDoc->cell[i][j] == pDoc->cell[k][j]) {
								pDoc->cell[i][j] += pDoc->cell[k][j];
								pDoc->points += pDoc->cell[i][j];
								pDoc->cell[k][j] = 0;
							}
							break;
						}
					}
				}
			}
		}
	}
	else if (nChar == 38) {
		for (int j = 0; j < pDoc->size; j++)
		{
			for (int i = 0; i < pDoc->size; i++)
			{
				for (int k = i + 1; k < pDoc->size; k++)
				{
					if (pDoc->cell[j][k] != 0)
					{
						if (pDoc->cell[j][i] == 0)
						{
							pDoc->cell[j][i] = pDoc->cell[j][k];
							pDoc->cell[j][k] = 0;
						}
						else
						{
							if (pDoc->cell[j][i] == pDoc->cell[j][k])
							{
								pDoc->cell[j][i] += pDoc->cell[j][k];
								pDoc->points += pDoc->cell[j][i];
								pDoc->cell[j][k] = 0;
							}
							break;
						}
					}
				}
			}
		}
	}
	else if (nChar == 39) {
		for (int j = pDoc->size - 1; j >= 0; j--)
		{
			for (int i = pDoc->size - 1; i >= 0; i--)
			{
				for (int k = i - 1; k >= 0; k--)
				{
					if (pDoc->cell[k][j] != 0)
					{
						if (pDoc->cell[i][j] == 0)
						{
							pDoc->cell[i][j] = pDoc->cell[k][j];
							pDoc->cell[k][j] = 0;
						}
						else
						{
							if (pDoc->cell[i][j] == pDoc->cell[k][j])
							{
								pDoc->cell[i][j] += pDoc->cell[k][j];
								pDoc->points += pDoc->cell[i][j];
								pDoc->cell[k][j] = 0;
							}
							break;
						}
					}
				}
			}
		}
	}
	else if (nChar == 40) {
		for (int j = pDoc->size - 1; j >= 0; j--) {
			for (int i = pDoc->size - 1; i >= 0; i--) {
				for (int k = i - 1; k >= 0; k--)
				{
					if (pDoc->cell[j][k] != 0)
					{
						if (pDoc->cell[j][i] == 0)
						{
							pDoc->cell[j][i] = pDoc->cell[j][k];
							pDoc->cell[j][k] = 0;
						}
						else
						{
							if (pDoc->cell[j][i] == pDoc->cell[j][k])
							{
								pDoc->cell[j][i] += pDoc->cell[j][k];
								pDoc->points += pDoc->cell[j][i];
								pDoc->cell[j][k] = 0;
							}
							break;
						}
					}
				}
			}
		}
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
