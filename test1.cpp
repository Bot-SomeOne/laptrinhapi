﻿// test1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "test1.h"

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
    LoadStringW(hInstance, IDC_TEST1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST1));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST1);
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

// Xu dung HPEN
void Day_12_02_25(HDC hdc, int width, int height) {
    // Ve 2 duong cheo, 1 pixel, mau green
    HPEN hPenGreen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));

    // Hinh chu nhat lay but BLACK_PEN
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    //HPEN hPenBlack = GetStockObject(BLACK_PEN);

    // Hinh elip net lien 3 pixel, mau RGB(255, 255, 0)
    HPEN hPenYellow = CreatePen(PS_DOT, 3, RGB(255, 255, 0));


    // Tính toán vị trí trung tâm
    int centerX = width / 2;
    int centerY = height / 2;

    SelectObject(hdc, hPenBlack);
    Rectangle(hdc, width / 8, height / 8, 7 * width / 8, 7 * height / 8);

    SelectObject(hdc, hPenGreen);
    // Vẽ 2 đoạn thẳng cắt chéo qua trung tâm
    MoveToEx(hdc, 0, 0, NULL); // Góc trên trái
    LineTo(hdc, width, height); // Góc dưới phải

    MoveToEx(hdc, 0, height, NULL); // Góc dưới trái
    LineTo(hdc, width, 0); // Góc trên phải

    SelectObject(hdc, hPenYellow);
    Ellipse(hdc, width / 8, height / 8, 7 * width / 8, 7 * height / 8);
    RoundRect(hdc, width / 4, height / 4, 3 * width / 4, 3 * height / 4, 20, 10);

	// destroy pen - thuong xu dung trong WM_DESTROY
    DeleteObject(hPenGreen);
    DeleteObject(hPenBlack);
    DeleteObject(hPenYellow);
}

// Xu dung HPEN va HBRUSH
void Day_12_02_25_Ex2(HDC hdc, int width, int height) {
    HPEN hPenGreen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    //HPEN hPenBlack = GetStockObject(BLACK_PEN);
    HPEN hPenYellow = CreatePen(PS_DOT, 3, RGB(255, 255, 0));

	HBRUSH hBrushViolet = CreateHatchBrush(HS_DIAGCROSS, RGB(238, 130, 238));
	HBRUSH bBrushLightBlue = CreateSolidBrush(RGB(0, 255, 255));

    // Tính toán vị trí trung tâm
    int centerX = width / 2;
    int centerY = height / 2;

    SelectObject(hdc, hPenBlack);
	SelectObject(hdc, hBrushViolet);
    Rectangle(hdc, width / 8, height / 8, 7 * width / 8, 7 * height / 8);

    SelectObject(hdc, hPenGreen);
    // Vẽ 2 đoạn thẳng cắt chéo qua trung tâm
    MoveToEx(hdc, 0, 0, NULL); // Góc trên trái
    LineTo(hdc, width, height); // Góc dưới phải

    MoveToEx(hdc, 0, height, NULL); // Góc dưới trái
    LineTo(hdc, width, 0); // Góc trên phải

    SelectObject(hdc, hPenYellow);
	SelectObject(hdc, bBrushLightBlue);
    Ellipse(hdc, width / 8, height / 8, 7 * width / 8, 7 * height / 8);
    RoundRect(hdc, width / 4, height / 4, 3 * width / 4, 3 * height / 4, 20, 10);

    // destroy pen - thuong xu dung trong WM_DESTROY
    DeleteObject(hPenGreen);
    DeleteObject(hPenBlack);
    DeleteObject(hPenYellow);

	DeleteObject(hBrushViolet);
	DeleteObject(bBrushLightBlue);
}

// Xu dung fMouse - Thay the file proc bang file nay, thay mot vai bien thanh static
void Day_12_02_25_Ex3(HWND hWnd,HDC hdc, UINT message) {

    //static HDC hdc;
    POINT pt[10000]; // static
    int count = 0; // static

    switch (message)
    {
    
    case WM_LBUTTONDBLCLK:
    {
		InvalidateRect(hWnd, NULL, TRUE);
        count = 0;
        // luu cac diem anh
        break;
    }
    case WM_LBUTTONDOWN:
    {
        
        // luu cac diem anh
		pt[count].x = LOWORD(GetMessagePos());
		pt[count].y = HIWORD(GetMessagePos());

		// ve 1 diem anhtai vi tri nhap chuot
		SetPixel(hdc, pt[count].x, pt[count].y, RGB(255, 0, 0));
        ReleaseDC(hWnd, hdc);
		count++;

        break;
    }

	case WM_RBUTTONDOWN:
	{
		// ve cac
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                MoveToEx(hdc, pt[i].x, pt[i].y, NULL);
                LineTo(hdc, pt[j].x, pt[j].y);
            }
        }
		ReleaseDC(hWnd, hdc);
		break;
	}
    default:
        break;
    }
}

