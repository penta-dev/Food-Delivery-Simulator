
// AbinashSimulatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "AbinashSimulator.h"
#include "AbinashSimulatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAbinashSimulatorDlg dialog



CAbinashSimulatorDlg::CAbinashSimulatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABINASHSIMULATOR_DIALOG, pParent)
	, _order_dur(0.5)
	, _courier_max_time(15)
	, _time(0)
	, _courier_min_time(3)
	, _m_avg_f(0)
	, _m_avg_c(0)
	, _fifo_avg_f(0)
	, _fifo_avg_c(0)/*
	, _static_kitchen(_T("Kitchen"))
	, _static_coming_couriers(_T("Coming couriers"))
	, _static_fifo_waiting_c(_T("Waiting couriers"))
	, _static_fifo_deliveried_c(_T("Deliveried couriers"))
	, _static_fifo_deliveried_f(_T("Deliveried foods"))
	, _static_fifo_waiting_f(_T("Waiting foods"))
	, _static_m_deliveried_c(_T("Deliveried couriers"))
	, _static_m_deliveried_f(_T("Deliveried foods"))
	, _static_m_waiting_c(_T("Waiting couriers"))
	, _static_m_waiting_f(_T("Waiting foods"))*/
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAbinashSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AVG_ORDER_DUR, _order_dur);
	DDX_Text(pDX, IDC_EDIT_COURIER_MAX_TIME, _courier_max_time);
	DDX_Text(pDX, IDC_EDIT_CURRENT_TIME, _time);
	DDX_Text(pDX, IDC_EDIT_COURIER_MIN_TIME, _courier_min_time);
	DDX_Text(pDX, IDC_EDIT_AVG_FOOD_WAITING, _m_avg_f);
	DDX_Text(pDX, IDC_EDIT_AVG_COURIER_WAITING, _m_avg_c);
	DDX_Text(pDX, IDC_EDIT_AVG_FOOD_WAITING2, _fifo_avg_f);
	DDX_Text(pDX, IDC_EDIT_AVG_COURIER_WAITING2, _fifo_avg_c);
	DDX_Control(pDX, IDC_LIST_KITCHEN, _list_kitchen);
	DDX_Control(pDX, IDC_LIST_MATCHED_COURIERS, _list_matched_couriers);
	DDX_Control(pDX, IDC_LIST_MATCHED_DELIVERY, _list_matched_delivery_foods);
	DDX_Control(pDX, IDC_LIST_MATCHED_FOOD, _list_matched_food);
	DDX_Control(pDX, IDC_LIST_FIFO_FOODS, _list_fifo_foods);
	DDX_Control(pDX, IDC_LIST_FIFO_DELIVERY, _list_fifo_delivery_foods);
	DDX_Control(pDX, IDC_LIST_FIFO_COURIERS, _list_fifo_couriers);
	DDX_Control(pDX, IDC_LIST_COMMING_COURIERS, _list_coming_couriers);
	DDX_Control(pDX, IDC_LIST_MATCHED_DELIVERY_COURIERS, _list_matched_delivery_couriers);
	DDX_Control(pDX, IDC_LIST_FIFO_DELIVERY_COURIERS, _list_fifo_delivery_couriers);
	/*
	DDX_Text(pDX, IDC_KITCHEN, _static_kitchen);
	DDX_Text(pDX, IDC_COMING_COURIERS, _static_coming_couriers);
	DDX_Text(pDX, IDC_FIFO_COURIERS, _static_fifo_waiting_c);
	DDX_Text(pDX, IDC_FIFO_DELIVERIED_COURIERS, _static_fifo_deliveried_c);
	DDX_Text(pDX, IDC_FIFO_DELIVERIED_FOODS, _static_fifo_deliveried_f);
	DDX_Text(pDX, IDC_FIFO_WAITING_FOODS, _static_fifo_waiting_f);
	DDX_Text(pDX, IDC_M_DELIVERIED_COURIERS, _static_m_deliveried_c);
	DDX_Text(pDX, IDC_M_DELIVERIED_FOODS, _static_m_deliveried_f);
	DDX_Text(pDX, IDC_M_WAITING_COURIERS, _static_m_waiting_c);
	DDX_Text(pDX, IDC_M_WAITING_FOODS, _static_m_waiting_f);
	*/
}

