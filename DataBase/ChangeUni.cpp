// ChangeUni.cpp: файл реализации
//

#include "stdafx.h"
#include "DataBase.h"
#include "ChangeUni.h"
#include "afxdialogex.h"


// Диалоговое окно ChangeUni

IMPLEMENT_DYNAMIC(ChangeUni, CDialogEx)

ChangeUni::ChangeUni(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHANGEUNI, pParent)
	, Faculity(_T(""))
	, Cathedra(_T(""))
	, Group(_T(""))
{

}

ChangeUni::~ChangeUni()
{
}

void ChangeUni::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ListFaculity);
	DDX_Control(pDX, IDC_LIST2, ListCathedra);
	DDX_Control(pDX, IDC_LIST3, ListGroup);
	DDX_Text(pDX, IDC_EDIT1, Faculity);
	DDX_Text(pDX, IDC_EDIT2, Cathedra);
	DDX_Text(pDX, IDC_EDIT3, Group);
}


BEGIN_MESSAGE_MAP(ChangeUni, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChangeUni::Button_changeFaculity)
	ON_BN_CLICKED(IDC_BUTTON2, &ChangeUni::Button_changeCathedra)
	ON_BN_CLICKED(IDC_BUTTON3, &ChangeUni::Button_changeGroup)
END_MESSAGE_MAP()


// Обработчики сообщений ChangeUni

BOOL ChangeUni::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ListBox();
	return TRUE;
}

CString* ChangeUni::FileToList(CString path, CListBox* list, CString*array)
{
	CStdioFile f;
	CString buf;
	int l = 0;
	delete[] array;
	if (f.Open(path, CFile::modeRead | CFile::typeBinary))
	{
		try
		{
			while (f.ReadString(buf))
			{
				l++;
			}
			array = new CString[l];
			l = 0;
			f.SeekToBegin();
			while (f.ReadString(buf))
			{
				array[l] = buf.Mid(0, buf.Find('|'));
				list->AddString(buf.Mid(buf.Find('|') + 1));
				l++;
			}
			f.Close();
		}
		catch (CFileException *ex)
		{
			ex->ReportError();
			MessageBox(L"Ошибка при чтении файла");
		}
	}
	UpdateData(false);
	return array;
}
void ChangeUni::ListBox()
{
	id_Faculity = FileToList(_T("Faculity.txt"), &ListFaculity, id_Faculity);
	id_Cathedra = FileToList(_T("Cathedra.txt"), &ListCathedra, id_Cathedra);
	id_Group = FileToList(_T("Group.txt"), &ListGroup, id_Group);
	if (ListFaculity.GetCount() == 0 || ListCathedra.GetCount() == 0 || ListGroup.GetCount() == 0)
	{
		MessageBox(L"Чтобы редактировать данные о университете сначала добавьте их");
		EndDialog(0);
	}
}
CString * ChangeUni::UpdateList(CString path, CListBox* list, CString* array)
{
	while (list->GetCount() > 0)
	{
		list->DeleteString(list->GetCount() - 1);
	}
	array = FileToList(path, list, array);
	return array;
}

CString ChangeUni::m_file(CListBox* list, CString path, CString path1, CString data, CString* array)
{
	if (list->GetCurSel() < 0)
	{
		MessageBox(L"Выберите поле");
		return data;
	}
	data.Remove('|');
	if (data == "")
	{
		MessageBox(L"Запишите данные в поле");
		return  data;
	}
	CStdioFile f, f1;
	CString buf;
	if (f1.Open(path1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary))
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
						if (buf.Mid(0, buf.Find('|')) == array[list->GetCurSel()])
							f1.WriteString(array[list->GetCurSel()] + L"|" + data + L"\r\n");
						else
							f1.WriteString(buf + L"\r\n");
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
		CFile::Remove(path);
	}
	catch(CFileException *ex)
	{
		MessageBox(L"Ошибка при удалении файла");
	}
	try
	{
		CFile::Rename(path1, path);
	}
	catch(CFileException *ex)
	{
		MessageBox(L"Ошибка при переименовании");
	}
	data = "";
	array = UpdateList(path, list, array);
	return data;
}
void ChangeUni::Button_changeFaculity()
{
	UpdateData(true);
	Faculity = m_file(&ListFaculity, L"Faculity.txt", L"cFaculity.txt", Faculity, id_Faculity);
	UpdateData(false);
}


void ChangeUni::Button_changeCathedra()
{
	UpdateData(true);
	Cathedra = m_file(&ListCathedra, L"Cathedra.txt", L"cCathedra.txt", Cathedra, id_Cathedra);
	UpdateData(false);
}


void ChangeUni::Button_changeGroup()
{
	UpdateData(true);
	Group = m_file(&ListGroup, L"Group.txt", L"cGroup.txt", Group, id_Group);
	UpdateData();
}
