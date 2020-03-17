package playground;

import org.junit.Test;

import java.util.*;
import java.util.stream.Collectors;

public class CollectionLoop {

    public static class MyObject {

        Integer id;
        String name;

        MyObject(Integer id, String name) {
            this.id = id;
            this.name = name;
        }

        public String toString() {
            return String.format("%s (%d)", name, id);
        }
    }

    public static List<MyObject> myObjects = Arrays.asList(
        new MyObject(1, "un"),
        new MyObject(2, "deux"),
        new MyObject(3, "trois"),
        new MyObject(4, "quatre"),
        new MyObject(5, "cinq"),
        new MyObject(6, "six"));

    @Test
    public void testForLoop1() {
        for (MyObject myObject : myObjects) {
            System.out.println(myObject);
        }
    }

    @Test
    public void testForLoop2() {
        for (int i = 0; i < myObjects.size(); i++) {
            MyObject myObject = myObjects.get(i);
            System.out.println(myObject);
        }
    }

    @Test
    public void testForLoop3() {
        myObjects.forEach(myObject -> System.out.println(myObject));
    }

}
