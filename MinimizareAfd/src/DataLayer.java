import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;

public class DataLayer {
	private int statesNumber;
	private ArrayList<String> states = new ArrayList<String>();
	private String initialState;
	private int finalStatesNumber;
	private ArrayList<String> finalStates = new ArrayList<String>();;
	private int NoSymbols;
	private ArrayList<String> symbols = new ArrayList<String>();
	private ArrayList<String> paths = new ArrayList<String>();
	String[][] pairTable;
	ArrayList<ArrayList<String>> eqStates = new ArrayList<ArrayList<String>>();
	public DataLayer(String data, String path) {
		readData(data);
		readPaths(path);
		
		

	}
	
	public void minimizare(){
		deleteInaccessibleStates();
		
		buildTableState();
		printTableState();
		
		getEquivalentStates();
		printEqStates();
		
		setNewValues();
		System.out.println("New States: " + states.toString());
	}

	// Read data about the system states
	public void readData(String filename) {
		File datafile = new File(filename);
		try {
			Scanner sc = new Scanner(datafile);
			statesNumber = Integer.parseInt(sc.nextLine());

			splitWord(states, sc);

			initialState = sc.nextLine();

			finalStatesNumber = Integer.parseInt(sc.nextLine());
			splitWord(finalStates, sc);

			NoSymbols = Integer.parseInt(sc.nextLine());
			splitWord(symbols, sc);

			sc.close();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}

	// Read information about system paths
	public void readPaths(String filename) {
		File pathFile = new File(filename);
		try {
			Scanner sc = new Scanner(pathFile);
			while (sc.hasNextLine()) {
				paths.add(sc.nextLine());
			}
			sc.close();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}

	// Checks whether a word belongs the language
	public boolean checkWord(String word) {
		String currentState = initialState;
		String checkword = word;
		while (checkword.length() > 0) {
			int ok = 0;
			for (String item : paths) {
				ArrayList<String> itemwords = returnWords(item);
				if (checkword.length() == 0 && itemwords.get(0).equals(currentState)
						&& itemwords.get(1).equals(checkword)) {
					checkword = null;
					currentState = itemwords.get(2);
					ok = 1;
					break;
				} else
					if (itemwords.get(0).equals(currentState) && itemwords.get(1).equals(checkword.substring(0, 1))) {
					checkword = checkword.substring(1);
					currentState = itemwords.get(2);
					ok = 1;
					break;
				}
			}
			System.out.println(checkword);
			if (ok == 0) {
				return false;
			}
		}
		for (String state : finalStates) {
			if (currentState.equals(state)) {
				return true;
			}
		}
		return false;
	}

	/**
	 * @return the statesNumber
	 */
	public int getStatesNumber() {
		return statesNumber;
	}

	/**
	 * @param statesNumber
	 *            the statesNumber to set
	 */
	public void setStatesNumber(int statesNumber) {
		this.statesNumber = statesNumber;
	}

	/**
	 * @return the states
	 */
	public ArrayList<String> getStates() {
		return states;
	}

	/**
	 * @param states
	 *            the states to set
	 */
	public void setStates(ArrayList<String> states) {
		this.states = states;
	}

	/**
	 * @return the initialState
	 */
	public String getInitialState() {
		return initialState;
	}

	/**
	 * @param initialState
	 *            the initialState to set
	 */
	public void setInitialState(String initialState) {
		this.initialState = initialState;
	}

	/**
	 * @return the finalStatesNumber
	 */
	public int getFinalStatesNumber() {
		return finalStatesNumber;
	}

	/**
	 * @param finalStatesNumber
	 *            the finalStatesNumber to set
	 */
	public void setFinalStatesNumber(int finalStatesNumber) {
		this.finalStatesNumber = finalStatesNumber;
	}

	/**
	 * @return the finalStates
	 */
	public ArrayList<String> getFinalStates() {
		return finalStates;
	}

	/**
	 * @param finalStates
	 *            the finalStates to set
	 */
	public void setFinalStates(ArrayList<String> finalStates) {
		this.finalStates = finalStates;
	}

	/**
	 * @return the noSymbols
	 */
	public int getNoSymbols() {
		return NoSymbols;
	}

	/**
	 * @param noSymbols
	 *            the noSymbols to set
	 */
	public void setNoSymbols(int noSymbols) {
		NoSymbols = noSymbols;
	}

	/**
	 * @return the symbols
	 */
	public ArrayList<String> getSymbols() {
		return symbols;
	}

	/**
	 * @param symbols
	 *            the symbols to set
	 */
	public void setSymbols(ArrayList<String> symbols) {
		this.symbols = symbols;
	}

	// Adds into a string list words from a phrase that was read from a scanner
	private void splitWord(ArrayList<String> list, Scanner sc) {
		String sep = new String(".,;!? ");
		String auxStates = sc.nextLine();
		StringTokenizer st = new StringTokenizer(auxStates, sep);
		while (st.hasMoreElements()) {
			list.add(st.nextElement().toString());
		}
	}

	private ArrayList<String> returnWords(String item) {
		String sep = new String(".,;!? ");
		ArrayList<String> auxlist = new ArrayList<String>();
		StringTokenizer st = new StringTokenizer(item, sep);
		while (st.hasMoreElements()) {
			auxlist.add(st.nextElement().toString());
		}
		return auxlist;
	}

	public boolean isAccesible(String st) {
		for (String item : paths) {
			ArrayList<String> itemwords = returnWords(item);
			if ((initialState.equals(st) == false) && st.equals(itemwords.get(itemwords.size() - 1))) {
				return true;
			}
		}
		return false;
	}

	public boolean isFinalState(String st) {
		for (String item : finalStates) {
			if (st.equals(item)) {
				return true;
			}
		}
		return false;
	}

	public void deleteInaccessibleStates() {
		ArrayList<String> aux = new ArrayList<String>();
		aux.add(initialState);
		for (String st : states) {
			if (isAccesible(st)) {
				aux.add(st);
			}
		}
		states = aux;
		statesNumber = states.size();
	}

	public void buildTableState() {
		pairTable = new String[states.size()][states.size()];
		for (int i = 0; i < states.size(); i++) {
			for (int j = 0; j < states.size(); j++) {
				if (i == j) {
					pairTable[i][j] = states.get(i);
				} else {
					if (i > j) {
						if (isFinalState(states.get(i)) && (isFinalState(states.get(j)) == false)
								|| (isFinalState(states.get(i)) == false) && isFinalState(states.get(j))) {
							pairTable[i][j] = "x";
						} else {
							pairTable[i][j] = "-1";
						}
					}
				}
			}
		}
		markPair();
	}

	public void markPair() {
		String[][] auxtable = pairTable;
		int ok = 0;
		for (int i = 0; i < states.size(); i++) {
			for (int j = 0; j < states.size(); j++) {
				if (i > j && auxtable[i][j].equals("-1")) {
					if (checkPair(i, j, auxtable)) {
						pairTable[i][j] = "x";
						ok = 1;
					}
				}
			}
		}
		if (ok == 1) {
			markPair();
		}

	}

	public boolean checkPair(int i, int j, String[][] auxtable) {
		for (String symb : symbols) {
			String iState = null;
			String jState = null;
			String istartwith = String.format(states.get(i) + " " + symb);
			String jstartwith = String.format(states.get(j) + " " + symb);
			for (String item : paths) {
				if (item.startsWith(istartwith)) {
					iState = returnWords(item).get(2);
				} else {
					if (item.startsWith(jstartwith)) {
						jState = returnWords(item).get(2);
					}
				}
			}
			if (iState != null && jState != null) {
				int x = Integer.valueOf(iState);
				int y = Integer.valueOf(jState);
				if (x > y && auxtable[x][y].equals("x")) {
					return true;
				}
			}
		}
		return false;
	}

	public void getEquivalentStates() {
		for (int i = 0; i < states.size(); i++) {
			ArrayList<String> aux = new ArrayList<String>();
			for (int j = 0; j < states.size(); j++) {
				if (i >= j && pairTable[i][j].equals("-1")) {
					if (checkForEq(i, j) == false) {
						aux.add(states.get(j));
						aux.add(states.get(i));
					}
				}
			}
			if (aux.size() > 0) {
				eqStates.add(aux);
			}
		}

	}

	public boolean checkForEq(int i, int j) {
		for (ArrayList<String> eqstates : eqStates) {
			for (String state : eqstates) {
				if (state.equals(states.get(i))) {
					eqstates.add(states.get(j));
					return true;
				} else {
					if (state.equals(states.get(j))) {
						eqstates.add(states.get(i));
						return true;
					}
				}
			}
		}
		return false;
	}

	public void printTableState() {
		for (int i = 0; i < getStatesNumber(); i++) {
			for (int j = 0; j < getStatesNumber(); j++) {
				if (i >= j) {
					System.out.print(pairTable[i][j] + " ");
				}
			}
			System.out.println();
		}
	}

	public void printEqStates() {
		if (eqStates.size() > 0) {
			System.out.println("Equivalent pair states: " + eqStates.size());
			for (ArrayList<String> eqstates : eqStates) {
				System.out.print(eqstates.toString());
			}
		}
		System.out.println();
	}

	public void setNewValues() {
		for (ArrayList<String> eqst : eqStates) {
			for (int i = 1; i < eqst.size(); i++) {
				for (int j = 0; j < states.size(); j++) {
					if (eqst.get(i).equals(states.get(j))) {
						states.remove(j);
						break;
					}
				}
			}
		}
		updatePaths();
		statesNumber = states.size();
	}

	public void updatePaths() {
		ArrayList<String> auxpath = new ArrayList<String>();
		for (String item : states) {
			for (String path : paths) {
				ArrayList<String> wd = returnWords(path);
				if (wd.get(0).equals(item)) {
					auxpath.add(path);
				}
			}
		}
		paths = auxpath;
		for(int i=0; i< eqStates.size(); i++){
			for(int j=1; j< eqStates.get(i).size(); j++){
				for (int k =0 ; k <paths.size(); k++) {
					ArrayList<String> wd = returnWords(paths.get(k));
					if (wd.get(0).equals(eqStates.get(i).get(j))) {
						wd.set(0, eqStates.get(i).get(0));
					}
					if (wd.get(2).equals(eqStates.get(i).get(j))) {
						wd.set(2, eqStates.get(i).get(0));
					}
					String path = String.format(wd.get(0)+ " "+ wd.get(1) + " " + wd.get(2));
					paths.set(k, path);
				}
			}
		}
		
		
		try {
			FileWriter pt = new FileWriter("newtransitions.txt");
			for (String item : paths){
				pt.write(item + "\n");
			}
			pt.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
		
	}
}
