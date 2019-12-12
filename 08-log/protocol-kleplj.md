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

