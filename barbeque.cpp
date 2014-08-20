
#include <iostream>
#include "curlget.h"

using namespace std;

CURLCode Barbeque::Fetch(string url) 
{
	HttpStatus = 0;
	Content.clear();
	Headers.clear();

	curl_easy_setopt(CurlHandle , CURLOPT_WRITEFUNCTION, HttpContent);
    curl_easy_setopt(CurlHandle, CURLOPT_HEADERFUNCTION, HttpHeader);
    curl_easy_setopt(CurlHandle, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(CurlHandle, CURLOPT_WRITEHEADER, this);

    // Define our target URL
    curl_easy_setopt(CurlHandle, CURLOPT_URL, url.c_str());

    // Make the call
    CURLcode curlErr = curl_easy_perform(CurlHandle);

    if (curlErr == CURLE_OK)
    {
    	char* content_type = NULL;

    	if((curl_easy_getinfo(CurlHandle, CURLINFO_CONTENT_TYPE, &content_type)) == CURLE_OK)
    	{
    		Type = string(content_type);
    	}

    	unsigned int http_code = 0;

    	if((curl_easy_getinfo (CurlHandle, CURLINFO_RESPONSE_CODE, &http_code)) == CURLE_OK)
    	{
    		HttpStatus = http_code;
    	}
    }
    return curlErr;
}

size_t Barbeque::HttpContent(void* ptr, size_t size, size_t memb, void* stream)
{
	Barbeque* handle = (Barbeque*)stream;
	size_t data_size = size*memb;

	if (handle != NULL)
	{
		handle->Content.append((char *)ptr, data_size);
	}
	return data_size;
}

size_t Barbeque::HttpHeader(void* ptr, size_t size, size_t memb, void* stream){
	Barbeque* handle = (Barbeque*)stream;
	size_t data_size = size*memb;

	if(handle != NULL)
	{
		string header_line((char *)ptr, data_size);
		handle->Headers.push_back(header_line);
	}
	return data_size;
}





