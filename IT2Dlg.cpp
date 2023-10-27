
// IT2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IT2.h"
#include "IT2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define M_PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214
#define INTERVAL 20



// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CIT2Dlg



CIT2Dlg::CIT2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IT2_DIALOG, pParent)
	, A1(4)
	, A2(2)
	, A3(5)
	, fd(1)
	, mu1(110)
	, mu2(220)
	, mu3(410)
	, N(512)
	, sigma1(3)
	, sigma2(2)
	, sigma3(3)
	, eps(1e-6)
	, t0(0)
	, otkl(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIT2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_A1, A1);
	DDX_Text(pDX, IDC_A2, A2);
	DDX_Text(pDX, IDC_A3, A3);
	DDX_Text(pDX, IDC_fd, fd);
	DDX_Text(pDX, IDC_mu1, mu1);
	DDX_Text(pDX, IDC_mu2, mu2);
	DDX_Text(pDX, IDC_mu3, mu3);
	DDX_Text(pDX, IDC_N, N);
	DDX_Text(pDX, IDC_sigma1, sigma1);
	DDX_Text(pDX, IDC_sigma2, sigma2);
	DDX_Text(pDX, IDC_sigma3, sigma3);
	DDX_Text(pDX, IDC_eps, eps);
	DDX_Text(pDX, IDC_t0, t0);
	DDX_Text(pDX, IDC_otkl, otkl);
}

