Jmeno Prijmeni
emailova@adresa

Deadline: 6.12.2019 / 12.12.2019


This assignment has two alternatives: finding and repairing bugs
  (1) either in your own non-trivial program (term project ("zapoctak"), module of some open source project, etc) written in your favorite language for which there exist bug-finding and debugging tools,
  (2) or in the supplied programs written in a rather old version of the C language.
You should pick just one alternative based on your preferences (language, platform).


====================
   ALTERNATIVE 1
====================

You can use any debugger or bug-finding tool (or combination thereof) that supports the language, in which your program is written, and the target platform of your choice.
Reasonable options include FindBugs (Java), Clang analyzer (C/C++), and ReSharper (C#).

-----
Tasks
-----

1. Apply the selected bug-finding tools and debuggers on your program and repair at least some high-priority bugs (issues) reported by the tools.

2. Submit the following: original source code of your program, report produced by the bug-finding tool, repaired source code (diff/patch is sufficient), and the list of bugs from the report (IDs) that you fixed.


====================
   ALTERNATIVE 2
====================

You can use any debugger that supports programs in C (that means GDB, any front-end to GDB, or Visual Studio, for example).
In addition, you may also use the available bug-finding tools (e.g., Clang) instead of GDB and Valgrind to solve the respective parts (the first, second, or both) of this homework assignment.
The only requirement is to report all the debugging actions that you perform (and in some cases also their output) into the protocol.

Useful links and help:
  http://sourceware.org/gdb/current/onlinedocs/gdb/
  http://users.ece.utexas.edu/~adnan/gdb-refcard.pdf
  http://valgrind.org/docs/manual/quick-start.html
  http://valgrind.org/docs/manual/manual-core.html
  http://valgrind.org/docs/manual/mc-manual.html 
  http://clang-analyzer.llvm.org/

-----
Tasks
-----

1. The directory "bc-1.06.95" contains sources of a recent version of the GNU "bc" package,
   an arbitrary precision numeric processing language. One of the programs built from this
   package is "dc", a reverse-polish (postfix notation) arbitrary precision calculator.
   Note that it is also installed in the system (you can use e.g. "man dc"), so make sure
   you run the locally compiled version (not the system one) during the task.

2. Build the sources using the commands "chmod u+x configure ; ./configure ; make". 
   The "dc" binary will be built in the "dc" subdirectory.

3. Run the command "./dc -e "1 1 +".
   This command tells "dc" to compute "1 + 1" in a non-interactive mode and print the result.
   It should crash with a segmentation fault and generate a core dump file ("core").

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/bc-1.06.95$ dc/dc -e "1 1 + p"
    Segmentation fault
    ```

4. Use GDB (or another debugger) to find the root cause of this bug in the code.
   Explain all commands that were used and their outputs.
   Include here the part of the source containing the bug.
   Fix the bug, and include here the modified source code.

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/bc-1.06.95$ gdb --args dc/dc -e "1 1 + p"
    start
    s
    <ENTER> x million times
    dc_add (a=0x5555555614c0, b=0x555555561540, kscale=kscale@entry=0, result=result@entry=0x7fffffffe598) at numeric.c:90
    90              bc_init_num(CastNumPtr(result));
    (gdb) 
    bc_init_num (num=num@entry=0x0) at number.c:136
    136       *num = bc_copy_num (_zero_);
    (gdb) 
    bc_copy_num (num=0x5555555612a0) at number.c:125
    125       num->n_refs++;
    (gdb) 
    bc_init_num (num=num@entry=0x0) at number.c:126
    126       return num;
    (gdb) 

    Program received signal SIGSEGV, Segmentation fault.
    bc_init_num (num=num@entry=0x0) at number.c:126
    126       return num;
    (gdb) 
    ```

    we can see that the problem is result being zero...
    In dc/numeric.c we can see
    ```c
    int
    dc_add DC_DECLARG((a, b, kscale, result))
        dc_num a DC_DECLSEP
        dc_num b DC_DECLSEP
        int kscale ATTRIB((unused)) DC_DECLSEP
        dc_num *result DC_DECLEND
    {
        result = 0;
        bc_init_num(CastNumPtr(result));
        bc_add(CastNum(a), CastNum(b), CastNumPtr(result), 0);
        return DC_SUCCESS;
    }
    ```

    So we can fix it just by deleting the `result = 0` line.


5. Run the command "./dc -e "10 2 - p". It should give a wrong result.
   The arithmetic operation "minus" (subtract) is probably not implemented correctly.

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/bc-1.06.95$ dc/dc -e "10 2 - p"
    -8
    ```

6. Use GDB (or another debugger) to find the root cause of this bug in the code.
   Explain all commands that were used and their outputs.
   Include here the part of the source containing the bug.
   Fix the bug, and include here the modified source code.

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/bc-1.06.95$ gdb --args dc/dc -e "10 2 - p"
    (gdb) i functions
    All defined functions:

    File array.c:
    106:    void dc_array_free(struct dc_array *);
    91:     dc_data dc_array_get(int, int);
    49:     void dc_array_init(void);
    55:     void dc_array_set(int, int, dc_data);

    File dc.c:
    250:    int main(int, char **);
    225:    static int flush_okay(void);
    108:    static void try_file(const char *);

    File eval.c:
    655:    int dc_evalfile(FILE *);
    528:    int dc_evalstr(dc_data *);
    164:    static dc_status dc_func(int, int, int);
    135:    static void dc_trap_interrupt(int);
    95:     static int input_fil(void);
    --Type <RET> for more, q to quit, c to continue without paging--
    107:    static int input_str(void);

    File misc.c:
    170:    dc_data dc_dup(dc_data);
    108:    void dc_garbage(const char *, int);
    68:     void *dc_malloc(size_t);
    60:     void dc_memfail(void);
    153:    void dc_print(dc_data, int, dc_newline, dc_discard);
    85:     void dc_show_id(FILE *, int, const char *);
    129:    const char *dc_system(const char *);

    File number.c:
    586:    void bc_add(bc_num, bc_num, bc_num *, int);
    269:    int bc_compare(bc_num, bc_num);
    122:    bc_num bc_copy_num(bc_num);
    937:    int bc_divide(bc_num, bc_num, bc_num *, int);
    1133:   int bc_divmod(bc_num, bc_num, bc_num *, bc_num *, int);
    91:     void bc_free_num(bc_num *);
    133:    void bc_init_num(bc_num *);
    --Type <RET> for more, q to quit, c to continue without paging--
    109:    void bc_init_numbers(void);
    1618:   void bc_int2num(bc_num *, int);
    314:    char bc_is_near_zero(bc_num, int);
    278:    char bc_is_neg(bc_num);
    287:    char bc_is_zero(bc_num);
    1170:   int bc_modulo(bc_num, bc_num, bc_num *, int);
    862:    void bc_multiply(bc_num, bc_num, bc_num *, int);
    64:     bc_num bc_new_num(int, int);
    1590:   long bc_num2long(bc_num);
    1661:   char *bc_num2str(bc_num);
    1433:   void bc_out_long(long, int, int, void (*)(int));
    1461:   void bc_out_num(bc_num, int, void (*)(int), int);
    1242:   void bc_raise(bc_num, bc_num, bc_num *, int);
    1182:   int bc_raisemod(bc_num, bc_num, bc_num, bc_num *, int);
    1326:   int bc_sqrt(bc_num *, int);
    1700:   void bc_str2num(bc_num *, char *, int);
    536:    void bc_sub(bc_num, bc_num, bc_num *, int);
    344:    static bc_num _bc_do_add(bc_num, bc_num, int);
    160:    static int _bc_do_compare(bc_num, bc_num, int, int);
    --Type <RET> for more, q to quit, c to continue without paging--q
    (gdb) break bc_sub
    Breakpoint 2 at 0x555555559420: file number.c, line 544.
    (gdb) run
    Starting program: /mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/dc/dc -e 10\ 2\ -\ p

    Breakpoint 2, bc_sub (n1=n1@entry=0x555555561540, n2=n2@entry=0x5555555614c0, result=result@entry=0x7fffffffe578, scale_min=scale_min@entry=0) at number.c:544
    544       if (n1->n_sign != n2->n_sign)
    (gdb) where
    #0  bc_sub (n1=n1@entry=0x555555561540, n2=n2@entry=0x5555555614c0, result=result@entry=0x7fffffffe578, scale_min=scale_min@entry=0) at number.c:544
    #1  0x0000555555557c76 in dc_sub (a=0x5555555614c0, b=0x555555561540, kscale=kscale@entry=0, result=result@entry=0x7fffffffe578) at numeric.c:106
    #2  0x000055555555727c in dc_binop (op=0x555555557c50 <dc_sub>, kscale=0) at stack.c:101
    #3  0x0000555555555e1d in dc_func (c=45, peekc=32, negcmp=<optimized out>) at eval.c:189
    #4  0x0000555555556549 in dc_evalstr (string=0x7fffffffe6a0) at eval.c:559
    #5  dc_evalstr (string=0x7fffffffe6a0) at eval.c:528
    #6  0x00005555555553ba in main (argc=3, argv=0x7fffffffe7c8) at dc.c:278
    (gdb) 
    ```

    ```c
    int
    dc_sub DC_DECLARG((a, b, kscale, result))
        dc_num a DC_DECLSEP
        dc_num b DC_DECLSEP
        int kscale ATTRIB((unused)) DC_DECLSEP
        dc_num *result DC_DECLEND
    {
        bc_init_num(CastNumPtr(result));
        bc_sub(CastNum(a), CastNum(b), CastNumPtr(result), 0);
        return DC_SUCCESS;
    }
    ```

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/bc-1.06.95$ make
    make  all-recursive
    make[1]: Entering directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95'
    Making all in lib
    make[2]: Entering directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/lib'
    make[2]: Nothing to be done for 'all'.
    make[2]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/lib'
    Making all in bc
    make[2]: Entering directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/bc'
    make[2]: Nothing to be done for 'all'.
    make[2]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/bc'
    Making all in dc
    make[2]: Entering directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/dc'
    if gcc -DHAVE_CONFIG_H -I. -I. -I.. -I./.. -I./../h   -g -O2 -Wall -funsigned-char -g -O2 -Wall -funsigned-char -MT numeric.o -MD -MP -MF ".deps/numeric.Tpo" -c -o numeric.o numeric.c; \
    then mv -f ".deps/numeric.Tpo" ".deps/numeric.Po"; else rm -f ".deps/numeric.Tpo"; exit 1; fi
    gcc -g -O2 -Wall -funsigned-char -g -O2 -Wall -funsigned-char   -o dc  dc.o misc.o eval.o stack.o array.o numeric.o string.o ../lib/libbc.a 
    make[2]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/dc'
    Making all in doc
    make[2]: Entering directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/doc'
    make[2]: Nothing to be done for 'all'.
    make[2]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95/doc'
    make[2]: Entering directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95'
    make[2]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95'
    make[1]: Leaving directory '/mnt/z/programming/NproVyvoj-2019/07-debug/bc-1.06.95'
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/bc-1.06.95$ dc/dc -e "10 2 - p"
    8
    ```

7. The 'cdc' directory contains a C verion of the CDC benchmark (this is a
   very old and artificially broken version).
   
   Before you build or change anything, it is recommended to copy the original
   directory (for later diffs). For example by "cp -a cdc cdc.orig".

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug$ cp -a cdc cdc-old
    ```

8. Build the program and try to run it using the provided script (it should crash).
   Dump the relevant parts of the crash output here. What type of error would you
   expect, based from the output ?

9. Run the program with Valgrind's memcheck tool. Note that you will have to run
   it directly on the ./cd binary, not the run.sh script (copy the command line options
   for ./cd from the script).
   
   Include here the whole command line and the first ~10 lines of the output.

   Describe what you have learned about the problem in ./cd, from the Valgrind output only
   (what is Valgrind suggesting that the problem is).

10. Use Valgrind, and GDB or manual code inspection to locate and fix the bugs in the program.
    You are done when Valgrind finds no error and the program does not crash.
    Ignore memory leaks summary for now (don't use the command line option for reporting individual
    memory leaks).

    Describe the steps you have taken, include relevant snippets of Valgrind output and comment them.
    (Hint: after the first error is fixed, there are two more).

    Include a diff of the fixed version against the original one (diff -ru cdc.orig/src cdc/src).
 
11. Use Valgrind to search for memory leaks. Include the command line and the first ~20 
    lines of outputs.

12. Fix all "definitely lost" memory leaks. You are done when Valgrind does not
    report any definitely lost blocks (with exceptions below).
   
    For one of the leaks (choose one yourself), include here the relevant part of Valgrind output
    that was used to detect the problem, and explain what exactly was the problem and how your change
    fixes it. You don't need to explain the other fixed errors.

    When done, include a diff against the original sources (diff -ru cdc.orig/src cdc/src) containing
    all fixes.

    (Hint: All leaks are limited to the scope of the function that calls malloc, except for
     the hashmap_new, which has a complementary function hashmap_free)

    Note: leaks reported in function 'collectMotions' in file TransientDetector.c would be hard
    to fix, so ignore them.
    You may create (and tell Valgrind to use) a suppression file .supp containing the following:

{
   collect_motions
   Memcheck:Leak
   fun:malloc
   fun:collectMotions
}
    
    (Hint: valgrind --tool=memcheck --leak-check=yes --suppressions=<file name>)

13. Submit the protocol including all the requested information (commands, output, diffs).

====================

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

