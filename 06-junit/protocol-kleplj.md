Jmeno Prijmeni
emailova@adresa

Deadline: 29.11.2019 / 5.12.2019

Requirements:
- You do not have to procotol absolutely everything, such as 'cd' commands,
  'rm -rf' when the task tells you to do a 'rm -rf', 'vim file', etc.
- Include output of commands only when explicitly requested.
- You can write answers in Czech.

Useful links and help:
  http://junit.org
  https://github.com/junit-team/junit/wiki

-----
Tasks
-----

0. All the required libraries (junit-4.11.jar, hamcrest-core-1.3.jar) are located in the "lib/" subdirectory.

1. Write unit tests for the class java.util.TreeMap.
   See http://docs.oracle.com/javase/8/docs/api/java/util/TreeMap.html.

   Cover the following basic use cases:
     - adding new mapping with the key different from all present mappings

    ```java
    @Test
    public void AddNewKeyValue() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.put("NewKey", 7);
        assertTrue(map.size() == 8);
    }
    ```

     - adding new mapping with a key equal to some already present mapping

    ```java
    @Test
    public void AddPresentKeyValue() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.put("FirstKey", 7);
        assertTrue(map.size() == 7);
        assertTrue(map.get("FirstKey") == 7);
    }
    ```

     - removing some element (mapping) already present in the map

    ```java
    @Test
    public void RemovePresentKeyValue() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.remove("FirstKey");
        assertTrue(map.size() == 6);
    }
    ```

     - attempt to remove some element (key) not present in the map

    ```java
    @Test
    public void RemoveNewKeyValue() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.remove("FirstypoKey");
        assertTrue(map.size() == 7);
    }
    ```

     - removing all elements from the map and checking for emptiness

    ```java
    @Test
    public void RemoveAllAndEmpty() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.remove("FirstKey");
        map.remove("SecondKey");
        map.remove("ThirdKey");
        map.remove("FourthKey");
        map.remove("FifthKey");
        map.remove("SixthKey");
        map.remove("SeventhKey");
        assertTrue(map.isEmpty());
    }
    ```

     - getting the value associated with a specific key

    ```java
    @Test
    public void GetKey() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        Integer i = map.get("FirstKey");
        assertTrue(i == 0);
    }
    ```

     - attempt to get a value for a key not present in the map

    ```java
    @Test
    public void GetNotPresentKey() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        Integer i = map.get("FirstypoKey");
        assertTrue(i == null);
    }
    ```

     - checking existence of a mapping for a given key

    ```java
    @Test
    public void ContainsKeyBoth() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        assertTrue(map.containsKey("FirstKey"));
        assertTrue(!map.containsKey("FirstypoKey"));
    }
    ```

     - iterating over sorted keys (from the lowest to the highest)

    ```java
    public void IterateOverSortedKeys() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        String old_key = null;
        int i = 0;

        for (String key : map.keySet()) {
            assertTrue(key != null);
            if (old_key != null) {
                // checking ordering
                assertTrue(old_key.compareTo(key) < 0);
            }

            old_key = key;
            ++i;
        }
        // checking whether iterated through whole set of keys
        assertTrue(i == map.size());
    }
    ```

   Always verify the current state of the map (content, size) and, if necessary, also the state of the associated iterator.

   Note that the Java package of your test classes must be different than "java.util", because application programs cannot modify or extend this package.
   This is not a problem since your tests will be calling only the public methods (you will make black-box tests).

   Follow the recommended practices for writing unit tests.

2. Build all tests for TreeMap and verify that they pass.
   Run tests from the command line, either by calling the appropriate runner class or use the "main" method in your test class (paste the command and test output here).

