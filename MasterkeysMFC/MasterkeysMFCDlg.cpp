
// MasterkeysMFCDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "MasterkeysMFC.h"
#include "MasterkeysMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMasterkeysMFCDlg-Dialogfeld



CMasterkeysMFCDlg::CMasterkeysMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MASTERKEYSMFC_DIALOG, pParent)
	, gui_rate(0)
	, gui_spread(0)
	, gui_cycle(0)
	, gui_size(0)
	, gui_start(0)
	, gui_color(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMasterkeysMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RATE, gui_rate);
	DDV_MinMaxInt(pDX, gui_rate, 1, 1000);
	DDX_Control(pDX, IDC_SLIDER_RATE, gui_slider_rate);
	DDX_Text(pDX, IDC_EDIT_SPREAD, gui_spread);
	DDX_Control(pDX, IDC_SLIDER_SPREAD, gui_slider_spread);
	DDX_Text(pDX, IDC_EDIT_CYCLE, gui_cycle);
	DDX_Control(pDX, IDC_SLIDER_CYCLE, gui_slider_cycle);
	DDX_Text(pDX, IDC_EDIT_SIZE, gui_size);
	DDX_Control(pDX, IDC_SLIDER_SIZE, gui_slider_size);
	DDX_Control(pDX, IDC_SLIDER_START, gui_slider_start);
	DDX_Text(pDX, IDC_EDIT_START, gui_start);
	DDX_Text(pDX, IDC_EDIT_COLOR, gui_color);
	DDX_Control(pDX, IDC_SLIDER_COLOR, gui_slider_color);
	DDX_Control(pDX, IDC_COMBO_TYPE, gui_combo_type);
}

BEGIN_MESSAGE_MAP(CMasterkeysMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_RATE, &CMasterkeysMFCDlg::OnNMCustomdrawSliderRate)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPREAD, &CMasterkeysMFCDlg::OnNMCustomdrawSliderSpread)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CYCLE, &CMasterkeysMFCDlg::OnNMCustomdrawSliderCycle)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SIZE, &CMasterkeysMFCDlg::OnNMCustomdrawSliderSize)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_START, &CMasterkeysMFCDlg::OnNMCustomdrawSliderStart)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_COLOR, &CMasterkeysMFCDlg::OnNMCustomdrawSliderColor)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CMasterkeysMFCDlg::OnCbnSelchangeComboType)
END_MESSAGE_MAP()


// CMasterkeysMFCDlg-Meldungshandler

BOOL CMasterkeysMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	gui_slider_rate.SetRange(1,1000,true);
	gui_slider_rate.SetPos(10);

	gui_slider_spread.SetRange(1, 400, true);
	gui_slider_spread.SetPos(50);

	gui_slider_cycle.SetRange(1, 300, true);
	gui_slider_cycle.SetPos(50);

	gui_slider_size.SetRange(50, 5000, true);
	gui_slider_size.SetPos(250);

	gui_slider_start.SetRange(0, 1000, true);
	gui_slider_start.SetPos(100);

	gui_slider_color.SetRange(0, 639, true);
	gui_slider_color.SetPos(384);

	gui_combo_type.AddString(_T("Masterkeys Pro L"));
	gui_combo_type.AddString(_T("Masterkeys Pro S"));
	gui_combo_type.AddString(_T("Masterkeys Pro L White"));
	gui_combo_type.AddString(_T("Masterkeys Pro M White"));
	gui_combo_type.SetCurSel(0);
	ColorCycleInit();

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CMasterkeysMFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	ColorCycleStop();
}


// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMasterkeysMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CMasterkeysMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMasterkeysMFCDlg::OnNMCustomdrawSliderRate(NMHDR *pNMHDR, LRESULT *pResult)
{
	gui_rate = gui_slider_rate.GetPos();
	UpdateData(false);
	setRate(gui_rate);

}




void CMasterkeysMFCDlg::OnNMCustomdrawSliderSpread(NMHDR *pNMHDR, LRESULT *pResult)
{
	gui_spread = gui_slider_spread.GetPos()/100.f;
	UpdateData(false);
	setSpread(gui_spread);

}


void CMasterkeysMFCDlg::OnNMCustomdrawSliderCycle(NMHDR *pNMHDR, LRESULT *pResult)
{
	gui_cycle = gui_slider_cycle.GetPos() / 100.f;
	UpdateData(false);
	setCycle(gui_cycle);
}


void CMasterkeysMFCDlg::OnNMCustomdrawSliderSize(NMHDR *pNMHDR, LRESULT *pResult)
{
	gui_size = gui_slider_size.GetPos() / 100.f;
	UpdateData(false);
	setSize(gui_size);
}


void CMasterkeysMFCDlg::OnNMCustomdrawSliderStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	gui_start = gui_slider_start.GetPos() / 100.f;
	UpdateData(false);
	setStart(gui_start);
}


void CMasterkeysMFCDlg::OnNMCustomdrawSliderColor(NMHDR *pNMHDR, LRESULT *pResult)
{
	gui_color = gui_slider_color.GetPos();
	UpdateData(false);
	setColor(gui_color);
}


void CMasterkeysMFCDlg::OnCbnSelchangeComboType()
{
	int i = gui_combo_type.GetCurSel();
	switchDevice(gui_combo_type.GetCurSel());
}
