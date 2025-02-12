// TH1_WinAPI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TH1_WinAPI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TH1WINAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TH1WINAPI));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TH1WINAPI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1); // Sua doi menu xu dung khi khoi tao
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

// xu li ve hinh
void xu_li_ve_hinh(HDC hdc, int hinh, int x_down, int y_down, int x_up, int y_up) {
	// tao but
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	// tao choi
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	// chon but
	SelectObject(hdc, hPen);
	// chon choi
	SelectObject(hdc, hBrush);

	// ve hinh
	switch (hinh)
	{
		case ID_HINH_DUONGTHANG:
		{
			MoveToEx(hdc, x_down, y_down, NULL); // diem bat dau
			LineTo(hdc, x_up, y_up); // diem ket thuc
			break;
		}

		case ID_HINH_TAMGIACVUONG:
		{
			POINT p[3];

			p[0].x = x_down;
			p[0].y = y_down;

			p[1].x = x_down;
			p[1].y = y_up;

			p[2].x = x_up;
			p[2].y = y_up;

			Polygon(hdc, p, 3);
			break;
		}
		default:
		{
			break;
		}
	}
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// bien xu dung ve
	static int hinh;

	static int x_down, y_down, x_up, y_up;
	switch (message)
	{
		// nhan chuot trai la bat dau ve
	case WM_LBUTTONDOWN:
	{
		// lay toa do chuot nhan
		x_down = LOWORD(lParam);
		y_down = HIWORD(lParam);

		break;
	}
	// nha chuot trai la ket thuc ve
	case WM_LBUTTONUP:
	{
		// lay toa do chuot nha
		x_up = LOWORD(lParam);
		y_up = HIWORD(lParam);
		// ve hinh
		HDC hdc = GetDC(hWnd);
		xu_li_ve_hinh(hdc, hinh, x_down, y_down, x_up, y_up);
		ReleaseDC(hWnd, hdc);

		break;
	}

	case WM_CLOSE:
	{
		if (MessageBox(hWnd, L"Bạn có chắc chắn muốn thoát?", L"Xác nhận", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			PostQuitMessage(0);
		}

		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_HINH_TAMGIACVUONG:
		{
			hinh = (hinh == ID_HINH_TAMGIACVUONG ? -1 : ID_HINH_TAMGIACVUONG);

			break;
		}

		case ID_HINH_DUONGTHANG:
		{
			hinh = (hinh == ID_HINH_DUONGTHANG ? -1 : ID_HINH_DUONGTHANG);

			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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
