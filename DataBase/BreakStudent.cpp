// BreakStudent.cpp: файл реализации
//

#include "stdafx.h"
#include "DataBase.h"
#include "BreakStudent.h"
#include "afxdialogex.h"


// Диалоговое окно BreakStudent

IMPLEMENT_DYNAMIC(BreakStudent, CDialogEx)

BreakStudent::BreakStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BREAK, pParent)
{

}

BreakStudent::~BreakStudent()
{
}

void BreakStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, gStudent);
	DDX_Control(pDX, IDC_LIST2, gYear);
	DDX_Control(pDX, IDC_LIST3, gNumber);
	DDX_Control(pDX, IDC_LIST4, gFaculity);
	DDX_Control(pDX, IDC_LIST5, gSession);
	DDX_Control(pDX, IDC_LIST6, gSubject);
	DDX_Control(pDX, IDC_LIST7, bStudent);
	DDX_Control(pDX, IDC_LIST8, bYear);
	DDX_Control(pDX, IDC_LIST9, bNumber);
	DDX_Control(pDX, IDC_LIST10, bFaculity);
	DDX_Control(pDX, IDC_LIST11, bSession);
	DDX_Control(pDX, IDC_LIST12, bSubject);
}


BEGIN_MESSAGE_MAP(BreakStudent, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &BreakStudent::List_Student)
	ON_LBN_SELCHANGE(IDC_LIST5, &BreakStudent::List_Session)
	ON_LBN_SELCHANGE(IDC_LIST7, &BreakStudent::List_bStudent)
	ON_LBN_SELCHANGE(IDC_LIST11, &BreakStudent::List_bSession)
END_MESSAGE_MAP()


