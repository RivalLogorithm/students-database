#pragma once


// Диалоговое окно changeStudent

class changeStudent : public CDialogEx
{
	DECLARE_DYNAMIC(changeStudent)

public:
	changeStudent(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~changeStudent();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
