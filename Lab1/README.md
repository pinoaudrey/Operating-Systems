The sample program currently produces a segmentation fault:
$ ./bugs
The current bug population of Earth is about: 1480000000000000000
The current bug population of Mars is about: 140727437236104
The current bug population of Venus is about: 0
The total bug population of the solar system is: 1480000000000000000
The most useless bug is a butterfly Segmentation fault (core dumped)
Your tasks for this lab are as follows:
Observe and explain the reasons for the memory leaks in the valgrind_test.c program (with the help of valgrind). Propose solutions to resolve the memory leaks.
Find and fix all of the problems of "bugs.c" with the aid of debugger (gdb and valgrind). When you are finished, the test output should print:
$ make test
gcc -g bugs.c -o bugs
valgrind --leak-check=full ./bugs > bugs_output.txt 2> valgrind_output.txt

=======================================
VALGRIND DIFF
---------------------------------------

=======================================
PROGRAM DIFF
---------------------------------------

$ cat bugs_output.txt
The current bug population of Earth is about: 1480000000000000000
The current bug population of Mars is about: 0
The current bug population of Venus is about: 0
The total bug population of the solar system is: 1480000000000000000
The most useless bug is a mosquito
The most colorful bug is a butterfly
The most colorful bug is a a is bug colorful most The
The current bug adjective is: (null)
Bugs didn't cause me to crash!

$ cat valgrind_output.txt
==#== Memcheck, a memory error detector
==#== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==#== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==#== Command: ./bugs
==#== 
==#==
==#== HEAP SUMMARY:
==#==     in use at exit: 0 bytes in 0 blocks
==#==   total heap usage: 7 allocs, 7 frees, 35 bytes allocated
==#== 
==#== All heap blocks were freed -- no leaks are possible
==#== 
==#== For counts of detected and suppressed errors, rerun with: -v
==#== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