BEGIN_MESSAGE_MAP(CAbinashSimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CAbinashSimulatorDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CAbinashSimulatorDlg::OnBnClickedButtonStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &CAbinashSimulatorDlg::OnClickedButtonResult)
END_MESSAGE_MAP()


// CAbinashSimulatorDlg message handlers

BOOL CAbinashSimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	srand(time(0));
	ASOrder::CreateSamples();

	init();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CAbinashSimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAbinashSimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAbinashSimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAbinashSimulatorDlg::OnBnClickedButtonPlay()
{
	if (_isPlaying)
	{// play -> pause
		_isPlaying = false;
		KillTimer(_timer);
		KillTimer(_guiTimer);
		SetDlgItemText(IDC_BUTTON_PLAY, _T("Play"));
	}
	else {	// play
		_isPlaying = true;
		_timer = SetTimer(1, 10, nullptr);
		_guiTimer = SetTimer(2, 1000, nullptr);
		SetDlgItemText(IDC_BUTTON_PLAY, _T("Pause"));
		UpdateData();
	}
}


void CAbinashSimulatorDlg::OnBnClickedButtonStop()
{
	KillTimer(_timer);
	KillTimer(_guiTimer);
	delete _system1;
	delete _system2;
	SetDlgItemText(IDC_BUTTON_PLAY, _T("Play"));
	init();
}

void CAbinashSimulatorDlg::init()
{
	_time = 0;
	_isPlaying = false;
	_newOrderTime = 0;
	_coming_couriers.clear();

	_system1 = new ASMatchedSystem();
	_system2 = new ASFIFOSystem();

	GetDlgItem(IDC_KITCHEN)->SetWindowText(L"Kitchen");
	GetDlgItem(IDC_COMING_COURIERS)->SetWindowText(L"Coming couriers");

	GetDlgItem(IDC_M_WAITING_FOODS)->SetWindowText(L"Waiting foods");
	GetDlgItem(IDC_M_WAITING_COURIERS)->SetWindowText(L"Waiting couriers");
	GetDlgItem(IDC_M_DELIVERIED_FOODS)->SetWindowText(L"Delivered foods");
	GetDlgItem(IDC_M_DELIVERIED_COURIERS)->SetWindowText(L"Delivered couriers");

	GetDlgItem(IDC_FIFO_WAITING_FOODS)->SetWindowText(L"Waiting foods");
	GetDlgItem(IDC_FIFO_WAITING_COURIERS)->SetWindowText(L"Waiting couriers");
	GetDlgItem(IDC_FIFO_DELIVERIED_FOODS)->SetWindowText(L"Delivered foods");
	GetDlgItem(IDC_FIFO_DELIVERIED_COURIERS)->SetWindowText(L"Delivered couriers");

	UpdateData(false);
}

void CAbinashSimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (_timer == nIDEvent)
	{
		// update time
		_time += 10 / 1000.0;

		// generate order
		if (_newOrderTime < _time)
		{
			auto order = ASOrder::CreateRandomOrder();
			order._created_time = _time;

			_system1->addOrder(order);
			_system2->addOrder(order);

			// calc next order time
			float dt = rand() % (int(_order_dur * 2000)) / 1000.0f;	// 0 ~ 2*dur, thus avg = dur
			_newOrderTime += dt;

			// courier will arrive for new order
			ASCourier courier;
			courier._created_time = _time;
			courier._arr_time = _time + rand() % ((_courier_max_time - _courier_min_time) * 1000) / 1000.0f;
			courier._specific_order = order;
			_coming_couriers.push_back(courier);
		}

		// process courier
		for (int i = 0; i < _coming_couriers.size(); i++)
		{
			auto c = _coming_couriers[i];
			if (c._arr_time < _time)
			{
				_system1->addCourier(c);
				_system2->addCourier(c);
				_coming_couriers.erase(_coming_couriers.begin() + i);
				break;
			}
		}

		// process system
		_system1->process(_time);
		_system2->process(_time);
	}

	// GUI update
	if (_guiTimer == nIDEvent)
	{
		// kitchen & cooking
		for (int i = 0; i < _list_kitchen.GetCount(); i++) _list_kitchen.DeleteString(0);
		for each (auto order in _system1->_cooking_orders)
		{
			_list_kitchen.AddString(CString(order.to_string().c_str()));
		}

		// coming couriers
		for (int i = 0; i < _list_coming_couriers.GetCount(); i++) _list_coming_couriers.DeleteString(0);
		for each (auto c in _coming_couriers)
		{
			_list_coming_couriers.AddString(CString(c.to_string().c_str()));
		}

		// matched waiting couriers
		for (int i = 0; i < _list_matched_couriers.GetCount(); i++) _list_matched_couriers.DeleteString(0);
		for each (auto c in _system1->_waiting_couriers)
		{
			_list_matched_couriers.AddString(CString(c.to_string().c_str()));
		}

		// matched waiting foods
		for (int i = 0; i < _list_matched_food.GetCount(); i++) _list_matched_food.DeleteString(0);
		for each (auto food in _system1->_waiting_foods)
		{
			_list_matched_food.AddString(CString(food.to_string().c_str()));
		}

		// matched delivery foods
		for (int i = 0; i < _list_matched_delivery_foods.GetCount(); i++) _list_matched_delivery_foods.DeleteString(0);
		for each (auto c in _system1->_deliveried_foods)
		{
			_list_matched_delivery_foods.AddString(CString(c.to_string().c_str()));
		}

		// matched delivery couriers
		for (int i = 0; i < _list_matched_delivery_couriers.GetCount(); i++) _list_matched_delivery_couriers.DeleteString(0);
		for each (auto c in _system1->_deliveried_couriers)
		{
			_list_matched_delivery_couriers.AddString(CString(c.to_string().c_str()));
		}

		// fifo waiting couriers
		for (int i = 0; i < _list_fifo_couriers.GetCount(); i++) _list_fifo_couriers.DeleteString(0);
		for each (auto c in _system2->_waiting_couriers)
		{
			_list_fifo_couriers.AddString(CString(c.to_string().c_str()));
		}

		// fifo waiting foods
		for (int i = 0; i < _list_fifo_foods.GetCount(); i++) _list_fifo_foods.DeleteString(0);
		for each (auto food in _system2->_waiting_foods)
		{
			_list_fifo_foods.AddString(CString(food.to_string().c_str()));
		}

		// fifo delivery foods
		for (int i = 0; i < _list_fifo_delivery_foods.GetCount(); i++) _list_fifo_delivery_foods.DeleteString(0);
		for each (auto food in _system2->_deliveried_foods)
		{
			_list_fifo_delivery_foods.AddString(CString(food.to_string().c_str()));
		}

		// fifo delivery couriers
		for (int i = 0; i < _list_fifo_delivery_couriers.GetCount(); i++) _list_fifo_delivery_couriers.DeleteString(0);
		for each (auto c in _system2->_deliveried_couriers)
		{
			_list_fifo_delivery_couriers.AddString(CString(c.to_string().c_str()));
		}

		UpdateData(false);
		CString str;

		// update numbers
		/*
		_static_kitchen.Format(_T("Kitchen (%d)"), _system1->_cooking_orders.size());
		_static_coming_couriers.Format(_T("Coming couriers (%d)"), _coming_couriers.size());

		_static_m_waiting_f.Format(_T("Waiting foods (%d)"), _system1->_waiting_foods.size());
		_static_m_waiting_c.Format(_T("Waiting couriers (%d)"), _system1->_waiting_couriers.size());
		_static_m_deliveried_f.Format(_T("Deliveried foods (%d)"), _system1->_deliveried_foods.size());
		_static_m_deliveried_c.Format(_T("Deliveried couriers (%d)"), _system1->_deliveried_couriers.size());

		_static_fifo_waiting_f.Format(_T("Waiting foods (%d)"), _system2->_waiting_foods.size());
		_static_fifo_waiting_c.Format(_T("Waiting couriers (%d)"), _system2->_waiting_couriers.size());
		_static_fifo_deliveried_f.Format(_T("Deliveried foods (%d)"), _system2->_deliveried_foods.size());
		_static_fifo_deliveried_c.Format(_T("Deliveried couriers (%d)"), _system2->_deliveried_couriers.size());*/

		str.Format(_T("Kitchen (%d)"), _system1->_cooking_orders.size());
		GetDlgItem(IDC_KITCHEN)->SetWindowText(str);
		str.Format(_T("Coming couriers (%d)"), _coming_couriers.size());
		GetDlgItem(IDC_COMING_COURIERS)->SetWindowText(str);

		str.Format(_T("Waiting foods (%d)"), _system1->_waiting_foods.size());
		GetDlgItem(IDC_M_WAITING_FOODS)->SetWindowText(str);
		str.Format(_T("Waiting couriers (%d)"), _system1->_waiting_couriers.size());
		GetDlgItem(IDC_M_WAITING_COURIERS)->SetWindowText(str);
		str.Format(_T("Delivered foods (%d)"), _system1->_deliveried_foods.size());
		GetDlgItem(IDC_M_DELIVERIED_FOODS)->SetWindowText(str);
		str.Format(_T("Delivered couriers (%d)"), _system1->_deliveried_couriers.size());
		GetDlgItem(IDC_M_DELIVERIED_COURIERS)->SetWindowText(str);

		str.Format(_T("Waiting foods (%d)"), _system2->_waiting_foods.size());
		GetDlgItem(IDC_FIFO_WAITING_FOODS)->SetWindowText(str);
		str.Format(_T("Waiting couriers (%d)"), _system2->_waiting_couriers.size());
		GetDlgItem(IDC_FIFO_WAITING_COURIERS)->SetWindowText(str);
		str.Format(_T("Delivered foods (%d)"), _system2->_deliveried_foods.size());
		GetDlgItem(IDC_FIFO_DELIVERIED_FOODS)->SetWindowText(str);
		str.Format(_T("Delivered couriers (%d)"), _system2->_deliveried_couriers.size());
		GetDlgItem(IDC_FIFO_DELIVERIED_COURIERS)->SetWindowText(str);

		OnClickedButtonResult();
	}
}