```bash
$ mvn test
WARNING: An illegal reflective access operation has occurred
WARNING: Illegal reflective access by com.google.inject.internal.cglib.core.$ReflectUtils$1 (file:/usr/share/maven/lib/guice.jar) to method java.lang.ClassLoader.defineClass(java.lang.String,byte[],int,int,java.security.ProtectionDomain)
WARNING: Please consider reporting this to the maintainers of com.google.inject.internal.cglib.core.$ReflectUtils$1
WARNING: Use --illegal-access=warn to enable warnings of further illegal reflective access operations
WARNING: All illegal access operations will be denied in a future release
[INFO] Scanning for projects...
[INFO] 
[INFO] ------------< com.github.jiriklepl.treemaptest:treemaptest >------------
[INFO] Building treemaptest 1.0
[INFO] --------------------------------[ jar ]---------------------------------
[INFO] 
[INFO] --- maven-resources-plugin:2.6:resources (default-resources) @ treemaptest ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /mnt/z/programming/NproVyvoj-2019/06-junit/src/main/resources
[INFO] 
[INFO] --- maven-compiler-plugin:3.1:compile (default-compile) @ treemaptest ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 1 source file to /mnt/z/programming/NproVyvoj-2019/06-junit/target/classes
[INFO] 
[INFO] --- maven-resources-plugin:2.6:testResources (default-testResources) @ treemaptest ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /mnt/z/programming/NproVyvoj-2019/06-junit/src/test/resources
[INFO] 
[INFO] --- maven-compiler-plugin:3.1:testCompile (default-testCompile) @ treemaptest ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 2 source files to /mnt/z/programming/NproVyvoj-2019/06-junit/target/test-classes
[INFO] 
[INFO] --- maven-surefire-plugin:2.12.4:test (default-test) @ treemaptest ---
[INFO] Surefire report directory: /mnt/z/programming/NproVyvoj-2019/06-junit/target/surefire-reports

-------------------------------------------------------
T E S T S
-------------------------------------------------------
Running com.github.jiriklepl.treemaptest.TestTreeMap
Tests run: 9, Failures: 0, Errors: 0, Skipped: 0, Time elapsed: 0.14 sec

Results :

Tests run: 9, Failures: 0, Errors: 0, Skipped: 0

[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  2.720 s
[INFO] Finished at: 2019-11-28T22:48:20+01:00
[INFO] ------------------------------------------------------------------------
```

3. Add another test for TreeMap that fails and prints a custom error message.
   For example, you can assert that the map has a key-value mapping which it does not really have.
   Run the tests and paste the output here. 
   In the output, mark the line of the output that contains the custom error message, and mark the line that identifies the place in the test code that has failed.

```java
@Test
public void TestThatFails() {
    TreeMap<String, Integer> map = TestFixture.initTreeMap();
    assertThat("This should fail", map.isEmpty(), is(true));
}
```

