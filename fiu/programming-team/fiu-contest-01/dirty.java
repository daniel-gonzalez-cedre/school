// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Spring 2014

import java.util.Scanner;

public class dirty{
	public static void main(String args[]){
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		String output = "";

		for(int m = 1; m <= n; m++){
			int counter = 0;
			int c = scanner.nextInt();
			int s = scanner.nextInt();
			int d = scanner.nextInt();
			boolean table = true;

			while(s > 0 || c > 0){
				if(table){
					if(s == 0 && d > 0){
						c = c - 1;
						s = s + 1;
						table = false;
					}

					if(s % 2 == 1)
						table = false;
				}

				if(!table){
					if(s % 2 == 0){
						if(s > 0){
							s = s - 1;
						} else {
							c = c - 1;
							s = s + 1;
						}
					}
				}

				if(c > 0){
					c = c - 1;
					s = s + 1;
					counter = counter + 1;
				} else if(s > 0) {
					s = s - 1;
					counter = counter + 1;
				}
			}

			output = output + "Scenario #" + m + ": " + counter + "\n";
		}

		System.out.println(output.substring(0, output.length() - 1));
	}
}
