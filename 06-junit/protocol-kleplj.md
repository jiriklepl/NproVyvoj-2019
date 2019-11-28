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
     - adding new mapping with a key equal to some already present mapping
     - removing some element (mapping) already present in the map
     - attempt to remove some element (key) not present in the map
     - removing all elements from the map and checking for emptiness
     - getting the value associated with a specific key
     - attempt to get a value for a key not present in the map
     - checking existence of a mapping for a given key
     - iterating over sorted keys (from the lowest to the highest)

   Always verify the current state of the map (content, size) and, if necessary, also the state of the associated iterator.

   Note that the Java package of your test classes must be different than "java.util", because application programs cannot modify or extend this package.
   This is not a problem since your tests will be calling only the public methods (you will make black-box tests).

   Follow the recommended practices for writing unit tests.

2. Build all tests for TreeMap and verify that they pass.
   Run tests from the command line, either by calling the appropriate runner class or use the "main" method in your test class (paste the command and test output here).

3. Add another test for TreeMap that fails and prints a custom error message.
   For example, you can assert that the map has a key-value mapping which it does not really have.
   Run the tests and paste the output here. 
   In the output, mark the line of the output that contains the custom error message, and mark the line that identifies the place in the test code that has failed.

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

6. Define and implement the class Statistics that satisfies the following requirements. Use your favorite language (Java, C#, C/C++).
   Constructor should have an argument of type Employees that represents an instance to be used inside the class.
   List of required methods that you should implement:
     int computeAverageSalary();
     int getMinSalary();
     void printSalariesByName(); // prints the list of pairs <name, salary> that is sorted by employee names

7. Write unit tests for methods of the Statistics class in any unit testing framework that is available for the selected language.
   In the unit tests, properly capture (model) the dependency on the instance of Employees given to the constructor.
   Define reasonable properties for the three methods and check whether they hold (using assertions in your unit tests).
   You should create unit tests that really check behavior of methods in the Statistics class (i.e., empty stub implementation of the Employee interface is not sufficient).

8. Submit an archive containing your tests (source code) and the build scripts along with the protocol.


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
 