BEGIN_MESSAGE_MAP(CIT2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER() //для работы с таймером
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDPlot, &CIT2Dlg::OnBnClickedPlot)
	ON_BN_CLICKED(IDRecover, &CIT2Dlg::OnBnClickedRecover)
	ON_BN_CLICKED(IDC_BUTTON1, &CIT2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CIT2Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Обработчики сообщений CIT2Dlg

BOOL CIT2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	plX.Create(GetDlgItem(IDC_PLOT1)->GetSafeHwnd());
	plSpectr.Create(GetDlgItem(IDC_PLOT2)->GetSafeHwnd());
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CIT2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CIT2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		if (x.size() > 0) {
			plX.DrawGrid(x, 1, dots, N);
			plX.DrawPlot(x, 1, dots, N);
		}
		if (spectr_mod.size() > 0) {
			plSpectr.DrawGrid(spectr_mod, 2, dots_spectr, N);
			plSpectr.DrawPlot(spectr_mod, 1, dots_spectr, N);
		}
		if (x_trans_copy.size() > 0) {
			plX.DrawPlot(x_trans_copy, 2, dots, N);
		}
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CIT2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//глобальные переменные для работы с потоком
bool wait(false);
vector<double>xx;
double eps_glob(0);

//Функция купола
double Gauss(double A, double mu, double sigma, double i, double fd) {
	return A * exp(-pow((i / fd - mu) / sigma, 2));
}
//БПФ
typedef complex<double> comp_double;

vector<comp_double> fft(vector<comp_double>& b, bool invert=false) {
	vector<comp_double> a = b;
	int n = (int)a.size();

	for (int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * M_PI / len * (invert ? -1 : 1);
		comp_double wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			comp_double w(1);
			for (int j = 0; j < len / 2; ++j) {
				comp_double u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i = 0; i < n; ++i)
			a[i] /= n;
	return a;
}
//быстрое фурье для реального сигнала
 vector<comp_double> fft(const vector<double>& In, bool invert=false) {
	 vector<comp_double> y;
	 for (int i = 0; i < In.size(); i++) {
		 comp_double z(In[i], 0);
		 y.push_back(z);
	 }
	 return fft(y, invert);

 }

 //получить модуль спектра
 vector<double> spectr_module(vector<comp_double> in) {
	 vector<double> out;
	 for (int i = 0; i < in.size(); i++) {
		 out.push_back(abs(in[i]));
	 }
	 return out;
 }
 
 //получить х(i), учитывая условия задачи (действительность и неотрицательность сигнала)
 vector<double> apply_conditions(vector<comp_double> in) {
	 vector<double> out;
	 for (int i = 0; i < in.size(); i++) {
		 double real = in[i].real();
		 if (real < 0) real = 0;
		 out.push_back(real);
	 }
	 return out;
 }

 //получить фазы
 vector<double> get_fi(vector<comp_double> in) {
	 vector<double> fi;
	 for (int i = 0; i < in.size(); i++) {
		 fi.push_back(arg(in[i]));
	 }
	 return fi;
 }
 
 //замена модуля спектра на истинный
 vector<comp_double> change_module_spectr(vector<double> X, vector<double> fi) {
	 vector<comp_double> x;
	 for (int i = 0; i < X.size(); i++) {
		 comp_double z(X[i] * cos(fi[i]), X[i] * sin(fi[i]));
		 x.push_back(z);
	 }
	 return x;
 }

 //структура для передачи в поток
 struct Conditions {
	 Conditions(vector<double>XX, double e) {
		 X = XX; //модуль спектра
		 eps = e; //условие остановки
	 }
	 vector<double> X;
	 double eps;
 };


void CIT2Dlg::OnBnClickedPlot()
{
	//очистка векторов
	srand(time(NULL));
	x.clear();
	spectr.clear();
	spectr_mod.clear();
	dots.clear();
	dots_spectr.clear();
	UpdateData();
	//формируем сигнал
	for (int i = 0; i < N; i++) {
		x.push_back(Gauss(A1, mu1, sigma1, i, fd) + Gauss(A2, mu2, sigma2, i, fd) + Gauss(A3, mu3, sigma3, i, fd));
		dots.push_back(i);
		dots_spectr.push_back((double)i * fd / N);
	}
	//посчитаем спектр
	spectr = fft(x);
	//посчитаем модуль спектра
	spectr_mod = spectr_module(spectr);
	//отрисуем
	RedrawWindow();
}
//вычисление энергии сигнала 
double Energy(vector<double>x) {
	double energy(0);
	for (int i = 0; i < x.size(); i++) {
		energy += x[i] * x[i];
	}
	return energy;
}

DWORD WINAPI Fienup(LPVOID param) {
	xx.clear(); //очищаем глобальный вектор восстановленного х
	Conditions* cond = (Conditions*)param; //считываем условия
	vector<double>spectr_mod(cond->X),fi, real_x_fien; //сохраняем в переменные: модуль спектра, фазы, сигнал с реальной неотрицательной частью
	vector<comp_double>comp_x_fien,spectr; //переменные для работы: комплексный сигнал, комплексный спектр
	double energy_now(Energy(spectr_mod)),energy_before(0); //переменные для хранения значений энергий на текущем и предыдущем шагах
	//заполним фазы случайными значениями
	for (int i = 0; i < spectr_mod.size(); i++) {
		fi.push_back(-M_PI + 2. * M_PI * (double)rand() / (double)RAND_MAX);
	}
	comp_x_fien = fft(change_module_spectr(spectr_mod, fi), true); //получаем сигнал из исходного модуля спектра и случайной фазы
	real_x_fien = apply_conditions(comp_x_fien); //применяем условия к сигналу
	while(abs(energy_now - energy_before) > cond->eps) {//пока разность энергий больше порога, выполняем
		energy_before = energy_now; //сохраняем энергию на предыдущем шаге
		spectr = fft(real_x_fien); //получаем комплексный спектр из сигнала с реальной частью
		energy_now = Energy(spectr_module(spectr)); //вычисляем значение энергии спектра в текущий момент
		fi = get_fi(spectr); //получаем фазы текущего комплексного спектра 
		comp_x_fien = change_module_spectr(spectr_mod, fi); //заменяем модуль спектра на исходный
		comp_x_fien = fft(comp_x_fien, true); //выполняем обратное преобразование фурье
		real_x_fien = apply_conditions(comp_x_fien); //применяем начальные условия
		if (wait)Sleep(5); //если включился таймер, то подождать
		xx = real_x_fien; //сохраняем восстановленный сигнал
		if (wait)Sleep(5);
		eps_glob = abs(energy_now - energy_before); //сохраняем текущую разность энергий
	} 
	return 0;
}

//кнопка восстановления сигнала
void CIT2Dlg::OnBnClickedRecover()
{
	UpdateData();
	if (!timer) {//запуск таймера
		Conditions* cond = new Conditions(spectr_mod, eps); //передача условий: модуль спектра и условие остановки
		CalcThread = CreateThread(NULL, NULL, Fienup, (void*)cond, NULL, NULL); //запуск потока вычислений
		timer = true;
		SetTimer(ID_TIMER, INTERVAL, NULL);
	}
	else { //вызывается самим таймером после вычислений
		if (WaitForSingleObject(CalcThread, 1) != WAIT_TIMEOUT) {
			timer = false;
			CloseHandle(CalcThread);
		}
	}
}

double Otkl(vector<double> vec1, vector<double>vec2){
	double sum(0);
	for (int i = 0; i < vec1.size(); i++){
		sum += pow((vec1[i] - vec2[i]), 2);
	}
	return sum;
}

void CIT2Dlg::OnTimer(UINT_PTR) {
	wait = true;
	x_trans = xx;
	if(eps == eps_glob) {
		OnBnClickedRecover();
		KillTimer(ID_TIMER);
	}
	eps = eps_glob;
	wait = false;
	x_trans_copy = x_trans;
	otkl = Otkl(x_trans_copy, x);
	UpdateData(FALSE);

	plX.DrawGrid(x, 1, dots, N);
	plX.DrawPlot(x, 1, dots, N);
	plX.DrawPlot(x_trans_copy, 2, dots, N);
	
}
//реверс сигнала
void CIT2Dlg::OnBnClickedButton1()
{
	for (int i = 0; i < N / 2; i++) {
		double temp = x_trans[i];
		x_trans[i] = x_trans[N - i - 1];
		x_trans[N - i - 1] = temp;
	}
	x_trans_copy = x_trans;
	otkl = Otkl(x_trans_copy, x);
	UpdateData(FALSE);
	RedrawWindow();
}

//сдвиг сигнала
void CIT2Dlg::OnBnClickedButton2()
{
	UpdateData();

	if (t0 > 0) {
		for (int i = 0; i < t0 / fd; i++) {
			x_trans_copy[i] = x_trans[N - t0 / fd + i];
		}
		for (int i = t0 / fd; i < N; i++) {
			x_trans_copy[i] = x_trans[i - t0 / fd];
		}
	}
	else {
		for (int i = 0; i < N + t0 / fd; i++) {
			x_trans_copy[i] = x_trans[i - t0 / fd];
		}
		for (int i = N + t0 / fd; i < N; i++) {
			x_trans_copy[i] = x_trans[i - N - t0 / fd];
		}
	}
	otkl = Otkl(x_trans_copy, x);
	UpdateData(FALSE);
	plX.DrawGrid(x, 1, dots, N);
	plX.DrawPlot(x, 1, dots, N);
	plX.DrawPlot(x_trans_copy, 2, dots, N);

}
