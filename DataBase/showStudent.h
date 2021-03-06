#pragma once


// Диалоговое окно showStudent

class showStudent : public CDialogEx
{
	DECLARE_DYNAMIC(showStudent)

public:
	showStudent(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~showStudent();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListBox Students;
	CListBox Year;
	CListBox Number;
	CListBox University;
	CListBox Session;
	CListBox Subject;
	afx_msg void List_Students();
	void readDB();
	void showDB();
	CString getUniver(CString, CString);
	int l;
	int *sCount;
	afx_msg void Button_changeStudent();
	afx_msg void List_Session();
	afx_msg void Button_breakStudent();
};
