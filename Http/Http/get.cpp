
#include"lib.h"

int get_request(){

	wchar_t  site[30];
	wchar_t url1[30];

	wcout << "Site:";
	wcin >> site;
	wcout << "Url:";
	wcin >> url1;

	wchar_t url[1000] = L"/";
	wcscat(url, url1);




	HINTERNET hSession = InternetOpen(
		L"Mozilla/5.0", // User-Agent
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);

	HINTERNET hConnect = InternetConnect(
		hSession,
		site, // HOST
		0,
		L"",
		L"",
		INTERNET_SERVICE_HTTP,
		0,
		0);

	HINTERNET hHttpFile = HttpOpenRequest(
		hConnect,
		L"GET", // METHOD
		url,   // URI
		NULL,
		NULL,
		NULL,
		0,
		0);

	while (!HttpSendRequest(hHttpFile, NULL, 0, 0, 0)) {
		printf("HttpSendRequest error : (%lu)\n", GetLastError());

		InternetErrorDlg(
			GetDesktopWindow(),
			hHttpFile,
			ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED,
			FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
			FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
			FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
			NULL);
	}

	/*
	  char bufQuery[32];
	  DWORD dwLengthBufQuery;
	  dwLengthBufQuery = sizeof(bufQuery);
	  DWORD dwIndex;
	  dwIndex = 0;

	  // get Content-Length value but... too small
	  BOOL bQuery;
	  bQuery = HttpQueryInfo(
		  hHttpFile,
		  HTTP_QUERY_CONTENT_LENGTH,
		  bufQuery,
		  &dwLengthBufQuery,
		  &dwIndex);
	  if (!bQuery)
		  printf("HttpQueryInfo error : <%lu>\n", GetLastError());
	  */

	DWORD dwFileSize;
	//dwFileSize = (DWORD)atol(bufQuery);
	dwFileSize = BUFSIZ;

	char* buffer;
	buffer = new char[dwFileSize + 1];

	while (true) {
		DWORD dwBytesRead;
		BOOL bRead;

		bRead = InternetReadFile(
			hHttpFile,
			buffer,
			dwFileSize + 1,
			&dwBytesRead);

		if (dwBytesRead == 0) break;

		if (!bRead) {
			printf("InternetReadFile error : <%lu>\n", GetLastError());
		}
		else {
			buffer[dwBytesRead] = 0;
			printf("Retrieved %lu data bytes: %s\n", dwBytesRead, buffer);
			
			
			getphoto(buffer,dwBytesRead);			//fotoyu kaydeder
		}
	}


	InternetCloseHandle(hHttpFile);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hSession);

	return 0;
}








int readfile(char* buffer,DWORD dwBytesRead) {


		HANDLE hFile = CreateFile(
			L"output.jpg",              // Dosya ad�
			FILE_APPEND_DATA,              // Yazma hakk�
			0,                          // Payla��m modu (0 = payla��ms�z)
			NULL,                       // G�venlik �znitelikleri
			OPEN_ALWAYS,              // Dosyay� her zaman olu�tur veya �st�ne yaz
			FILE_ATTRIBUTE_NORMAL,      // Dosya nitelikleri
			NULL                        // �ablon dosya
		);

		if (hFile == INVALID_HANDLE_VALUE) {
			std::cerr << "Dosya olu�turulamad�. Hata kodu: " << GetLastError() << std::endl;
			return 1;
		}

		
		
		DWORD bytesWritten = 0; // Yaz�lan bayt say�s�

		BOOL result = WriteFile(
			hFile,          // Dosya tan�t�c�s�
			buffer,           // Yaz�lacak veri
			dwBytesRead,       // Veri boyutu
			&bytesWritten,  // Yaz�lan bayt say�s�
			NULL            // ��lem tamamland���nda beklemeyi bekleme nesnesi
		);

		if (result) {
			std::cout << "Dosyaya yazma tamamland�. Yaz�lan bayt say�s�: " << bytesWritten << std::endl;
		}
		else {
			std::cerr << "Dosyaya yazma hatas�. Hata kodu: " << GetLastError() << std::endl;
		}

		CloseHandle(hFile); // Dosya tan�t�c�s�n� kapat

		return 0;
	




















	/*

	std::ofstream dosya("output.txt", std::ios::app); // Dosyay� olu�tur veya var olan dosyay� a�
	if (dosya.is_open()) { // Dosyan�n a��l�p a��lmad���n� kontrol et
		
		dosya << buffer; // Dosyaya metni yaz
		
	
		
		dosya.close(); // Dosyay� kapat
		std::cout << "Dosyaya yazma tamamland�." << std::endl;
	}
	else {
		std::cerr << "Dosya a��lamad�." << std::endl;
	}

	return 0;
	*/

}




