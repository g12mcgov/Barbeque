/**********************************************************/
//                     get_ex.cpp                          //
//                                                         //
//      ~ This files shows how to use Barbeque ~           //
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
#include <string>
#include <curl/curl.h>

using namespace std;


int main()
{
    string url = "http://api.aerisapi.com/observations/20015/";

    // Create Barbeque object
    Barbeque* bbq = new Barbeque();
    // Pass in our URL
    string response1 = bbq->get(url);
}

