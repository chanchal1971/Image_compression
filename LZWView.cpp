// LZWView.cpp : implementation of the CLZWView class
//

#include "stdafx.h"
#include "LZW.h"

#include "LZWDoc.h"
#include "LZWView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLZWView

IMPLEMENT_DYNCREATE(CLZWView, CScrollView)

BEGIN_MESSAGE_MAP(CLZWView, CScrollView)
	//{{AFX_MSG_MAP(CLZWView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLZWView construction/destruction

CLZWView::CLZWView()
{
	// TODO: add construction code here

}

CLZWView::~CLZWView()
{
}

BOOL CLZWView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLZWView drawing

void CLZWView::OnDraw(CDC* pDC)
{
	CStringArray *log = NULL;
	int counter, total;
	long line = 5, indent = 5;
	CString sline;
	CRect rc, rcTotal = CRect(0, 0, 0, 0);
	CLZWDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//	Get the log array from the Document class
	log = pDoc->GetLog();
	total = log->GetSize();
	pDC->SetBkMode(TRANSPARENT);

	//	Go over each line of the document and print it to the view
	for (counter = 0; counter < total; counter++)
	{
		//	Calculate the text size (for one line)
		rc = CRect(0, 0, 0, 0);
		sline = log->GetAt(counter);
		pDC->DrawText(sline, &rc, DT_CALCRECT);

		//	Calculate the full recangle size of the written document
		//	This is for reseting the scroll bars values, so we can use
		//	them to scroll ove the document
		if (rc.Width() > rcTotal.Width())
			rc.right = rc.right;
		rcTotal.bottom += rc.bottom;

		//	Change the values for the next line (with spaces from the previous)
		rc.left = indent;
		rc.right += 5;
		rc.top = line;
		rc.bottom += line;

		line = rc.bottom + 5;

		//	Draw the line text in the view
		pDC->DrawText(sline, &rc, DT_LEFT | DT_VCENTER);
	}

	//	Change the view scroll bars, and set the movement sizes to match the
	//	rows of data
	SetScrollSizes(MM_TEXT, CSize(rcTotal.Width(), rcTotal.Height()),
		CSize(10, rc.Height() * 10), CSize(3, rc.Height() * 3));
}

void CLZWView::OnInitialUpdate()
{
	CRect rc;

	CScrollView::OnInitialUpdate();

	GetClientRect(&rc);

	SetScrollSizes(MM_TEXT, CSize(rc.Width(), rc.Height()), CSize(1, 1), CSize(3, 3));
}

/////////////////////////////////////////////////////////////////////////////
// CLZWView diagnostics

#ifdef _DEBUG
void CLZWView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CLZWView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CLZWDoc* CLZWView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLZWDoc)));
	return (CLZWDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLZWView message handlers

void CLZWView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CDC *pDC = NULL;

	Invalidate(FALSE);
	OnDraw((pDC = GetDC()));
	ReleaseDC(pDC);
}

