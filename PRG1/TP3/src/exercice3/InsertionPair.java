package exercice3;
/* 
 * 
 * Groupe 3.2: 	Foucheur Alexandre
 * 				Baron Alexis			 	
 *  
 *  
 *  TP3 - ALGORITHIMIQUES ET CODAGES
 *  
 * 	Exercice 3 - Classement des doublets par insertion
 *  
 * 
 */


import java.util.Scanner;
import java.io.File;



public class InsertionPair {
	
	private static int SIZE_MAX = 10;
	private int size;
	private Pair[] array = new Pair[SIZE_MAX];
	private static Scanner input;
	
	public boolean insert(Pair p) {
		
		//V�rifie si le couple entr� n'est pas d�j� dans le tableau.
		boolean ok = true;
		for (int i = 0; i < size; i++) {
			if (array[i].equals(p)) {
				ok = false;
			}
		}
		
		/* Retourne false si le couple est d�j� dans le tableau ou 
		 * si le tableau est d�j� rempli.
		 */
		if (!ok  || size == SIZE_MAX) {
			return false;
		}
		/*
		 * On augmente la taille du tableau rempli de 1 et on place le couple dans la derni�re
		 * case du tableau.
		 */
		else {
			size++;
		    array[size-1] = p;
		    
		    /*
		     * On effectue un tri par insertion
		     */
		    int i;
		    /*
		     * On positionne i sur la case contenant la premi�re sup�rieure � la valeur entr�e.
		     */
		      for(i=0;i<array.length-1;i++){
		        if(p.less(array[i])) {
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
		       * On ins�re le couple � la case i.
		       */
		      array[i]=p;

		      System.out.println(toString());


			
			return true;

		}
	}
	
	public void createArrayClavier(Scanner scanner) {
		/*
		 * Demande � l'utilisateur de saisir les couples de son tableau puis les ins�re.
		 */
		
		System.out.println("Veuillez saisir un couple :");
		
		System.out.println("Veuillez saisir la 1ere valeur :");


		int value1 = scanner.nextInt();
		
		System.out.println("Veuillez saisir la 2eme valeur :");
		
		int value2 = scanner.nextInt();

		while (value1 != -1) {
			
			insert(new Pair(value1, value2));
			
			System.out.println("Veuillez saisir la 1ere valeur :");
			value1 = scanner.nextInt();
			if (value1 != -1) {
				System.out.println("Veuillez saisir la 2eme valeur :");			
				value2 = scanner.nextInt();
			}
		}			
	}
	
	public void createArrayFichier(Scanner scanner) {
		/*
		 * M�me chose que createArrayClavier mais sans les informations affich�es
		 */
		
		int value1 = scanner.nextInt();
		
		
		int value2 = scanner.nextInt();

		while (value1 != -1) {
			
			insert(new Pair(value1, value2));
			
			value1 = scanner.nextInt();
			if (value1 != -1) {
				value2 = scanner.nextInt();
			}
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
			string += array[i].toString();

			if(i < size - 1) {
				string += " , ";
			}
		}
		string +=" ]\n";
		
		return string;
	}
	
	public static void main (String[] args) {
		
		Scanner sc = new Scanner(System.in);
	

		
		InsertionPair ip = new InsertionPair();
		
		System.out.println("Comment souhaitez-vous entrer vos donn�es ?\nEntrer 1 pour une entr�e clavier ou 2 pour une entr�e via fichier");
		
		int choix = sc.nextInt();
		
		while(choix != 1 && choix !=2) {
			System.out.println("Veuillez entrer 1 ou 2");
			choix = sc.nextInt();
		}
		
		if (choix == 1) {
			
			ip.createArrayClavier(sc);
			
			System.out.println(ip.toString());
		}
		else {
			try {
				System.out.println("Veuillez entrer le nom du fichier � lire");
				
	            input = new Scanner(System.in);

				
	            File file = new File(input.nextLine());
	            
	            /*
	             * On utilise le fichier renseign� comme entr�e
	             */
	
	            input = new Scanner(file);
	            
	            ip.createArrayFichier(input);			

				
			} catch(Exception e) {
				e.printStackTrace();
			}		

		}
		
	}
		

}
