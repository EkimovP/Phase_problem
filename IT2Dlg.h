
// IT2Dlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include <ccomplex>
#define ID_TIMER 1 //объявляем идентификатор таймера

// Диалоговое окно CIT2Dlg
class CIT2Dlg : public CDialogEx
{
// Создание
public:
	CIT2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IT2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR);//функция реакции на таймер
	DECLARE_MESSAGE_MAP()
public:
	//переменные исходного сигнала
	double A1;
	double A2;
	double A3;
	double fd;
	double mu1;
	double mu2;
	double mu3;
	int N;
	double sigma1;
	double sigma2;
	double sigma3;
	afx_msg void OnBnClickedPlot();

	//векторы точек
	vector <complex<double>> spectr;
	vector<double> x; //исходный сигнал
	vector<double> spectr_mod; //модуль спектра
	vector<double> dots; //точки сигнала
	vector<double> dots_spectr; //точки спектра
	vector<double> x_trans; //восстановленный сигнал
	vector<double> x_trans_copy; //восстановленный сигнал

	Drawer plX; //рисовалка сигнала
	Drawer plSpectr; //рисовалка спектра 
	HANDLE CalcThread; //хэндл для потока
	BOOL timer = false; //проверка на состояние таймера
	afx_msg void OnBnClickedRecover();

	double eps; //условие остановки
	double t0; //временной сдвиг сигнала
	afx_msg void OnBnClickedButton1();// реверс сигнала
	afx_msg void OnBnClickedButton2(); //сдвиг сигнала
	double otkl;
};
