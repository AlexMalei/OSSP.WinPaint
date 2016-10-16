#include "stdafx.h"
#include "WinPaint.h"
#include "InputManager.h"
#include "AppContext.h"
#include "SceneManager.h"

#define MAX_LOADSTRING 100
#define MAX_FILE_PATH 512

/////////////////////////////////////////////////////

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hwnd;
HMENU menu;
OPENFILENAMEA openFileDlg;
CHOOSECOLORA colorDialog;
COLORREF colorRef[16];
CHAR fileNameBuffer[MAX_FILE_PATH];

/////////////////////////////////////////////////////

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK PenWidthDialog(HWND, UINT, WPARAM, LPARAM);
VOID InitToolsMenuItemsAssocs();
VOID InitFileDialogs();
LPCSTR GetExtension(LPCSTR path);
VOID SaveToFile(LPCSTR path);

/////////////////////////////////////////////////////

std::unique_ptr<paint::AppContext> context;

/////////////////////////////////////////////////////

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINPAINT));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		paint::InputManager::GetInstance()->Update(msg.hwnd);
	}

	return (int)msg.wParam;
}

/////////////////////////////////////////////////////

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINPAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINPAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

/////////////////////////////////////////////////////

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in global variable

	hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hwnd)
	{
		return FALSE;
	}

	context.reset(new paint::AppContext(hwnd));
	InitToolsMenuItemsAssocs();
	InitFileDialogs();

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	return TRUE;
}

/////////////////////////////////////////////////////

VOID InitFileDialogs()
{
	ZeroMemory(&openFileDlg, sizeof(OPENFILENAMEA));
	openFileDlg.lStructSize = sizeof(OPENFILENAMEA);
	openFileDlg.hwndOwner = hwnd;
	openFileDlg.hInstance = hInst;
	openFileDlg.lpstrFilter = "Enhanced metafile (*.emf)\0*.EMF\0Bitmap (*.bmp)\0*.BMP";
	openFileDlg.nFilterIndex = 0;
	openFileDlg.lpstrFile = fileNameBuffer;
	openFileDlg.nMaxFile = MAX_FILE_PATH - 1;
	openFileDlg.lpstrTitle = "Select file to open";

	ZeroMemory(fileNameBuffer, MAX_FILE_PATH);

	ZeroMemory(&colorDialog, sizeof(CHOOSECOLORA));
	colorDialog.lStructSize = sizeof(CHOOSECOLORA);
	colorDialog.hwndOwner = hwnd;
	colorDialog.lpCustColors = colorRef;
	colorDialog.Flags = CC_RGBINIT | CC_SOLIDCOLOR;
}

