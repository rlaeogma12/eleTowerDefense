#include "stdafx.h"
#include "Utility.h"
#include "resource.h"
#include "Setting.h"

////////////

/*
	Memo : PostQuitMessage 받을 시 MenuSet 삭제 안되서 메모리릭 있음.. 근데 소멸자든 OnDestroy든 쓰면 정상종료가 안됨.,,,,ㅠㅠ
*/

Utility::Utility()
{

}


Utility::~Utility()
{

}

void Utility::WriteText(CDC* pDC, CString aa, int x, int y, int width, int height, long size, CString fontname, int R, int G, int B, BOOL align) {
	StringFormat SF;

	Graphics graphics(pDC->GetSafeHdc());
	graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

	Gdiplus::Font Setfont(fontname, size, FontStyleBold, UnitPixel);

	RectF fontrect(x, y, width, height);

	if (align) {
		SF.SetAlignment(StringAlignmentCenter);
	}
	else {
		SF.SetAlignment(StringAlignmentNear);
	}

	SF.SetLineAlignment(StringAlignmentCenter);

	SolidBrush SB(Color(R, G, B));
	graphics.DrawString(aa, -1, &Setfont, fontrect, &SF, &SB);
}

void Utility::WriteText(CDC * pDC, int x_pos, int y_pos, int width, int height, Text text, BOOL align)
{
	StringFormat SF;

	Graphics graphics(pDC->GetSafeHdc());
	graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

	Gdiplus::Font Setfont(text.fontName, text.textSize, FontStyleBold, UnitPixel);

	RectF fontrect(x_pos, y_pos, width, height);

	if (align) {
		SF.SetAlignment(StringAlignmentCenter);
	}
	else {
		SF.SetAlignment(StringAlignmentNear);
	}

	SF.SetLineAlignment(StringAlignmentCenter);

	SolidBrush SB(Color(text.R, text.G, text.B));
	graphics.DrawString(text.text, -1, &Setfont, fontrect, &SF, &SB);
}

IStream* Utility::CreateStreamOnResource(LPCTSTR lpName, LPCTSTR lpType)
{
	IStream * ipStream = NULL;

	HRSRC hrsrc = FindResource(NULL, lpName, lpType);
	if (hrsrc == NULL)
		goto Return;

	DWORD dwResourceSize = SizeofResource(NULL, hrsrc);
	HGLOBAL hglbImage = LoadResource(NULL, hrsrc);
	if (hglbImage == NULL)
		goto Return;

	LPVOID pvSourceResourceData = LockResource(hglbImage);
	if (pvSourceResourceData == NULL)
		goto Return;

	HGLOBAL hgblResourceData = GlobalAlloc(GMEM_MOVEABLE, dwResourceSize);
	if (hgblResourceData == NULL)
		goto Return;

	LPVOID pvResourceData = GlobalLock(hgblResourceData);

	if (pvResourceData == NULL)
		goto FreeData;

	CopyMemory(pvResourceData, pvSourceResourceData, dwResourceSize);

	GlobalUnlock(hgblResourceData);

	if (SUCCEEDED(CreateStreamOnHGlobal(hgblResourceData, TRUE, &ipStream)))
		goto Return;

FreeData:
	GlobalFree(hgblResourceData);

Return:
	return ipStream;
}

void Utility::SetImage(CImage* rImage, int ResourceID, LPCTSTR lpType) {

	if (rImage != NULL) {
		rImage->Destroy();
	}
	IStream *pStream = CreateStreamOnResource(MAKEINTRESOURCE(ResourceID), lpType);
	if (pStream != nullptr)
	{
		rImage->Load(pStream);
		rImage->SetHasAlphaChannel(true);
		pStream->Release();
	}
	Convert_png_transparent(rImage, lpType);
}

