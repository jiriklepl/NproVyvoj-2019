Jiří Klepl
jiriklepl@seznam.cz

Deadline: 17.10.2019 / 18.10.2019

Requirements:
- You do not have to procotol absolutely everything, such as 'cd' commands,
  'rm -rf' when the task tells you to do a 'rm -rf', 'vim file', etc.
- Include output of commands only when explicitly requested.
- Exact command for repeated actions (such as 'git commit -m') is needed
  only once. You can just state "(commit)" on further occurences.
- You can write answers in Czech.

Useful links and help:
  http://git-scm.com/doc
  'git' - lists basic commands (you should not need any other commands here)
  'git help <command>' - detailed syntax and options of a given command


-----
Tasks
-----

1. Configure your identity (name, email) on the target machine, if you have not already.

2. Create your own private Git repository in a local project directory (working copy).

```bash
mkdir factorials
cd factorials
git init
code .
```

3. Create a new file that contains a program computing factorials for numbers 1 to 10.
   The program should print each computed factorial on a separate line.
   Use your favorite programming language (C, Java, C#, ...).
   Make the file tracked by Git. Save current version into the repository.

The C++ program code is in src/main.cpp:

```cpp
// Copyright 2019 Jiří Klepl <jiriklepl@seznam.czm>
#include <cstdio>

void factorials(
    std::size_t end,
    std::size_t start = 1,
    std::size_t value = 1
) {
    if (start <= end) {
        printf("%zu \n", value *= start++);
        return factorials(end, start, value);
    }
}

int main() {
    factorials(10);

    return 0;
}
```

```bash
git add .
git commit -m "Created the program"
```

4. Split the program into two parts: (1) a library that contains the function for computing factorials and (2) a client that invokes the procedure.
   Use an approach typical for your favorite programming language.
   However, you have to create new file(s) to contain the new parts.

The function definition moved to include/factorials.hpp and created in src/factorials.cpp in a manner that reflects this change

factorials.hpp:

```cpp
// Copyright 2019 Jiří Klepl <jiriklepl@seznam.czm>
#pragma once

#ifndef FACTORIALS_HPP_
#define FACTORIALS_HPP_

#include <cstdio>

void factorials(
    std::size_t end,
    std::size_t start = 1,
    std::size_t value = 1
) {
    if (start <= end) {
        printf("%zu \n", value *= start++);
        return factorials(end, start, value);
    }
}

#endif  // FACTORIALS_HPP_
```

5. Ensure that new file(s), created in step 4, are tracked by Git and commit everything into the repository.


```bash
$ git add .
$ git commit -m "added the new split program"
```


6. Remove the original file created in step 3 (make sure it is not tracked by Git anymore). Commit everything.

```bash
$ git rm src/main.cpp
$ git commit -m "Removed the original code"
```

7. Create new branch with the name "oneline" and switch to it.

```bash
$ git branch oneline master
$ git checkout oneline
```

8. In your branch, modify the program to print all computed factorials on a single line.
   Commit everything properly.

```bash
$ git diff -U0 include/factorials.hpp
diff --git a/include/factorials.hpp b/include/factorials.hpp
index 58e5d68..73afd0d 100644
--- a/include/factorials.hpp
+++ b/include/factorials.hpp
@@ -15 +15 @@ void factorials(
-        printf("%zu \n", value *= start++);
+        printf("%zu ", value *= start++);
$ git add .
$ git commit -m "Printing on one line"
```

9. Go back to the original branch (master).

```bash
$ git checkout master
```

10. Make the following two changes to the factorial program in the given order, but commit only the second modification.
   (i) Program should compute factorials for the numbers 1 to 15.
   (ii) Add new procedure that computes and prints squares of numbers 1 to 10.

```bash
$ git diff -U0 | grep -E "^[+-]"
--- a/include/factorials.hpp
+++ b/include/factorials.hpp
-        printf("%zu \n", value *= start++);
+        printf("%zu\n", value *= start++);
+void squares(
+    std::size_t end,
+    std::size_t start = 1,
+    std::size_t value = 0
+) {
+    if (start <= end) {
+        printf("%zu\n", value += (start++ << 1) - 1);
+        return squares(end, start, value);
+    }
+}
+
--- a/src/factorials.cpp
+++ b/src/factorials.cpp
-    factorials(10);
+    factorials(15);
+
+    squares(10);
$ git add --patch src/factorials.cpp
diff --git a/src/factorials.cpp b/src/factorials.cpp
index 17eb381..d1f859e 100644
--- a/src/factorials.cpp
+++ b/src/factorials.cpp
@@ -2,7 +2,9 @@
 #include "factorials.hpp"
 
 int main() {
-    factorials(10);
+    factorials(15);
+
+    squares(10);
 
     return 0;
 }
Stage this hunk [y,n,q,a,d,e,?]? e
```

Then changed in nano accordingly...

```bash
$ git add include/factorials.hpp 
$ git commit -m "Printing also squares"
```

11. Print the current status of the working copy and all uncommitted modifications.

```bash
$ git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   src/factorials.cpp

no changes added to commit (use "git add" and/or "git commit -a")
$ git diff
diff --git a/src/factorials.cpp b/src/factorials.cpp
index 7511e2e..d1f859e 100644
--- a/src/factorials.cpp
+++ b/src/factorials.cpp
@@ -2,7 +2,7 @@
 #include "factorials.hpp"
 
 int main() {
-    factorials(10);
+    factorials(15);
 
     squares(10);
```

12. Revert uncommitted modifications in the working copy.

```bash
$ git reset --hard
```

13. Merge the branch "oneline" into the last version on the master branch.

```
$ git merge oneline
```

Then clicked on accept incoming, staged and committed with "Merging with oneline"

14. Print short information about each commit.

```bash
$ git log --all | cat
commit bc4d9f2e66800141350b35f387cb31ffb45e5de5
Merge: ce73e01 329a38a
Author: Jiří Klepl <jiriklepl@seznam.cz>
Date:   Sun Oct 13 23:59:24 2019 +0200

    Merging with oneline

commit ce73e01435cdd0fe792f81eb0755747437281652
Author: Jiří Klepl <jiriklepl@seznam.cz>
Date:   Sun Oct 13 23:47:09 2019 +0200

    Printing also squares

commit 329a38afcd77ace11e0c5dbe11f00e55d2c38782
Author: Jiří Klepl <jiriklepl@seznam.cz>
Date:   Sun Oct 13 23:37:11 2019 +0200

    Printing on one line

commit 21b7cfc0d982b6b16c45cd4176a5bec4bd393447
Author: Jiří Klepl <jiriklepl@seznam.cz>
Date:   Sun Oct 13 23:31:17 2019 +0200

    Removed the original code

commit ef8e4a3749a6e30f3b88027c699fa7ee5c4d4d2b
Author: Jiří Klepl <jiriklepl@seznam.cz>
Date:   Sun Oct 13 23:29:01 2019 +0200

    added the new split program

commit 27e800238313bc6a494cac5f9f5c7913da5227fc
Author: Jiří Klepl <jiriklepl@seznam.cz>
Date:   Sun Oct 13 23:21:12 2019 +0200

    Created the program
```

15. Clone existing repository into a completely separate directory (new working copy).
	URL: https://gitlab.mff.cuni.cz/teaching/nswi154/cviceni2019.git
	Note that your Git client may use GUI to ask for the password, so it may not work when you do it in console remotely over ssh.
	You probably have to log in at least once through the web interface (https://gitlab.mff.cuni.cz) to ensure that your Git account is created.
	Let me know if you have any problems with accessing the repository (it works for me, but I cannot use it from a student account, obviously).

```
$ cd ..
$ git clone https://gitlab.mff.cuni.cz/teaching/nswi154/cviceni2019.git
```

16. Modify content of the file main.c somehow.
    For example, add the code printing your name.

```
$ cd cviceni2019
$ code .
```

Added my name

17. Print all modifications done in the working copy.

```bash
$ git diff
diff --git a/cviceni2019/main.c b/cviceni2019/main.c
index f19839b..a53ac8a 100644
--- a/cviceni2019/main.c
+++ b/cviceni2019/main.c
@@ -1,7 +1,7 @@
 <U+FEFF>#include <stdio.h>
 
 int main(int argc, char** argv) {
-  printf("Put your names here:\nPeter Grajcar\nMichal Kyjovsky\nSebastian Uhlik\nOlga Andrusenko Tomas Kalva\nHoang Anh Tuan\nVojtech Svandelik\nDominik Prokop\nTomas Cizek\nNatalia Potocekova\nPeter Lakatos");
+  printf("Put your names here:\nPeter Grajcar\nMichal Kyjovsky\nSebastian Uhlik\nOlga Andrusenko Tomas Kalva\nHoang Anh Tuan\nVojtech Svandelik\nDominik Prokop\nTomas Cizek\nNatalia Potocekova\nPeter Lakatos\nJiří Klepl");
   
   return 0;
 }
```

18. Update your working copy to match the current state of the remote public repository (at the server "gitlab.mff.cuni.cz").
    Someone might have changed the remote repository in the meantime.

```bash
$ git fetch origin master
```

19. Publish your modifications in the remote repository (at the server "gitlab.mff.cuni.cz").

```bash
$ git push origin master
```

20. Create new branch in your local repository (cloned from the server "gitlab.mff.cuni.cz") that starts in the version that was HEAD at the point of time when you cloned the original remote repository (gitlab.mff).
    Give unique name to your branch (to avoid conflicts with other students).
    Make some changes in the branch (e.g., add new files with some content) and commit them.

```bash
$ git branch master Very-Unique-Branch-7804930a-5fc5-4733-b17d-8f988c7e8187-kleplj
$ git checkout Very-Unique-Branch-7804930a-5fc5-4733-b17d-8f988c7e8187-kleplj
```

Did some changes

21. Merge the current HEAD of the master branch into your branch created in the previous task (everything just in the local repository).

```bash
$ git checkout master
$ git pull origin master
$ git checkout Very-Unique-Branch-7804930a-5fc5-4733-b17d-8f988c7e8187-kleplj
$ git merge master
Already up to date
```

22. Publish your branch to the remote repository.

```bash
$ git push origin Very-Unique-Branch-7804930a-5fc5-4733-b17d-8f988c7e8187-kleplj
```

23. Remove the whole directory "cviceni2019" that contains your local repository.
    Clone the existing repository again (like in the task 15).

```bash
cd ..
rm -rf cviceni2019
$ git clone https://gitlab.mff.cuni.cz/teaching/nswi154/cviceni2019.git
cd cviceni2019.git
```

24. List all the branches. Switch to your own branch that you created in the task 20.

```bash
$ git show-branch --list --remotes
  [origin/BackInTime] Merge branch 'master' into BackInTime I added a great file
  [origin/HEAD] Added Martin Gora
  [origin/MartinGoraBranch] Merge branch 'master' into MartinGoraBranch
  [origin/NataliaPotocekova] added name Natalia Potocekova
  [origin/Very-Unique-Branch-7804930a-5fc5-4733-b17d-8f988c7e8187-kleplj] commit
  [origin/VojtechSvandelikBranch] Merge branch 'master' into VojtechSvandelikBranch
  [origin/ando] pridany dve kopie soubou  main.c
  [origin/grajcarp-branch] format main.c
  [origin/lakatopBranch] add NovyTxtSubor
  [origin/master] Added Martin Gora
  [origin/mojeUnikatniVetev] Oprava
  [origin/novaVetevSUnikatnimJmenem1234] Merge branch 'master' into novaVetevSUnikatnimJmenem1234
  [origin/spidoosho] added bible
```

-------
Anketa:
-------

Anketa slouzi pro zhodnoceni temat cviceni a domacich uloh. 
Vyplneni je dobrovolne, nicmene vhodne k budoucimu ladeni obsahu a narocnosti cviceni. 
Na vetsinu otazek je mozna odpoved od 1 do 10, odpoved piste pod prislusnou otazku. 

(1) Nakolik nove pro vas bylo tema cviceni?
    (1 - zcela nove, 10 - vse jsem jiz znal)

8

(2) Domnivate se, ze bylo tema cviceni uzitecne?
    (1 - neuzitecne ci prilis trivialni, 10 - velmi uzitecne)

7

(3) Jak hodnotite narocnost domaci ulohy?
    (1 - prilis trivialni, 5-6 - akorat, 10 - prilis narocne)

5.5

(4) Jak hodnotite svoje zkusenosti s nastrojem ve srovnani s domaci ulohou?
    (1 - vsechno uz znam a umim pouzivat, 10 - vsechno jsem si prakticky vyzkousel poprve)

4

(5) Kolik casu (v minutach) vam reseni zhruba zabralo?

40

(6) Prostor pro vlastni komentare ke cviceni a domaci uloze:

Trochu se mi podarilo pokazit repozitar (z duvodu alternativniho pochopeni ulohy 15, kde jsem clonoval svuj repozitar s programem na faktorialy a ten vzdaleny teprve nato fetchoval dovnitr), ten jsem pote musel opravit (pote co jej zmenil i Martin Gora), aby me zmeny neovlivnily postup ostatnich. Vse od ulohy 15. je tedy rekonstrukce meho postupu (nejspise trochu nedokonala, protoze vsechno jsem musel delat jenom jako).