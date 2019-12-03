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

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/cdc$ ./run.sh 
    Running with java threads and java memory
    cd: malloc.c:2379: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
    ./run.sh: line 2:  4823 Aborted                 ./cd mono10.bin MAX_FRAMES 400 PERIOD 50 DETECTOR_PRIORITY 9
    ```

    Probably some error in arithmetics or something like that that breaks asserted state.

9. Run the program with Valgrind's memcheck tool. Note that you will have to run
   it directly on the ./cd binary, not the run.sh script (copy the command line options
   for ./cd from the script).
   
   Include here the whole command line and the first ~10 lines of the output.

   Describe what you have learned about the problem in ./cd, from the Valgrind output only
   (what is Valgrind suggesting that the problem is).

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/cdc$ valgrind ./cd mono10.bin MAX_FRAMES 400 PERIOD 50 DETECTOR_PRIORITY 9
    ==4850== Memcheck, a memory error detector
    ==4850== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==4850== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==4850== Command: ./cd mono10.bin MAX_FRAMES 400 PERIOD 50 DETECTOR_PRIORITY 9
    ==4850== 
    Running with java threads and java memory
    ==4850== Invalid write of size 4
    ==4850==    at 0x109E5F: VOXELMAP_init (VoxelMap.c:37)
    ==4850==    by 0x10CAE3: TRANSIENTDETECTOR_init (TransientDetector.c:36)
    ==4850==    by 0x10C0EA: DETECTOR_init (Detector.c:17)
    ==4850==    by 0x10BF07: IMMORTALENTRY_run (ImmortalEntry.c:17)
    ==4850==    by 0x10C190: main (CDC.c:24)
    ==4850==  Address 0x4b9ef54 is 0 bytes after a block of size 100 alloc'd
    ==4850==    at 0x483877F: malloc (vg_replace_malloc.c:309)
    ==4850==    by 0x109E3A: VOXELMAP_init (VoxelMap.c:35)
    ==4850==    by 0x10CAE3: TRANSIENTDETECTOR_init (TransientDetector.c:36)
    ==4850==    by 0x10C0EA: DETECTOR_init (Detector.c:17)
    ==4850==    by 0x10BF07: IMMORTALENTRY_run (ImmortalEntry.c:17)
    ==4850==    by 0x10C190: main (CDC.c:24)
    ==4850== 

    valgrind: m_mallocfree.c:280 (mk_plain_bszB): Assertion 'bszB != 0' failed.
    valgrind: This is probably caused by your program erroneously writing past the
    end of a heap block and corrupting heap metadata.  If you fix any
    invalid writes reported by Memcheck, this assertion failure will
    probably go away.  Please try that before reporting this as a bug.


    host stacktrace:
    ==4850==    at 0x58046A3A: show_sched_status_wrk (m_libcassert.c:388)
    ==4850==    by 0x58046B57: report_and_quit (m_libcassert.c:459)
    ==4850==    by 0x58046CE7: vgPlain_assert_fail (m_libcassert.c:525)
    ==4850==    by 0x58051154: mk_plain_bszB (m_mallocfree.c:280)
    ==4850==    by 0x58051154: mk_plain_bszB (m_mallocfree.c:278)
    ==4850==    by 0x58051154: get_bszB_as_is (m_mallocfree.c:303)
    ==4850==    by 0x58051154: get_bszB (m_mallocfree.c:315)
    ==4850==    by 0x58051154: get_next_b (m_mallocfree.c:434)
    ==4850==    by 0x58051154: vgPlain_arena_malloc (m_mallocfree.c:1796)
    ==4850==    by 0x58005BA3: vgMemCheck_new_block (mc_malloc_wrappers.c:372)
    ==4850==    by 0x58005BA3: vgMemCheck_malloc (mc_malloc_wrappers.c:407)
    ==4850==    by 0x580A5624: do_client_request (scheduler.c:1958)
    ==4850==    by 0x580A5624: vgPlain_scheduler (scheduler.c:1521)
    ==4850==    by 0x580F3550: thread_wrapper (syswrap-linux.c:103)
    ==4850==    by 0x580F3550: run_a_thread_NORETURN (syswrap-linux.c:156)

    sched status:
    running_tid=1

    Thread 1: status = VgTs_Runnable (lwpid 4850)
    ==4850==    at 0x483877F: malloc (vg_replace_malloc.c:309)
    ==4850==    by 0x10A954: hashmap_new (HashMap.c:39)
    ==4850==    by 0x109E78: VOXELMAP_init (VoxelMap.c:38)
    ==4850==    by 0x10CAE3: TRANSIENTDETECTOR_init (TransientDetector.c:36)
    ==4850==    by 0x10C0EA: DETECTOR_init (Detector.c:17)
    ==4850==    by 0x10BF07: IMMORTALENTRY_run (ImmortalEntry.c:17)
    ==4850==    by 0x10C190: main (CDC.c:24)
    client stack range: [0x1FFEFFE000 0x1FFF000FFF] client SP: 0x1FFF000580
    valgrind stack range: [0x1003211000 0x1003310FFF] top usage: 7472 of 1048576


    Note: see also the FAQ in the source distribution.
    It contains workarounds to several common problems.
    In particular, if Valgrind aborted or crashed after
    identifying problems in your program, there's a good chance
    that fixing those problems will prevent Valgrind aborting or
    crashing, especially if it happened in m_mallocfree.c.

    If that doesn't help, please report this bug to: www.valgrind.org

    In the bug report, send all the above text, the valgrind
    version, and what OS and version you are using.  Thanks.
    ```

    Valgrind suggests that the program writes past the heap delimeters

