// LZWView.h : interface of the CLZWView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LZWVIEW_H__0BB12B82_062A_4983_BC08_583D0292419E__INCLUDED_)
#define AFX_LZWVIEW_H__0BB12B82_062A_4983_BC08_583D0292419E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLZWView : public CScrollView
{
protected: // create from serialization only
	CLZWView();
	DECLARE_DYNCREATE(CLZWView)

// Attributes
public:
	CLZWDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLZWView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLZWView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLZWView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LZWView.cpp
inline CLZWDoc* CLZWView::GetDocument()
   { return (CLZWDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LZWVIEW_H__0BB12B82_062A_4983_BC08_583D0292419E__INCLUDED_)
