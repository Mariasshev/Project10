
#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <commctrl.h>
#include "Resource.h"

#pragma comment(lib,"comctl32")

#define BUTTON_COUNT 16
#define TIMER_ID 1

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace std;

HWND hSpin, hEdit1, hEdit2;
vector<HWND> buttonHandles;
vector<int>answers;

void UpdateCounter(HWND hwnd, int count) {
	TCHAR buffer[100];
	_stprintf_s(buffer, _T("%d"), count);
	SetWindowText(hEdit2, buffer);
}

void CALLBACK OnTimer(HWND hwnd, UINT message, UINT_PTR idTimer, DWORD dwTime) {
	TCHAR buffer[100];
	GetDlgItemText(hwnd, IDC_EDIT2, buffer, sizeof(buffer) / sizeof(buffer[0]));
	int count = stoi(buffer);

	if (count > 0) {
		count--;
		UpdateCounter(hwnd, count);
	}
	else {
		KillTimer(hwnd, TIMER_ID);
		MessageBox(hwnd, _T("Время закончилось!"), _T("Таймер"), MB_OK | MB_ICONINFORMATION);
	}
}

void addNumbers(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	vector<int> numbers;

	int num;
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		num = rand() % 100 + 1;
		for (int j = 0; j < numbers.size(); j++)
		{
			if (numbers.size() == NULL)
			{
				break;
			}
			else {
				if (num == numbers[j])
				{
					--i;
					break;
				}
			}
		}
		numbers.push_back(num);

	}

	

	//fill buttons with numbers
	TCHAR buffer[100];
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		wsprintf(buffer, TEXT("%d"), numbers[i]);
		SetDlgItemText(hwnd, IDC_BUTTON1 + i, buffer);

	}
}

void initDlg(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	hSpin = GetDlgItem(hwnd, IDC_SPIN1);
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);


	if (hEdit2 != NULL) {
		int textLength = GetWindowTextLength(hEdit2);

		if (textLength > 0) {
			// Элемент управления содержит текст
			addNumbers(hwnd, wParam, lParam);
		}
		else {
			// Элемент управления пуст
			SetWindowText(hEdit2, TEXT("10"));
			addNumbers(hwnd, wParam, lParam);
		}
	}


	for (int i = 0; i < BUTTON_COUNT; i++) 
	{
		buttonHandles.push_back(GetDlgItem(hwnd, IDC_BUTTON1+i));
	}

	SetTimer(hwnd, TIMER_ID, 1000, OnTimer);







}


INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR buf[100];
	TCHAR str[256];

	switch (uMsg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwnd, 0);
			return TRUE;
		}

		else if (LOWORD(wParam) == IDC_BUTTON17)
		{
			initDlg(hwnd, wParam, lParam);
		}

		else if (LOWORD(wParam) >= IDC_BUTTON1 && LOWORD(wParam) <= IDC_BUTTON1 + BUTTON_COUNT - 1) 
		{
			if (HIWORD(wParam) == BN_CLICKED) 
			{
				for (int i = 0; i < buttonHandles.size(); i++) 
				{
					if (LOWORD(wParam) == GetDlgCtrlID(buttonHandles[i])) 
					{
						// Кнопка с индексом i была нажата
						/*MessageBox(hwnd, (L"Кнопка " + to_wstring(i + 1) + L" нажата!").c_str(), L"Информация", MB_OK);
						break;*/

						if (answers.size() == 0)
						{
							answers.push_back(GetWindowText(buttonHandles[i], str, sizeof(str) / sizeof(str[0])));
							for (int i = 0; i < answers.size(); i++)
							{
								wsprintf(buf, TEXT("%d"), answers[0]);
								SetDlgItemText(hwnd, GetDlgCtrlID(hEdit1), buf);

							}
						}
					}
				}
			}
		}
		break;
	}


	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}