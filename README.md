DESCRIPTION
==================================================
The repository contains codes to test the performance 
of standaard and optimized mathematical functions.

* Trigonometric functions by orlp:
https://github.com/orlp

* Fast sqrt and invsqrt functions. 

* The library that implements Vector3D class ussing SSE.

The purpose of the library is testing the extent of optimization that can 
be done solely by _g++_ compiler and comapring it to the _in-house_ vectorization.

GETTING THE CODE
==================================================
* To get the code:
```
git clone git@bitbucket.org:pawelgniewek/fastmath.git
```

* To obtain the most recent version of the code:
```
git pull origin master
```


COMPILING - LINUX
==================================================
To compile a test, one needs to symbolically link
configuration and Make file.
Those files are in a directory: ```compile_files```.
For example to run trigonometric function test 
type in a command line:
```
ln -s ./compile_files/config_sin.mk config.mk

ln -s ./compile_files/Makefile_sin Makefile

make
```

USAGE
=====
To run the sin/cos test run in the command line:
```
./bin/sin_test
```

To run sqrt and iverse sqrt test run in the command line:
```
./bin/sqrt_test
```

To run SSE-Vector3D test run in the command line:
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
The fast sin coputation is by O.P. and can be found at:
https://gist.github.com/orlp/1501b5faa56b592683d5

SSE implementation of the class Vector3Dsse follows the blog:
http://fastcpp.blogspot.fr/2011/12/simple-vector3-class-with-sse-support.html
