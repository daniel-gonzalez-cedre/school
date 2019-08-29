// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013
// Codeforces 226: Bear & Strings

import java.util.Scanner;

public class B
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		String s = scanner.next();
		int pairs = 0;
		//int counter = 0;
		int lastBear = -1;
		
		for(int i = 0; i < s.length() - 3; i++)
		{
			if(s.substring(i, i + 4).equals("bear"))
			{
				pairs = pairs + ((i - lastBear) * (s.length() - (i + 3)));
				lastBear = i;
				//counter = counter + 1;
			}
		}
		
		System.out.println(pairs);
	}
}
