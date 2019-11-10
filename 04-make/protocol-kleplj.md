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

    ```Makefile
    CC := gcc
    CFLAGS := -g -Wall

    SRC := src

    NESTED_CALL = $(MAKE) -C $(SRC) CC="$(CC)" CFLAGS="$(CFLAGS)"

    .PHONY: all testclient testserver testadmin clean

    all: testclient testserver testadmin

    clean testclient testserver testadmin:
        $(NESTED_CALL) $@
    ```

    - the full build process should create three binaries (programs): testadmin, testclient, testserver
        - each binary program should be linked against the static library libmydb.a (see below)
        - the binary programs 'testclient' and 'testadmin' will be also linked with the following libraries: libreadline, libhistory
        - you can use a command similar to the following one to perform correct linking: gcc -o testclient -L. testclient.c client_comm.c -lmydb -lreadline -lhistory
        - the binary program 'testclient' must be built from these source files: testclient.c, client_comm.c
        - the binary program 'testserver' must be built from these source files: testserver.c, server_comm.c
        - the binary program 'testadmin' must be built from these source files: testadmin.c

    ```Makefile
    CC_COMMAND = $(CC) $(CFLAGS) -I$(INCLUDE) -o $@

    testclient: $(SRC)/libmydb.a $(addsuffix .o, $(CLIENT_FILES))
        $(CC_COMMAND) $(addsuffix .o, $(CLIENT_FILES)) -L$(LIB) -lmydb -lreadline -lhistory

    testserver: $(SRC)/libmydb.a $(addsuffix .o, $(SERVER_FILES))
        $(CC_COMMAND) $(addsuffix .o, $(SERVER_FILES)) -L$(LIB) -lmydb

    testadmin: $(SRC)/libmydb.a $(addsuffix .o, $(ADMIN_FILES))
        $(CC_COMMAND) $(addsuffix .o, $(ADMIN_FILES)) -L$(LIB) -lmydb -lreadline -lhistory

    data.o: data.c $(addprefix $(INCLUDE)/, $(DATA_C_INCLUDES))
        $(CC_COMMAND) -c $<

    %.o: %.c
        $(CC_COMMAND) -c $<
    ```

    - the build process should also create the static library libmydb.a 
        - the library must contain object files for all source files except those specific for the binary programs (see above)
        - use the following command to create the library file libmydb.a: ar -rcvs libmydb.a \<list of object files to be included\>

    ```Makefile
    COMMON_FILES := $(patsubst %.c,%.o,$(filter-out $(addsuffix .c, $(CLIENT_FILES) $(SERVER_FILES) $(ADMIN_FILES)), $(wildcard $(SRC)/*.c)))

    libmydb.a: $(COMMON_FILES)
        ar -rcvs libmydb.a $(COMMON_FILES)
    ```

    - specify proper dependencies between object files, source files (.c), and binary programs
    - specify dependencies on header files (.h) only for "data.c" (by looking into the source code)
        - you do *not* have to specify dependencies on header files in the case of other source files, because there is too many of them

    > See previous points

    - other requirements on both Makefiles
        - support the following targets
            all -> compiles everything (i.e., the full build)
            clean -> deletes all the generated files

        ```Makefile
        .PHONY: all clean

        all: testadmin testclient testserver

        clean:
            $(RM) $(wildcard $(SRC)/*.o) $(LIB)/libmydb.a
        ```

        - define and use built-in variables for compiler and flags
            - variable CC with the value 'gcc'
            - variable CFLAGS with the value '-g -Wall'
            - set values of the variables in the top-level Makefile and tell Make to propagate the values to the Makefile in the 'src' subdirectory

        > See the first point

        - use features supported by Make to eliminate duplication (static pattern rules, implicit rules, variables, functions), but do not over-generalize at the expense of clarity
        - targets that do not correspond to real files should be marked appropriately

2. Test the Makefiles by executing "make" in the root directory of "mydb".
   Ignore all the warnings printed by GCC. The source code is quite old and does not follow the recent standards of C, but it should compile anyway.
   Paste the output of Make here.

