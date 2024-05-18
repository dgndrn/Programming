#include"lib.h"


void registryOps_::RegFlow(){

    registryOps_ registryOps;
    HKEY hkey = NULL;
    HKEY hkcr = HKEY_CLASSES_ROOT;
    HKEY hkcu = HKEY_CURRENT_USER;
    HKEY hklm = HKEY_LOCAL_MACHINE;
    HKEY hku = HKEY_USERS;
    HKEY hkcc = HKEY_CURRENT_CONFIG;
    int choice;
    wstring subkey;
    cout << "1 HKEY_CLASSES_ROOT\n2 HKEY_CURRENT_USER\n3 HKEY_LOCAL_MACHINE\n4 HKEY_USERS\n4 HKEY_CURRENT_CONFIG\n";
    cout << "Giris:";
    cin >> choice;

    switch (choice) {

    case 1:
        hkey = hkcr;
        break;
    case 2:
        hkey = hkcu;
        break;
    case 3:
        hkey = hklm;
        break;
    case 4:
        hkey = hku;
        break;
    case 5:
        hkey = hkcc;
        break;
    default:
        cout << "Yanlýþ bir deger girildi!";
        break;
    }
        switch (choice) {
            case 1:
            break;

            case 2:
                    choice = 0;
                    cout << "1 Run\n2 RunOnce\n3 Steam\n4 Votalie Environment\n";
                    cout << "Giris:";
                    cin >> choice;


                    switch (choice) { // current user

                    case 1:
                        subkey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
                        break;

                    case 2:
                        subkey = L"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
                        break;

                    case 3:
                        subkey = L"SOFTWARE\\Valve\\Steam"; // alt keylerde yazilabilir
                        break;

                    case 4:
                        subkey = L"Volatile Environment";
                        break;
                    }
            break;
   
            case 3:

                choice = 0;
                cout << "1 Run\n2 RunOnce\n";
                cin >> choice;
                switch (choice) { // local machine 
                case 1:
                    subkey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
                break;
                
                case 2:
                    subkey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
                break;

                case 3:
                    subkey = ;

                break;


                }

                break;
            case 4:
                break;
    
    
            }

    registryOps.ListRegistryValues(hkey, subkey.c_str());
    // return 0;


    return ;

}




