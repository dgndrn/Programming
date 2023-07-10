#include<windows.h>
#include<iostream>
#include "shlobj_core.h"

using namespace std;

int main() {
	int index;
	static char path[MAX_PATH + 1];

	SHGetSpecialFolderPathA(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE);
	char exe[] = "\\program.exe\0";
	
	lstrcatA(path, exe);
	cout << path;

	
	HKEY hkey;
	int status{RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hkey)
	};
		if(!status) {
			cout << "Key opened successfully\n";

		
			long regOpenResult;
			// const char path[] = "C:\\Users\\user\\Desktop\\program.exe";
			LPCSTR program = "program";
		int set =	RegSetValueExA(hkey, program, 0, REG_SZ, (BYTE*)path, strlen(path));
		if (set == ERROR_SUCCESS) {
			cout << "\nProgram saved succesfully\n";
			}
		RegCloseKey(hkey);

		}
		else {
			cout << "Key couldn't open!\n";
		}


		system("pause");




}