/**********************************************************/
//                     example.cpp                         //
//                                                         //
// 	    ~ This files shows how to use Barbeque ~           //
//                                                         //
//                                                         //
//   Author: Grant McGovern                                //
//   Email: grantmcgovern.mcgovern@gmail.com               //
//                                                         //
//   Date: 20 August 2014                                  //
//                                                         //
//                                                         //
/***********************************************************/

// Local Includes
#include "barbeque.h"

// Public Includes
#include <iostream>
#include <map>
#include <string>
#include <curl/curl.h>

using namespace std;


int main()
{
    string url = "http://api.aerisapi.com/observations/20015/";

    // Construct a map for our JSON params. Much like a Python Dict
    map<string, string> params;
    params["client_id"] = "So5KnMdtB8V1R0CvSfS8u";
    params["client_secret"] = "8aGQkpCIjzaVdMWDZJT2iWRmP1KvlSic5kE5lIGq";

    map<string, string> headers;
    headers["Content-type"] = "application/json";


    Barbeque* bbq = new Barbeque();
    string response1 = bbq->get(url);
    string response2 = bbq->post(url, params, headers);
}

