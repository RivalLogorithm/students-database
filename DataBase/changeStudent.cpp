// changeStudent.cpp: файл реализации
//

#include "stdafx.h"
#include "DataBase.h"
#include "changeStudent.h"
#include "afxdialogex.h"


// Диалоговое окно changeStudent

IMPLEMENT_DYNAMIC(changeStudent, CDialogEx)

changeStudent::changeStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENT, pParent)
{

}

changeStudent::~changeStudent()
{
}

void changeStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(changeStudent, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений changeStudent
