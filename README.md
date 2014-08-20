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


