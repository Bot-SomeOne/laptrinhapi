// KTR_DAY_19_02_25.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "KTR_DAY_19_02_25.h"
#include <math.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
// My Variables for the program
POINT pt;
struct HINH
{
    int typeShape;
	COLORREF fillColor;
	COLORREF borderColor;
	int borderSize;
	int hatchStyle; // HS_HORIZONTAL, HS_DIAGCROSS
};
// Mac Dinh mau vien la do, do day duong vien la 3
HINH trangThaiHinh = { ID_HINH_LUCGIACDEU, RGB(255, 255, 255), RGB(255, 0, 0), 3, HS_HORIZONTAL};
void VeHinh(HDC hdc, int x1, int y1, int x2, int y2);
void VeLucGiac(HDC hdc, int cx, int cy, int radius);
int minutes = 60; 
int seconds = 0;
int sizeWindowWeight;
int sizeWindowHeight;

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
    LoadStringW(hInstance, IDC_KTRDAY190225, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KTRDAY190225));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KTRDAY190225));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KTRDAY190225);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    switch (message)
    {
    // Xu li lay kich thuoc khi kich thuoc thay doi
    case WM_SIZE: {
		sizeWindowWeight = LOWORD(lParam);
		sizeWindowHeight = HIWORD(lParam);
        break;
    }
    // Tao Dong Ho
    case WM_CREATE:
    {
        // Tao dong ho dem gio
        SetTimer(hWnd, 1, 1000, NULL);

        break;
    }
    // Xu li thoi gian dem nguoc 
    case WM_TIMER: {
        if (minutes == 0 && seconds == 0) {
            KillTimer(hWnd, 1);
            MessageBox(hWnd, L"Hết giờ!", L"Thông báo", MB_OK | MB_ICONINFORMATION);
        }
        else {
            if (seconds == 0) {
                minutes--;
                seconds = 59;
            }
            else {
                seconds--;
            }
			// Hien thi thoi gian voi mau do
			WCHAR str[100];
			wsprintf(str, L"%d:%d", minutes, seconds);
            HDC hdc;
			hdc = GetDC(hWnd);
			SetTextColor(hdc, RGB(255, 0, 0));
			TextOut(hdc, sizeWindowWeight - 50, sizeWindowHeight - 50, str, wcslen(str));
			
            ReleaseDC(hWnd, hdc);  
        }
        break;
    }

    // Lay Toa Do Khi Nhan Chuot Trai  
    case WM_LBUTTONDOWN:{
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        break;
    }
	// Xu li khi tha chuot trai - ve hinh
    case WM_LBUTTONUP: {
        POINT ptDown = { LOWORD(lParam), HIWORD(lParam) };
		HDC hdc = GetDC(hWnd);
		VeHinh(hdc, pt.x, pt.y, ptDown.x, ptDown.y);
		ReleaseDC(hWnd, hdc);
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			// Xu li click thoat
            case ID_HINH_THOAT:
            {
                if (MessageBox(hWnd, L"Ban co muon thoat khong?", L"Thong Bao", MB_YESNO | MB_ICONQUESTION) == IDYES)
                {
                    DestroyWindow(hWnd);
                }
                break;
            }
            // Xu li click cho hinh luc giac
            case ID_HINH_LUCGIACDEU: {
                trangThaiHinh.typeShape = ID_HINH_LUCGIACDEU;
                break;
            }
			// Xu li click cho hinh ellipse
            case ID_HINH_ELLIPSE: {
				trangThaiHinh.typeShape = ID_HINH_ELLIPSE;
				break;
			}
            // Xu li click chon mau nen: Xanh la cay
            case ID_MAUNEN_XANHLACAY: {
				trangThaiHinh.fillColor = RGB(0, 128, 0);
				break;
            }
			// Xu li click chon mau nen: Vang
            case ID_MAUNEN_VANG: {
                trangThaiHinh.fillColor = RGB(255, 255, 0);
                break;
            }
		    // Xu li chon kieu nen: Gach ngang
            case ID_KIEUNEN_GACHNGANG: {
				trangThaiHinh.hatchStyle = HS_HORIZONTAL;
                break;
            }
			// Xu li chon kieu nen: Den hinh tram
            case ID_KIEUNEN_DENHINHTRAM: {
				trangThaiHinh.hatchStyle = HS_DIAGCROSS;
				break;
            }
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

// Xu li ve hinh
void VeHinh(HDC hdc, int x1, int y1, int x2, int y2) {
    // Tao but ve
	HPEN hPen = CreatePen(PS_SOLID, trangThaiHinh.borderSize, trangThaiHinh.borderColor);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hBrush = CreateHatchBrush(trangThaiHinh.hatchStyle, trangThaiHinh.fillColor);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    
    switch (trangThaiHinh.typeShape) {
        case ID_HINH_LUCGIACDEU: {
            int radius = min(abs(x2 - x1), abs(y2 - y1)) / 2;
            int cx = (x1 + x2) / 2;
            int cy = (y1 + y2) / 2;
            VeLucGiac(hdc, cx, cy, radius);
            break;
        }
        case ID_HINH_ELLIPSE: {
            Ellipse(hdc, x1, y1, x2, y2);
            break;
        }
        default: {
            break;
        }   
    }
}

void VeLucGiac(HDC hdc, int cx, int cy, int radius) {
    POINT hexagon[6];
    for (int i = 0; i < 6; i++) {
        double angle = 3.14 / 3 * i;
        hexagon[i].x = cx + radius * cos(angle);
        hexagon[i].y = cy + radius * sin(angle);
    }
    Polygon(hdc, hexagon, 6);
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
