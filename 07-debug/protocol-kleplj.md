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

4. Use GDB (or another debugger) to find the root cause of this bug in the code.
   Explain all commands that were used and their outputs.
   Include here the part of the source containing the bug.
   Fix the bug, and include here the modified source code.
   
5. Run the command "./dc -e "10 2 - p". It should give a wrong result.
   The arithmetic operation "minus" (subtract) is probably not implemented correctly.

6. Use GDB (or another debugger) to find the root cause of this bug in the code.
   Explain all commands that were used and their outputs.
   Include here the part of the source containing the bug.
   Fix the bug, and include here the modified source code.

7. The 'cdc' directory contains a C verion of the CDC benchmark (this is a
   very old and artificially broken version).
   
   Before you build or change anything, it is recommended to copy the original
   directory (for later diffs). For example by "cp -a cdc cdc.orig".

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

