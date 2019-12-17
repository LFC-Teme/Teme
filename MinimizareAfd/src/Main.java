import java.io.File;
import java.util.Scanner;

public class Main {
	public static void showTestedWords(DataLayer alg) {
		File filename = new File("wordsfortest.txt");	
		try {
			Scanner sc = new Scanner(filename);
			while (sc.hasNext()) {
				String word = sc.nextLine();
				System.out.println("Tested word is " + word);
				if (alg.checkWord(word)) {
					System.out.println("The inserted word is correct \n");
				} else {
					System.out.println("The inserted word is not correct \n");
				}
			}
			sc.close();
		} catch (Exception e) {
			System.out.println(e.getMessage());

		}
	}

	public static void main(String[] args) {
		String data = new String("data.txt");
		String path = new String("transitions.txt");

		DataLayer alg = new DataLayer(data, path);
		
		System.out.println("Inainte de minimizare: ");
		showTestedWords(alg);
		
		alg.minimizare();
		
		System.out.println("Dupa minimizare: ");
		showTestedWords(alg);
	}
}
