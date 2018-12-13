This directory is intended for the project specific (private) libraries.

The source code of each library should be placed in separate directory, like
"lib/private_lib/(here are source files)".

For example, see how can be organized `Foo` and `Bar` libraries:

|--lib
|  |--Bar
|  |  |--docs
|  |  |--examples
|  |  |--src
|  |     |- Bar.c
|  |     |- Bar.h
|  |  |--test
|  |--Foo
|  |  |- Foo.c
|  |  |- Foo.h
|  |- readme.txt --> THIS FILE
|--src
   |- main.c

Then in `src/main.c` you should use:

#include <Foo.h>
#include <Bar.h>
