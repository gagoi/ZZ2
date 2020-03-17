package playground;

import org.apache.commons.collections4.bag.HashBag;
import org.junit.Test;

public class Dependencies {

    @Test
    public void testNewDepedency() {
        HashBag<String> bag = new HashBag<>();
        bag.add("element", 30);
        bag.stream().forEach(System.out::println);
    }
}
