#pragma once


// Диалоговое окно AddUniversity

class AddUniversity : public CDialogEx
{
	DECLARE_DYNAMIC(AddUniversity)

public:
	AddUniversity(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~AddUniversity();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNUVERSITY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int my_fread(CString);
	void my_fwrite(CString, CString, int);
	CString Faculity;
	CString Cathedra;
	CString Group;
	afx_msg void Button_addFaculity();
	afx_msg void Button_addCathedra();
	afx_msg void Button_addGroup();
};