void Utility::DrawBack(CDC * pDC, int x_pos, int y_pos, int width, int height, int R, int G, int B, int bR, int bG, int bB, int borderEdge, int borderSize)
{
	CPen myPen, *pOldPen;
	CBrush myBrush, *pOldBrush;

	int k = borderEdge;

	POINT pts[] = {
		{ x_pos + k, y_pos },{ x_pos + width - k,y_pos },{ x_pos + width,y_pos + k },{ x_pos + width,y_pos + height - k },{ x_pos + width - k,y_pos + height },
		{ x_pos + k,y_pos + height },{ x_pos,y_pos + height - k },{ x_pos,y_pos + k },{ x_pos + k,y_pos }
	};

	myPen.CreatePen(PS_SOLID, borderSize, RGB(bR, bG, bB));
	myBrush.CreateSolidBrush(RGB(R, G, B));

	pOldPen = pDC->SelectObject(&myPen);
	pOldBrush = pDC->SelectObject(&myBrush);

	pDC->Polygon(pts, 9);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

void Utility::DrawWordBack(CDC * pDC, int x_pos, int y_pos, int width, int height, int R, int G, int B, int bR, int bG, int bB, int borderEdge, int borderSize, int edgeLocate)
{
	CPen myPen, *pOldPen;
	CBrush myBrush, *pOldBrush;

	int k = borderEdge;
	int j = width / 6;

	POINT pts[] = {
		{ x_pos + k, y_pos },{ x_pos + width - k,y_pos },{ x_pos + width,y_pos + k },{ x_pos + width,y_pos + height - k },{ x_pos + width - k,y_pos + height },
		{ x_pos + j,y_pos + height },{ x_pos,y_pos + height + j },{ x_pos,y_pos + k },{ x_pos + k,y_pos }
	};

	POINT pts2[] = {
		{ x_pos + k, y_pos },{ x_pos + width + j,y_pos },{ x_pos + width,y_pos + j },{ x_pos + width,y_pos + height - k },{ x_pos + width - k,y_pos + height },
		{ x_pos + k,y_pos + height },{ x_pos,y_pos + height - k },{ x_pos,y_pos + k },{ x_pos + k,y_pos }
	};

	myPen.CreatePen(PS_SOLID, borderSize, RGB(bR, bG, bB));
	myBrush.CreateSolidBrush(RGB(R, G, B));

	pOldPen = pDC->SelectObject(&myPen);
	pOldBrush = pDC->SelectObject(&myBrush);

	switch (edgeLocate) {
	case 0:
		pDC->Polygon(pts, 9);
		break;
	case 1:
		pDC->Polygon(pts2, 9);
		break;
	}
	
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

void Utility::DrawEnemy(CDC * pDC, int  x_pos, int y_pos, int Enemy_Width, int Enemy_Height, int Bar_Interval, int Bar_xpos, int Bar_ypos, int HP_Width, int HP_Height, int monState, int hR, int hG, int hB)
{
	//적을 그려낸다. 일단 임시로 동그라미로 그리자.
	CPen pen;
	pen.CreatePen(PS_NULL, 1, RGB(hR, hG, hB));    // 널 펜을 생성
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush brush;
	switch (monState) {
	case 0:
		brush.CreateSolidBrush(RGB(169, 169, 169));     //무속성
		break;
	case 1:
		brush.CreateSolidBrush(RGB(165, 42, 42));     //불속성
		break;
	case 2:
		brush.CreateSolidBrush(RGB(0, 191, 255));     //물속성
		break;
	case 3:
		brush.CreateSolidBrush(RGB(218, 165, 32));     //전기속성
		break;
	case 4:
		brush.CreateSolidBrush(RGB(34, 139, 34));     //자연속성
		break;		
	}
	
	CBrush* oldBrush = pDC->SelectObject(&brush);
	pDC->Ellipse(x_pos, y_pos, x_pos+Enemy_Width, y_pos+Enemy_Height);
	pDC->SelectObject(oldBrush);

	DrawHPBar(pDC, Bar_xpos, Bar_ypos, HP_Width, HP_Height, hR, hG, hB);
}

void Utility::DrawHPBar(CDC * pDC, int & bar_xpos, int & bar_ypos, int & HP_Width, int & HP_Height, int& hR, int& hG, int& hB)
{
	CPen pen;
	pen.CreatePen(PS_NULL, 1, RGB(hR, hG, hB));    // 널 펜을 생성
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(hR, hG, hB));     // 빨간색 배경색을 설정
	CBrush* oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(bar_xpos, bar_ypos, bar_xpos+HP_Width, bar_ypos+HP_Height);
	pDC->SelectObject(oldBrush);
}

void Utility::DrawTower(CDC * pDC, CPoint towerPos, int tWidth, int tHeight, CImage *img, int towerAttribute, int towerLv, CRect towerRange, int borderEdge, int borderSize, BOOL isShownRange)
{
	if (isShownRange) {
		CPen pen;
		pen.CreatePen(PS_DASH, 5, RGB(240, 230, 140));    // 노란색 펜
		CPen* oldPen = pDC->SelectObject(&pen);
		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);    // 투명 브러시
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		CPoint edgeCurve(30, 30);
		pDC->RoundRect(towerRange, edgeCurve);
		pDC->SelectObject(pOldBrush);
	}

	//타워 배경을 그린다. (레벨에 따라 배경색상이 변경)
	if (towerLv < 5) {
		DrawBack(pDC, towerPos.x, towerPos.y, tWidth, tHeight, 150, 140, 30, 120, 100, 0, borderEdge, borderSize);
	}
	else if (towerLv >= 5 && towerLv < 10) {
		DrawBack(pDC, towerPos.x, towerPos.y, tWidth, tHeight, 220, 200, 30, 100, 80, 40, borderEdge, borderSize);
	}
	else {
		DrawBack(pDC, towerPos.x, towerPos.y, tWidth, tHeight, 220, 100, 255, 255, 80, 255, borderEdge, borderSize);
	}	

	//내부 동그라미를 그린다.
	CPen pen;
	pen.CreatePen(PS_NULL, 1, RGB(255, 255, 240));    // 널 펜을 생성
	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush brush(RGB(255, 230, 222));     // 배경색을 생성 (기본 = 흰색)
	CBrush* oldBrush = pDC->SelectObject(&brush);

	int roundSize = 32;
	int halfSize = (tWidth - roundSize) / 2;
	
	pDC->Ellipse(towerPos.x + halfSize, towerPos.y + halfSize, towerPos.x + halfSize+roundSize, towerPos.y + halfSize+roundSize);

	if (img) { img->Draw(pDC->m_hDC, towerPos.x + halfSize, towerPos.y + halfSize, roundSize, roundSize); }

	pDC->SelectObject(oldBrush);
}



