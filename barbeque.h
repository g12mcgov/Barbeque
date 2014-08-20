#ifndef barbeque_h
#define barbeque_h

#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>

using namespace std;

class Barbeque
{
	private:
		string Content;
		string Type;
		vector Headers; // To contain params
		unsigned int HttpStatus;
		CURL* CurlHandle;
		
		/* Methods */ 
		static size_t HttpContent(void* ptr, size_t size,
								size_t memb, void* stream);
		static size_t HttpHeader(void* ptr, size_t size,
								size_t memb, void* stream);

	public:
		Barbeque():CurlHandle(curl_easy_int()){};
		~Barbeque(){};

		CURLcode Fetch(string);

		inline string Content() const {return Content;}
		inline string Type() const {return Type;}
		inline unsigned int HttpStatus() const {return HttpStatus;}
		inline vector Headers() const {return Headers;}
};

#endif