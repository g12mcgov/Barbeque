#include "barbeque.h"


#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;


int main()
{
    string url;

    cout << "Please input a URL" << endl;
    cin >> url;

    Barbeque* bbq = new Barbeque();
    string response = bbq->get(url);
}

