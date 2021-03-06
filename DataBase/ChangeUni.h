#pragma once


// Диалоговое окно ChangeUni

class ChangeUni : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeUni)

public:
	ChangeUni(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ChangeUni();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGEUNI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListBox ListFaculity;
	CListBox ListCathedra;
	CListBox ListGroup;
	CString Faculity;
	CString Cathedra;
	CString Group;
	afx_msg void Button_changeFaculity();
	afx_msg void Button_changeCathedra();
	afx_msg void Button_changeGroup();
	void ListBox();
	CString *id_Faculity;
	CString *id_Cathedra;
	CString *id_Group;
	CString * FileToList(CString, CListBox*, CString*);
	CString * UpdateList(CString, CListBox*, CString*);
	CString m_file(CListBox*, CString, CString, CString, CString*);
};
