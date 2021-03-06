// showStudent.cpp: файл реализации
//

#include "stdafx.h"
#include "DataBase.h"
#include "showStudent.h"
#include "afxdialogex.h"
#include "DataChange.h"
#include "BreakStudent.h"

// Диалоговое окно showStudent

IMPLEMENT_DYNAMIC(showStudent, CDialogEx)

showStudent::showStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW, pParent)
	,l(0)
{

}

showStudent::~showStudent()
{
}

void showStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, Students);
	DDX_Control(pDX, IDC_LIST2, Year);
	DDX_Control(pDX, IDC_LIST3, Number);
	DDX_Control(pDX, IDC_LIST4, University);
	DDX_Control(pDX, IDC_LIST5, Session);
	DDX_Control(pDX, IDC_LIST6, Subject);
}


BEGIN_MESSAGE_MAP(showStudent, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &showStudent::List_Students)
	ON_BN_CLICKED(IDC_BUTTON1, &showStudent::Button_changeStudent)
	ON_LBN_SELCHANGE(IDC_LIST5, &showStudent::List_Session)
	ON_BN_CLICKED(IDC_BUTTON11, &showStudent::Button_breakStudent)
END_MESSAGE_MAP()


// Обработчики сообщений showStudent
BOOL showStudent::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	readDB();
	showDB();
	return TRUE;
}

void showStudent::readDB()
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
		catch (CFileException* pEx)
		{
			pEx->ReportError();
			AfxMessageBox(L"Ошибка при чтении файла");
		}
	}
	else
	{
		AfxMessageBox(L"Пусто");
	}
	l++;
	sCount = new int[l];
	for (int i = 0; i < l; i++)
		sCount[i] = -1;
}

CString showStudent::getUniver(CString path, CString source)
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
		catch (CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
	return L"Проверьте данные";
}
void showStudent::showDB()
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
					int m = Subject.GetCount();
					for (int i = 0; i < m; i++)
					{
						if (Students.GetCount() < m)
							Students.AddString(L"");
						if (Year.GetCount() < m)
							Year.AddString(L"");
						if (University.GetCount() < m)
							University.AddString(L"");
						if (Number.GetCount() < m)
							Number.AddString(L"");
					}
					if (m != 0)
					{
						Students.AddString(L"*********");
						Year.AddString(L"*********");
						University.AddString(L"*********");
						Number.AddString(L"*********");
						Session.AddString(L"*********");
						Subject.AddString(L"*********");
					}
					buf = buf.Mid(buf.Find('S') + 1);
					CString s = buf.Mid(buf.Find('|') + 1);
					for (int i = 0; i < 4; i++)
					{
						Students.AddString(s.Mid(0, s.Find('|'))); //фио + дата рождения
						s = s.Mid(s.Find('|') + 1);
					}
					Year.AddString(s.Mid(0, s.Find('|'))); //год
					s = s.Mid(s.Find('|') + 1);
					University.AddString(getUniver(L"Faculity.txt", s.Mid(0, s.Find('|'))));
					s = s.Mid(s.Find('|') + 1);
					University.AddString(getUniver(L"Cathedra.txt", s.Mid(0, s.Find('|'))));
					s = s.Mid(s.Find('|') + 1);
					University.AddString(getUniver(L"Group.txt", s.Mid(0, s.Find('|'))));
					s = s.Mid(s.Find('|') + 1);
					Number.AddString(s);
					sCount[_wtoi(buf.Mid(0, buf.Find('|')))] = Students.GetCount() - 4;
				}
				else
				{
					CString s = buf.Mid(buf.Find('*') + 2);
					Session.AddString(L"Сессия " + s.Mid(0, s.Find('|')));
					s = s.Mid(s.Find('|') + 1);
					CString str;
					while (s.Find('|') != -1)
					{
						str = s.Mid(0, s.Find('|'));
						s = s.Mid(s.Find('|') + 1);
						str += L" " + s.Mid(0, s.Find('|'));
						s = s.Mid(s.Find('|') + 1);
						Subject.AddString(str);
						if (s.Find('|') != -1)
							Session.AddString(L"");
					}
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
}
void showStudent::List_Students()
{
	int m = Students.GetCurSel();
	University.SetCurSel(m);
	Year.SetCurSel(m);
	Number.SetCurSel(m);
	Session.SetCurSel(m);
	Subject.SetCurSel(m);
}


void showStudent::Button_changeStudent()
{
	CString s = L"";
	int m = Students.GetCurSel();
	if (m < 0)
	{
		MessageBox(L"Нажмите на фамилию студента, которго нужно изменить");
		return;
	}
	for (int i = 0; i < l; i++)
	{
		if (sCount[i] == m)
		{
			s.Format(L"%i", i);
			break;
		}
	}
	if (s == "")
	{
		MessageBox(L"Нажмите на фамилию студента, которго нужно изменить");
		return;
	}
	CStdioFile f;
	CString buf;
	if (f.Open(L"change.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		try
		{
			f.WriteString(L"S" + s);
			f.Close();
		}
		catch (CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
		DataChange change;
		change.DoModal();
		EndDialog(0);
	}
}


void showStudent::List_Session()
{
	int m = Session.GetCurSel();
	Students.SetCurSel(m);
	University.SetCurSel(m);
	Year.SetCurSel(m);
	Number.SetCurSel(m);
	Subject.SetCurSel(m);
}


void showStudent::Button_breakStudent()
{
	BreakStudent stud;
	stud.DoModal();
}
