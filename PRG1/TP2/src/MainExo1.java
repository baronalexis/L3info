/*
 * 
 * TP2 : Codages Java
 * 
 * 
 * Exercice 1 - Tri et recherche dichotomique
 * 
 *  
 * Alexis Baron
 *  
 * 
 * Groupe 3.2
 * 
 */


public class MainExo1 {

	public static int [] inputTabValues() {
		
		int size;
		
		Ecriture.ecrireString("Entrer la taille du tableau désirée (entre 1 et 50):\n");
		
		size = Lecture.lireInt();
		
		while(size < 1 || size > 51 ) {

			Ecriture.ecrireString("La taille du tableau doit être comprise entre 1 et 50 !, Veuillez entrer la taille du tableau de nouveau. \n");
			size = Lecture.lireInt();

		}

		int [] tab = new int[size];
		
		Ecriture.ecrireString("Entrer les valeurs du tableau de taille " + size + ":\n");

		
		for(int i = 0; i < size; i++) {
			Ecriture.ecrireString("Valeur " + i + " :");
			tab[i] = Lecture.lireInt();
		}
		
		return tab;
	}
	
	public static void printTab(int [] tab) {
		Ecriture.ecrireString("[ ");

		for(int i = 0; i < tab.length ; i++) {
			Ecriture.ecrireInt(tab[i]);
			if(i < tab.length - 1) {
				Ecriture.ecrireString(" , ");
			}
		}
		Ecriture.ecrireString(" ]\n");
	}
	
	public static void triNaif(int [] tab) {
		
		int n = tab.length;
		
		for(int i = 0; i <= n - 2; ++i) {
			int rangMin = i;
			for(int j = i + 1; j <= n - 1; ++j) {
				if(tab[j] < tab[rangMin]) {
					rangMin = j;
				}
			}
			int aux = tab[i];
			tab[i] = tab[rangMin];
			tab[rangMin] = aux;
		}
	}
	
	public static boolean rechercheDichotomique(int a, int [] tab) {
		
		int deb = 0;
		int fin = tab.length - 1;
		int milieu = (deb + fin) / 2;
		
		while(deb <= fin && a != tab[milieu]) {
			if (a < tab[milieu]) {
				fin = milieu - 1;
			}
			else if(a > tab[milieu]) {
				deb = milieu +1;
			}
			milieu = (deb + fin) / 2;
		}
		return deb <= fin;
	}
	
	
	
	public static void main(String[] args) {
		
		int tab [] = inputTabValues();
		Ecriture.ecrireString("Tableau non trié= ");
		printTab(tab);
		triNaif(tab);
		Ecriture.ecrireString("Tableau trié = ");
		printTab(tab);
		Ecriture.ecrireString("Entrer valeur recherchée : \n");
		int a = Lecture.lireInt();
		
		if(rechercheDichotomique(a, tab)) {
			Ecriture.ecrireString("La valeur " + a + " a été trouvée.\n");
		}
		else {
			Ecriture.ecrireString("La valeur " + a + " n'a pas été trouvée.\n");
		}
	}
}
