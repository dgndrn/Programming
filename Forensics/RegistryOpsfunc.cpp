#include"lib.h"



void registryOps_::ListRegistryValues(HKEY hKey, LPCWSTR subkey) {
    HKEY hSubKey;

    // Belirtilen anahtarý açýn.
    if (RegOpenKeyExW(hKey, subkey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
        DWORD index = 0;
        WCHAR valueName[MAX_PATH];
        DWORD valueNameSize = MAX_PATH;
        DWORD dataType;
        BYTE data[1024]; // Deðerin maksimum boyutunu burada ayarlayabilirsiniz.

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




void registryOps_::getTypeAndContent() { // reg_sz gibi type verilerini yazdiriyorum keyin degerini de yazdir
    registryOps_ registryOps;
    HKEY hKey1 = HKEY_CURRENT_USER;

     //  wchar_t value[] = L"";
    wstring value;
    wcout << "Enter the key value:";
    //  wcin >> value;
    //  value[wcslen(value) / sizeof(WCHAR) + 1] = L'\0';

    HKEY hKey;
    LONG lRes = RegOpenKeyExW(HKEY_CURRENT_USER, /*L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"*/ L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);
    bool bExistsAndSuccess(lRes == ERROR_SUCCESS);
    bool bDoesNotExistsSpecifically(lRes == ERROR_FILE_NOT_FOUND);
    std::wstring strValueOfBinDir;
    std::wstring strKeyDefaultValue;
    registryOps.GetStringRegKey(hKey, /*value*//*L"Surfshark"*/L"Steam", strValueOfBinDir, L"[-]Key okuma basarisiz oldu\n");
    // GetStringRegKey(hKey, L"", strKeyDefaultValue, L"bad");

    RegCloseKey(hKey);
    return ;



}










LONG  registryOps_::GetDWORDRegKey(HKEY hKey, const std::wstring& strValueName, DWORD& nValue, DWORD nDefaultValue)
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


LONG registryOps_::GetBoolRegKey(HKEY hKey, const std::wstring& strValueName, bool& bValue, bool bDefaultValue)
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


LONG registryOps_::GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
{
    strValue = strDefaultValue;
    DWORD lptype;
    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    wstring inp;
    nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, &lptype, (LPBYTE)szBuffer, &dwBufferSize);
   
    
    if (ERROR_SUCCESS == nError)
    {
        if (lptype == REG_SZ) {
            wprintf(L"Value: %s\n",szBuffer);
            wprintf(L"Value type: REG_SZ\n");
            
        }
        else if (lptype == REG_DWORD) {
            wprintf(L"Value: %s\n", szBuffer);
            wprintf(L"Value type: REG_DWORD\n");
        }
        else {
            wprintf(L"Value: %s\n",szBuffer);
            wprintf(L"Value type: %lu\n", lptype);
        }


    }
    return nError;
}

