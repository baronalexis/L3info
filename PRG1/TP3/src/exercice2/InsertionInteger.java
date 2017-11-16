package exercice2;
/* 
 * 
 * Groupe 3.2: 	Foucheur Alexandre
 * 				Baron Alexis			 	
 *  
 *  
 *  TP3 - ALGORITHIMIQUES ET CODAGES
 *  
 * 	Exercice 2 - Classement par insertion
 *  
 * 
 */


import java.util.Scanner;

public class InsertionInteger {
	
	private static final int SIZE_MAX = 10;
	private int size = 0;
	private int[] array = new int[SIZE_MAX];
	
	
	/*
	 * @return copie de la partie remplie du tableau.
	 */
	
	public int[] toArray() {
		int[] copy = new int[this.size];
		for (int i = 0; i < copy.length; i++) {
			copy[i] = array[i];
		}
		return copy;		
	}
	
	
	public boolean insert(int value) {
		
		//V�rifie si la valeur entr�e n'est pas d�j� dans le tableau.
		boolean ok = true;
		for (int i = 0; i < size; i++) {
			if (array[i] == value) {
				ok = false;
			}
		}
		
		/* Retourne false si la valeur est d�j� dans le tableau ou 
		 * si le tableau est d�j� rempli.
		 */
		if (!ok  || size == SIZE_MAX) {
			return false;
		}
		/*
		 * On augmente la taille du tableau rempli de 1 et on place la valeur dans la derni�re
		 * case du tableau.
		 */
		else {
			size++;
		    array[size-1] = value;
		    
		    /*
		     * On effectue un tri par insertion
		     */
		    int i;
		    /*
		     * On positionne i sur la case contenant la premi�re valeur sup�rieure � la valeur entr�e.
		     */
		      for(i=0;i<array.length-1;i++){
		        if(array[i]>value) {
		          break;
		        }
		      }
		      /*
		       * On d�place les cases de i+1 � i+2.
		       */
		      for(int k=array.length-2; k>=i; k--){
		    	  array[k+1]=array[k];            
		      }
		      /*
		       * On ins�re la valeur � la case i.
		       */
		      array[i]=value;

		      System.out.println(toString());

			return true;
		}
	}
	
	public void createArray(Scanner scanner) {
		/*
		 * Demande � l'utilisateur de saisir les valeurs de son tableau puis les ins�re.
		 */
		System.out.println("Veuillez saisir un nombre :");

		int value = scanner.nextInt();
		while (value != -1) {
			insert(value);
			System.out.println("Veuillez saisir un nombre :");
			value = scanner.nextInt();
		}			
	}
	
	/*
	 * Retourne une string d�crivant le tableau.
	 */
	@Override
	public String toString() {
		String string = "";
		string += "[ ";
			
		for(int i = 0; i < size ; i++) {
			string += array[i];

			if(i < size - 1) {
				string += " , ";
			}
		}
		string +=" ]\n";
		
		return string;
	}
	
	public static void main (String[] args) {
		
		InsertionInteger ii = new InsertionInteger();
		
		Scanner sc = new Scanner(System.in);
		
		ii.createArray(sc);
		
		System.out.println(ii.toString());
		
	
	}
}