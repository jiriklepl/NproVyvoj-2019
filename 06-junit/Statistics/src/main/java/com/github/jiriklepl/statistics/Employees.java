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
