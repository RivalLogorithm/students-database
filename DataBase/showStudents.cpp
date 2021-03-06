// showStudents.cpp: файл реализации
//

#include "stdafx.h"
#include "DataBase.h"
#include "showStudents.h"
#include "afxdialogex.h"
#include "changeStudent.h"


// Диалоговое окно showStudents

IMPLEMENT_DYNAMIC(showStudents, CDialogEx)

showStudents::showStudents(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW, pParent)
	,l(0)
{

}

showStudents::~showStudents()
{
}

void showStudents::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, Students);
	DDX_Control(pDX, IDC_LIST2, Year);
	DDX_Control(pDX, IDC_LIST3, Number);
	DDX_Control(pDX, IDC_LIST4, University);
	DDX_Control(pDX, IDC_LIST5, Session);
	DDX_Control(pDX, IDC_LIST6, Subject);
}


BEGIN_MESSAGE_MAP(showStudents, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &showStudents::List_Student)
	ON_BN_CLICKED(IDC_BUTTON1, &showStudents::Button_changeStudent)
END_MESSAGE_MAP()

//SHOW STUDENT
// Обработчики сообщений showStudents
BOOL showStudents::OnInitDialog()
{
	readDB();
	showDB();
	return TRUE;
}

void showStudents::readDB()
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
				if (buf[0] != '-')
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

CString showStudents::getUniver(CString path, CString source)
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
void showStudents::showDB()
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
					int m = 0;
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
						Students.AddString(L"_______");
						Year.AddString(L"_______");
						University.AddString(L"_______");
						Number.AddString(L"_______");
						Session.AddString(L"_______");
						Subject.AddString(L"_______");
					}
					buf = buf.Mid(buf.Find('S') + 1);
					CString s = buf.Mid(buf.Find('|') + 1);
					for (int i = 0; i < 4; i++)
					{
						Students.AddString(s.Mid(0, s.Find('|'))); //фио + дата рождения
					}
					Year.AddString(s.Mid(0, s.Find('|'))); //год
					s = s.Mid(s.Find('|') + 1);
					University.AddString(getUniver(L"Faculity.txt", s.Mid(0, s.Find('|'))));
					s = s.Mid(s.Find('|') + 1);
					University.AddString(getUniver(L"Cathdra.txt", s.Mid(0, s.Find('|'))));
					s = s.Mid(s.Find('|') + 1);
					University.AddString(getUniver(L"Group.txt", s.Mid(0, s.Find('|'))));
					s = s.Mid(s.Find('|') + 1);
					Number.AddString(s);
				}
				else
				{
					CString s = buf.Mid(buf.Find('*') + 2);
					Session.AddString(L"Сессия №" + s.Mid(0, s.Find('|')));
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
void showStudents::List_Student()
{
	int m = Students.GetCurSel();
	University.SetCurSel(m);
	Year.SetCurSel(m);
	Number.SetCurSel(m);
	Session.SetCurSel(m);
	Subject.SetCurSel(m);
}


void showStudents::Button_changeStudent()
{
	CString s = L"";
	int m = Students.GetCurSel();
	if (m < 0)
	{
		MessageBox(L"Нажмите на фамилию студента, которого нужно изменить");
		return;
	}
	for (int i = 0; i < l; i++)
	{
		if (sCount[i] == m)
		{
			s.Format(L"%i", i);
			return;
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
		changeStudent change;
		change.DoModal();
		EndDialog(0);
	}
}
