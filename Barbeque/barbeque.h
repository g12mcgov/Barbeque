/**********************************************************/
//                     Barbeque.h                          //
//                                                         //
// ~ This files defines the class structure for Barbeque ~ //
//                                                         //
//                                                         //
//   Author: Grant McGovern                                //
//   Email: grantmcgovern.mcgovern@gmail.com               //
//                                                         //
//   Date: 20 August 2014                                  //
//                                                         //
//                                                         //
/***********************************************************/

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

    // GET methods:

        string get(string &url);
        string get(string &url, map<string, string> &params);
        string get(string &url, map<string, int> &params);
        string get(string &url, map<int, string> &params);
        string get(string &url, map<int, int> &params);

    // POST methods:

        string post(string &url, string &data);
        string post(string &url, map<string, string> &params);
        string post(string &url, map<string, string> &params, map<string, string> &headers_map);

    inline unsigned int  HttpStatus() const { return http_status; }

    struct postData
    {
        const char *readptr;
        long sizeleft;
    };

private:
    // To store response codes from HTTP Request
    unsigned int http_status;
};

#endif