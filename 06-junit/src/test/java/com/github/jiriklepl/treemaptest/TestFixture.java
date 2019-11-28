package com.github.jiriklepl.treemaptest;

import java.util.TreeMap;

/**
 * Fixtures for java.util.TreeMap
 */
public final class TestFixture {
    public static TreeMap<String, Integer> initTreeMap() {
        TreeMap<String, Integer> map = new TreeMap<String, Integer>();

        map.put("FirstKey",   0);
        map.put("SecondKey",  1);
        map.put("ThirdKey",   2);
        map.put("FourthKey",  3);
        map.put("FifthKey",   4);
        map.put("SixthKey",   5);
        map.put("SeventhKey", 6);

        return map;
    }

    public static boolean areSame(TreeMap<String, Integer> a, TreeMap<String, Integer> b) {
        return a.entrySet().equals(b.entrySet());
    }
}