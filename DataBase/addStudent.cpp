// addStudent.cpp: файл реализации
//

#include "stdafx.h"
#include "DataBase.h"
#include "addStudent.h"
#include "afxdialogex.h"


// Диалоговое окно addStudent

IMPLEMENT_DYNAMIC(addStudent, CDialogEx)

addStudent::addStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENT, pParent)
	, Surname(_T(""))
	, Name(_T(""))
	, Patronymic(_T(""))
	, Birthday(COleDateTime::GetCurrentTime())
	, ArrivalDate(2017)
	, BookNumber(_T(""))
	, Subject(_T(""))
	, Mark(_T(""))
{

}

addStudent::~addStudent()
{
}

void addStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, Surname);
	DDX_Text(pDX, IDC_EDIT3, Name);
	DDX_Text(pDX, IDC_EDIT4, Patronymic);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, Birthday);
	DDX_Text(pDX, IDC_EDIT5, ArrivalDate);
	DDX_Text(pDX, IDC_EDIT6, BookNumber);
	DDX_Control(pDX, IDC_COMBO1, ComboFaculity);
	DDX_Control(pDX, IDC_COMBO2, ComboCathedra);
	DDX_Control(pDX, IDC_COMBO3, ComboGroup);
	DDX_Control(pDX, IDC_LIST1, SessionList);
	DDX_Control(pDX, IDC_LIST2, SubjectList);
	DDX_Control(pDX, IDC_LIST3, MarkList);
	DDX_Text(pDX, IDC_EDIT8, Subject);
	DDX_Text(pDX, IDC_EDIT7, Mark);
}


BEGIN_MESSAGE_MAP(addStudent, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &addStudent::Button_addSession)
	ON_BN_CLICKED(IDC_BUTTON7, &addStudent::Button_deleteSession)
	ON_BN_CLICKED(IDC_BUTTON5, &addStudent::Button_addSubject)
	ON_BN_CLICKED(IDC_BUTTON8, &addStudent::Button_deleteSubject)
	ON_LBN_SELCHANGE(IDC_LIST1, &addStudent::List_SessionReset)
	ON_LBN_SELCHANGE(IDC_LIST2, &addStudent::List_Subject)
	ON_LBN_SELCHANGE(IDC_LIST3, &addStudent::List_Mark)
	ON_BN_CLICKED(IDC_BUTTON1, &addStudent::Button_save)
END_MESSAGE_MAP()

BOOL addStudent::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ComboBox();
	ListBox();
	return true;
}

CString * addStudent::FileToBox(CString file, CComboBox *box, CString *array)
{
	CStdioFile f;
	CString buf;
	int l = 0;
	if (f.Open(file, CFile::modeRead | CFile::typeBinary))
	{
		try
		{
			while (f.ReadString(buf))
				l++;
			array = new CString[l];
			l = 0;
			f.SeekToBegin();
			while (f.ReadString(buf))
			{
				array[l] = buf.Mid(0, buf.Find('|'));
				box->AddString(buf.Mid(buf.Find('|') + 1));
				l++;
			}
			f.Close();
		}
		catch (CFileException* ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при заполнении списка");
		}
	}
	return array;
}

void addStudent::ComboBox()
{
	CString file = _T("Faculity.txt");
	id_faculity = FileToBox(file, &ComboFaculity, id_faculity);
	file = _T("Cathedra.txt");
	id_cathedra = FileToBox(file, &ComboCathedra, id_cathedra);
	file = _T("Group.txt");
	id_group = FileToBox(file, &ComboGroup, id_group);
	if (ComboFaculity.GetCount() == 0 || ComboCathedra.GetCount() == 0 || ComboGroup.GetCount() == 0)
	{
		MessageBox(L"Сначала заполните сведения о университете!");
		EndDialog(0);
	}
}

void addStudent::ListBox()
{
	MarkListArray = new CString*[9];
	SubjectListArray = new CString*[9];
	for (int i = 0; i < 10; i++)
	{
		MarkListArray[i] = new CString[10];
		SubjectListArray[i] = new CString[10];
	}
}


void addStudent::Button_addSession()
{
	if (SessionList.GetCount() == 9)
	{
		MessageBox(L"Максимальное количество сессий - 9!");
		return;
	}
	CString str;
	str.Format(L"%i", SessionList.GetCount() + 1);
	SessionList.AddString(L"Сессия " + str);
}




void addStudent::Button_deleteSession()
{
	if (SessionList.GetCurSel() != SessionList.GetCount() - 1)
	{
		MessageBox(L"Удаление сессий возможно только с конца");
		return;
	}
	SessionList.DeleteString(SessionList.GetCount() - 1);
	for (int i = 0; i < 10; i++)
	{
		MarkList.DeleteString(i);
		SubjectList.DeleteString(i);
		MarkListArray[SessionList.GetCount()][i] = "";
		SubjectListArray[SessionList.GetCount()][i] = "";
	}
}


void addStudent::Button_addSubject()
{
	UpdateData(true);
	if (Subject == "")
	{
		return;
	}
	int m = SessionList.GetCurSel();
	if (m < 0)
	{
		MessageBox(L"Вы должны выбрать сессию!");
		return;
	}
	if (SubjectList.GetCount() == 10)
	{
		MessageBox(L"Максимум предметов в одной сессии - 10!");
		return;
	}
	if (Subject == "" || Mark == "")
	{
		MessageBox(L"Заполните поля предмет/оценка");
		return;
	}
	SubjectListArray[m][SubjectList.GetCount()] = Subject;
	SubjectList.AddString(Subject);
	Subject = "";
	MarkListArray[m][MarkList.GetCount()] = Mark;
	MarkList.AddString(Mark);
	Mark = "";
	UpdateData(false);
}


