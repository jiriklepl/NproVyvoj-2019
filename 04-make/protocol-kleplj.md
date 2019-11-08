Jiří Klepl
jiriklepl@seznam.cz

Deadline: 14.11.2019 / 15.11.2019

Requirements:
- You do not have to procotol absolutely everything, such as 'cd' commands,
  'rm -rf' when the task tells you to do a 'rm -rf', 'vim file', etc.
- Include output of commands only when explicitly requested.
- You can write answers in Czech.

Useful links and help:
  http://www.gnu.org/software/make/manual/


-----
Tasks
-----

0. The "mydb" directory contains implementation of a very simple database.
   All source code files are in the "src" subdirectory.

1. Write all necessary Makefiles for the "mydb" project.
   Satisfy the following requirements:
    - create one Makefile at the top level (project root) and one Makefile in the 'src' subdirectory
        - for each target, the top-level Makefile should invoke the nested Makefile (in the 'src' directory) using the recommended approach
        - the nested Makefile should contain the actual rules for compiling source code files, removing generated object files, and so on
    - the full build process should create three binaries (programs): testadmin, testclient, testserver
        - each binary program should be linked against the static library libmydb.a (see below)
        - the binary programs 'testclient' and 'testadmin' will be also linked with the following libraries: libreadline, libhistory
        - you can use a command similar to the following one to perform correct linking: gcc -o testclient -L. testclient.c client_comm.c -lmydb -lreadline -lhistory
        - the binary program 'testclient' must be built from these source files: testclient.c, client_comm.c
        - the binary program 'testserver' must be built from these source files: testserver.c, server_comm.c
        - the binary program 'testadmin' must be built from these source files: testadmin.c
    - the build process should also create the static library libmydb.a 
        - the library must contain object files for all source files except those specific for the binary programs (see above)
        - use the following command to create the library file libmydb.a: ar -rcvs libmydb.a <list of object files to be included>
    - specify proper dependencies between object files, source files (.c), and binary programs
    - specify dependencies on header files (.h) only for "data.c" (by looking into the source code)
        - you do *not* have to specify dependencies on header files in the case of other source files, because there is too many of them
    - other requirements on both Makefiles
        - support the following targets
            all -> compiles everything (i.e., the full build)
            clean -> deletes all the generated files
        - define and use built-in variables for compiler and flags
            - variable CC with the value 'gcc'
            - variable CFLAGS with the value '-g -Wall'
            - set values of the variables in the top-level Makefile and tell Make to propagate the values to the Makefile in the 'src' subdirectory
        - use features supported by Make to eliminate duplication (static pattern rules, implicit rules, variables, functions), but do not over-generalize at the expense of clarity
        - targets that do not correspond to real files should be marked appropriately

2. Test the Makefiles by executing "make" in the root directory of "mydb".
   Ignore all the warnings printed by GCC. The source code is quite old and does not follow the recent standards of C, but it should compile anyway.
   Paste the output of Make here.

3. Demonstrate that the dependencies work properly by invoking "make", "touch src/memory.h", "make", "touch src/testserver.c", "make". 
   Paste the output of each command here.

4. Send all the Makefiles together with the protocol in a single archive.
   Do not include binaries, object files, and other temporary files generated during the build.


-------
Anketa:
-------

Anketa slouzi pro zhodnoceni temat cviceni a domacich uloh. 
Vyplneni je dobrovolne, nicmene vhodne k budoucimu ladeni obsahu a narocnosti cviceni. 
Na vetsinu otazek je mozna odpoved od 1 do 10, odpoved piste pod prislusnou otazku. 

(1) Nakolik nove pro vas bylo tema cviceni?
    (1 - zcela nove, 10 - vse jsem jiz znal)


(2) Domnivate se, ze bylo tema cviceni uzitecne?
    (1 - neuzitecne ci prilis trivialni, 10 - velmi uzitecne)


(3) Jak hodnotite narocnost domaci ulohy?
    (1 - prilis trivialni, 5-6 - akorat, 10 - prilis narocne)


(4) Jak hodnotite svoje zkusenosti s nastrojem ve srovnani s domaci ulohou?
    (1 - vsechno uz znam a umim pouzivat, 10 - vsechno jsem si prakticky vyzkousel poprve)


(5) Kolik casu (v minutach) vam reseni zhruba zabralo?


(6) Prostor pro vlastni komentare ke cviceni a domaci uloze:

