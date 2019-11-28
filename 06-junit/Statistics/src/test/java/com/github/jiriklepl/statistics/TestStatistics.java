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
