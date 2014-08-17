// LZWDoc.h : interface of the CLZWDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LZWDOC_H__17CF5A65_8CA3_4367_BCCB_821BFDBACD02__INCLUDED_)
#define AFX_LZWDOC_H__17CF5A65_8CA3_4367_BCCB_821BFDBACD02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLZWDoc : public CDocument
{
protected: // create from serialization only
	CLZWDoc();
	DECLARE_DYNCREATE(CLZWDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLZWDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Decompress();
	void Compress();
	CStringArray * GetLog();
	virtual ~CLZWDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLZWDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ClearLog();
	void Log(CString entry);
	CString m_SourceFile;
	CString m_TargetFile;
	CStringArray m_Log;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LZWDOC_H__17CF5A65_8CA3_4367_BCCB_821BFDBACD02__INCLUDED_)
