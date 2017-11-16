package exercice1;
/* 
 * 
 * Groupe 3.2: 	Foucheur Alexandre
 * 				Baron Alexis			 	
 *  
 *  
 *  TP3 - ALGORITHIMIQUES ET CODAGES
 *  
 * 	Exercice 1 - Suite des fourmis 
 *  
 * 
 */


public class Fourmis
{
 
public static String next(String chaine){
		
		/* Initialisation de la variable qui contiendra la chaine u+1
		 * Et intialisation du compteur.
		 */
		String chaineFinale = "";
		int counter = 0;
		
		
		//Parcours la chaine d'origine
		for (int i = 0; i < chaine.length(); i++) {
			
			/* 
			 * Si le compteur est supérieur à 1, vérifie si toute la chaine d'origine a été vérifiée dans la 2eme boucle for,
			 * Si c'est le cas toute la chaine a été parcourue, on sort de la boucle. 
			 * 
			 * Sinon on replace j a l'index sur lequel il s'est arreté précédement et on réinitialise le compteur à  0.
			 * 
			 * Sinon le compteur est à  1, la boucle j reprend à  j+1.
			 * 
			 */
			if(counter > 1){
				if((i + counter) > chaine.length()){
					break;
				}
				else{
					i += counter - 1;	
					counter = 0;
				}
			}
			else{
				counter = 0;
			}
			
			
			//Le character que l'on vérifie.
			char workingChar = chaine.charAt(i);
		
			//Parcours la chaine d'origine afin de verifier le nombre d'occurences du workingChar à la suite.
			for (int j = i; j < chaine.length(); j++) {
				
			   /* Compte le nombre de répétitions du workingChar
				* Sinon sort de la boucle, le compteur contient alors le nombre de répétitions du workingChar.
				*/
				if(workingChar == chaine.charAt(j)){
					counter += 1;
				}
				else{
					j = chaine.length();
				}
			}
			//Chaine finale u+1, incrémentée au fur et à  mesure des vérifications.
			chaineFinale += (counter + String.valueOf(workingChar));
		}
			
		return chaineFinale;
	}
  
  
  public static void main (String[] args) {
		String string = "1";
		System.out.println(string);

		/*
		 * Affiche les 10 premiers termes de la suite
		 */
		
		for (int i=0;i<10;i++) {
			string = next(string);
			System.out.println(string);
		}
	}
 
}

