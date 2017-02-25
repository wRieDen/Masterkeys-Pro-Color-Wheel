
// MasterkeysMFCDlg.h: Headerdatei
//

#pragma once
#include "afxcmn.h"
#include "effect.h"
#include "afxwin.h"

// CMasterkeysMFCDlg-Dialogfeld
class CMasterkeysMFCDlg : public CDialogEx
{
// Konstruktion
public:
	CMasterkeysMFCDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MASTERKEYSMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	int gui_rate;
	float gui_cycle;
	float gui_spread;
	float gui_size;
	float gui_start;
	int gui_color;
	
	CSliderCtrl gui_slider_rate;
	CSliderCtrl gui_slider_spread;
	CSliderCtrl gui_slider_cycle;
	CSliderCtrl gui_slider_size;
	CSliderCtrl gui_slider_start;
	CSliderCtrl gui_slider_color;
	CComboBox gui_combo_type;


	afx_msg void OnNMCustomdrawSliderRate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSpread(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnNMCustomdrawSliderCycle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSize(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderColor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboType();
};
