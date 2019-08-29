// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Spring 2014

import java.util.Scanner;

public class frog{
	public static void main(String args[]){
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		String output = "";

		for(int day = 1; day <= n; day++){
			int counter = 0;
			int cells = scanner.nextInt();
			int jump = scanner.nextInt();
			String temp = scanner.next();
			char[] line = temp.toCharArray();

			output = output + "Day #" + day + "\n";
			output = output + cells + " " + jump + "\n";
			output = output + temp + "\n";

			for(int i = 0; i < line.length; i++){
				if(i + jump >= line.length - 1)
					break;

				if(line[i + jump] == '.'){
					counter = counter + 1;
					i = i + jump + 1;
				} else {
					int k = i;

					for(int j = i + jump; j > i; j--){
						if(line[j] == '.'){
							i = j;
							counter = counter + 1;
							break;
						}
					}
					
					if(k == i){
						counter = -1;
						break;
					}
				}
			}

			counter = counter + 1;
			output = output + counter + "\n\n";
		}

		System.out.println(output);
	}
}
