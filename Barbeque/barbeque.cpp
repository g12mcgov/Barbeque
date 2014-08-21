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

/* Callbacks */

struct postData
{
    const char *readptr;
    long sizeleft;
};

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct postData *data_content = (struct postData *)userp;
     
    if(size*nmemb < 1)
        return 0;

    if(data_content->sizeleft)
    {
        *(char *)ptr = data_content->readptr[0]; /* copy one single byte */ 
        data_content->readptr++;                 /* advance pointer */ 
        data_content->sizeleft--;                /* less data left */ 
        return 1;                        /* we return 1 byte at a time! */ 
    }

    return 0;                          /* no more data left to deliver */ 
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/* GET methods */

auto Barbeque::get(string &url)
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


string Barbeque::get(string &url, map<string, string> &params)
{
    // Clear out the HTTP status
    http_status = 0;

    // Define our "string-i-fied" response variable
    string readBuffer;
    string parameters;

    curl = curl_easy_init();

    // Iterate through parameters map and construct a string from it.
    for(map<string, string>::iterator itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(itr->first + "=" + itr->second + "&");

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());

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


string Barbeque::get(string &url, map<int, string> &params)
{
    // Clear out the HTTP status
    http_status = 0;

    // Define our "string-i-fied" response variable
    string readBuffer;
    string parameters;

    curl = curl_easy_init();

    // Iterate through parameters map and construct a string from it.
    for(map<int, string>::iterator itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(to_string(itr->first) + "=" + itr->second + "&"); 

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
        
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


string Barbeque::get(string &url, map<string, int> &params)
{
    // Clear out the HTTP status
    http_status = 0;

    // Define our "string-i-fied" response variable
    string readBuffer;
    string parameters;

    curl = curl_easy_init();

    // Iterate through parameters map and construct a string from it.
    for(map<string, int>::iterator itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(itr->first + "=" + to_string(itr->second) + "&"); 

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
        
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

string Barbeque::get(string &url, map<int, int> &params)
{
    // Clear out the HTTP status
    http_status = 0;

    // Define our "string-i-fied" response variable
    string readBuffer;
    string parameters;

    curl = curl_easy_init();

    // Iterate through parameters map and construct a string from it.
    for(map<int, int>::iterator itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(to_string(itr->first) + "=" + to_string(itr->second) + "&"); 

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
        
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


/* POST methods */

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
        parameters.append(itr->first + "=" + itr->second + "&");

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

string Barbeque::post(string &url, string &data)
{   
    const char * data_char_array = data.c_str(); // Convert to const char array

    struct postData data_content;

    curl = curl_easy_init();
     
    data_content.readptr = data_char_array;
    data_content.sizeleft = (long)strlen(data_char_array);   

    string readBuffer;

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &data_content);

        bool debug = true;

        /* Allows us to view what's going on/debug if necessary */
        if(debug)
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
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

