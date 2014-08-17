// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LZW.h"

#include "LZWDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_FILE_COMPRESS, OnFileCompress)
	ON_COMMAND(ID_FILE_DECOMPRESS, OnFileDecompress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.cx = 800;
	cs.cy = 600;
	cs.x = (GetSystemMetrics(SM_CXFULLSCREEN)-cs.cx) / 2;
	cs.y = (GetSystemMetrics(SM_CYFULLSCREEN)-cs.cy) / 2;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnFileCompress() 
{
	((CLZWDoc*)GetActiveDocument())->Compress();
}

void CMainFrame::OnFileDecompress() 
{
	((CLZWDoc*)GetActiveDocument())->Decompress();
}
