DESCRIPTION
==================================================
The library implements Vector3D class ussing SSE.

The purpose of the library is testing the extent of optimization that can 
be done solely by _g++_ compiler and comapring it to the _in-house_ vectorization.

GETTING THE CODE
==================================================
* To get the code:
```
git@bitbucket.org:pawelgniewek/sse-vector3d.git
```

* To obtain the most recent version of the code:
```
git pull origin master
```

COMPILING - LINUX
==================================================
```
make
```

USAGE
=====
To run the test simply run in the command line:
```
./bin/vec_sse
```

COPYRIGHT NOTICE
================
Copyright (C) 2016-,  Pawel Gniewek

Email  : pawel.gniewek@berkeley.edu

All rights reserved.

License: BSD

ACKNOWLEDGMENTS
===============
SSE implementation of the class Vector3Dsse follows the blog:

http://fastcpp.blogspot.fr/2011/12/simple-vector3-class-with-sse-support.html
