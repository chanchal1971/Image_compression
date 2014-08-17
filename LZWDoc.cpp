// LZWDoc.cpp : implementation of the CLZWDoc class
//

#include "stdafx.h"
#include "LZW.h"

#include "LZWCompression.h"
#include "LZWDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLZWDoc

IMPLEMENT_DYNCREATE(CLZWDoc, CDocument)

BEGIN_MESSAGE_MAP(CLZWDoc, CDocument)
	//{{AFX_MSG_MAP(CLZWDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLZWDoc construction/destruction

CLZWDoc::CLZWDoc()
{
}

CLZWDoc::~CLZWDoc()
{
}

BOOL CLZWDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLZWDoc serialization

void CLZWDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLZWDoc diagnostics

#ifdef _DEBUG
void CLZWDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLZWDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLZWDoc commands

CStringArray * CLZWDoc::GetLog()
{
	return &m_Log;
}

void CLZWDoc::Log(CString entry)
{
	m_Log.Add(entry);
	UpdateAllViews(NULL);
}

void CLZWDoc::ClearLog()
{
	m_Log.RemoveAll();
	UpdateAllViews(NULL);
}

void CLZWDoc::Compress()
{
	CLZWCompression cLZWC;
	CFile sourceFile, targetFile;
	BOOL delTarget = FALSE;
	BYTE extSize = 0;

	//	Clear the view log
	ClearLog();

	Log("Requesting source file!");
	//	Open the dialog to select a file
	CFileDialog cFD(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All files (*.*)|*.*|");

	//	Select a file to be opened
	if (cFD.DoModal() == IDCANCEL)
	{
		ClearLog();
		Log("You must select a file to compress!");
		return;
	}
	//	Set the files names and data
	m_SourceFile = cFD.GetPathName();
	m_TargetFile = m_SourceFile.Left(m_SourceFile.ReverseFind('.') + 1) + "lzw";

	Log("Compression begins!");
	Log("Openning Source file: " + m_SourceFile);

	if (!sourceFile.Open(m_SourceFile, CFile::modeRead))
	{
		ClearLog();
		Log("Can't open source file!");
		return;
	}

	Log("Destination file: " + m_TargetFile);
	if (!targetFile.Open(m_TargetFile, CFile::modeWrite | CFile::modeCreate))
	{
		ClearLog();
		Log("Can't create target file!");
		return;
	}

	//	Creathe the LZW dictionary
	cLZWC.CreateDictionary();

	//	Save the extention of the source file inside the destination file
	//	This was added to make sure that we will get the same file type (by
	//	extension), in the result
	extSize = (BYTE)cFD.GetFileExt().GetLength();
	targetFile.Write(&extSize, 1);
	targetFile.Write(cFD.GetFileExt().GetBuffer(extSize), extSize);

	//	Compress the file
	if (!cLZWC.CompressWithLog(sourceFile, targetFile, &m_Log))
	{
		ClearLog();
		Log("Error while compressing!");
		Log("Compression aborted!");
		delTarget = TRUE;
	}
	else
	{
		Log("Compression succeded!");
	}

	//	Close the files
	targetFile.Close();
	sourceFile.Close();

	//	Remove the target if an erro occur
	if (delTarget)
		CFile::Remove(m_TargetFile);
}

void CLZWDoc::Decompress()
{
	CLZWCompression cLZWC;
	CFile sourceFile, targetFile;
	BOOL delTarget = FALSE;
	BYTE extSize = 0;
	CString ext;

	//	Clear the view log
	ClearLog();
	Log("Requesting source file!");

	//	Open the dialog to select a file
	CFileDialog cFD(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Compressed files (*.lzw)|*.lzw|");

	//	Select a file to be opened
	if (cFD.DoModal() == IDCANCEL)
	{
		ClearLog();
		Log("You must select a file to decompress!");
		return;
	}
	m_SourceFile = cFD.GetPathName();

	Log("Decompression begins!");
	Log("Openning Source file: " + m_SourceFile);

	if (!sourceFile.Open(m_SourceFile, CFile::modeRead))
	{
		ClearLog();
		Log("Can't open source file!");
		return;
	}

	//	Get the original file extension from the source file
	sourceFile.Read(&extSize, 1);
	sourceFile.Read(ext.GetBuffer(extSize), extSize);
	ext.ReleaseBuffer(extSize);

	//	set the extension in the destination file string, and create the file
	m_TargetFile = m_SourceFile.Left(m_SourceFile.ReverseFind('.') + 1) + ext;

	Log("Destination file: " + m_TargetFile);
	if (!targetFile.Open(m_TargetFile, CFile::modeWrite | CFile::modeCreate))
	{
		ClearLog();
		Log("Can't create target file!");
		return;
	}

	//	Decompress the file
	if (!cLZWC.DecompressWithLog(sourceFile, targetFile, &m_Log))
	{
		ClearLog();
		Log("Error while decompressing!");
		Log("Decompression aborted!");
		delTarget = TRUE;
	}
	else
	{
		Log("Decompression succeded!");
	}

	//	Close both files
	targetFile.Close();
	sourceFile.Close();

	//	delete the destination file if theres an error
	if (delTarget)
		CFile::Remove(m_TargetFile);
}