/////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		auto toolbar = paint::AppContext::GetInstance()->GetToolbar();
		DWORD state;
		COLORREF color;
		
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_EDIT_CLEAR:
			paint::SceneManager::GetInstance()->Clear();
			break;
		case IDM_OPEN:
			if (GetOpenFileNameA(&openFileDlg))
			{
				paint::SceneManager::GetInstance()->LoadFromEnhancedMetafile(openFileDlg.lpstrFile);
			}
			break;
		case IDM_SAVE:
			if (GetSaveFileNameA(&openFileDlg))
			{
				SaveToFile(openFileDlg.lpstrFile);
				
			}
			break;
		case IDM_SAVEAS:
			if (GetSaveFileNameA(&openFileDlg))
			{
				SaveToFile(openFileDlg.lpstrFile);
			}
			break;
		case IDM_UNDO:
			paint::SceneManager::GetInstance()->UndoAction();
			break;
		case IDM_REDO:
			paint::SceneManager::GetInstance()->RedoAction();
			break;
		case ID_TOOLBAR_PEN:
			toolbar->SelectTool(paint::Tool::Pen);
			break;
		case ID_TOOLBAR_LINE:
			toolbar->SelectTool(paint::Tool::Line);
			break;
		case ID_TOOLBAR_ELLIPSE:
			toolbar->SelectTool(paint::Tool::Ellipse);
			break;
		case ID_TOOLBAR_RECTANGLE:
			toolbar->SelectTool(paint::Tool::Rectangle);
			break;
		case ID_TOOLBAR_TEXT:
			toolbar->SelectTool(paint::Tool::Text);
			break;
		case ID_STYLE_PENCOLOR:
			if (ChooseColorA(&colorDialog))
			{
				context->GetToolbar()->SetPenColor(colorDialog.rgbResult);
			}
			break;
		case ID_STYLE_BRUSHCOLOR:
			if (ChooseColorA(&colorDialog))
			{
				context->GetToolbar()->SetBrushColor(colorDialog.rgbResult);
			}
			break;
		case ID_STYLE_USEBRUSH:
			// Make menu check box
			state = GetMenuState(menu, ID_STYLE_USEBRUSH, MF_CHECKED);
			state = (state == MF_CHECKED) ? MF_UNCHECKED : MF_CHECKED;
			CheckMenuItem(menu, ID_STYLE_USEBRUSH, state);

			color = context->GetToolbar()->GetBrushColor();
			color = color & 0x00FFFFFF; // Mask opacity byte
			color |= ((state == MF_UNCHECKED) ? (0xFF << 24) : 0);
			context->GetToolbar()->SetBrushColor(color);
			break;
		case ID_STYLE_PENWIDTH:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_PEN_VIEW), hWnd, PenWidthDialog);
			break;
		case ID_TOOLBAR_POLYLINE:
			toolbar->SelectTool(paint::Tool::Polyline);
			break;
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
	case WM_CHAR:
		paint::InputManager::GetInstance()->OnCharKeyPress(static_cast<char>(wParam));
		break;
	case WM_PAINT:
		context->OnRender();
		break;
	case WM_ERASEBKGND:
		break;
	case WM_SIZE:
		context->OnResize(paint::Point(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////

INT_PTR CALLBACK PenWidthDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	DWORD sliderPos;
	const DWORD maxThickness = 100;
	std::string tempStr;

	switch (message)
	{
	case WM_INITDIALOG:
		sliderPos = context->GetToolbar()->GetLineThickness();
		tempStr = std::to_string(sliderPos);
		sliderPos = (static_cast<float>(sliderPos) / maxThickness) * 100;
		SendMessage(GetDlgItem(hDlg, IDC_SLIDER), TBM_SETPOS, TRUE, sliderPos);
		
		SetDlgItemTextA(hDlg, IDC_SLIDER_DESC, tempStr.c_str());
		return (INT_PTR)TRUE;

	case WM_HSCROLL:
		sliderPos = SendMessage(GetDlgItem(hDlg, IDC_SLIDER), TBM_GETPOS, 0, 0);
		sliderPos = static_cast<DWORD>((sliderPos / 100.f) * maxThickness);
		tempStr = std::to_string(sliderPos);
		context->GetToolbar()->SetLineThickness(sliderPos);

		SetDlgItemTextA(hDlg, IDC_SLIDER_DESC, tempStr.c_str());
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}

	return (INT_PTR)FALSE;
}

/////////////////////////////////////////////////////

VOID InitToolsMenuItemsAssocs()
{
	menu = GetMenu(hwnd);

	std::unordered_map<DWORD, paint::Tool> assocs;
	assocs.insert(std::pair<DWORD, paint::Tool>(ID_TOOLBAR_PEN, paint::Tool::Pen));
	assocs.insert(std::pair<DWORD, paint::Tool>(ID_TOOLBAR_LINE, paint::Tool::Line));
	assocs.insert(std::pair<DWORD, paint::Tool>(ID_TOOLBAR_RECTANGLE, paint::Tool::Rectangle));
	assocs.insert(std::pair<DWORD, paint::Tool>(ID_TOOLBAR_ELLIPSE, paint::Tool::Ellipse));
	assocs.insert(std::pair<DWORD, paint::Tool>(ID_TOOLBAR_POLYLINE, paint::Tool::Polyline));
	assocs.insert(std::pair<DWORD, paint::Tool>(ID_TOOLBAR_TEXT, paint::Tool::Text));

	auto toolbar = context->GetToolbar();
	toolbar->LoadMenuItemLinks(assocs);
	toolbar->SelectTool(paint::Tool::Pen);
}

/////////////////////////////////////////////////////

LPCSTR GetExtension(LPCSTR path)
{
	LPCSTR ext = strrchr(path, '.');
	if (ext)
	{
		ext++;
	}

	return ext;
}

/////////////////////////////////////////////////////

VOID SaveToFile(LPCSTR path)
{
	LPCSTR ext = GetExtension(path);
	if (ext)
	{
		if (strcmp(ext, "emf") == 0)
		{
			paint::SceneManager::GetInstance()->SaveToEnhancedMetafile(path);
		}
		else if (strcmp(ext, "bmp") == 0)
		{

		}
	}
}

/////////////////////////////////////////////////////
