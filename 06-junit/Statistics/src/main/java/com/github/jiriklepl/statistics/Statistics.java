package com.github.jiriklepl.statistics;

import java.util.*;

public class Statistics {
    public Statistics(Employees newEmployees) {
        employees = newEmployees;
    }

    int computeAverageSalary() {
        int sum = 0;
        Set<Integer> ids = employees.getAll();
        for (int i : ids) {
            sum += employees.getSalary(i);
        }

        return sum / ids.size();
    }

    int getMinSalary() {
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

    void printSalariesByName() {
        // here we print salaries
    }

    Employees employees;
}