void addStudent::Button_deleteSubject()
{
	if (SubjectList.GetCount() > 0)
	{
		for (int i = SubjectList.GetCurSel(); i < SubjectList.GetCount(); i++)
		{
			SubjectListArray[SessionList.GetCurSel()][i] =
				SubjectListArray[SessionList.GetCurSel()][i + 1];
			MarkListArray[SessionList.GetCurSel()][i] = MarkListArray[SessionList.GetCurSel()][i + 1];
		}
		SubjectList.DeleteString(SubjectList.GetCurSel());
		MarkList.DeleteString(MarkList.GetCurSel());
	}
}


void addStudent::List_SessionReset()
{
	int m = SessionList.GetCurSel();
	while (SubjectList.GetCount())
	{
		SubjectList.DeleteString(SubjectList.GetCount() - 1);
		MarkList.DeleteString(MarkList.GetCount() - 1);
	}
	if (m < 0)
		return;
	int n = 0;
	while (SubjectListArray[m][n] != "")
	{
		SubjectList.AddString(SubjectListArray[m][n]);
		n++;
	}
	n = 0;
	while (MarkListArray[m][n] != "")
	{
		MarkList.AddString(MarkListArray[m][n]);
		n++;
	}
}


void addStudent::List_Subject()
{
	MarkList.SetCurSel(SubjectList.GetCurSel());
}


void addStudent::List_Mark()
{
	SubjectList.SetCurSel(MarkList.GetCurSel());
}

int addStudent::Check()
{
	UpdateData(true);
	if (ComboFaculity.GetCurSel() < 0 || ComboCathedra.GetCurSel() < 0 || ComboGroup.GetCurSel() < 0)
		return 1;
	CString f, c, g, db;
	ComboFaculity.GetLBText(ComboFaculity.GetCurSel(), f);
	ComboCathedra.GetLBText(ComboCathedra.GetCurSel(), c);
	ComboGroup.GetLBText(ComboGroup.GetCurSel(), g);
	db = Birthday.Format(_T("%Y"));
	Surname.Remove('|');
	Name.Remove('|');
	Patronymic.Remove('|');
	BookNumber.Remove('|');
	UpdateData(false);
	if (Surname == "" || Name == "" || ArrivalDate <= _wtoi(db) || f == "" || c == ""
		|| g == "" || BookNumber == "" || SessionList.GetCount() == 0)
		return 1;

	for (int i = 0; i < SessionList.GetCount(); i++)
	{
		int j = 0;
		SubjectListArray[i][j].Remove('|');
		while (SubjectListArray[i][j] != "")
		{
			SubjectListArray[i][j].Remove('|');
			MarkListArray[i][j].Remove('|');
			if (MarkListArray[i][j] == "")
				return 1;
			if (j == 9)
				break;
			j++;
		}
		if (j == 0)
			return 1;
	}
	return 0;
}

int addStudent::m_fread()
{
	CStdioFile f;
	CString path = _T("Student.txt");
	CString buf;
	int index = 0;
	if (f.Open(path, CFile::modeRead | CFile::typeBinary))
	{
		try
		{
			f.SeekToBegin();
			while (f.ReadString(buf))
			{
				if (buf[0] != '*')
				{
					buf = buf.Mid(buf.Find('S') + 1);
					index = _wtoi(buf.Mid(0, buf.Find('|', 0)));
				}
			}
			f.Close();
		}
		catch (CFileException* ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
	return index;
}

void addStudent::m_fwrite(int index)
{
	UpdateData(true);
	CStdioFile f;
	CString path = _T("Student.txt");
	CString s, y;
	s.Format(L"%i", index);
	y.Format(L"%i", ArrivalDate);
	if (f.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate | CFile::typeBinary))
	{
		try
		{
			f.SeekToEnd();
			f.WriteString(L"S" + s + L"|" + Surname + L"|" + Name + L"|" + Patronymic + L"|"
				+ Birthday.Format(_T("%d.%m.%Y")) + L"|" + y + L"|" + id_faculity[ComboFaculity.GetCurSel()] + L"|"
				+ id_cathedra[ComboCathedra.GetCurSel()] + L"|" + id_group[ComboGroup.GetCurSel()] + L"|" + BookNumber + L"\r\n");
			for (int i = 0; i < SessionList.GetCount(); i++)
			{
				s.Format(L"%i", i + 1);
				f.WriteString(L"*C" + s +'|');
				int j = 0;
				while (SubjectListArray[i][j] != "")
				{
					f.WriteString(SubjectListArray[i][j] + "|" + MarkListArray[i][j] + "|");
					if (j == 9)
						break;
					j++;
				}
				f.WriteString(L"\r\n");
			}
			f.Close();
		}
		catch(CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при записи в файл");
		}
	}
}

void addStudent::Button_save()
{
	UpdateData(true);
	int c = Check();
	if (c == 1)
	{
		MessageBox(L"Проверьте правильность введенных данных!");
		return;
	}
	int index = m_fread();
	index++;
	m_fwrite(index);
	EndDialog(0);
}

