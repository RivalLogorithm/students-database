// DataChange.cpp: файл реализации
//

#include "stdafx.h"
#include "DataBase.h"
#include "DataChange.h"
#include "afxdialogex.h"


// Диалоговое окно DataChange

IMPLEMENT_DYNAMIC(DataChange, CDialogEx)

DataChange::DataChange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATACHANGE, pParent)
	, Surname(_T(""))
	, Name(_T(""))
	, Patronymic(_T(""))
	, Birthday(COleDateTime::GetCurrentTime())
	, ArrivalDate(0)
	, BookNumber(_T(""))
	, Subject(_T(""))
	, Mark(_T(""))
{

}

DataChange::~DataChange()
{
}

void DataChange::DoDataExchange(CDataExchange* pDX)
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
	DDX_Text(pDX, IDC_EDIT8, Subject);
	DDX_Text(pDX, IDC_EDIT7, Mark);
	DDX_Control(pDX, IDC_LIST1, SessionList);
	DDX_Control(pDX, IDC_LIST2, SubjectList);
	DDX_Control(pDX, IDC_LIST3, MarkList);
}


BEGIN_MESSAGE_MAP(DataChange, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &DataChange::Button_addSession)
	ON_BN_CLICKED(IDC_BUTTON7, &DataChange::Button_deleteSession)
	ON_BN_CLICKED(IDC_BUTTON5, &DataChange::Button_addSubject)
	ON_BN_CLICKED(IDC_BUTTON8, &DataChange::Button_deleteSubject)
	ON_LBN_SELCHANGE(IDC_LIST1, &DataChange::List_ResetSession)
	ON_LBN_SELCHANGE(IDC_LIST2, &DataChange::List_Subject)
	ON_LBN_SELCHANGE(IDC_LIST3, &DataChange::List_Mark)
	ON_BN_CLICKED(IDC_BUTTON1, &DataChange::Button_changeStudent)
	ON_BN_CLICKED(IDC_BUTTON9, &DataChange::Button_renameSubjectMark)
	ON_BN_CLICKED(IDC_BUTTON12, &DataChange::Button_deleteStudent)
END_MESSAGE_MAP()


// Обработчики сообщений DataChange
BOOL DataChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ListBox();
	ComboBox();
	getId();
	Data();
	return TRUE;
}

CString * DataChange::FileToBox(CString file, CComboBox *box, CString *array)
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

void DataChange::ComboBox()
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

void DataChange::ListBox()
{
	MarkListArray = new CString*[9];
	SubjectListArray = new CString*[9];
	for (int i = 0; i < 10; i++)
	{
		MarkListArray[i] = new CString[10];
		SubjectListArray[i] = new CString[10];
	}
}

void DataChange::Data()
{
	CStdioFile f;
	CString buf;
	bool fl = false;
	if (f.Open(L"Student.txt", CFile::modeRead | CFile::typeBinary))
	{
		try
		{
			while (f.ReadString(buf))
			{
				if (buf[0] != '*')
				{
					if (fl)
						break;
					CString s = buf.Mid(buf.Find('S') + 1);
					if (s.Mid(0, s.Find('|')) == id_student)
					{
						fl = true;
						s = s.Mid(s.Find('|') + 1);
						Surname = s.Mid(0, s.Find('|'));
						s = s.Mid(s.Find('|') + 1);
						Name = s.Mid(0, s.Find('|')); 
						s = s.Mid(s.Find('|') + 1);
						Patronymic = s.Mid(0, s.Find('|'));
						s = s.Mid(s.Find('|') + 1);
						Birthday.ParseDateTime(s.Mid(0, s.Find('|')));
						s = s.Mid(s.Find('|') + 1);
						ArrivalDate = _wtoi(s.Mid(0, s.Find('|')));
						s = s.Mid(s.Find('|') + 1);
						for (int i = 0; i < ComboFaculity.GetCount(); i++)
						{
							if (id_faculity[i] == s.Mid(0, s.Find('|')))
							{
								ComboFaculity.SetCurSel(i);
								break;
							}
						}
						s = s.Mid(s.Find('|') + 1);
						for (int i = 0; i < ComboCathedra.GetCount(); i++)
						{
							if (id_cathedra[i] == s.Mid(0, s.Find('|')))
							{
								ComboCathedra.SetCurSel(i);
								break;
							}
						}
						s = s.Mid(s.Find('|') + 1);
						for (int i = 0; i < ComboGroup.GetCount(); i++)
						{
							if (id_group[i] == s.Mid(0, s.Find('|')))
							{
								ComboGroup.SetCurSel(i);
								break;
							}
						}
						s = s.Mid(s.Find('|') + 1);
						BookNumber = s;
					}
				}
				else if(fl)
				{
					CString s = buf.Mid(buf.Find('*') + 2);
					int m = SessionList.GetCount();
					SessionList.AddString(L"Сессия №" + s.Mid(0, s.Find('|')));
					s = s.Mid(s.Find('|') + 1);
					int n = 0;
					while (s.Find('|') != -1)
					{
						SubjectListArray[m][n] = s.Mid(0, s.Find('|'));
						s = s.Mid(s.Find('|') + 1);
						MarkListArray[m][n] = s.Mid(0, s.Find('|'));
						s = s.Mid(s.Find('|') + 1);
						n++;
					}
				}
			}
			f.Close();
		}
		catch(CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
	UpdateData(false);
}

CString DataChange::getId()
{
	CStdioFile f;
	CString buf;
	if (f.Open(L"change.txt", CFile::modeRead | CFile::typeBinary))
	{
		try
		{
			while (f.ReadString(buf))
			{
				id_student = buf.Mid(buf.Find('S') + 1);
			}
			f.Close();
		}
		catch(CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
	return id_student;
}
void DataChange::Button_addSession()
{
	if (SessionList.GetCount() == 9)
	{
		MessageBox(L"Максимальное количество сессий - 9!");
		return;
	}
	CString str;
	str.Format(L"%i", SessionList.GetCount() + 1);
	SessionList.AddString(L"Сессия №" + str);
}


void DataChange::Button_deleteSession()
{
	if (SessionList.GetCurSel() != SessionList.GetCount() - 1)
	{
		MessageBox(L"Удаление сессий возможно только с конца");
		return;
	}
	SessionList.DeleteString(SessionList.GetCount()-1);
	for (int i = 0; i < 10; i++)
	{
		MarkList.DeleteString(i);
		SubjectList.DeleteString(i);
		MarkListArray[SessionList.GetCount()][i] = "";
		SubjectListArray[SessionList.GetCount()][i] = "";
	}
}

void DataChange::Button_renameSubjectMark()
{
	UpdateData(true);
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
	SubjectListArray[m][SubjectList.GetCurSel()] = Subject;
	Subject = "";
	MarkListArray[m][MarkList.GetCurSel()] = Mark;
	MarkList.UpdateWindow();
	Mark = "";
	UpdateData(false);
}


void DataChange::Button_addSubject()
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


void DataChange::Button_deleteSubject()
{
	if (SubjectList.GetCount() > 0)
	{
		for (int i = SubjectList.GetCurSel(); i < SubjectList.GetCount(); i++)
		{
			SubjectListArray[SessionList.GetCurSel()][i] = 
				SubjectListArray[SessionList.GetCurSel()][i+1];
			MarkListArray[SessionList.GetCurSel()][i] = MarkListArray[SessionList.GetCurSel()][i+1];
		}
		SubjectList.DeleteString(SubjectList.GetCurSel());
		MarkList.DeleteString(MarkList.GetCurSel());
	}
}

void DataChange::List_ResetSession()
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


void DataChange::List_Subject()
{
	MarkList.SetCurSel(SubjectList.GetCurSel());
	Subject = SubjectListArray[SessionList.GetCurSel()][SubjectList.GetCurSel()];
	Mark = MarkListArray[SessionList.GetCurSel()][MarkList.GetCurSel()];
	UpdateData(false);
}


void DataChange::List_Mark()
{
	SubjectList.SetCurSel(MarkList.GetCurSel());
	Subject = SubjectListArray[SessionList.GetCurSel()][SubjectList.GetCurSel()];
	Mark = MarkListArray[SessionList.GetCurSel()][MarkList.GetCurSel()];
	UpdateData(false);
}

int DataChange::Check()
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

void DataChange::m_fwrite()
{
	UpdateData(true);
	CStdioFile f, f1;
	CString path = _T("Student.txt");
	CString buf, y;
	y.Format(L"%i", ArrivalDate);
	int w = 0;
	if (f1.Open(L"Rewrite.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary))
	{
		f1.SeekToBegin();
		try
		{
			if (f.Open(path, CFile::modeNoTruncate | CFile::modeRead | CFile::typeBinary))
			{
				try
				{
					f.SeekToBegin();
					while (f.ReadString(buf))
					{
						if (buf[0] != '*')
						{
							CString s = buf.Mid(buf.Find('S') + 1);
							if (s.Mid(0, s.Find('|')) == id_student)
							{
								w = 1;
								f1.WriteString(L"S" + id_student + L"|" + Surname + L"|" + Name + L"|" + Patronymic + L"|"
									+ Birthday.Format(_T("%d.%m.%Y")) + L"|" + y + L"|" + id_faculity[ComboFaculity.GetCurSel()] + L"|"
									+ id_cathedra[ComboCathedra.GetCurSel()] + L"|" + id_group[ComboGroup.GetCurSel()] + L"|" + BookNumber + L"\r\n");
							}
							else
							{
								w = 2;
								f1.WriteString(buf + L"\r\n");
							}
						}
						else if (w == 1 && buf[0] == '*')
						{
							w = 0;
							for (int i = 0; i < SessionList.GetCount(); i++)
							{
								CString s;
								s.Format(L"%i", i + 1);
								f1.WriteString(L"*C" + s + L"|");
								int j = 0;
								while (SubjectListArray[i][j] != "")
								{
									f1.WriteString(SubjectListArray[i][j] + L"|" + MarkListArray[i][j] + L"|");
									if (j == 9)
										break;
									j++;
								}
								f1.WriteString(L"\r\n");
							}
						}
						else if (w == 2)
						{
							f1.WriteString(buf + L"\r\n");
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
			f1.Close();
		}
		catch (CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при записи в файл");
		}
	}
}
void DataChange::Button_changeStudent()
{
	UpdateData(true);
	int c = Check();
	if (c == 1)
	{
		MessageBox(L"Проверьте правильность введенных данных!");
		return;
	}
	m_fwrite();
	try
	{
		CFile::Remove(L"Student.txt");
	}
	catch(CFileException *ex)
	{
		ex->ReportError();
		MessageBox(L"Ошибка при удалении файла");
	}
	try
	{
		CFile::Rename(L"Rewrite.txt", L"Student.txt");
	}
	catch(CFileException *ex)
	{
		ex->ReportError();
		MessageBox(L"Ошибка при переименовании файла");
	}
	EndDialog(0);
}


void DataChange::Button_deleteStudent()
{
	UpdateData(true);
	CStdioFile f, f1;
	CString path = _T("Student.txt");
	CString buf;
	int fl = 0;
	if (f1.Open(L"Rewrite.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary))
	{
		f1.SeekToBegin();
		try
		{
			if (f.Open(path, CFile::modeNoTruncate | CFile::modeRead | CFile::typeBinary))
			{
				try
				{
					f.SeekToBegin();
					while (f.ReadString(buf))
					{
						if (buf[0] != '*')
						{
							if (!fl)
							{
								CString s = buf.Mid(buf.Find('S') + 1);
								if (s.Mid(0, s.Find('|')) == id_student)
									fl = 1;
								else
									f1.WriteString(buf + L"\r\n");
							}
							else
							{
								fl = 2;
								f1.WriteString(buf + L"\r\n");
							}
						}
						else if (fl != 1)
							f1.WriteString(buf + "\r\n");
					}
					f.Close();
				}
				catch (CFileException *ex)
				{
					MessageBox(L"Ошибка при чтении файла");
				}
			}
			f1.Close();
		}
		catch (CFileException *ex)
		{
			MessageBox(L"Ошибка при записи в файл");
		}
	}
	try
	{
		CFile::Remove(L"Student.txt");
	}
	catch(CFileException *ex)
	{
		MessageBox(L"Ошибка удаления файла");
	}
	try
	{
		CFile::Rename(L"Rewrite.txt", L"Student.txt");
	}
	catch (CFileException *ex)
	{
		MessageBox(L"Ошибка при переименовании файла");
	}
	EndDialog(0);
}
