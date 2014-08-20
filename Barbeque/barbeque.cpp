/**********************************************************/
//                     Barbeque.cpp                        //
//                                                         //
// ~This files defines the methods for the Barbeque class~ //
//                                                         //
//                                                         //
//   Author: Grant McGovern                                //
//   Email: grantmcgovern.mcgovern@gmail.com               //
//                                                         //
//   Date: 20 August 2014                                  //
//                                                         //
//                                                         //
/***********************************************************/


#include "barbeque.h"

#include <iostream>
#include <map>
#include <iterator>

using namespace std; 

// Constructor
Barbeque::Barbeque(){};

// Destructor 
Barbeque::~Barbeque(){};


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string Barbeque::get(string &url)
{   
    // Clear out the HTTP status
    http_status = 0;

    // Define our "string-i-fied" response variable
    string readBuffer;

    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        unsigned int http_code = 0;
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }
        // Get the response code 
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        http_status = http_code;

        // Assure it's an int by casting
        if(int(http_status) == 400)
            cout << "Response <" << http_status << "> thrown." << endl;

        curl_easy_cleanup(curl);
    }

  return readBuffer;
}

string Barbeque::post(string &url, map<string, string> &params)
{   
    curl = curl_easy_init();

    string parameters;
    string readBuffer;

    // Iterate through parameters map and construct a string from it.
    for(map<string, string>::iterator itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(itr->first + "=" + itr->second);

    cout << parameters << endl;

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
        
        // Make the call
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

string Barbeque::post(string &url, map<string, string> &params, map<string, string> &headers_map)
{   
    curl = curl_easy_init();

    string parameters;
    string headers_data;

    // This is how libcurl natively stores headers
    struct curl_slist *headers = NULL;

    string readBuffer;

    // Iterate through parameters map and construct a string from it.
    for(map<string, string>::iterator itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(itr->first + "=" + itr->second);

    // Iterate through headers map and construct the headers string from it.
    for(map<string, string>::iterator itr = headers_map.begin(); itr != headers_map.end(); ++itr)
        headers_data.append(itr->first + ": "+itr->second);

    if(curl)
    {
        // Construct our headers
        headers = curl_slist_append(headers, headers_data.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
        
        // Make the call
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