10. Use Valgrind, and GDB or manual code inspection to locate and fix the bugs in the program.
    You are done when Valgrind finds no error and the program does not crash.
    Ignore memory leaks summary for now (don't use the command line option for reporting individual
    memory leaks).

    Describe the steps you have taken, include relevant snippets of Valgrind output and comment them.
    (Hint: after the first error is fixed, there are two more).

    Include a diff of the fixed version against the original one (diff -ru cdc.orig/src cdc/src).
 
    Voxelmap.c: (valgrind suggested a leak there, so the allocation of usedMotionsInList had to be fixed)
    ```c
    void VOXELMAP_init() {
        int i=0,j=0;

        allocatedMotions = (Motion ***) malloc (MAX_LIST*sizeof (Motion**));
        for (i=0;i<MAX_LIST;i++)
            allocatedMotions[i] = (Motion **) malloc(MAX_ITEMS_PER_LIST*sizeof(Motion *));
    //	for(;i<MAX_LIST;i++){
    //		for(j=0;j<MAX_ITEMS_PER_LIST;j++)
    //			allocatedMotions[i][j]=0;
    //	}

        usedMotions = 0;
        // allocate an array of MAX_ITEMS_PER_LIST integers
        usedMotionsInList = (int *) malloc(MAX_ITEMS_PER_LIST * sizeof(int));
        // initialize all the allocated integers to zero
        for (j=0;j<MAX_ITEMS_PER_LIST;j++)usedMotionsInList[j]=0;
        voxel_map = hashmap_new();
    }
    ```

    Then it detected double free in Simulator.c:freadswap, fix:
    ```c
    void freadswap(void* ptr, int size, int cnt, FILE* f) {

        int i=0,j=0;
        char * p = malloc(size*cnt);

        if (!p) {
            fprintf(stderr,"Out of memory in malloc at %s:%d.\n", __FILE__, __LINE__);
            exit(1);
        }

        if (fread(p,size,cnt,f) != cnt) {
            fprintf(stderr,"Error reading input file at %s:%d\n", __FILE__, __LINE__);
            exit(1);
        }

        for(i=0; i<cnt; i++) {
            for(j=0; j<size; j++) {
                *(char *)(ptr+i*size+j) = *(char *)(p+(i*size+size-j-1));
            }
        }
        free(p);
    }
    ```

    ./run.sh stops saying anything is wrong

    Valgrind then suggests conditional jump depending on uninitialised value frameCounter in function generate in Simulator.c, fix:

    `frameCounter == 0;` -> `frameCounter = 0;`

    Valgrind then doesn't detect any errors.

11. Use Valgrind to search for memory leaks. Include the command line and the first ~20 
    lines of outputs.

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/cdc$ valgrind --leak-check=yes ./cd mono10.bin MAX_FRAMES 400 PERIOD 50 DETECTOR_PRIORITY 9 2>&1 | head -n 21
    ==5104== Memcheck, a memory error detector
    ==5104== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==5104== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==5104== Command: ./cd mono10.bin MAX_FRAMES 400 PERIOD 50 DETECTOR_PRIORITY 9
    ==5104== 
    Running with java threads and java memory
    ==5104== 
    ==5104== HEAP SUMMARY:
    ==5104==     in use at exit: 33,622,432 bytes in 243,052 blocks
    ==5104==   total heap usage: 325,654 allocs, 82,602 frees, 132,672,584 bytes allocated
    ==5104== 
    ==5104== 2,656 bytes in 332 blocks are definitely lost in loss record 98 of 242
    ==5104==    at 0x483877F: malloc (vg_replace_malloc.c:309)
    ==5104==    by 0x1097EB: REDUCER_dfsVoxelHashRecurse (Reducer.c:127)
    ==5104==    by 0x1098CE: REDUCER_dfsVoxelHashRecurse (Reducer.c:143)
    ==5104==    by 0x10989D: REDUCER_dfsVoxelHashRecurse (Reducer.c:139)
    ==5104==    by 0x109AA8: REDUCER_performVoxelHashing (Reducer.c:178)
    ==5104==    by 0x10CEFC: TRANSIENTDETECTOR_reduceCollisionSet (TransientDetector.c:192)
    ==5104==    by 0x10CB10: TRANSIENTDETECTOR_lookForCollisions (TransientDetector.c:87)
    ==5104==    by 0x10C9EF: TRANSIENTDETECTOR_run (TransientDetector.c:64)
    ==5104==    by 0x10BD71: DETECTOR_run (Detector.c:24)
    ```

12. Fix all "definitely lost" memory leaks. You are done when Valgrind does not
    report any definitely lost blocks (with exceptions below).
   
    For one of the leaks (choose one yourself), include here the relevant part of Valgrind output
    that was used to detect the problem, and explain what exactly was the problem and how your change
    fixes it. You don't need to explain the other fixed errors.

    Valgrind suggests there is a memory leak in Reducer.c (there are actually 2 instances of that and the other is detected later in the same output), fix:
    
    ```c
    void REDUCER_dfsVoxelHashRecurse(Motion * motion, Vector2d * next_voxel, map_t graph_colors) {
        Vector2d *tmp;
        tmp = (Vector2d *) malloc(sizeof(Vector2d));
        Vector2d *tmp2;

        if (REDUCER_isInVoxel(next_voxel, motion) &&
                (hashmap_get(graph_colors, VECTOR2D_hashCode(next_voxel), NULL)!=MAP_OK)) {
            tmp2 = (Vector2d *) malloc(sizeof(Vector2d));
            VECTOR2D_init(tmp2,next_voxel);
            hashmap_put(graph_colors,VECTOR2D_hashCode(tmp2),(any_t)0);

            VOXELMAP_put(next_voxel, motion);

            // left boundary
            VERCORMATH2D_subtract(next_voxel, horizontal, tmp);
            REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

            // right boundary
            VERCORMATH2D_add(next_voxel, horizontal, tmp);
            REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

            // upper boundary
            VERCORMATH2D_add(next_voxel, vertical, tmp);
            REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

            // lower boundary
            VERCORMATH2D_subtract(next_voxel, vertical, tmp);
            REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

            // upper-left
            VERCORMATH2D_subtract(next_voxel, horizontal, tmp);
            VERCORMATH2D_add(tmp, vertical, tmp);
            REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

            // upper-right
            VERCORMATH2D_add(next_voxel, horizontal, tmp);
            VERCORMATH2D_add(tmp, vertical, tmp);
            REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

            // lower-left
            VERCORMATH2D_subtract(next_voxel, horizontal, tmp);
            VERCORMATH2D_subtract(tmp, vertical, tmp);
            REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

            // lower-right
            VERCORMATH2D_add(next_voxel, horizontal, tmp);
            VERCORMATH2D_subtract(tmp, vertical, tmp);
            REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);

            free(tmp2);
        }

        free(tmp);
    }
    ```

    Then Valgrind suggested a leak in TransientDetector.c in function TRANSIENTDETECTOR_createMotions, fix:
    
    ```c
    Vector3d * save_old_position = (Vector3d *) malloc(sizeof(Vector3d));
    VECTOR3D_init2(save_old_position,old_pos->x, old_pos->y, old_pos->z);

    //updating position in the StateTable
    VECTOR3D_set(old_pos,new_pos->x, new_pos->y, new_pos->z);
    STATETABLE_put(v, new_pos->x, new_pos->y, new_pos->z);

    //MOTION_init1(&ret[motionctr], craft, save_old_position, new_pos);
    VECTOR3D_init2(createdMotions[motionctr].pos_one,save_old_position->x,save_old_position->y,save_old_position->z);
    VECTOR3D_init2(createdMotions[motionctr].pos_two,new_pos->x,new_pos->y,new_pos->z);

    if (DEBUG_DETECTOR || SYNCHRONOUS_DETECTOR) {
        printf("createMotions: adding motion: %s\n", MOTION_toString(&createdMotions[motionctr]));
    }
    motionctr++;

    free(save_old_position);
    ```

    Then in the same file in function TRANSIENTDETECTOR_createMotions there is unallocated string cs_copy, which is just a copy of string cs, fixed by removing any mention of it (whole thing being just local).

    Then undeallocated variable v, fixed by adding `free(v)` (here i stopped doing detailed protocol and i'll just provide the requested diff)

    When done, include a diff against the original sources (diff -ru cdc.orig/src cdc/src) containing
    all fixes.

    ```bash
    jirka@Klepl-PC:~/programming/NproVyvoj-2019/07-debug/cdc$ diff -ru . ../cdc-old/
    Only in .: cd
    Only in ./src: Aircraft.d
    Only in ./src: Aircraft.o
    Only in ./src: CallSign.d
    Only in ./src: CallSign.o
    Only in ./src: CDC.d
    Only in ./src: CDC.o
    Only in ./src: Constants.d
    Only in ./src: Constants.o
    Only in ./src: Detector.d
    Only in ./src: Detector.o
    Only in ./src: FrameBuffer.d
    Only in ./src: FrameBuffer.o
    Only in ./src: HashMap.d
    Only in ./src: HashMap.o
    Only in ./src: helper.d
    Only in ./src: helper.o
    Only in ./src: ImmortalEntry.d
    Only in ./src: ImmortalEntry.o
    Only in ./src: Motion.d
    Only in ./src: Motion.o
    Only in ./src: NanoClock.d
    Only in ./src: NanoClock.o
    Only in ./src: RawFrame.d
    Only in ./src: RawFrame.o
    diff -ru ./src/Reducer.c ../cdc-old/src/Reducer.c
    --- ./src/Reducer.c     2019-12-03 19:34:50.866490700 +0100
    +++ ../cdc-old/src/Reducer.c    2010-12-16 10:06:42.000000000 +0100
    @@ -165,11 +165,7 @@
                    VERCORMATH2D_add(next_voxel, horizontal, tmp);
                    VERCORMATH2D_subtract(tmp, vertical, tmp);
                    REDUCER_dfsVoxelHashRecurse(motion, tmp, graph_colors);
    -
    -               free(tmp2);
            }
    -
    -       free(tmp);
    }
    
    void REDUCER_performVoxelHashing(Motion * motion, map_t graph_colors) {
    Only in ./src: Reducer.d
    Only in ./src: Reducer.o
    diff -ru ./src/Simulator.c ../cdc-old/src/Simulator.c
    --- ./src/Simulator.c   2019-12-03 19:23:53.438394000 +0100
    +++ ../cdc-old/src/Simulator.c  2010-12-14 23:03:58.000000000 +0100
    @@ -42,13 +42,15 @@
                    fprintf(stderr,"Error reading input file at %s:%d\n", __FILE__, __LINE__);
                    exit(1);
            }
    +       char * q = p;
    
            for(i=0; i<cnt; i++) {
                    for(j=0; j<size; j++) {
    -                       *(char *)(ptr+i*size+j) = *(char *)(p+(i*size+size-j-1));
    +                       *(char *)(ptr+i*size+j) = *(char *)(q+(i*size+size-j-1));
                    }
            }
            free(p);
    +       free(q);
    }
    
    void generate(char * args[]) {
    @@ -74,7 +76,7 @@
                    exit(1);
            }
    
    -       frameCounter = 0;
    +       frameCounter == 0;
    
            FRAMEBUFFER_init();
    
    Only in ./src: Simulator.d
    Only in ./src: Simulator.o
    Only in ./src: StateTable.d
    Only in ./src: StateTable.o
    diff -ru ./src/TransientDetector.c ../cdc-old/src/TransientDetector.c
    --- ./src/TransientDetector.c   2019-12-03 20:33:21.016623500 +0100
    +++ ../cdc-old/src/TransientDetector.c  2012-01-04 14:22:36.000000000 +0100
    @@ -119,30 +119,7 @@
                    truesize += TRANSIENTDETECTOR_determineCollisions(mlist->val,c);
                    mlist = mlist ->next;
            }
    -
    -       for (; l != 0; l = mlist) {
    -               mlist = l->next;
    -
    -               for (
    -                       motions *val_ptr = l->val, *val_next;
    -                       val_ptr != 0;
    -                       val_ptr = val_next
    -               ) {
    -                       val_next = val_ptr->next;
    -                       free(val_ptr);
    -               }
    -
    -               free(l);
    -       }
    -
    -       for (int i = 0; i < currentFrame->planeCnt; ++i) {
    -               free(m[i].aircraft);
    -               free(m[i].pos_one);
    -               free(m[i].pos_two);
    -       }
    -
    -       free(m);
    -
    +       free(l);
            return truesize;
    
    }
    @@ -199,7 +176,8 @@
    */
    list_motions * TRANSIENTDETECTOR_reduceCollisionSet(Motion * m,list_motions * l) {
            //map_t voxel_map;
    -       map_t graph_colors = hashmap_new();
    +       map_t graph_colors;
    +       graph_colors = hashmap_new();
    //     int rr=0;
    //     for(;rr<currentFrame->planeCnt;rr++) {
    //             printf("motion: %s\n", MOTION_toString(&m[rr]));
    @@ -220,11 +198,6 @@
    //     }
    
    
    -       if (graph_colors != 0) {
    -               hashmap_free(graph_colors);
    -       }
    -
    -
            l = (list_motions *)malloc(sizeof(list_motions));
            l->next=0;
            l->val=0;
    @@ -260,7 +233,10 @@
    
                    createdMotions[motionctr].aircraft = (Aircraft *) malloc(sizeof(Aircraft));
    
    -               createdMotions[motionctr].aircraft->callsign = cs;
    +               char* cs_copy = (char *)malloc(strlen(cs)+1);
    +               strcpy(cs_copy,cs);
    +
    +               createdMotions[motionctr].aircraft->callsign = cs_copy;
    
                    createdMotions[motionctr].pos_one = (Vector3d *) malloc(sizeof(Vector3d));
                    createdMotions[motionctr].pos_two = (Vector3d *) malloc(sizeof(Vector3d));
    @@ -297,12 +273,8 @@
                                    printf("createMotions: adding motion: %s\n", MOTION_toString(&createdMotions[motionctr]));
                            }
                            motionctr++;
    -
    -                       free(save_old_position);
                    }
    -
                    free(cs);
    -               free(v);
                    free(new_pos);
                    free(old_pos);
    
    Only in ./src: TransientDetector.d
    Only in ./src: TransientDetector.o
    Only in ./src: Vector2d.d
    Only in ./src: Vector2d.o
    Only in ./src: Vector3d.d
    Only in ./src: Vector3d.o
    Only in ./src: VectorMath.d
    Only in ./src: VectorMath.o
    diff -ru ./src/VoxelMap.c ../cdc-old/src/VoxelMap.c
    --- ./src/VoxelMap.c    2019-12-03 19:12:33.378598200 +0100
    +++ ../cdc-old/src/VoxelMap.c   2010-12-14 23:09:22.000000000 +0100
    @@ -32,7 +32,7 @@
    
            usedMotions = 0;
            // allocate an array of MAX_ITEMS_PER_LIST integers
    -       usedMotionsInList = (int *) malloc(MAX_ITEMS_PER_LIST * sizeof(int));
    +       usedMotionsInList = (int *) malloc(MAX_ITEMS_PER_LIST);
            // initialize all the allocated integers to zero
            for (j=0;j<MAX_ITEMS_PER_LIST;j++)usedMotionsInList[j]=0;
            voxel_map = hashmap_new();
    Only in ./src: VoxelMap.d
    Only in ./src: VoxelMap.o
    ```

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

1

(2) Domnivate se, ze bylo tema cviceni uzitecne?
    (1 - neuzitecne ci prilis trivialni, 10 - velmi uzitecne)

8

(3) Jak hodnotite narocnost domaci ulohy?
    (1 - prilis trivialni, 5-6 - akorat, 10 - prilis narocne)

9

(4) Jak hodnotite svoje zkusenosti s nastrojem ve srovnani s domaci ulohou?
    (1 - vsechno uz znam a umim pouzivat, 10 - vsechno jsem si prakticky vyzkousel poprve)

10

(5) Kolik casu (v minutach) vam reseni zhruba zabralo?

240

(6) Prostor pro vlastni komentare ke cviceni a domaci uloze:

