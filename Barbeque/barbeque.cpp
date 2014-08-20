/**********************************************************/
//                     Barbeque.cpp                        //
//                                                         //
// ~This files defines the methods for the Barbeque class  //
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


size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string Barbeque::get(string &url)
{
    string readBuffer;

    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }

        curl_easy_cleanup(curl);

        cout << readBuffer << endl;
    }
  return readBuffer;
}

string Barbeque::post(string &url, map<string, string> &params)
{   
    cout << "in function" << endl;

    curl = curl_easy_init();

    string parameters;
    string readBuffer;

    for(map<string, string>::iterator itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(itr->first + "=" + itr->second);

    cout << parameters << endl;

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameterss.c_str());
        
        // Make the call
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }
        curl_easy_cleanup(curl);
        cout << readBuffer << endl;
    }
    return readBuffer;
}
