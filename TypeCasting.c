#include<stdio.h>

int main(){

int num = 321;
char snum[5];

// Convert 123 to string [buf]
itoa(num, snum, 10);

// Print our string
printf("%s\n", snum);

char str[] = "123";
int number;
number =  atoi(str);


string veli = "string";
	 sayi1 = atoi(veli.c_str());


}


/*
60

You must call MultiByteToWideChar twice:

The first call to MultiByteToWideChar is used to find the buffer size you need for the wide string. Look at Microsoft's documentation; it states:

If the function succeeds and cchWideChar is 0, the return value is the required size, in characters, for the buffer indicated by lpWideCharStr.

Thus, to make MultiByteToWideChar give you the required size, pass 0 as the value of the last parameter, cchWideChar. You should also pass NULL as the one before it, lpWideCharStr.

Obtain a non-const buffer large enough to accommodate the wide string, using the buffer size from the previous step. Pass this buffer to another call to MultiByteToWideChar. And this time, the last argument should be the actual size of the buffer, not 0.

A sketchy example:

int wchars_num = MultiByteToWideChar( CP_UTF8 , 0 , x.c_str() , -1, NULL , 0 );
wchar_t* wstr = new wchar_t[wchars_num];
MultiByteToWideChar( CP_UTF8 , 0 , x.c_str() , -1, wstr , wchars_num );
// do whatever with wstr
delete[] wstr;
Also, note the use of -1 as the cbMultiByte argument. This will make the resulting string null-terminated, saving you from dealing with them.


*/


/*

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <string>

std::string ConvertWideToANSI(const std::wstring& wstr)
{
    int count = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}

std::wstring ConvertAnsiToWide(const std::string& str)
{
    int count = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
}

std::string ConvertWideToUtf8(const std::wstring& wstr)
{
    int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}

std::wstring ConvertUtf8ToWide(const std::string& str)
{
    int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
}
*/





inline std::wstring convert(const std::string& as)  //verinin stringden wstringe donusturulmesi
 {
	// deal with trivial case of empty string
	if (as.empty())    return std::wstring();

	// determine required length of new string
	size_t reqLength = ::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), 0, 0);

	// construct new string of required length
	std::wstring ret(reqLength, L'\0');

	// convert old string to new string
	::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), &ret[0], (int)ret.length());

	// return new string ( compiler should optimize this away )
	return ret;
}