int getphoto(char* buffer, DWORD dwBytesRead) {


	HANDLE hFile = CreateFile(
		L"output.jpg",              // Dosya ad�
		FILE_APPEND_DATA,              // Yazma hakk�
		0,                          // Payla��m modu (0 = payla��ms�z)
		NULL,                       // G�venlik �znitelikleri
		OPEN_ALWAYS,              // Dosyay� her zaman olu�tur veya �st�ne yaz
		FILE_ATTRIBUTE_NORMAL,      // Dosya nitelikleri
		NULL                        // �ablon dosya
	);

	if (hFile == INVALID_HANDLE_VALUE) {
		std::cerr << "Dosya olu�turulamad�. Hata kodu: " << GetLastError() << std::endl;
		return 1;
	}



	DWORD bytesWritten = 0; // Yaz�lan bayt say�s�

	BOOL result = WriteFile(
		hFile,          // Dosya tan�t�c�s�
		buffer,           // Yaz�lacak veri
		dwBytesRead,       // Veri boyutu
		&bytesWritten,  // Yaz�lan bayt say�s�
		NULL            // ��lem tamamland���nda beklemeyi bekleme nesnesi
	);

	if (result) {
		std::cout << "Dosyaya yazma tamamland�. Yaz�lan bayt say�s�: " << bytesWritten << std::endl;
	}
	else {
		std::cerr << "Dosyaya yazma hatas�. Hata kodu: " << GetLastError() << std::endl;
	}

	CloseHandle(hFile); // Dosya tan�t�c�s�n� kapat

	return 0;









	/*

	std::ofstream dosya("output.txt", std::ios::app); // Dosyay� olu�tur veya var olan dosyay� a�
	if (dosya.is_open()) { // Dosyan�n a��l�p a��lmad���n� kontrol et

		dosya << buffer; // Dosyaya metni yaz



		dosya.close(); // Dosyay� kapat
		std::cout << "Dosyaya yazma tamamland�." << std::endl;
	}
	else {
		std::cerr << "Dosya a��lamad�." << std::endl;
	}

	return 0;
	*/

}







int setWallPaper() {
							// ekran degismiyor ???

	
		int index;
		static char path[MAX_PATH + 1];

		SHGetSpecialFolderPathA(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE);
		char photo[] = "\\output.jpg\0";

		lstrcatA(path, photo);
		cout << path;


		HKEY hkey;
		int status{ RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hkey)
		};
		if (!status) {
			cout << "Key opened successfully\n";


			long regOpenResult;
			LPCSTR program = "WallPaper";
			int set = RegSetValueExA(hkey, program, 0, REG_SZ, (BYTE*)path, strlen(path));
			if (set == ERROR_SUCCESS) {
				cout << "\nProgram saved succesfully\n";
			}
			RegCloseKey(hkey);

		}
		else {
			cout << "Key couldn't open!\n";
		}


		
		return 0;

















}



void setWall() {
	wchar_t  test[] = L"C:\\Users\\zorro\\Desktop\\output.jpg";
	BOOL result;
	result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, test, SPIF_UPDATEINIFILE);

}