```bash
$ mvn test
WARNING: An illegal reflective access operation has occurred
WARNING: Illegal reflective access by com.google.inject.internal.cglib.core.$ReflectUtils$1 (file:/usr/share/maven/lib/guice.jar) to method java.lang.ClassLoader.defineClass(java.lang.String,byte[],int,int,java.security.ProtectionDomain)
WARNING: Please consider reporting this to the maintainers of com.google.inject.internal.cglib.core.$ReflectUtils$1
WARNING: Use --illegal-access=warn to enable warnings of further illegal reflective access operations
WARNING: All illegal access operations will be denied in a future release
[INFO] Scanning for projects...
[INFO] 
[INFO] ------------< com.github.jiriklepl.treemaptest:treemaptest >------------
[INFO] Building treemaptest 1.0
[INFO] --------------------------------[ jar ]---------------------------------
[INFO] 
[INFO] --- maven-resources-plugin:2.6:resources (default-resources) @ treemaptest ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /mnt/z/programming/NproVyvoj-2019/06-junit/src/main/resources
[INFO] 
[INFO] --- maven-compiler-plugin:3.1:compile (default-compile) @ treemaptest ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 1 source file to /mnt/z/programming/NproVyvoj-2019/06-junit/target/classes
[INFO] 
[INFO] --- maven-resources-plugin:2.6:testResources (default-testResources) @ treemaptest ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /mnt/z/programming/NproVyvoj-2019/06-junit/src/test/resources
[INFO] 
[INFO] --- maven-compiler-plugin:3.1:testCompile (default-testCompile) @ treemaptest ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 2 source files to /mnt/z/programming/NproVyvoj-2019/06-junit/target/test-classes
[INFO] 
[INFO] --- maven-surefire-plugin:2.12.4:test (default-test) @ treemaptest ---
[INFO] Surefire report directory: /mnt/z/programming/NproVyvoj-2019/06-junit/target/surefire-reports

-------------------------------------------------------
 T E S T S
-------------------------------------------------------
Running com.github.jiriklepl.treemaptest.TestTreeMap
Tests run: 10, Failures: 1, Errors: 0, Skipped: 0, Time elapsed: 0.171 sec <<< FAILURE!
TestThatFails(com.github.jiriklepl.treemaptest.TestTreeMap)  Time elapsed: 0.028 sec  <<< FAILURE!
java.lang.AssertionError: This should fail
Expected: is <true>
     but: was <false>
        at org.hamcrest.MatcherAssert.assertThat(MatcherAssert.java:20)
        at org.junit.Assert.assertThat(Assert.java:956)
        at com.github.jiriklepl.treemaptest.TestTreeMap.TestThatFails(TestTreeMap.java:99)
        at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
        at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
        at java.base/jdk.internal.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
        at java.base/java.lang.reflect.Method.invoke(Method.java:566)
        at org.junit.runners.model.FrameworkMethod$1.runReflectiveCall(FrameworkMethod.java:50)
        at org.junit.internal.runners.model.ReflectiveCallable.run(ReflectiveCallable.java:12)
        at org.junit.runners.model.FrameworkMethod.invokeExplosively(FrameworkMethod.java:47)
        at org.junit.internal.runners.statements.InvokeMethod.evaluate(InvokeMethod.java:17)
        at org.junit.runners.ParentRunner.runLeaf(ParentRunner.java:325)
        at org.junit.runners.BlockJUnit4ClassRunner.runChild(BlockJUnit4ClassRunner.java:78)
        at org.junit.runners.BlockJUnit4ClassRunner.runChild(BlockJUnit4ClassRunner.java:57)
        at org.junit.runners.ParentRunner$3.run(ParentRunner.java:290)
        at org.junit.runners.ParentRunner$1.schedule(ParentRunner.java:71)
        at org.junit.runners.ParentRunner.runChildren(ParentRunner.java:288)
        at org.junit.runners.ParentRunner.access$000(ParentRunner.java:58)
        at org.junit.runners.ParentRunner$2.evaluate(ParentRunner.java:268)
        at org.junit.runners.ParentRunner.run(ParentRunner.java:363)
        at org.apache.maven.surefire.junit4.JUnit4Provider.execute(JUnit4Provider.java:252)
        at org.apache.maven.surefire.junit4.JUnit4Provider.executeTestSet(JUnit4Provider.java:141)
        at org.apache.maven.surefire.junit4.JUnit4Provider.invoke(JUnit4Provider.java:112)
        at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
        at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
        at java.base/jdk.internal.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
        at java.base/java.lang.reflect.Method.invoke(Method.java:566)
        at org.apache.maven.surefire.util.ReflectionUtils.invokeMethodWithArray(ReflectionUtils.java:189)
        at org.apache.maven.surefire.booter.ProviderFactory$ProviderProxy.invoke(ProviderFactory.java:165)
        at org.apache.maven.surefire.booter.ProviderFactory.invokeProvider(ProviderFactory.java:85)
        at org.apache.maven.surefire.booter.ForkedBooter.runSuitesInProcess(ForkedBooter.java:115)
        at org.apache.maven.surefire.booter.ForkedBooter.main(ForkedBooter.java:75)


Results :

Failed tests:   TestThatFails(com.github.jiriklepl.treemaptest.TestTreeMap): This should fail(..)

Tests run: 10, Failures: 1, Errors: 0, Skipped: 0

[INFO] ------------------------------------------------------------------------
[INFO] BUILD FAILURE
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  2.745 s
[INFO] Finished at: 2019-11-28T23:05:45+01:00
[INFO] ------------------------------------------------------------------------
[ERROR] Failed to execute goal org.apache.maven.plugins:maven-surefire-plugin:2.12.4:test (default-test) on project treemaptest: There are test failures.
[ERROR] 
[ERROR] Please refer to /mnt/z/programming/NproVyvoj-2019/06-junit/target/surefire-reports for the individual test results.
[ERROR] -> [Help 1]
[ERROR] 
[ERROR] To see the full stack trace of the errors, re-run Maven with the -e switch.
[ERROR] Re-run Maven using the -X switch to enable full debug logging.
[ERROR] 
[ERROR] For more information about the errors and possible solutions, please read the following articles:
[ERROR] [Help 1] http://cwiki.apache.org/confluence/display/MAVEN/MojoFailureException
```

```bash
(com.github.jiriklepl.treemaptest.TestTreeMap): This should fail(..)
```

[OPTIONAL] 4. Create a simple Ant script to build and run all your tests. 
   Feel free to copy-paste examples from the Ant manual or from the slides, and update them if needed.
   The build script should work as follows:
     - classpath is set up to contain all the necessary jar files and classes with your tests
     - the target "compile-tests" should compile all the unit tests that you created in task 1
     - the target "run-tests" runs all unit tests and print a summary using the XML formatter
     - the target "report" should create a HTML report of the test results from the xml output

