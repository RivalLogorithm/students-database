// AddUniversity.cpp: файл реализации
//

#include "stdafx.h"
#include "DataBase.h"
#include "AddUniversity.h"
#include "afxdialogex.h"


// Диалоговое окно AddUniversity

IMPLEMENT_DYNAMIC(AddUniversity, CDialogEx)

AddUniversity::AddUniversity(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNUVERSITY, pParent)
	, Faculity(_T(""))
	, Cathedra(_T(""))
	, Group(_T(""))
{

}

AddUniversity::~AddUniversity()
{
}

void AddUniversity::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Faculity);
	DDX_Text(pDX, IDC_EDIT2, Cathedra);
	DDX_Text(pDX, IDC_EDIT3, Group);
}

int AddUniversity::my_fread(CString file)
{
	CStdioFile f;
	CString buf;
	int index = 0;
	if (f.Open(file, CFile::modeRead| CFile::typeBinary))
	{
		try
		{
			while (f.ReadString(buf))
				index = _wtoi(buf.Mid(0, buf.Find('|', 0)));
			f.Close();
		}
		catch (CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
	return index;
}

void AddUniversity::my_fwrite(CString file, CString data, int n)
{
	CStdioFile f;
	if (f.Open(file, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::typeBinary))
	{
		try
		{
			f.SeekToEnd();
			n++;
			CString	s;
			s.Format(L"%i", n);
			f.WriteString(s + L"|" + data + L"\r\n");
		}
		catch (CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при записи в файл");
		}
	}
	f.Close();
}


BEGIN_MESSAGE_MAP(AddUniversity, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddUniversity::Button_addFaculity)
	ON_BN_CLICKED(IDC_BUTTON2, &AddUniversity::Button_addCathedra)
	ON_BN_CLICKED(IDC_BUTTON3, &AddUniversity::Button_addGroup)
END_MESSAGE_MAP()


// Обработчики сообщений AddUniversity

void AddUniversity::Button_addFaculity()
{
	UpdateData(true);
	Faculity.Remove('|');
	UpdateData(false);
	if (Faculity == "")
	{
		MessageBox(L"Введите название факультета");
		return;
	}
	CString path = _T("Faculity.txt");
	int n = my_fread(path);
	my_fwrite(path, Faculity, n);
	Faculity = "";
	UpdateData(false);
}

void AddUniversity::Button_addCathedra()
{
	UpdateData(true);
	Cathedra.Remove('|');
	UpdateData(false);
	if (Cathedra == "")
	{
		MessageBox(L"Введите название кафедры");
		return;
	}
	CString path = _T("Cathedra.txt");
	int n = my_fread(path);
	my_fwrite(path, Cathedra, n);
	Cathedra = "";
	UpdateData(false);
}

void AddUniversity::Button_addGroup()
{
	UpdateData(true);
	Group.Remove('|');
	UpdateData(false);
	if (Group == "")
	{
		MessageBox(L"Введите название группы");
		return;
	}
	CString path = _T("Group.txt");
	int n = my_fread(path);
	my_fwrite(path, Group, n);
	Group = "";
	UpdateData(false);
}


