Jiří Klepl
jiriklepl@seznam.cz

Deadline: 19.12.2019 / 13.12.2019

Requirements:

- You do not have to procotol absolutely everything, such as 'cd' commands,
  'rm -rf' when the task tells you to do a 'rm -rf', 'vim file', etc.
- Include output of commands only when explicitly requested.
- You can write answers in Czech.

Useful links and help:

  http://logging.apache.org/log4j/2.x/
  http://www.gnu.org/software/libc/manual/html_node/Syslog.html
  man pages of respective tools

-----

Tasks
-----

0. Tasks 1 and 2 have two alternatives - Java and C#/.NET.
   You should pick just one based on your favorite platform and programming language.

1. Java: The directory "daisyfs" contains a very simple concurrent file system written in Java.
        A short description and the list of relevant operations (API) is in the file "daisy.txt".
        The main class is "DaisyTest". It creates two threads which perform various operations.

2. Java: Implement logging into the "daisyfs" program. Use the Log4j library (version 2).
        Configure the Log4j library such that log messages are saved into the file "events.log".
        Log the following actions:
          - creating a new file or directory
          - opening some directory
          - closing the given directory
        For each action, record this information: 
          - a file name or inode number
          - current time (up to seconds)
          - number of the current thread
          - result (success, error status)
        Report errors also to console. Use filters on messages.

3. The directory "sockets" contains sources for a simple network client and server,
   and the script "build.sh" that can be used to compile everything.
   This software package was already used in lecture 4.

4. Implement logging into the "sockets" program. Use the syslog API.
   Record the IP address of each client that connects to the server.
   Also log the length of each message received from the clients.

5. Count the number of invocations of each system call and the number of invocations of each library call during execution of the server.
   You can just run the server and kill it when the message "Waiting for TCP ..." appears.
   Make also sure that names of library methods are printed in readable format (not mangled).
       Hint: use abilities of the respective tools as much as possible for this purpose, instead of shell scripts and basic linux utilities (grep, wc).
   Include all the commands that you used to fulfill this task.

```bash
run.sh
```

```log
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 99.38    0.987150      987150         1 SYS_accept
  0.07    0.000696         174         4 std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
  0.06    0.000601         150         4 std::ios_base::Init::Init()
  0.06    0.000565         141         4 __cxa_atexit
  0.05    0.000502          55         9 SYS_mmap
  0.04    0.000391          55         7 SYS_open
  0.04    0.000384         384         1 std::basic_ostream<char, std::char_traits<char> >::operator<<(std::basic_ostream<char, std::char_traits<char> >& (*)(std::basic_ostream<char, std::char_traits<char> >&))
  0.04    0.000378         378         1 std::basic_istream<char, std::char_traits<char> >::operator>>(unsigned short&)
  0.03    0.000256         256         1 socket
  0.03    0.000251         251         1 listen
  0.03    0.000250         250         1 bind
  0.02    0.000220          73         3 SYS_writev
  0.02    0.000219          54         4 SYS_mprotect
  0.02    0.000167          55         3 SYS_read
  0.01    0.000143         143         1 std::basic_ostream<char, std::char_traits<char> >::operator<<(unsigned short)
  0.01    0.000140         140         1 openlog
  0.01    0.000140         140         1 htonl
  0.01    0.000139         139         1 htons
  0.01    0.000110          55         2 SYS_fstat
  0.01    0.000109          54         2 SYS_fcntl
  0.01    0.000104          52         2 SYS_brk
  0.01    0.000104          52         2 SYS_close
  0.01    0.000056          56         1 SYS_socket
  0.01    0.000053          53         1 SYS_arch_prctl
  0.01    0.000053          53         1 SYS_bind
  0.01    0.000052          52         1 SYS_listen
  0.01    0.000051          51         1 SYS_set_tid_address
  0.01    0.000051          51         1 SYS_ioctl
------ ----------- ----------- --------- --------------------
100.00    0.993335                    62 total
```

Nicer (not just waiting but active usage):

```bash
run2.sh
```

```log
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 21.77    0.354747        3619        98 accept
 20.08    0.327226        3339        98 SYS_accept
 13.02    0.212107         239       885 std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
  9.50    0.154829         789       196 syslog
  6.96    0.113382         165       686 toupper
  4.17    0.067895         346       196 recv
  2.74    0.044626         455        98 send
  2.44    0.039754         202       196 memset
  2.27    0.036923         376        98 closelog
  2.23    0.036294         184       197 std::basic_ostream<char, std::char_traits<char> >::operator<<(unsigned short)
  2.15    0.034962         178       196 strlen
  1.90    0.030936         157       196 ntohs
  1.87    0.030555         155       196 inet_ntoa
  1.86    0.030267         101       297 SYS_writev
  1.40    0.022816          77       294 SYS_sendto
  1.15    0.018752         189        99 openlog
  1.04    0.017010          57       294 SYS_connect
  0.86    0.013938          71       196 SYS_recvfrom
  0.72    0.011795          58       203 SYS_open
  0.67    0.010897          55       196 SYS_getpid
  0.51    0.008313          83       100 SYS_close
  0.37    0.006036          60        99 SYS_socket
  0.05    0.000746         186         4 std::ios_base::Init::Init()
  0.04    0.000726         181         4 __cxa_atexit
  0.04    0.000656          72         9 SYS_mmap
  0.04    0.000573         573         1 std::basic_ostream<char, std::char_traits<char> >::operator<<(std::basic_ostream<char, std::char_traits<char> >& (*)(std::basic_ostream<char, std::char_traits<char> >&))
  0.03    0.000410         410         1 std::basic_istream<char, std::char_traits<char> >::operator>>(unsigned short&)
  0.02    0.000348          87         4 SYS_mprotect
  0.02    0.000303         303         1 socket
  0.02    0.000285         285         1 SYS_ioctl
  0.02    0.000261         261         1 bind
  0.02    0.000255         255         1 listen
  0.01    0.000153         153         1 htons
  0.01    0.000144         144         1 htonl
  0.01    0.000131          65         2 SYS_brk
  0.01    0.000122          61         2 SYS_fcntl
  0.01    0.000110          55         2 SYS_fstat
  0.01    0.000110          36         3 SYS_read
  0.01    0.000106         106         1 SYS_arch_prctl
  0.01    0.000098          98         1 SYS_set_tid_address
  0.00    0.000056          56         1 SYS_bind
  0.00    0.000052          52         1 SYS_listen
------ ----------- ----------- --------- --------------------
100.00    1.629705                  5156 total
```

6. Submit an archive containing the protocol, modified sources (complete, not just
   a diff with your changes), all necessary libraries, and configuration files.

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

