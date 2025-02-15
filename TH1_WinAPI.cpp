// TH1_WinAPI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TH1_WinAPI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HMENU hMenuPopupSelectColor; // Menu chon mau cho hinh ve tiep theo

struct DrawingState {
	int shape;         // Hình đang chọn
	COLORREF fillColor;  // Màu nền hình
	COLORREF borderColor; // Màu viền hình
};
// Biến toàn cục lưu trạng thái vẽ - Mac dinh la ve hinh chu nhat, mau nen do, mau vien do
DrawingState currentDrawingState = { ID_SELECT_SHAPE_RECTANGLE, RGB(255, 0, 0), RGB(255, 0, 0) };


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
	hMenuPopupSelectColor = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU2)); // Load menu chon mau

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
void xu_li_ve_hinh(HDC hdc, int hinh, int x_down, int y_down, int x_up, int y_up, int mau) {
	// tao but
	HPEN hPen;
	switch (mau)
	{
		case 1: // Do
		{
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			break;
		}
		case 2: // xanh
		{
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
			break;
		}
		default: // den
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
			break;
	}
	// tao choi
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

	switch (mau)
	{
		case 1: // Do
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			break;
		}
		case 2: // xanh
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		}
	default: // den
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		break;
	}
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

	// xoa but
	DeleteObject(hPen);
	// xoa choi
	DeleteObject(hBrush);
}

// CreateGroupBoxShape
void CreateGroupBoxShape(HWND hwnd, HINSTANCE hInstance) {
	HWND hGroupShape = CreateWindowEx(0, L"BUTTON", L"Chọn hình",
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		20, 20, 120, 60, hwnd, NULL, hInstance, NULL);

	// Button vẽ hình chữ nhật
	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		30, 40, 40, 30, hwnd, (HMENU)ID_SELECT_SHAPE_RECTANGLE, hInstance, NULL);

	// Button vẽ hình elip
	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		80, 40, 40, 30, hwnd, (HMENU)ID_SELECT_SHAPE_ELIPSE, hInstance, NULL);
}

void DrawItemShapeButton(LPDRAWITEMSTRUCT pDIS) {
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));  // Viền đen
	HBRUSH hBrush = CreateSolidBrush(RGB(220, 220, 220)); // Màu xám nền

	SelectObject(pDIS->hDC, hPen);
	SelectObject(pDIS->hDC, hBrush);

	// Vẽ nền button
	Rectangle(pDIS->hDC, pDIS->rcItem.left, pDIS->rcItem.top, pDIS->rcItem.right, pDIS->rcItem.bottom);

	// Chọn màu vẽ hình
	SelectObject(pDIS->hDC, GetStockObject(WHITE_BRUSH));

	// Vẽ hình dựa trên ID của button
	if (pDIS->CtlID == ID_SELECT_SHAPE_RECTANGLE) {
		Rectangle(pDIS->hDC, pDIS->rcItem.left + 8, pDIS->rcItem.top + 8,
			pDIS->rcItem.right - 8, pDIS->rcItem.bottom - 8);
	}
	else if (pDIS->CtlID == ID_SELECT_SHAPE_ELIPSE) {
		Ellipse(pDIS->hDC, pDIS->rcItem.left + 8, pDIS->rcItem.top + 8,
			pDIS->rcItem.right - 8, pDIS->rcItem.bottom - 8);
	}

	// Giải phóng tài nguyên
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

// Tạo GroupBox chọn màu nền
void CreateGroupBoxColorBackgroupShapw(HWND hwnd, HINSTANCE hInstance) {
	HWND hGroupColor = CreateWindowEx(0, L"BUTTON", L"Chọn màu nền",
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		150, 20, 260, 60, hwnd, NULL, hInstance, NULL);

	// Tạo các button 
	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		160, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BACKGROUND_RED, hInstance, NULL);

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW ,
		210, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BACKGROUND_GREEN, hInstance, NULL);

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		260, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BACKGROUND_BLUE, hInstance, NULL);

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		310, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BACKGROUND_YELLOW, hInstance, NULL);

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		360, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BACKGROUND_CYAN, hInstance, NULL);
}