void Utility::Convert_png_transparent(CImage *m_image, LPCTSTR lpType) {
	if (m_image->GetBPP() == 32)
	{
		if (lpType == _T("PNG"))
		{

			unsigned char * pCol = 0;
			long w = m_image->GetWidth();
			long h = m_image->GetHeight();
			for (long y = 0; y < h; y++)
			{
				for (long x = 0; x < w; x++)
				{
					pCol = (unsigned char *)m_image->GetPixelAddress(x, y);
					unsigned char alpha = pCol[3];
					if (alpha != 255)
					{
						pCol[0] = ((pCol[0] * alpha) + 128) >> 8;
						pCol[1] = ((pCol[1] * alpha) + 128) >> 8;
						pCol[2] = ((pCol[2] * alpha) + 128) >> 8;
					}
				}
			}
			m_image->SetHasAlphaChannel(true);
		}
	}
}

void Utility::SetCursor(int CursorState)
{
	switch (CursorState) {
	case CURSORNORMAL:
		SetCursorNormal();
		break;
	case CURSORCLICK:
		SetCursorClick();
		break;
	}
}

void Utility::SetCursorNormal() {
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_CHANGECURSOR, FALSE, 0);
}


void Utility::SetCursorClick() {
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_CHANGECURSOR, TRUE, 0);
}





////Text 클래스 정의

Text::Text()
{
	textSize = 15;
	fontName = L"Corbel";
	R = 255;
	G = 255;
	B = 255;
	text = L"Example";
}

Text::Text(CString _text, int _textSize, CString _fontName, int R, int G, int B)
{
	setText(_text, _textSize, _fontName, R, G, B);
}

Text::~Text()
{
}

//오오오보러딩
void Text::setText(CString _text, int _textSize, CString _fontName, int _R, int _G, int _B)
{
	text = _text;
	textSize = _textSize;
	fontName = _fontName;
	R = _R;
	G = _G;
	B = _B;
}

void Text::setText(CString _text)
{
	text = _text;
}

void Text::setText(int _R, int _G, int _B)
{
	R = _R;
	G = _G;
	B = _B;
}

CString Text::getText()
{
	return text;
}

void Text::showTextMessage()
{
	AfxMessageBox(text);
}

void Text::setText(int _textSize)
{
	textSize = _textSize;
}
