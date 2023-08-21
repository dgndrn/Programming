#include"lib.h"

int post_request() {
    HINTERNET hInternet = InternetOpen(L"HTTP POST Example", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet) {
        HINTERNET hConnect = InternetConnect(hInternet, L"www.zapparozuppara.com", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
        if (hConnect) {
            HINTERNET hRequest = HttpOpenRequest(hConnect, L"POST", L"/upload", NULL, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
            if (hRequest) {
                const wchar_t* headers = L"Content-Type: application/x-www-form-urlencoded";
                const wchar_t* data = L"param1=value1&param2=value2"; // Göndermek istediðiniz veriler

                BOOL sendRequest = HttpSendRequest(hRequest, headers, -1, (LPVOID)data, wcslen(data));
                if (sendRequest) {
                    std::cout << "Request sent successfully!" << std::endl;
                }
                else {
                    std::cerr << "Failed to send request. Error: " << GetLastError() << std::endl;
                }

                InternetCloseHandle(hRequest);
            }
            else {
                std::cerr << "Failed to open request. Error: " << GetLastError() << std::endl;
            }

            InternetCloseHandle(hConnect);
        }
        else {
            std::cerr << "Failed to connect. Error: " << GetLastError() << std::endl;
        }

        InternetCloseHandle(hInternet);
    }
    else {
        std::cerr << "Failed to open internet. Error: " << GetLastError() << std::endl;
    }

    return 0;
}
