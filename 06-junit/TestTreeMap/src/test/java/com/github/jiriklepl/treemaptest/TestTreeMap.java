package com.github.jiriklepl.treemaptest;

import org.junit.Test;
import java.util.TreeMap;

import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.*;

/**
 * Unit test for java.util.TreeMap
 */
public class TestTreeMap {
    @Test
    public void AddNewKeyValue() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.put("NewKey", 7);
        assertTrue(map.size() == 8);
    }
    
    @Test
    public void AddPresentKeyValue() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.put("FirstKey", 7);
        assertTrue(map.size() == 7);
        assertTrue(map.get("FirstKey") == 7);
    }
    
    @Test
    public void RemovePresentKeyValue() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.remove("FirstKey");
        assertTrue(map.size() == 6);
    }
    
    @Test
    public void RemoveNewKeyValue() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        map.remove("FirstypoKey");
        assertTrue(map.size() == 7);
    }
    
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
    
    @Test
    public void GetKey() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        Integer i = map.get("FirstKey");
        assertTrue(i == 0);
    }
    
    @Test
    public void GetNotPresentKey() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        Integer i = map.get("FirstypoKey");
        assertTrue(i == null);
    }
    
    @Test
    public void ContainsKeyBoth() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        assertTrue(map.containsKey("FirstKey"));
        assertTrue(!map.containsKey("FirstypoKey"));
    }
    
    @Test
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
    
    @Test
    public void TestThatFails() {
        TreeMap<String, Integer> map = TestFixture.initTreeMap();
        assertThat("This should fail", map.isEmpty(), is(true));
    }
}
