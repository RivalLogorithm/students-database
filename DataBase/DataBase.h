
// DataBase.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDataBaseApp:
// Сведения о реализации этого класса: DataBase.cpp
//

class CDataBaseApp : public CWinApp
{
public:
	CDataBaseApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDataBaseApp theApp;
