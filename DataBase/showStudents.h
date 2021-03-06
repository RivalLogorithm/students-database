#pragma once


// Диалоговое окно showStudents

class showStudents : public CDialogEx
{
	DECLARE_DYNAMIC(showStudents)

public:
	showStudents(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~showStudents();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	void readDB();
	void showDB();
	CString getUniver(CString,CString);
	int l;
	int *sCount;
	afx_msg void List_Student();
	CListBox Students;
	CListBox Year;
	CListBox Number;
	CListBox University;
	CListBox Session;
	afx_msg void Button_changeStudent();
	CListBox Subject;
};