// Tạo GroupBox chọn màu viền
void CreateGroupBoxColorBorderShapw(HWND hwnd, HINSTANCE hInstance) {
	HWND hGroupBorder = CreateWindowEx(0, L"BUTTON", L"Chọn màu đường viền",
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		420, 20, 260, 60, hwnd, NULL, hInstance, NULL);  // Điều chỉnh tọa độ X

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		430, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BORDER_RED, hInstance, NULL);

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		480, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BORDER_GREEN, hInstance, NULL);

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		530, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BORDER_BLUE, hInstance, NULL);

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		580, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BORDER_YELLOW, hInstance, NULL);

	CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		630, 40, 40, 30, hwnd, (HMENU)ID_SELECT_COLOR_BORDER_CYAN, hInstance, NULL);
}

// Ve mau nen cho cac button trong group box
void DrawItemColorButton(LPARAM lParam) {
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
	HBRUSH hBrush = NULL;
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Viền đen

	switch (pDIS->CtlID) {  // Kiểm tra ID button
		// Màu nền
	case ID_SELECT_COLOR_BACKGROUND_RED:
		hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Đỏ
		break;
	case ID_SELECT_COLOR_BACKGROUND_GREEN:
		hBrush = CreateSolidBrush(RGB(0, 255, 0)); // Xanh lá
		break;
	case ID_SELECT_COLOR_BACKGROUND_BLUE:
		hBrush = CreateSolidBrush(RGB(0, 0, 255)); // Xanh dương
		break;
	case ID_SELECT_COLOR_BACKGROUND_YELLOW:
		hBrush = CreateSolidBrush(RGB(255, 255, 0)); // Vàng
		break;
	case ID_SELECT_COLOR_BACKGROUND_CYAN:
		hBrush = CreateSolidBrush(RGB(0, 255, 255)); // Cyan
		break;

		// Màu đường viền
	case ID_SELECT_COLOR_BORDER_RED:
		hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Đỏ
		break;
	case ID_SELECT_COLOR_BORDER_GREEN:
		hBrush = CreateSolidBrush(RGB(0, 255, 0)); // Xanh lá
		break;
	case ID_SELECT_COLOR_BORDER_BLUE:
		hBrush = CreateSolidBrush(RGB(0, 0, 255)); // Xanh dương
		break;
	case ID_SELECT_COLOR_BORDER_YELLOW:
		hBrush = CreateSolidBrush(RGB(255, 255, 0)); // Vàng
		break;
	case ID_SELECT_COLOR_BORDER_CYAN:
		hBrush = CreateSolidBrush(RGB(0, 255, 255)); // Cyan
		break;
	default:
		return;
	}

	// Chọn bút và chổi vẽ
	SelectObject(pDIS->hDC, hPen);
	SelectObject(pDIS->hDC, hBrush);

	// Vẽ button
	Rectangle(pDIS->hDC, pDIS->rcItem.left, pDIS->rcItem.top, pDIS->rcItem.right, pDIS->rcItem.bottom);

	// Giải phóng tài nguyên
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

// Xử lý các hành động khi bấm vào group box
void ExecClickInGroupBox(int id, HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (id) {
		// Xử lý chọn hình
	case ID_SELECT_SHAPE_RECTANGLE:
		currentDrawingState.shape = ID_SELECT_SHAPE_RECTANGLE;
		break;
	case ID_SELECT_SHAPE_ELIPSE:
		currentDrawingState.shape = ID_SELECT_SHAPE_ELIPSE;
		break;

		// Xử lý chọn màu nền
	case ID_SELECT_COLOR_BACKGROUND_RED:
		currentDrawingState.fillColor = RGB(255, 0, 0);
		break;
	case ID_SELECT_COLOR_BACKGROUND_GREEN:
		currentDrawingState.fillColor = RGB(0, 255, 0);
		break;
	case ID_SELECT_COLOR_BACKGROUND_BLUE:
		currentDrawingState.fillColor = RGB(0, 0, 255);
		break;
	case ID_SELECT_COLOR_BACKGROUND_YELLOW:
		currentDrawingState.fillColor = RGB(255, 255, 0);
		break;
	case ID_SELECT_COLOR_BACKGROUND_CYAN:
		currentDrawingState.fillColor = RGB(0, 255, 255);
		break;

		// Xử lý chọn màu viền
	case ID_SELECT_COLOR_BORDER_RED:
		currentDrawingState.borderColor = RGB(255, 0, 0);
		break;
	case ID_SELECT_COLOR_BORDER_GREEN:
		currentDrawingState.borderColor = RGB(0, 255, 0);
		break;
	case ID_SELECT_COLOR_BORDER_BLUE:
		currentDrawingState.borderColor = RGB(0, 0, 255);
		break;
	case ID_SELECT_COLOR_BORDER_YELLOW:
		currentDrawingState.borderColor = RGB(255, 255, 0);
		break;
	case ID_SELECT_COLOR_BORDER_CYAN:
		currentDrawingState.borderColor = RGB(0, 255, 255);
		break;

	default:
		DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}

}


// Xu ly ve hinh 
void DrawShape(HDC hdc, int x_down, int y_down, int x_up, int y_up) {
	// Tạo bút vẽ viền
	HPEN hPen = CreatePen(PS_SOLID, 3, currentDrawingState.borderColor);
	SelectObject(hdc, hPen);

	// Tạo chổi tô màu nền
	HBRUSH hBrush = CreateSolidBrush(currentDrawingState.fillColor);
	SelectObject(hdc, hBrush);

	// Xử lý vẽ hình dựa trên lựa chọn của người dùng
	switch (currentDrawingState.shape) {
	case ID_SELECT_SHAPE_RECTANGLE:  // Vẽ hình chữ nhật
		Rectangle(hdc, x_down, y_down, x_up, y_up);
		break;

	case ID_SELECT_SHAPE_ELIPSE:  // Vẽ hình elip
		Ellipse(hdc, x_down, y_down, x_up, y_up);
		break;

	default:
		// Không vẽ nếu không chọn hình
		break;
	}

	// Giải phóng tài nguyên
	DeleteObject(hPen);
	DeleteObject(hBrush);
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
	static int hinh, mau_nen, mau_duong_vien;
	static int mau; // TODO giu lai de code cu khong anh huong

	static int x_down, y_down, x_up, y_up;

	static int m = 0, s = 0;

	static int width_window, height_window;
	switch (message)
	{
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam; // truy cập thông tin

		// kiem tra ton tai khong
		if (pDIS->CtlID == ID_SELECT_SHAPE_RECTANGLE || pDIS->CtlID == ID_SELECT_SHAPE_ELIPSE) {
			DrawItemShapeButton(pDIS);  // Xử lý vẽ hình chữ nhật & elip
		}

		DrawItemColorButton(lParam);
		break;
	}

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
		xu_li_ve_hinh(hdc, hinh, x_down, y_down, x_up, y_up, mau);
	
		DrawShape(hdc, x_down, y_down, x_up, y_up);

		ReleaseDC(hWnd, hdc);

		break;
	}
	// nhan chuot phai xuat hien cua so chon mau
	case WM_RBUTTONDOWN:
	{
		// lay toa do
		POINT p;
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		// Chuyển đổi tọa độ máy khách sang tọa độ màn hình
		ClientToScreen(hWnd, &p);
		// Hiển thị menu
		TrackPopupMenu(
			GetSubMenu(hMenuPopupSelectColor, 0), 
			TPM_RIGHTBUTTON, 
			p.x, p.y, 0, 
			hWnd, NULL
		);

		break;
	}	

	case WM_CREATE:
	{
		// Tao dong ho dem gio
		SetTimer(hWnd, 1, 1000, NULL);

		// Tao group box chon hinh
		CreateGroupBoxShape(hWnd, ((LPCREATESTRUCT)lParam)->hInstance);
		// Tao group box chon mau nen
		CreateGroupBoxColorBackgroupShapw(hWnd, ((LPCREATESTRUCT)lParam)->hInstance);
		// Tao group box chon mau duong vien
		CreateGroupBoxColorBorderShapw(hWnd, ((LPCREATESTRUCT)lParam)->hInstance);

		// Cập nhật giao diện để đảm bảo button hiển thị màu ngay lập tức
		//InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	// Tao dong ho dem gio
	case WM_TIMER:
	{
		if (s == 59) {
			m++;
			s = 0;
		}
		else {
			s++;
		}
		// Hien thi thoi gian
		wchar_t str[100];
		wsprintf(str, L"Time: %d:%d", m, s);

		HDC hdc;
		hdc = GetDC(hWnd);

		TextOut(hdc, width_window - 120, height_window - 20, str, wcslen(str));

		ReleaseDC(hWnd, hdc);

		break;
	}

	// xu li cua so thay doi kich thuoc
	case WM_SIZE:
	{
		width_window = LOWORD(lParam);
		height_window = HIWORD(lParam);

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

		case ID_CHONMAU_D:
		{
			mau = 1;

			break;
		}

		case ID_CHONMAU_XANH:
		{
			mau = 2;

			break;
		}
		default:
			// handle click in group box
			ExecClickInGroupBox(wmId, hWnd, message, wParam, lParam);
			break;
		}

		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
		break;
	}
	
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
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
