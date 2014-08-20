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
    CURLcode res;
   
    // Constructor
    Barbeque();
    // Destructor 
    ~Barbeque();

    // Actual Methods 
    string get(string &url);
    string post(string &url, map<string, string> &params);
};

#endif