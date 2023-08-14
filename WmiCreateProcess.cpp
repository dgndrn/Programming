

#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

int main() {
    HRESULT hres;

    // COM kütüphanesini başlat
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "COM kütüphanesi başlatılamadı. Hata kodu: " << hres << std::endl;
        return 1;
    }

    // COM güvenlik seviyesini ayarla
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );
    if (FAILED(hres)) {
        std::cerr << "COM güvenlik ayarları yapılamadı. Hata kodu: " << hres << std::endl;
        CoUninitialize();
        return 1;
    }

    // WMI COM nesnesini başlat
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc
    );
    if (FAILED(hres)) {
        std::cerr << "IWbemLocator nesnesi oluşturulamadı. Hata kodu: " << hres << std::endl;
        CoUninitialize();
        return 1;
    }

    // WMI hizmetine bağlan
    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"root\\cimv2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        &pSvc
    );
    if (FAILED(hres)) {
        std::cerr << "WMI hizmetine bağlanılamadı. Hata kodu: " << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Güvenlik bağlantısını ayarla
    hres = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
    );
    if (FAILED(hres)) {
        std::cerr << "Güvenlik bağlantısı ayarlanamadı. Hata kodu: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Yeni bir süreç oluştur
    IWbemClassObject* pClass = NULL;
    hres = pSvc->GetObject(
        _bstr_t(L"Win32_Process"),
        0,
        NULL,
        &pClass,
        NULL
    );
    if (FAILED(hres)) {
        std::cerr << "Win32_Process sınıfı alınamadı. Hata kodu: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Yeni bir işlem başlat
    IWbemClassObject* pInParamsDefinition = NULL;
    hres = pClass->GetMethod(
        _bstr_t(L"Create"),
        0,
        &pInParamsDefinition,
        NULL
    );
    if (FAILED(hres)) {
        std::cerr << "Create metodu alınamadı. Hata kodu: " << hres << std::endl;
        pClass->Release();
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    IWbemClassObject* pClassInstance = NULL;
    hres = pInParamsDefinition->SpawnInstance(0, &pClassInstance);
    if (FAILED(hres)) {
        std::cerr << "Sınıf örneği oluşturulamadı. Hata kodu: " << hres << std::endl;
        pInParamsDefinition->Release();
        pClass->Release();
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Komutu ayarla (burada "netstat -a" komutu çalıştırılır)
    _variant_t varCommand = L"netstat -a";
    hres = pClassInstance->Put(
        _bstr_t(L"CommandLine"),
        0,
        &varCommand,
        0
    );
    if (FAILED(hres)) {
        std::cerr << "Komut ayarlanamadı. Hata kodu: " << hres << std::endl;
        pClassInstance->Release();
        pInParamsDefinition->Release();
        pClass->Release();
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // Yeni işlemi başlat
    IWbemClassObject* pOutParams = NULL;
    hres = pSvc->ExecMethod(
        _bstr_t(L"Win32_Process"),
        _bstr_t(L"Create"),
        0,
        NULL,
        pClassInstance,
        &pOutParams,
        NULL
    );
    if (FAILED(hres)) {
        std::cerr << "İşlem başlatılamadı. Hata kodu: " << hres << std::endl;
        pClassInstance->Release();
        pInParamsDefinition->Release();
        pClass->Release();
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }

    // İşlem sonuçlarını al
    _variant_t varProcessId;
    hres = pOutParams->Get(
        _bstr_t(L"ProcessId"),
        0,
        &varProcessId,
        0,
        0
    );
    if (FAILED(hres)) {
        std::cerr << "İşlem sonucu alınamadı. Hata kodu: " << hres << std::endl;
    }
    else {
        std::cout << "Başlatılan işlem ID'si: " << V_I4(&varProcessId) << std::endl;
    }

    // Belleği temizle ve kaynakları serbest bırak
    pOutParams->Release();
    pClassInstance->Release();
    pInParamsDefinition->Release();
    pClass->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    return 0;
}
