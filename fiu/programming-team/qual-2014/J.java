// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Spring 2014

import java.util.Scanner;

public class J
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);

		int n = scanner.nextInt();

		while(n != 0)
		{
			Unit[] units = new Unit[n];

			for(int i = 0; i < n; i++)
				units = new Unit(scanner.next());

			for(int i = 0; i < n - 1; i++)
			{
				String v = scanner.next();
				scanner.next();
				int factor = scanner.nextInt();
				String w = scanner.next();

				for(int j = 0; j < n; j++)
				{
					if(units[j].equals(w))
					{
						units[j].relative = v;
						units[j].carry = factor;
						units[j].flag = false;
						break;
					}
				}
			}

			n = scanner.nextInt();
		}
	}
}

class Unit implements Comparable<Unit>
{
	String unit;
	String relative;
	int carry;
	int factor;
	boolean flag;

	public Unit(String unit)
	{
		this.unit = unit;
		this.relative = "";
		carry = 1;
		factor = 1;
		flag = true;
	}

	public boolean equals(Unit unit)
	{
		return this.unit.equals(unit.unit);
	}

	public int compareTo(Unit unit)
	{
		return this.factor - unit.factor;
	}
}
