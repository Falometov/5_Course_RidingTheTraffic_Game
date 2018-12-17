// Cars.cpp: определяет точку входа для приложения.
//
#include "stdafx.h"
#include "Windows.h"
#include <objidl.h>
#include <gdiplus.h>
#include "windowsx.h"
#include <string>
#include <ctime>
#include "Cars.h"
using namespace Gdiplus;
using namespace std;
#pragma comment (lib, "Gdiplus.lib")
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
RECT rc;
int x = 215, y = 450, fon2X=0,fon2Y=-750 ;
int RandNum;
int idTimer = -1;
double speed=0.3,score=0;

bool Lose=false;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.
	ULONG_PTR token;
	GdiplusStartupInput input = { 0 };
	input.GdiplusVersion = 1;
	GdiplusStartup(&token, &input, NULL);
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CARS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CARS));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CARS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = NULL;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CARS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 540, 750, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

class supercar {
public:
	int x = 0, y = 0;
	bool alive;
};
supercar cars[2];

void CloseCars() {
	for (supercar car : cars)
	{
		car.alive = false;
	}
}

void GenerateCars() {
	if (Lose == false)
	{
		if (cars[0].alive == false && cars[1].alive == false)
		{
			srand(time(0));
			RandNum = rand() % 6 + 1;
			switch (RandNum)
			{

			case 1: {

				cars[0].x = 30;
				cars[1].x = 215;
				cars[0].y = -250;
				cars[1].y = -250;
				cars[0].alive = true;
				cars[1].alive = true;

			}
					break;
			case 2: {
				cars[0].x = 215;
				cars[1].x = 370;
				cars[0].y = -250;
				cars[1].y = -250;
				cars[0].alive = true;
				cars[1].alive = true;
			}
					break;
			case 3: {
				cars[0].x = 30;
				cars[1].x = 370;
				cars[0].y = -250;
				cars[1].y = -250;
				cars[0].alive = true;
				cars[1].alive = true;
			}
					break;
			case 4: {

				cars[0].x = 30;
				cars[0].y = -250;
				cars[0].alive = true;

			}
					break;
			case 5: {

				cars[0].x = 215;
				cars[0].y = -250;
				cars[0].alive = true;

			}

					break;
			case 6: {
				cars[0].x = 370;
				cars[0].y = -250;
				cars[0].alive = true;

			}
					break;
			}


		}
	}
}





void Score(Graphics &g)
{
	if (Lose == false)
	{
		score=score+1*speed;
		int i = int(round(score * 1) / 1);
		string text = to_string(i);
		RectF bounds(0, 0, 950, 50);
		SolidBrush brush(Color(255, 255, 0));
		StringFormat format;
		format.SetAlignment(StringAlignmentCenter);
		format.SetLineAlignment(StringAlignmentCenter);
		Font font(L"Arial", 20, FontStyleBold);
		wstring str(text.begin(), text.end());
		const WCHAR *wchText = str.c_str();
		g.DrawString(wchText, -1, &font, bounds, &format, &brush);
	}
}
/*	картинка  */
void DrawSprite(HDC hdc, RECT& rc)
{
	Graphics graphics(hdc);
	Bitmap BackBuf(rc.right, rc.bottom, &graphics);
	Graphics temp(&BackBuf);
	
	Image player =(L"images\\Player.png");
	Image fon = (L"images\\fon.jpg");
	Image fon2 = (L"images\\fon2.png");
	Image entity = (L"images\\Entity.png");



	temp.DrawImage(&fon, 0, 0,fon.GetWidth(),fon.GetHeight());
	temp.DrawImage(&fon2, fon2X, fon2Y, fon2.GetWidth(), fon2.GetHeight());
	temp.DrawImage(&player, x, y,player.GetWidth(), player.GetHeight());


	for (supercar car :cars)
	{
		if (car.alive==true)
		{
			temp.DrawImage(&entity, car.x, car.y, entity.GetWidth(), entity.GetHeight());
		}
	}

	if (Lose)
	{
		Image esc = (L"images\\esc.png");
		Image boom = (L"images\\boom.png");
		temp.DrawImage(&boom, x-50, y-50, boom.GetWidth(), boom.GetHeight());
		temp.DrawImage(&esc, 0, 150, esc.GetWidth(), esc.GetHeight());
	}
	Score(temp);
	graphics.DrawImage(&BackBuf, 0, 0, 0,0,rc.right,rc.bottom,UnitPixel);
}


void DrawLines()
{
	if (Lose == false)
	{
		if (fon2Y > 0)
		{
			fon2X = 0;
			fon2Y = -750;
		}
		fon2Y = fon2Y + 20*speed;

	}
}

void moveCars() {
	if (Lose == false)
	{
		for (int i = 0; i < 2; i++)
		{
			if (cars[i].alive == true) {
				cars[i].y = cars[i].y + 20*speed;
			}

			if (cars[i].y >= 800)
			{
				cars[i].alive = false;
			}
		}
	}
	
}

void CheckCollision() {

	if (Lose == false)
	{
		for (int i = 0; i < 2; i++)
		{
		
			if (y <= cars[i].y + 232 && y >= cars[i].y && x >= cars[i].x && x <= cars[i].x + 120) //левый угол машины
				Lose = true;
			if (y <= cars[i].y + 232 && y >= cars[i].y && x + 100 >= cars[i].x && x + 100 <= cars[i].x + 120) //правый угол
				Lose = true;
			if (y + 230 <= cars[i].y + 232 && y + 230 >= cars[i].y && x >= cars[i].x && x <= cars[i].x + 120) //левый нижний угол
				Lose = true;
			if (y+230 <= cars[i].y + 232 && y+230 >= cars[i].y && x + 100 >= cars[i].x && x + 100 <= cars[i].x + 120) //правый нижний угол
				Lose = true;
		}
	}
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
		
	
	case WM_CREATE:
	{
		CloseCars();
		SetTimer(hWnd, idTimer = 1, 20, NULL);
	}
	
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rc);
			DrawSprite(hdc, rc);
            EndPaint(hWnd, &ps);
			UpdateWindow(hWnd);
        }
        break;


	case WM_DESTROY: 
		PostQuitMessage(0);
		break;

	
		/*	таймер */
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
		{
			speed += 0.000000001;
			DrawLines();
			moveCars();
			GenerateCars();
			CheckCollision();
			
			InvalidateRect(hWnd, NULL, TRUE);

		}
		break;

		case 2:
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 1, 20, NULL);
			break;

		}
	

		
	}

	/*	клавиши  */
	case WM_KEYDOWN:
	{

		if (Lose == false)
		{
			if (GetAsyncKeyState(VK_LEFT))
				if (x >= 0)
				{
					x = x - 10;
					InvalidateRect(hWnd, NULL, TRUE);
				}
			if (GetAsyncKeyState(VK_RIGHT))
				if (x <= 405)
				{
					x = x + 10;
					InvalidateRect(hWnd, NULL, TRUE);
				}
			if (GetAsyncKeyState(VK_UP))
				if (y >= 0)
				{
					y = y - 10;
					InvalidateRect(hWnd, NULL, TRUE);
				}
			if (GetAsyncKeyState(VK_DOWN))
				if (y <= 450)
				{
					y = y + 10;
					InvalidateRect(hWnd, NULL, TRUE);
				}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			PostQuitMessage(0);
		}
	}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
	

    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
