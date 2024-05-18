#include"lib.h"



LPCWSTR strToLPCWSTR(string nano) {

	LPCSTR nano1 = nano.c_str();

	return LPCSTR_To_LPCWSTR(nano1);

}


LPCWSTR WstrToLPCWSTR(wstring nano) {

	
	return nano.c_str();

	
}


LPCWSTR LPCSTR_To_LPCWSTR(LPCSTR nano) {


	int sayac = 0;
	int sayx = 0;
	int num = strlen(nano);
	
	char *ptr;

	ptr = (char*)VirtualAlloc(0,(2*num+1), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);


	for (int i = 0; i < 2 * strlen(nano) + 1; i++) {
		sayac++;
		if (sayac % 2 == 1) {
			ptr[i] = nano[sayx];
			sayx++;
		}
		else {
			ptr[i] = 0x0;
		}

	}







	PVOID awq = ptr;
	wchar_t sws[MAX] = L"";
	static wchar_t* nams = sws;
	LPCWSTR nme;
	LPWSTR sne;
	

	
	wcscpy(nams, (wchar_t*)awq);
	
		

	//wcout << nams;
	return nams;


}