// Обработчики сообщений BreakStudent
BOOL BreakStudent::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	readDB();
	CalcData();
	return true;
}
void BreakStudent::readDB()
{
	CStdioFile f;
	CString path = _T("Student.txt");
	CString buf;
	if (f.Open(path, CFile::modeRead | CFile::typeBinary))
	{
		try
		{
			f.SeekToBegin();
			while (f.ReadString(buf))
			{
				if (buf[0] != '*')
				{
					l = _wtoi(buf.Mid(1, buf.Find('|', 0)));
				}
			}
			f.Close();
		}
		catch (CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
	else
	{
		EndDialog(0);
	}
	l++;
	sCount = new int[l];
	for (int i = 0; i < l; i++)
	{
		sCount[i] = -1;
	}
}

CString BreakStudent::getUniver(CString path, CString source)
{
	CStdioFile f;
	CString buf;
	if (f.Open(path, CFile::modeRead | CFile::typeBinary))
	{
		try
		{
			f.SeekToBegin();
			while (f.ReadString(buf))
			{
				if (buf.Mid(0, buf.Find('|')) == source)
					return buf.Mid(buf.Find('|') + 1);
			}
		}
		catch (CFileException* ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
	return L"Проверьте данные";
}

bool BreakStudent::CheckBad(CString s)
{
	int gCount = 0;
	int bCount = 0;
	s = s.Mid(s.Find('|') + 1);
	while (s.Find('|') != -1)
	{
		s = s.Mid(s.Find('|') + 1);
		if (s.Mid(0, s.Find('|')) == '5' || s.Mid(0,s.Find('|')) == '4')
			gCount++;
		
		if (s.Mid(0, s.Find('|')) == '3' || s.Mid(0, s.Find('|')) == '2' || s.Mid(0, s.Find('|')) == '1')
			bCount++;

		s = s.Mid(s.Find('|') + 1);
	}
	if (gCount >= bCount)
		return false;
	else
		return true;
}

void BreakStudent::CalcData()
{
	CStdioFile f;
	CString buf, students;
	CString * session = new CString[9];
	bool nothalfmarks = true;
	int n;
	if (f.Open(L"Student.txt", CFile::modeRead | CFile::typeBinary))
	{
		try
		{
			f.SeekToBegin();
			while (f.ReadString(buf))
			{
				if (buf[0] != '*')
				{
					if (!nothalfmarks)
					{
						GoodData(students, session, n);
					}
					nothalfmarks = false;
					students = buf;
					n = 0;
				}
				else
				{
					if (!nothalfmarks)
					{
						nothalfmarks = CheckBad(buf);
					}
					session[n] = buf;
					n++;
				}
				if (nothalfmarks && n != 1)
					BadData(students, session, n);
			}
			f.Close();
		}
		catch (CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
}

void BreakStudent::GoodData(CString st, CString *ses, int num)
{
	int n = gSubject.GetCount();
	for (int i = 0; i < n; i++)
	{
		if (gStudent.GetCount() < n)
			gStudent.AddString(L"");
		if (gYear.GetCount() < n)
			gYear.AddString(L"");
		if (gFaculity.GetCount() < n)
			gFaculity.AddString(L"");
		if (gNumber.GetCount() < n)
			gNumber.AddString(L"");
	}
	if (n != 0)
	{
		gStudent.AddString(L"*********");
		gYear.AddString(L"*********");
		gFaculity.AddString(L"*********");
		gNumber.AddString(L"*********");
		gSession.AddString(L"*********");
		gSubject.AddString(L"*********");
	}
	st = st.Mid(st.Find('S') + 1);
	CString s = st.Mid(st.Find('|') + 1);
	for (int i = 0; i < 4; i++)
	{
		gStudent.AddString(s.Mid(0, s.Find('|')));
		s = s.Mid(s.Find('|') + 1);
	}
	gYear.AddString(s.Mid(0, s.Find('|')));
	s = s.Mid(s.Find('|') + 1);
	gFaculity.AddString(getUniver(L"Faculity.txt", s.Mid(0, s.Find('|'))));
	s = s.Mid(s.Find('|') + 1);
	gFaculity.AddString(getUniver(L"Cathedra.txt", s.Mid(0, s.Find('|'))));
	s = s.Mid(s.Find('|') + 1);
	gFaculity.AddString(getUniver(L"Group.txt", s.Mid(0, s.Find('|'))));
	s = s.Mid(s.Find('|') + 1);
	gNumber.AddString(s);
	sCount[_wtoi(st.Mid(0, st.Find('|')))] = gStudent.GetCount() - 4;
	for (int i = 0; i < num; i++)
	{
		CString s = ses[i].Mid(ses[i].Find('*') + 2);
		gSession.AddString(L"Сессия " + s.Mid(0, s.Find('|')));
		s = s.Mid(s.Find('|') + 1);
		CString str;
		while (s.Find('|') != -1)
		{
			str = s.Mid(0, s.Find('|'));
			s = s.Mid(s.Find('|') + 1);
			str += L" " + s.Mid(0, s.Find('|'));
			s = s.Mid(s.Find('|') + 1);
			gSubject.AddString(str);
			if (s.Find('|') != -1)
				gSession.AddString(L"");
		}
	}
}

void BreakStudent::BadData(CString st, CString *ses, int num)
{
	int n = bSubject.GetCount();
	for (int i = 0; i < n; i++)
	{
		if (bStudent.GetCount() < n)
			bStudent.AddString(L"");
		if (bYear.GetCount() < n)
			bYear.AddString(L"");
		if (bFaculity.GetCount() < n)
			bFaculity.AddString(L"");
		if (bNumber.GetCount() < n)
			bNumber.AddString(L"");
	}
	if (n != 0)
	{
		bStudent.AddString(L"*********");
		bYear.AddString(L"*********");
		bFaculity.AddString(L"*********");
		bNumber.AddString(L"*********");
		bSession.AddString(L"*********");
		bSubject.AddString(L"*********");
	}
	st = st.Mid(st.Find('S') + 1);
	CString s = st.Mid(st.Find('|') + 1);
	for (int i = 0; i < 4; i++)
	{
		bStudent.AddString(s.Mid(0, s.Find('|')));
		s = s.Mid(s.Find('|') + 1);
	}
	bYear.AddString(s.Mid(0, s.Find('|')));
	s = s.Mid(s.Find('|') + 1);
	bFaculity.AddString(getUniver(L"Faculity.txt", s.Mid(0, s.Find('|'))));
	s = s.Mid(s.Find('|') + 1);
	bFaculity.AddString(getUniver(L"Cathedra.txt", s.Mid(0, s.Find('|'))));
	s = s.Mid(s.Find('|') + 1);
	bFaculity.AddString(getUniver(L"Group.txt", s.Mid(0, s.Find('|'))));
	s = s.Mid(s.Find('|') + 1);
	bNumber.AddString(s);
	sCount[_wtoi(st.Mid(0, st.Find('|')))] = bStudent.GetCount() - 4;
	for (int i = 0; i < num; i++)
	{
		CString s = ses[i].Mid(ses[i].Find('*') + 2);
		bSession.AddString(L"Сессия " + s.Mid(0, s.Find('|')));
		s = s.Mid(s.Find('|') + 1);
		CString str;
		while (s.Find('|') != -1)
		{
			str = s.Mid(0, s.Find('|'));
			s = s.Mid(s.Find('|') + 1);
			str += L" " + s.Mid(0, s.Find('|'));
			s = s.Mid(s.Find('|') + 1);
			bSubject.AddString(str);
			if (s.Find('|') != -1)
				bSession.AddString(L"");
		}
	}
}



void BreakStudent::List_Student()
{
	int m = gStudent.GetCurSel();
	gFaculity.SetCurSel(m);
	gYear.SetCurSel(m);
	gNumber.SetCurSel(m);
	gSession.SetCurSel(m);
	gSubject.SetCurSel(m);
}


void BreakStudent::List_Session()
{
	int m = gSession.GetCurSel();
	gStudent.SetCurSel(m);
	gFaculity.SetCurSel(m);
	gYear.SetCurSel(m);
	gNumber.SetCurSel(m);
	gSubject.SetCurSel(m);
}


void BreakStudent::List_bStudent()
{
	int m = bStudent.GetCurSel();
	bFaculity.SetCurSel(m);
	bYear.SetCurSel(m);
	bNumber.SetCurSel(m);
	bSession.SetCurSel(m);
	bSubject.SetCurSel(m);
}


void BreakStudent::List_bSession()
{
	int m = bSession.GetCurSel();
	bStudent.SetCurSel(m);
	bFaculity.SetCurSel(m);
	bYear.SetCurSel(m);
	bNumber.SetCurSel(m);
	bSubject.SetCurSel(m);
}
