package com.github.jiriklepl.statistics;

/**
 * Fixtures for java.util.TreeMap
 */
public final class TestFixture {
    public static Employees initEmployees() {
        Employees employees = new Employees();

        employees.add("John", 30000);
        employees.add("Jack", 40000);
        employees.add("Adam", 50000);
        employees.add("Dominic", 40000);
        employees.add("David", 35000);
        employees.add("Jonathan", 45000);

        return employees;
    }
}