/*
 * 
 * TP2 : Codages Java
 * 
 * 
 * Exercice 2 - Recherche de nombres mystérieux
 * 
 *  
 * Alexis Baron
 *  
 * 
 * Groupe 3.2
 * 
 */

import java.util.ArrayList;


public class MainExo2 {
	
	
	public static void printTab(boolean [] tab) {
		Ecriture.ecrireString("[ ");

		for(int i = 0; i < tab.length ; i++) {
			Ecriture.ecrireInt(tab[i] ? 1 : 0);
			if(i < tab.length - 1) {
				Ecriture.ecrireString(" , ");
			}
		}
		Ecriture.ecrireString(" ]\n");
	}
	
	
	public static boolean rechercheMysterieuse(int val) {
		
		boolean [] tab = new boolean[10];
		
		int val2 = (int) Math.pow(val, 2);
		int val3 = (int) Math.pow(val, 3);
		
		String mot = String.valueOf(val2) + String.valueOf(val3);
		
		for(int j = 0; j < mot.length(); j++) {
			if(tab[Character.getNumericValue(mot.charAt(j))])
				return false;
			else
				tab[Character.getNumericValue(mot.charAt(j))] = true;


		}
		
		for(int k = 0; k < tab.length; k++) {
			if (tab[k] == false ) {
				return false;
			}
		}
			
		return true;
	}
	
	
	
	public static void main(String[] args) {
		
		int n;
		ArrayList trouve = new ArrayList();
		
		Ecriture.ecrireString("Entrer la valeur max de n :\n");
		
		n = Lecture.lireInt();
		
		for(int i = 0; i <= n; i++) {
			if(rechercheMysterieuse(i)) {
				trouve.add(i);
			}
		}
		Ecriture.ecrireString("Terminé !\n");
		
		Ecriture.ecrireString("Nombres mystérieux :\n");
		
	    for(int i = 0; i < trouve.size(); i++)
	    {
	      Ecriture.ecrireInt((int) trouve.get(i));
	      Ecriture.ecrireString("\n");
	    }   
	}
}
