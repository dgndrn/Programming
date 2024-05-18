#include<windows.h>
#include<iostream>

using namespace std;

void ListRegistryValues(HKEY hKey, LPCWSTR subkey);

LONG GetDWORDRegKey(HKEY hKey, const std::wstring& strValueName, DWORD& nValue, DWORD nDefaultValue)
{
    nValue = nDefaultValue;
    DWORD dwBufferSize(sizeof(DWORD));
    DWORD nResult(0);
    LONG nError = ::RegQueryValueExW(hKey,
        strValueName.c_str(),
        0,
        NULL,
        reinterpret_cast<LPBYTE>(&nResult),
        &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        nValue = nResult;
    }
    return nError;
}


LONG GetBoolRegKey(HKEY hKey, const std::wstring& strValueName, bool& bValue, bool bDefaultValue)
{
    DWORD nDefValue((bDefaultValue) ? 1 : 0);
    DWORD nResult(nDefValue);
    LONG nError = GetDWORDRegKey(hKey, strValueName.c_str(), nResult, nDefValue);
    if (ERROR_SUCCESS == nError)
    {
        bValue = (nResult != 0) ? true : false;
    }
    return nError;
}


LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
{
    strValue = strDefaultValue;
    DWORD lptype;
    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    wstring inp;
    nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, &lptype, (LPBYTE)szBuffer, &dwBufferSize);
 //   nError = RegGetValueW(hKey, 0, strValueName.c_str(), 0, &type, (PVOID)inp.c_str(), &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {

        /*
        strValue = szBuffer;
   
        wcout << L"Value:" << strValue;
        //   wcout << L"Value:" << strValue;
    */
        if (lptype == REG_SZ) {
            wprintf(L"Value type is REG_SZ\n");
        }
        else if (lptype == REG_DWORD) {
            wprintf(L"Value type is REG_DWORD\n");
        }
        else {
            wprintf(L"Value type is %lu\n", lptype);
        }
    
    
    }
    return nError;
}



int main() {
   
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);

    if (GetComputerNameA(computerName, &size)) {
        std::cout << "Bilgisayar Adı: " << computerName << std::endl;
    }
    else {
        std::cerr << "Bilgisayar adı alınamadı." << std::endl;
    }

    return 0;


    return 0;

    HKEY hKey1 = HKEY_CURRENT_USER;

    ListRegistryValues(hKey1, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run");
    return 0;


  //  wchar_t value[] = L"";
    wstring value;
    wcout << "Enter the key value:";
  //  wcin >> value;
  //  value[wcslen(value) / sizeof(WCHAR) + 1] = L'\0';

    HKEY hKey;
    LONG lRes = RegOpenKeyExW(HKEY_CURRENT_USER, /*L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"*/ L"Software\\OpenCV\\HighGUI\\Windows\\Foto", 0, KEY_READ, &hKey);
    bool bExistsAndSuccess(lRes == ERROR_SUCCESS);
    bool bDoesNotExistsSpecifically(lRes == ERROR_FILE_NOT_FOUND);
    std::wstring strValueOfBinDir;
    std::wstring strKeyDefaultValue;
    GetStringRegKey(hKey, /*value*//*L"Surfshark"*/L"*", strValueOfBinDir, L"[-]Key okuma basarisiz oldu\n");
   // GetStringRegKey(hKey, L"", strKeyDefaultValue, L"bad");
        
    RegCloseKey(hKey);
    return 0;

}





void ListRegistryValues(HKEY hKey, LPCWSTR subkey) {
    HKEY hSubKey;

    // Belirtilen anahtarı açın.
    if (RegOpenKeyExW(hKey, subkey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
        DWORD index = 0;
        WCHAR valueName[MAX_PATH];
        DWORD valueNameSize = MAX_PATH;
        DWORD dataType;
        BYTE data[1024]; // Değerin maksimum boyutunu burada ayarlayabilirsiniz.

        while (RegEnumValueW(hSubKey, index, valueName, &valueNameSize, NULL, &dataType, data, &valueNameSize) == ERROR_SUCCESS) {
            wprintf(L"Value Name: %s\n", valueName);
            wprintf(L"Data Type: %d\n", dataType);

            if (dataType == REG_SZ) {
                wprintf(L"Value Data: %s\n", (LPWSTR)data);
            }
            else if (dataType == REG_DWORD) {
                wprintf(L"Value Data: %u\n", *(DWORD*)data);
            }

            wprintf(L"---------------------------------\n");
            valueNameSize = MAX_PATH;
            index++;
        }

        RegCloseKey(hSubKey);
    }
}
