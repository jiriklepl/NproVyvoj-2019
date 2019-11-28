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