// Xu ly Timer
void Day_12_02_25_Ex4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    HDC hdc;
	int minutes = 50, seconds = 0;
	TCHAR timeLeft[30];

    switch (message)
    {
	case WM_CREATE:
	{
		// Khoi tao timer
		SetTimer(hWnd, 1, 1000, NULL);
		break;
	}
    case WM_TIMER:
    {
        if (seconds > 0 && seconds <= 50) {
            seconds = seconds - 1;
        }
		else if (seconds == 0 && minutes > 0) {
            minutes = minutes - 1;
            seconds = 59;
		}
		else if (minutes == 0 && seconds == 0) {
			KillTimer(hWnd, 1);
		}
		wsprintf(timeLeft, L"%d:%d", minutes, seconds); // tao chuoi thoi gian co dang timeLeft - Eg: 5:20

		hdc = GetDC(hWnd);
		//TextOut(hdc, 0, 0, timeLeft, wsprintf(timeLeft, L"%d:%d", minutes, seconds));
		TextOut(hdc, 0, 0, timeLeft, 20); // Ve noi dung bien time left ra cua so tai vi tri (0, 0)

		ReleaseDC(hWnd, hdc);

		break;
    }
    default:
        break;
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
    static HMENU hMenuE, hMenuV;
    static HMENU hCurrentMenu, hPopupMenu;

    static POINT pt;

	static HDC hdc; // handle device context
	static int width, height;
    switch (message)
    {
    case WM_SIZE: // Khi cửa sổ thay đổi kích thước
    {
        // Lấy kích thước cửa sổ
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        hdc = GetDC(hWnd);
        // TODO
    }
		break;

    case WM_LBUTTONDOWN: // Khi nhấn chuột trái
    {
        hdc = GetDC(hWnd);
        // TODO
        SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), RGB(255, 0, 0));
        ReleaseDC(hWnd, hdc); //
        break;
    }

    case WM_RBUTTONDOWN: { // Khi nhấn chuột phải
        // Lấy vị trí chuột
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        ClientToScreen(hWnd, &pt);

        // Hiển thị menu ngữ cảnh
        if (hCurrentMenu == hMenuE) {
            hPopupMenu = GetSubMenu(hMenuE, 1); // Menu tiếng Anh
        }
        else if (hCurrentMenu == hMenuV) {
            hPopupMenu = GetSubMenu(hMenuV, 1); // Menu tiếng Việt
        }

        if (hPopupMenu) {
            TrackPopupMenu(hPopupMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
        }
        break;
    }

	case WM_PAINT: // Khi cần vẽ lại cửa sổ
    {
        /*PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        Day_12_02_25_Ex2(hdc, width, height);

        EndPaint(hWnd, &ps);*/
    }
        break;
    case WM_CREATE: // Khi cửa sổ được tạo
    {
        // Load menu từ resource
        hMenuE = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_TEST1));
        hMenuV = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
        if (hMenuE) {
            hCurrentMenu = hMenuE;
            SetMenu(hWnd, hMenuE); // Gắn menu vào cửa sổ
        }
        else {
            MessageBox(hWnd, L"Không thể load menu.", L"Lỗi", MB_ICONERROR);
        }
    }
        break;

	case WM_COMMAND: // Khi có lệnh từ menu
        {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            /*DestroyWindow(hWnd);*/
            if (MessageBox(hWnd, L"Bạn có chắc chắn muốn thoát?", L"Xác nhận", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                DestroyWindow(hWnd);
            }
            break;
        case ID_LANGUAGES_ENGLISH:
            hCurrentMenu = hMenuE;
            SetMenu(hWnd, hCurrentMenu);
            DrawMenuBar(hWnd); // Vẽ lại menu
            break;
        case ID_LANGUAGES_VIETNAMESE:
            hCurrentMenu = hMenuV;
            SetMenu(hWnd, hCurrentMenu);
            DrawMenuBar(hWnd); // Vẽ lại menu
            break;
        case ID_NGONNGU_TIENGANH:
            hCurrentMenu = hMenuE;
            SetMenu(hWnd, hCurrentMenu);
            DrawMenuBar(hWnd); // Vẽ lại menu
            break;
        case ID_NGONNGU_TIENGVIET:
            hCurrentMenu = hMenuV;
            SetMenu(hWnd, hCurrentMenu);
            DrawMenuBar(hWnd); // Vẽ lại menu
            break;
        case ID_THUMUC_DONG:
            MessageBox(hWnd, L"Dong Thu Muc", L"Xac Nhan", MB_YESNO);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        }
        break;
    case WM_DESTROY: // Khi cửa sổ bị hủy
    {
        PostQuitMessage(0);
    }
        break; 
    case WM_CLOSE: // Khi cửa sổ được đóng
    {
        if (MessageBox(hWnd, L"Bạn có chắc chắn muốn thoát?", L"Xác nhận", MB_YESNO | MB_ICONQUESTION) == IDYES) {
            PostQuitMessage(0);
        }
    }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    
	//Day_12_02_25_Ex3(hWnd, hdc, message);

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
