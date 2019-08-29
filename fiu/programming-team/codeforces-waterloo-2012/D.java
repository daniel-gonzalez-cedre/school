// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013
// Codeforces Waterloo 2012: Course Scheduling

import java.util.Scanner;
import java.util.TreeMap;
import java.util.TreeSet;

public class D 
{
    public static void main(String args[])
    {
        Scanner scanner = new Scanner(System.in);
        TreeMap<String, TreeSet<String>> map = new TreeMap<String, TreeSet<String>>();
        //TreeMap<Integer, MyString> temp = new TreeMap<>();
        
        int n = scanner.nextInt();
        
        for(int i = 0; i < n; i++)
        {
            String name = scanner.next() + " " + scanner.next();
            String course = scanner.next();
            
            if(!map.containsKey(course))
            {
                TreeSet<String> set = new TreeSet<String>();
                set.add(name);
                map.put(course, set);
            } else {
                if(!map.get(course).contains(name))
                    map.get(course).add(name);
            }
        }
        
        for(String x : map.keySet())
            System.out.println(x + " " + map.get(x).size());
    }
}
