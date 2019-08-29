// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013
// Codeforces 226: Bear & Raspberry

import java.util.Scanner;

public class A
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		int days = scanner.nextInt();
		int rent = scanner.nextInt();
		int prices[] = new int[days];
		int max = 0;
		
		for(int i = 0; i < days; i++)
			prices[i] = scanner.nextInt();
		
		for(int i = 0; i < days - 1; i++)
			if(prices[i] - prices[i + 1] > max && prices[i] - prices[i + 1] > rent)
				max = prices[i] - prices[i + 1];
		
		if(max != 0)
			System.out.println(max - rent);
		else
			System.out.println(max);
	}
}
