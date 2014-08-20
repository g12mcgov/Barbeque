#ifndef barbeque_h
#define barbeque_h

#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
 
using namespace std;

class Barbeque 
{
    public:
        Barbeque()
        {

        };

        ~Barbeque()
        {

        };

        struct string {
          char *ptr;
          size_t len;
        };       

        size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
        {
          size_t new_len = s->len + size*nmemb;
          s->ptr = realloc(s->ptr, new_len+1);
          if (s->ptr == NULL) {
            fprintf(stderr, "realloc() failed\n");
            exit(EXIT_FAILURE);
          }
          memcpy(s->ptr+s->len, ptr, size*nmemb);
          s->ptr[new_len] = '\0';
          s->len = new_len;

          cout << size*nmemb;
        }

        string get(string url)
        {
        	CURL *curl;
  			CURLcode res;
 
  			curl = curl_easy_init();
  			if(curl)
  			{
    			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    			// Perform the request, res will get the return code
    			res = curl_easy_perform(curl);
    			CString formatted_res = str(curl_easy_strerror(res));
    			// Check for errors 
    			if(res != CURLE_OK)
    			{
    				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    			}
    			// always cleanup 
   				curl_easy_cleanup(curl);
  			}
  			
  			return formatted_res;
        }
};

#endif