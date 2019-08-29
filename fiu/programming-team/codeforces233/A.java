// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013

import java.util.Scanner;

public class A
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		
		int n = scanner.nextInt();
		int p = scanner.nextInt();
		int k = scanner.nextInt();
		
		if(p - k > 1)
			System.out.print("<< ");
		
		for(int i = k; i > 0; i--)
			if(p - i > 0)
				System.out.print(p - i + " ");
		
		System.out.print("(" + p + ") ");
		
		for(int i = 1; i <= k; i++)
			System.out.print(p + i + " ");
		
		if(p + k < n)
			System.out.print(">>");
	}
}
