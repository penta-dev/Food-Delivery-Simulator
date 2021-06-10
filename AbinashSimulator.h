
// AbinashSimulator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAbinashSimulatorApp:
// See AbinashSimulator.cpp for the implementation of this class
//

class CAbinashSimulatorApp : public CWinApp
{
public:
	CAbinashSimulatorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAbinashSimulatorApp theApp;
