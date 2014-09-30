!['Barbeque Logo'](http://i1158.photobucket.com/albums/p618/g12mcgov/Untitleddrawing.png)
========

A libcurl C++ HTTP Request wrapper to make life easier.

Description
========
HTTP requests shouldn't be hard. While C++ does not have a native library, there are several other options but they all overcomplicate the process. I was looking for a simple, liteweight solution to make calls against APIs and return the response content. 

Barbeque is based on libcurl, the C++ HTTP request library, and wraps it in an easy to use fashion. Each method returns a string (of you content) which you can then use against your favorite JSON parser.

Installation
========

You must first install <code>libcurl</code> as it is the basis for Barbeque.

Go here: http://curl.haxx.se/download.html to download the latest source archive.

Then:
  1. Expand the tarball <code>tar -xvf curl-7.XX.XX.tar</code>
  2. <code>cd</code> into the newly created directory <code>curl-7.XX.XX</code>

Run:
  - <code>./configure</code>
  - <code>make</code>
  - <code>make test</code>
  - <code>sudo make install</code>


Assuming everything went OK, libcurl should now be installed.

Now:

<code>git clone https://github.com/g12mcgov/Barbeque.git</code>

Move thee cloned files into your local directory and finally:

<code>#include "barbeque.h"</code>

Documentation
========
Currently Barbeque supports <code>GET</code> and <code>POST</code> operations. To do the following please look at the documentation below:

<code>[ GET ]</code>

  ### Example:

    int main()
    {
      string url = "http://api.aerisapi.com/observations/20015/";
      
      // Create Barbeque object
      Barbeque* bbq = new Barbeque();
      
      // Pass in our URL
      string response1 = bbq->get(url);
    }
  
  Simply declare the Barbeque object (I strongly suggest doing so dynamically), and use it as shown in the example. The <code>GET</code> method expects a string to be passed.
  
<code>[ PUSH ]</code>

  The PUSH method expects a <code><b><map></b></code> to be passed in as the argument. This way, you can construct Key/Value pairs for APIs. For instance, the example below shows a scenario where the given API requires 2 parameters.
  
  <code>client_id</code><br>
  <code>client_secret</code>
    
  
  ### Example:

    #include <map>
    ...
      
    int main()
    {
      string url = "http://api.aerisapi.com/observations/20015/";
      
      // Construct a map for our JSON params. Much like a Python Dict
      map<string, string> params;
      
      // Populate the map
      params["client_id"] = "#######";
      params["client_secret"] = "########";
      
      // Construct our [optional] headers map
      map<string, string> headers;
      
      // Populate the map
      headers["Content-type"] = "application/json";
      
      // Declare a new Barbeque object
      Barbeque* bbq = new Barbeque();
      
      // Here we call it with no headers
      string response1 = bbq->post(url, params);
      
      // Optionally (and alternatively), we can add headers.
      string response2 = bbq->post(url, params, headers);
    }
    
  Simply declare the Barbeque object (I strongly suggest doing so dynamically), and use it as shown in the example. The <code>POST</code> method has been overloaded to also accept headers.
    
  Happy HTTP requesting!
