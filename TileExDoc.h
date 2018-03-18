
// TileExDoc.h : CTileExDoc Ŭ������ �������̽�
//


#pragma once


class CTileExDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CTileExDoc();
	DECLARE_DYNCREATE(CTileExDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:


	//���ϰ� Doc ȣ���� ����.
	static CTileExDoc* GetDoc();

	//////////////////////////////////////////////////////////


// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CTileExDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
