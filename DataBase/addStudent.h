#pragma once


// Диалоговое окно addStudent

class addStudent : public CDialogEx
{
	DECLARE_DYNAMIC(addStudent)

public:
	addStudent(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~addStudent();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString Surname;
	CString Name;
	CString Patronymic;
	COleDateTime Birthday;
	int ArrivalDate;
	CString BookNumber;
	CComboBox ComboFaculity;
	CComboBox ComboCathedra;
	CComboBox ComboGroup;
	CString *FileToBox(CString, CComboBox*, CString*);
	void ComboBox();
	void ListBox();
	CString *id_faculity;
	CString *id_cathedra;
	CString *id_group;
	CString **MarkListArray;
	CString **SubjectListArray;
	afx_msg void Button_addSession();
	CListBox SessionList;
	CListBox SubjectList;
	CListBox MarkList;
	afx_msg void Button_deleteSession();
	afx_msg void Button_addSubject();
	CString Subject;
	afx_msg void Button_deleteSubject();
	CString Mark;
	afx_msg void List_SessionReset();
	afx_msg void List_Subject();
	afx_msg void List_Mark();
	afx_msg void Button_save();
	int Check();
	int m_fread();
	void m_fwrite(int);
};