```bash
jirka@Klepl-PC:/mnt/z/programming/NproVyvoj-2019/04-make/mydb$ make
make -C src CC="gcc" CFLAGS="-g -Wall" all
make[1]: Entering directory '/mnt/z/programming/NproVyvoj-2019/04-make/mydb/src'
gcc -g -Wall -I. -o config.o -c config.c
gcc -g -Wall -I. -o error.o -c error.c
gcc -g -Wall -I. -o parser_conds.o -c parser_conds.c
gcc -g -Wall -I. -o strutil.o -c strutil.c
gcc -g -Wall -I. -o result.o -c result.c
gcc -g -Wall -I. -o sql_parser.o -c sql_parser.c
gcc -g -Wall -I. -o conds.o -c conds.c
conds.c: In function ‘copy_condnode’:
conds.c:523:4: warning: ‘cnnod’ may be used uninitialized in this function [-Wmaybe-uninitialized]
    destroy_condnode(cnnod);
    ^~~~~~~~~~~~~~~~~~~~~~~
gcc -g -Wall -I. -o tabconf.o -c tabconf.c
gcc -g -Wall -I. -o tabdef.o -c tabdef.c
gcc -g -Wall -I. -o db_main.o -c db_main.c
gcc -g -Wall -I. -o index.o -c index.c
index.c: In function ‘get_indexrows’:
index.c:151:6: warning: variable ‘block’ set but not used [-Wunused-but-set-variable]
  int block;
      ^~~~~
index.c:150:21: warning: variable ‘cur’ set but not used [-Wunused-but-set-variable]
  st_block_no *head,*cur;
                     ^~~
index.c: In function ‘index_insertrow’:
index.c:255:24: warning: variable ‘cur’ set but not used [-Wunused-but-set-variable]
     st_block_no *head,*cur;
                        ^~~
index.c:254:6: warning: variable ‘block’ set but not used [-Wunused-but-set-variable]
  int block;
      ^~~~~
index.c: In function ‘index_deleterow’:
index.c:395:24: warning: variable ‘cur’ set but not used [-Wunused-but-set-variable]
     st_block_no *head,*cur;
                        ^~~
index.c: In function ‘destroy_indexrow’:
index.c:791:12: warning: ‘cur’ may be used uninitialized in this function [-Wmaybe-uninitialized]
   xfree(cur->value);
         ~~~^~~~~~~
gcc -g -Wall -I. -o textfileio.o -c textfileio.c
gcc -g -Wall -I. -o memory.o -c memory.c
gcc -g -Wall -I. -o query.o -c query.c
gcc -g -Wall -I. -o db_engine.o -c db_engine.c
db_engine.c: In function ‘get_resset_tree’:
db_engine.c:97:13: warning: this ‘if’ clause does not guard... [-Wmisleading-indentation]
             if (!cnnod) goto error1;
             ^~
db_engine.c:99:4: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the ‘if’
    resnode = create_resnode(resnode1,resnode2,NULL,0,cnnod);
    ^~~~~~~
db_engine.c: In function ‘join_resulttabs’:
db_engine.c:683:29: warning: variable ‘prev’ set but not used [-Wunused-but-set-variable]
  st_result_tab *tab1,*tab2,*prev,*cur,*copy_head;
                             ^~~~
db_engine.c: In function ‘sort_rows’:
db_engine.c:1106:39: warning: variable ‘cur2’ set but not used [-Wunused-but-set-variable]
  st_row_data *head,*cur,*prev,*head2,*cur2,*prev2;
                                       ^~~~
db_engine.c: In function ‘remove_duplicate_rows’:
db_engine.c:1234:6: warning: variable ‘remove’ set but not used [-Wunused-but-set-variable]
  int remove;
      ^~~~~~
gcc -g -Wall -I. -o data.o -c data.c
gcc -g -Wall -I. -o parser_commands.o -c parser_commands.c
parser_commands.c: In function ‘parse_select’:
parser_commands.c:381:9: warning: this ‘if’ clause does not guard... [-Wmisleading-indentation]
         if (!s) goto error1;
         ^~
parser_commands.c:383:6: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the ‘if’
      selectquery->ordercol = s;
      ^~~~~~~~~~~
gcc -g -Wall -I. -o btree_int.o -c btree_int.c
ar -rcvs libmydb.a ./config.o ./error.o ./parser_conds.o ./strutil.o ./result.o ./sql_parser.o ./conds.o ./tabconf.o ./tabdef.o ./db_main.o ./index.o ./textfileio.o ./memory.o ./query.o ./db_engine.o ./data.o ./parser_commands.o ./btree_int.o
a - ./config.o
a - ./error.o
a - ./parser_conds.o
a - ./strutil.o
a - ./result.o
a - ./sql_parser.o
a - ./conds.o
a - ./tabconf.o
a - ./tabdef.o
a - ./db_main.o
a - ./index.o
a - ./textfileio.o
a - ./memory.o
a - ./query.o
a - ./db_engine.o
a - ./data.o
a - ./parser_commands.o
a - ./btree_int.o
gcc -g -Wall -I. -o testadmin.o -c testadmin.c
gcc -g -Wall -I. -o testadmin ./testadmin.o -L. -lmydb -lreadline -lhistory
gcc -g -Wall -I. -o testclient.o -c testclient.c
gcc -g -Wall -I. -o client_comm.o -c client_comm.c
gcc -g -Wall -I. -o testclient ./testclient.o ./client_comm.o -L. -lmydb -lreadline -lhistory
gcc -g -Wall -I. -o testserver.o -c testserver.c
gcc -g -Wall -I. -o server_comm.o -c server_comm.c
server_comm.c: In function ‘wait_for_request’:
server_comm.c:66:57: warning: passing argument 3 of ‘accept’ from incompatible pointer type [-Wincompatible-pointer-types]
    new_sock = accept(sock,(struct sockaddr*)&clientname,&size);
                                                         ^
In file included from server_comm.c:1:0:
/usr/include/x86_64-linux-gnu/sys/socket.h:232:12: note: expected ‘socklen_t * restrict {aka unsigned int * restrict}’ but argument is of type ‘size_t * {aka long unsigned int *}’
 extern int accept (int __fd, __SOCKADDR_ARG __addr,
            ^~~~~~
server_comm.c: In function ‘send_result’:
server_comm.c:174:6: warning: this ‘if’ clause does not guard... [-Wmisleading-indentation]
      if (!s) return 0;
      ^~
server_comm.c:176:3: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the ‘if’
   ret = snprintf(s,15,"%d",result->resultret);
   ^~~
gcc -g -Wall -I. -o testserver ./testserver.o ./server_comm.o -L. -lmydb
make[1]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/04-make/mydb/src'
```

