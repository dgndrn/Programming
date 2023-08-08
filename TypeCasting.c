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

