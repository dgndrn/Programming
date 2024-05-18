#pragma once
#include"lib.h"




int ussu(int sayi, int us) {
    int sonuc = 1;
    for (int i = 0; i < us; i++) {

        sonuc = sonuc * sayi;


    }
    return sonuc;
}


int ToBinary(int decimal) {


  return  dec_to_base(decimal, 2);

}


int ToHex(int decimal) {

    return  dec_to_base(decimal, 16);

}


int ToOctal(int decimal) {

    return  dec_to_base(decimal, 8);

}



int dec_to_base(int deger, int taban) {



    /*
    0,00
    1,01
    2,10
    3,11
    4,100
    5,101
    6,110
    7,111
    8,1000
    9,1001
    10,1010
    11,1011
    12,1100
    13,1101
    14,1110
    15,1111
    16,10000
    */
    int  kalan, sayac, binary;


    

    // bolum + kalan  2/2,  bolum = 1 kalan = 0 , 2 = 10.bin
    while (1) {

        int kalanlar[16];

        sayac = 0;


        while (1) {
            sayac++;
            kalanlar[sayac - 1] = deger % taban;
            deger = deger / taban;

            if (deger == 0) {

                break;
            }


        }

        /*
        switch (sayac) {    // basamak belirlemek icin

        case 1:

            binary = (kalanlar[0] * 1);
            break;
        case 2:

            binary = (kalanlar[1] * 10) + (kalanlar[0] * 1);
            break;
        case 3:
            binary = (kalanlar[2] * 100) + (kalanlar[1] * 10) + (kalanlar[0] * 1);
            break;
        case 4:
            binary = (kalanlar[3] * 1000) + (kalanlar[2] * 100) + (kalanlar[1] * 10) + (kalanlar[0] * 1);
            break;
        case 5:
            binary = (kalanlar[4] * 10000) + (kalanlar[3] * 1000) + (kalanlar[2] * 100) + (kalanlar[1] * 10) + (kalanlar[0] * 1);
            break;
        case 6:
            binary = (kalanlar[5] * 100000) + (kalanlar[4] * 10000) + (kalanlar[3] * 1000) + (kalanlar[2] * 100) + (kalanlar[1] * 10) + (kalanlar[0] * 1);
            break;


        }*/

        // cout << binary;
        int gecici;
        binary = 0;
        for (int i = 0; i < sayac; i++) {
            gecici = ussu(10, sayac - 1);
            binary += kalanlar[sayac - i - 1] * ussu(10, sayac - i - 1);

        }

        return binary;




    }
}