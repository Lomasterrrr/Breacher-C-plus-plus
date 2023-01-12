#include <iostream>
#include <fstream>
#include <string>
#include "curl/curl.h"
#include "lib/termcolor.hpp"

using namespace std;
using namespace termcolor;

size_t ClearWrite(void *buffer, size_t size, size_t nmemb, void *userp){

    return size * nmemb;
}
long ResponseCode(std::string link){
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        const char * linkConvert = link.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, linkConvert);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ClearWrite);
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK) {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            return response_code;
        }
        curl_easy_cleanup(curl);
        return 0;
    }
}

int main(int argc, char *argv[]){
    cout << bold << "\n  Breacher C++ - by lomaster\n";
    cout << "  ---------------------------------\n";
    cout << "  File is: " << argv[1] << endl;
    cout << "  Target is: " << argv[2] << endl;
    cout << "  ---------------------------------\n";
    string array[500]; 
    short loop=0; 
    string line; 
    ifstream myfile (argv[1]); 
    if (myfile.is_open()){
        while (!myfile.eof() ) 
        {
            getline (myfile,line); 
            array[loop] = line;
            loop++;
        }
        myfile.close(); 
    }
    else cout << "  Can't open the file";
    for (int a = 0; a < loop; a++) {
        switch (ResponseCode(argv[2] + array[a])) {
             case 404:
                cout << bold << red << "  [-] " << reset  << argv[2] + array[a] << bold << blue << " | " << red << "404 Not Found\n" << reset;
                break;
             case 403:
                cout << bold << red << "  [-] " << reset << argv[2] + array[a] << bold << blue << " | " << red << "403 Forbidden\n" << reset;
                break;
             case 500:
                cout << bold << red << "  [-] " << reset << argv[2] + array[a] << bold << blue << " | " << red << "500 Internet Server Error\n" << reset;
                break;
             case 502:
                cout << bold << red << "  [-] " << reset << argv[2] + array[a] << bold << blue << " | " << red << "502 Bad Gateway\n" << reset;
                break;
             case 503:
                cout << bold << red << "  [-] " << reset << argv[2] + array[a] << bold << blue << " | " << red << "503 Service Unavailable\n" << reset;
                break;
             case 504:
                cout << bold << red << "  [-] " << reset << argv[2] + array[a] << bold << blue << " | " << red << "504 Gateway Timeout\n" << reset;
                break;
             case 301:
                cout << bold << yellow << "  [/] " << reset << argv[2] + array[a] << bold << blue << " | " << yellow << "301 Moved Permanently\n" << reset;
                break;
             case 200:
                cout << bold << green << "  [+] " << reset << argv[2] + array[a] << bold << blue << " | " << green << "200 OK\n" << reset;
                break;
             case 201:
                cout << bold << green << "  [+] " << reset << argv[2] + array[a] << bold << blue << " | " << green << "201 Created\n" << reset;
                break;
             case 202:
                cout << bold << green << "  [+] " << reset << argv[2] + array[a] << bold << blue << " | " << green << "202 Accepted\n" << reset;
                break;
             case 203:
                cout << bold << green << "  [+] " << reset << argv[2] + array[a] << bold << blue << " | " << green << "203 Non-Authoritative Information\n" << reset;
                break;
             case 204:
                cout << bold << green << "  [+] " << reset << argv[2] + array[a] << bold << blue << " | " << green << "204 No Content\n" << reset;
                break;
             case 206:
                cout << bold << green << "  [+] " << reset << argv[2] + array[a] << bold << blue << " | " << green << "206 Partial Content\n" << reset;
                break;
             case 304:
                cout << bold << red << "  [-] " << reset << argv[2] + array[a] << bold << blue << " | " << red << "304 Not Modified\n" << reset;
                break;
             case 302:
                cout << bold << green << "  [/] " << reset << argv[2] + array[a] << bold << blue << " | " << green << "302 Found\n" << reset;
                break;
             case 205:
                cout << bold << green << "  [+] " << reset << argv[2] + array[a] << bold << blue << " | " << green << "205 Reset Content\n" << reset;
                break;
             default:
                cout << bold << yellow << "  [/] " << reset << argv[2] + array[a] << bold << blue << " | " << yellow << "Code Not Found\n" << reset;
                break;

         }
    }

    cout << "  ---------------------------------\n\n";
    return 0;
}
