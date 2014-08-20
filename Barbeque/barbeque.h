#ifndef barbeque_h
#define barbeque_h

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <map>

using namespace std;

class Barbeque
{
public:
    // Declare libcurl object
    CURL* curl;
    // Declare object to hold libcurl response bytes
    CURLcode res;
   
    // Constructor
    Barbeque();
    // Destructor 
    ~Barbeque();

    // Actual Methods 
    string get(string &url);
    string post(string &url, map<string, string> &params);
    string post(string &url, map<string, string> &params, map<string, string> &headers_map);

    inline unsigned int  HttpStatus() const { return http_status; }

private:
    // To store response codes from HTTP Request
    unsigned int http_status;
};

#endif