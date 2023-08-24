// downloading picture from url  (install wget)

#include <iostream>
#include <string>
using namespace std;
int main() {
    string url = "https://pghnetworks.com/wp-content/uploads/2018/06/Blog-pic-1200x750.jpg";
    string cmd = "wget -nd -r -P ./images -A jpeg,jpg,bmp,gif,png " + url;
    system(cmd.c_str());
    return 0;
}
