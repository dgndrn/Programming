
#include"lib.h"

int main()
{				// LPCSTR_to_LPCWSTR mainde tek harf bastýrýyor   strToLPCWSTR ikinci returnde bozuluyor  local degiskenden dolayi


	LPCSTR nano1 = "zapzap";
	wcout << LPCSTR_To_LPCWSTR(nano1);
	
	
 
 return 0;


	int secim, veri;
	cout << "1 Heksadesimal\n2 Oktal\n3 Binary\n";
	cin >> secim;

	cout << "Sayi giriniz:";
	cin >> veri;
	switch (secim) {

	case 1:
		cout << ToHex(veri);

		break;
	case 2:
		cout << ToOctal(veri);
		break;
	case 3:
		cout << ToBinary(veri);
		break;

	}



}