5. Define interface Employees with the following methods in your favorite language (Java, C#, C/C++).
   List of required methods:
     int add(String name, int salary); // returns ID
     Set<Integer> getAll(); // returns a set of IDs
     String getName(int id);
     int getSalary(int id);
     void changeSalary(int id, int newSalary);
   It represents a simple database of employees.
   You do not have to create a real implementation of this interface (e.g., using an SQL database).

```java
package com.github.jiriklepl.statistics;

import java.util.*;

public class Employees {
    public Employees() {
        employees = new ArrayList<>();
    }

    private class EmployeeData {
        public EmployeeData(String newName, int newSalary) {
            name = newName;
            salary = newSalary;
        }

        public String name;
        public int salary;
    }

    public int add(String name, int salary) {
        employees.add(new EmployeeData(name, salary));
        return employees.size() - 1;
    }

    public Set<Integer> getAll() {
        Set<Integer> ret = new HashSet<Integer>();

        for (int i = 0; i < employees.size(); ++i) {
            ret.add(i);
        }

        return ret;
    }

    public String getName(int id) {
        return employees.get(id).name;
    }

    public int getSalary(int id) {
        return employees.get(id).salary;
    }

    public void changeSalary(int id, int newSalary) {
        employees.get(id).salary = newSalary;
    }

    private ArrayList<EmployeeData> employees;
}
```

6. Define and implement the class Statistics that satisfies the following requirements. Use your favorite language (Java, C#, C/C++).
   Constructor should have an argument of type Employees that represents an instance to be used inside the class.
   List of required methods that you should implement:
     int computeAverageSalary();
     int getMinSalary();
     void printSalariesByName(); // prints the list of pairs <name, salary> that is sorted by employee names

```java
package com.github.jiriklepl.statistics;

import java.io.Console;
import java.util.*;

public class Statistics {
    public Statistics(Employees newEmployees) {
        employees = newEmployees;
    }

    public int computeAverageSalary() {
        int sum = 0;
        Set<Integer> ids = employees.getAll();
        for (int i : ids) {
            sum += employees.getSalary(i);
        }

        return sum / ids.size();
    }

    public int getMinSalary() {
        Set<Integer> ids = employees.getAll();
        if (ids.isEmpty()) {
            return 0;
        }

        Integer min = null;

        for (int i : ids) {
            int salary = employees.getSalary(i);

            if (min == null || salary < min) {
                min = salary;
            }
        }

        return min;
    }

    public void printSalariesByName() {
        Map<String, Integer> name_salary = new TreeMap<>();

        Set<Integer> ids = employees.getAll();

        for (int i : ids) {
            int salary = employees.getSalary(i);
            String name = employees.getName(i);

            name_salary.put(name, salary);
        }

        for (String name : name_salary.keySet()) {
            System.out.printf("%s: %d\n", name, name_salary.get(name));
        }
    }

    private Employees employees;
}
```

7. Write unit tests for methods of the Statistics class in any unit testing framework that is available for the selected language.
   In the unit tests, properly capture (model) the dependency on the instance of Employees given to the constructor.
   Define reasonable properties for the three methods and check whether they hold (using assertions in your unit tests).
   You should create unit tests that really check behavior of methods in the Statistics class (i.e., empty stub implementation of the Employee interface is not sufficient).

```java
package com.github.jiriklepl.statistics;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Unit test for Statistics
 */
public class TestStatistics {
    @Test
    public void MinSalary() {
        Employees employees = TestFixture.initEmployees();
        Statistics statistics = new Statistics(employees);

        assertTrue(statistics.getMinSalary() == 30000);
    }

    @Test
    public void AverageSalaray() {
        Employees employees = TestFixture.initEmployees();
        Statistics statistics = new Statistics(employees);

        assertTrue(statistics.computeAverageSalary() == 40000);
    }
}
```

8. Submit an archive containing your tests (source code) and the build scripts along with the protocol.


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

8

(4) Jak hodnotite svoje zkusenosti s nastrojem ve srovnani s domaci ulohou?
    (1 - vsechno uz znam a umim pouzivat, 10 - vsechno jsem si prakticky vyzkousel poprve)

10

(5) Kolik casu (v minutach) vam reseni zhruba zabralo?

180

(6) Prostor pro vlastni komentare ke cviceni a domaci uloze:
