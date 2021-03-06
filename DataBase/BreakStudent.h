#pragma once


// Диалоговое окно BreakStudent

class BreakStudent : public CDialogEx
{
	DECLARE_DYNAMIC(BreakStudent)

public:
	BreakStudent(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~BreakStudent();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BREAK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	void readDB();
	int l;
	int* sCount;
	CString	getUniver(CString, CString);
	bool CheckBad(CString);
	void CalcData();
	void GoodData(CString,CString*,int);
	void BadData(CString, CString*, int);
	CListBox gStudent;
	CListBox gYear;
	CListBox gNumber;
	CListBox gFaculity;
	CListBox gSession;
	CListBox gSubject;
	CListBox bStudent;
	CListBox bYear;
	CListBox bNumber;
	CListBox bFaculity;
	CListBox bSession;
	CListBox bSubject;
	afx_msg void List_Student();
	afx_msg void List_Session();
	afx_msg void List_bStudent();
	afx_msg void List_bSession();
};