3. Demonstrate that the dependencies work properly by invoking "make", "touch src/memory.h", "make", "touch src/testserver.c", "make". 
   Paste the output of each command here.

```bash
jirka@Klepl-PC:/mnt/z/programming/NproVyvoj-2019/04-make/mydb$ make
make -C src CC="gcc" CFLAGS="-g -Wall" all
make[1]: Entering directory '/mnt/z/programming/NproVyvoj-2019/04-make/mydb/src'
make[1]: Nothing to be done for 'all'.
make[1]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/04-make/mydb/src'
jirka@Klepl-PC:/mnt/z/programming/NproVyvoj-2019/04-make/mydb$ touch src/memory.h
jirka@Klepl-PC:/mnt/z/programming/NproVyvoj-2019/04-make/mydb$ make
make -C src CC="gcc" CFLAGS="-g -Wall" all
make[1]: Entering directory '/mnt/z/programming/NproVyvoj-2019/04-make/mydb/src'
gcc -g -Wall -I. -o data.o -c data.c
ar -rcvs libmydb.a ./config.o ./error.o ./parser_conds.o ./strutil.o ./tabconf.o ./result.o ./sql_parser.o ./conds.o ./tabdef.o ./db_main.o ./index.o ./textfileio.o ./query.o ./memory.o ./db_engine.o ./data.o ./parser_commands.o ./btree_int.o
r - ./config.o
r - ./error.o
r - ./parser_conds.o
r - ./strutil.o
r - ./tabconf.o
r - ./result.o
r - ./sql_parser.o
r - ./conds.o
r - ./tabdef.o
r - ./db_main.o
r - ./index.o
r - ./textfileio.o
r - ./query.o
r - ./memory.o
r - ./db_engine.o
r - ./data.o
r - ./parser_commands.o
r - ./btree_int.o
gcc -g -Wall -I. -o testadmin ./testadmin.o -L. -lmydb -lreadline -lhistory
gcc -g -Wall -I. -o testclient ./testclient.o ./client_comm.o -L. -lmydb -lreadline -lhistory
gcc -g -Wall -I. -o testserver ./testserver.o ./server_comm.o -L. -lmydb
make[1]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/04-make/mydb/src'
jirka@Klepl-PC:/mnt/z/programming/NproVyvoj-2019/04-make/mydb$ touch src/testserver.c
jirka@Klepl-PC:/mnt/z/programming/NproVyvoj-2019/04-make/mydb$ make
make -C src CC="gcc" CFLAGS="-g -Wall" all
make[1]: Entering directory '/mnt/z/programming/NproVyvoj-2019/04-make/mydb/src'
gcc -g -Wall -I. -o testserver.o -c testserver.c
gcc -g -Wall -I. -o testserver ./testserver.o ./server_comm.o -L. -lmydb
make[1]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/04-make/mydb/src'
```

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

