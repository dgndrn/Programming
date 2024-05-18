#include"lib.h"

int post_request() {


    wchar_t  site[30];
 
    
    const char* headers = "Connection: keep-alive\r\n"
        "Cache-Control: max-age=0\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "Origin: http://192.168.183.128\r\n"
        "Content-Type: multipart/form-data; boundary=----WebKitFormBoundarympIl430kLv20mdeL\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n"
        "Referer: http://192.168.183.128/upload_form.html\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "Accept-Language: tr-TR,tr;q=0.9,en-US;q=0.8,en;q=0.7\r\n";



    const char* data = //"------WebKitFormBoundarysT8CyiWXa7kjJG52\r\n"
        "Content-Disposition: form-data; name=\"targetfile\"; filename=\"tatan.txt\"\r\n"
        "Content-Type: text/plain\r\n\r\ndeneme1234\r\n"

        "Content-Disposition: form-data; name=\"submit\"\r\n\r\nUpload File\r\n";
        


    HINTERNET hInternet = InternetOpen(L"Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet) {
        HINTERNET hConnect = InternetConnect(hInternet,L"192.168.183.128", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
        if (hConnect) {
            HINTERNET hRequest = HttpOpenRequest(hConnect, L"POST", L"/upload.php", NULL, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
            if (hRequest) {
    //            const wchar_t* headers = L"Content-Type: text/html";
      //          const wchar_t* data = L"param1=value1&param2=value2"; // Göndermek istediðiniz veriler

                BOOL sendRequest = HttpSendRequestA(hRequest, headers, -1, (LPVOID)data, strlen(data));
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
