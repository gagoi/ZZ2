package playground;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import org.junit.Test;

public class CollectionTypes {

    @Test
    public void testArray() {

        String[] strings = new String[4];
        strings[0] = "a";
        strings[0] = "a";
        strings[2] = "b";
        strings[3] = "c";

        System.out.println(strings[0]);
        System.out.println(strings[1]);
        System.out.println(strings[2]);
        System.out.println(strings[3]);
    }

    @Test
    public void testArrayList() {
        ArrayList<String> strings = new ArrayList<>();
        strings.add("a");
        strings.add("a");
        strings.add("b");
        strings.add("c");

        System.out.println(strings.get(0));
        System.out.println(strings.get(1));
        System.out.println(strings.get(2));
        System.out.println(strings.get(3));
    }

    @Test
    public void testHashSet() {
        HashSet<String> strings = new HashSet<>();
        strings.add("a");
        strings.add("a");
        strings.add("b");
        strings.add("c");

        System.out.println(strings);
    }

    @Test
    public void testHashMap1() {
        HashMap<Integer, String> strings = new HashMap<>();
        strings.put(1, "a");
        strings.put(2, "b");
        strings.put(3, "c");

        strings.put(1, "A");

        System.out.println(strings);
    }

    @Test
    public void testHashMap2() {
        HashMap<Integer, String> strings = new HashMap<>();
        strings.put(1, "a");
        strings.put(2, "b");
        strings.put(3, "c");

        System.out.println(strings.get(1));
        System.out.println(strings.get(2));
        System.out.println(strings.get(3));
    }
}
