#pragma once


// Диалоговое окно DataChange

class DataChange : public CDialogEx
{
	DECLARE_DYNAMIC(DataChange)

public:
	DataChange(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~DataChange();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATACHANGE };
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
	CString Subject;
	CString Mark;
	CListBox SessionList;
	CListBox SubjectList;
	CListBox MarkList;
	afx_msg void Button_addSession();
	afx_msg void Button_deleteSession();
	afx_msg void Button_addSubject();
	afx_msg void Button_deleteSubject();
	void ComboBox();
	void ListBox();
	CString getId();
	int Check();
	void m_fwrite();
	void Data();
	CString* FileToBox(CString, CComboBox*, CString*);
	CString id_student;
	CString *id_cathedra;
	CString *id_group;
	CString *id_faculity;
	CString **MarkListArray;
	CString **SubjectListArray;
	afx_msg void List_ResetSession();
	afx_msg void List_Subject();
	afx_msg void List_Mark();
	afx_msg void Button_changeStudent();
	afx_msg void Button_renameSubjectMark();
	afx_msg void Button_deleteStudent();
};