void CAbinashSimulatorDlg::OnClickedButtonResult()
{
	float total;
	int n;

	// matched food avg waiting
	total = 0;
	n = 0;
	for each (auto food in _system1->_deliveried_foods)
	{
		float dt = food._delivery_time - food._created_time - food._prep_time;
		total += dt;
		n++;
	}
	if (n) {
		_m_avg_f = total / n * 1000;
	}

	// matched courier avg waiting
	total = 0;
	n = 0;
	for each (auto c in _system1->_deliveried_couriers)
	{
		float dt = c._delivery_time - c._arr_time;
		total += dt;
		n++;
	}
	if (n) {
		_m_avg_c = total / n * 1000;
	}

	// fifo food avg waiting
	total = 0;
	n = 0;
	for each (auto food in _system2->_deliveried_foods)
	{
		float dt = food._delivery_time - food._created_time - food._prep_time;
		total += dt;
		n++;
	}
	if (n) {
		_fifo_avg_f = total / n * 1000;
	}

	// fifo courier avg waiting
	total = 0;
	n = 0;
	for each (auto c in _system2->_deliveried_couriers)
	{
		float dt = c._delivery_time - c._arr_time;
		total += dt;
		n++;
	}
	if (n) {
		_fifo_avg_c = total / n * 1000;
	}

	UpdateData(false);
}
