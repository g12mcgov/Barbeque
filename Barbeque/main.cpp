
#include <iostream>
#include <vector>
#include "barbeque.h"

using namespace std;

int main (int argc, const char * argv[])
{

   Barbeque bbq;

   string response = bbq.get("www.google.com");
   cout << response << endl;

}