
// AbinashSimulatorDlg.h : header file
//

#pragma once

#include "ASOrder.h"
#include "ASCourier.h"
#include "ASSystem.h"
#include "ASMatchedSystem.h"
#include "ASFIFOSystem.h"

// CAbinashSimulatorDlg dialog
class CAbinashSimulatorDlg : public CDialogEx
{
// Construction
public:
	CAbinashSimulatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABINASHSIMULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnClickedButtonResult();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	void init();

public:
	float _order_dur;
	int _courier_max_time;
	float _time;
	int _courier_min_time;

	float _m_avg_f;
	float _m_avg_c;
	float _fifo_avg_f;
	float _fifo_avg_c;

	CListBox _list_kitchen;
	CListBox _list_matched_couriers;
	CListBox _list_matched_delivery_foods;
	CListBox _list_matched_food;
	CListBox _list_fifo_foods;
	CListBox _list_fifo_delivery_foods;
	CListBox _list_fifo_couriers;
	CListBox _list_coming_couriers;
	CListBox _list_matched_delivery_couriers;
	CListBox _list_fifo_delivery_couriers;

	/*
	CString _static_kitchen;
	CString _static_coming_couriers;
	CString _static_fifo_waiting_c;
	CString _static_fifo_deliveried_c;
	CString _static_fifo_deliveried_f;
	CString _static_fifo_waiting_f;
	CString _static_m_deliveried_c;
	CString _static_m_deliveried_f;
	CString _static_m_waiting_c;
	CString _static_m_waiting_f;
	*/
public:
	bool _isPlaying;
	UINT_PTR _timer;
	UINT_PTR _guiTimer;
	ASSystem* _system1;
	ASSystem* _system2;

	float _newOrderTime;
	vector<ASCourier> _coming_couriers;
};
