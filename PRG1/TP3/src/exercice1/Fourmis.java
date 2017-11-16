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
			 * Si le compteur est sup�rieur � 1, v�rifie si toute la chaine d'origine a �t� v�rifi�e dans la 2eme boucle for,
			 * Si c'est le cas toute la chaine a �t� parcourue, on sort de la boucle. 
			 * 
			 * Sinon on replace j a l'index sur lequel il s'est arret� pr�c�dement et on r�initialise le compteur � 0.
			 * 
			 * Sinon le compteur est � 1, la boucle j reprend � j+1.
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
			
			
			//Le character que l'on v�rifie.
			char workingChar = chaine.charAt(i);
		
			//Parcours la chaine d'origine afin de verifier le nombre d'occurences du workingChar �la suite.
			for (int j = i; j < chaine.length(); j++) {
				
			   /* Compte le nombre de r�p�titions du workingChar
				* Sinon sort de la boucle, le compteur contient alors le nombre de r�p�titions du workingChar.
				*/
				if(workingChar == chaine.charAt(j)){
					counter += 1;
				}
				else{
					j = chaine.length();
				}
			}
			//Chaine finale u+1, incr�ment�e au fur et � mesure des v�rifications.
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

