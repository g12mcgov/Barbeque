#ifndef barbeque_h
#define barbeque_h

#include <iostream>
#include <string>
#include <curl/curl.h>

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
    string get(string url);
    //string post(string url);

    // Helping Methods
    //size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif