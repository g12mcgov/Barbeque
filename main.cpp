#include <vector>
#include <iostream>
#include "barbeque.h"

using namespace std;

int main(int argc, const char* argv[])
{
	// Create a new BBQ object
	Barbeque bbq;

	if (bbq.Fetch("http://www.dahu.co.uk") == CURLE_OK)
	{
		cout << "status: " << bbq.HttpStatus() << endl;
		cout << "type: " << bbq.Type() << endl;

		vector<string> headers = curly.Headers();

		for (vector::iterator itr = headers.begin(); itr != headers.end(); itr++)
		{
			cout << "Header: " << (*itr) << endl;
		}
		cout << "Content:\n" << bbq.Content() << endl;
	}
	return 0;
}