package src.fr.istic.prg1.list;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;

import fr.istic.prg1.list.util.Comparison;
import fr.istic.prg1.list.util.Iterator;
import fr.istic.prg1.list.util.List;
import fr.istic.prg1.list.util.SmallSet;

/**
 * @author Micka�l Foursov <foursov@univ-rennes1.fr>
 * @version 4.0
 * @since 2015-06-15
 */

public class MySet extends List<SubSet> {

	/**
	 * Borne sup�rieure pour les rangs des sous-ensembles.
	 */
	private static final int MAX_RANG = 128;
	/**
	 * Sous-ensemble de rang maximal � mettre dans le drapeau de la liste.
	 */
	private static final SubSet FLAG_VALUE = new SubSet(MAX_RANG,
			new SmallSet());
	/**
	 * Entr�e standard.
	 */


	public MySet() {
		super();
		setFlag(FLAG_VALUE);
	}

	/**
	 * Fermer tout (actuellement juste l'entr�e standard).
	 */
	public static void closeAll() {
		TpListe.standardInput.close();
	}

	private static Comparison compare(int a, int b) {
		if (a < b) {
			return Comparison.INF;
		} else if (a == b) {
			return Comparison.EGAL;
		} else {
			return Comparison.SUP;
		}
	}

	/**
	 * Afficher � l'�cran les entiers appartenant � this, dix entiers par ligne
	 * d'�cran.
	 */
	public void print() {
		System.out.println(" [version corrigee de contenu]");
		this.print(System.out);
	}

	// //////////////////////////////////////////////////////////////////////////////
	// //////////// Appartenance, Ajout, Suppression, Cardinal
	// ////////////////////
	// //////////////////////////////////////////////////////////////////////////////

	/**
	 * @return true si le nombre saisi par l'utilisateur appartient � this,
	 *         false sinon
	 */
	public boolean contains() {
		System.out.println(" valeur cherchee : ");
		int value = readValue(TpListe.standardInput, 0);
		return this.contains(value);
	}

	/**
	 * @param value
	 *            valeur � tester
	 * @return true si valeur appartient � l'ensemble, false sinon
	 */

	public boolean contains(int value) {
		
		int rank = value / 256;
		int set = value % 256;
		
		if ((value >= 0) && (value <= 32767)) {
			Iterator<SubSet> it = this.iterator();

			while ((it.isOnFlag() == false) && (it.getValue().rank < rank)) {
				it.goForward();
			}

			if (it.getValue().rank == rank) {
				return it.getValue().set.contains(set);
			}
		}

		return false;
	}

	/**
	 * Ajouter � this toutes les valeurs saisies par l'utilisateur et afficher
	 * le nouveau contenu (arr�t par lecture de -1).
	 */
	public void add() {
		System.out.println(" valeurs a ajouter (-1 pour finir) : ");
		this.add(System.in);
		System.out.println(" nouveau contenu :");
		this.printNewState();
	}

	/**
	 * Ajouter � this toutes les valeurs prises dans is.
	 * 
	 * @param is
	 *            flux d'entr�e.
	 */
	public void add(InputStream is) {
		int value = TpListe.standardInput.nextInt();
		Iterator<SubSet> it = this.iterator();
		
		while(value != -1) {
			
			int rank = value / 256;
			int set  = value % 256;
			
			while((it.isOnFlag() == false) && (it.getValue().rank < rank)) {
				it.goForward();
			}
			
			if(it.getValue().rank == rank) {
				it.getValue().set.add(set);
			}
			else {
				SubSet subset = new SubSet(rank, new SmallSet());
				subset.set.add(set);
				it.addRight(subset);
			}
		
			value =  TpListe.standardInput.nextInt();
			
		}
		
	}

	/**
	 * Ajouter value � this.
	 * 
	 * @param value
	 *            valuer � ajouter.
	 */
	public void addNumber(int value) {
		System.out.println();
		System.out.println("-------------------------------------------------");
		System.out.println("Fonction � �crire");
		System.out.println("-------------------------------------------------");
		System.out.println();
	}

	/**
	 * Supprimer de this toutes les valeurs saisies par l'utilisateur et
	 * afficher le nouveau contenu (arrêt par lecture de -1).
	 */
	public void remove() {
		System.out.println("  valeurs a supprimer (-1 pour finir) : ");
		this.remove(System.in);
		System.out.println(" nouveau contenu :");
		this.printNewState();
	}

	/**
	 * Supprimer de this toutes les valeurs prises dans is.
	 * 
	 * @param is
	 *            flux d'entr�e
	 */
	public void remove(InputStream is) {
		Scanner sc = new Scanner(is);
		int value = sc.nextInt();
		Iterator<SubSet> it = this.iterator();
		
		while(value != -1) {
			
			int rank = value / 256;
			int set  = value % 256;
			
			while((it.isOnFlag() == false) && (it.getValue().rank < rank)) {
				it.goForward();
			}
			
			if(it.getValue().rank == rank) {
				it.getValue().set.remove(set);
			}
			 value = sc.nextInt();
			
		}
		
		sc.close();
	}

	/**
	 * Supprimer value de this.
	 * 
	 * @param value
	 *            valeur � supprimer
	 */
	public void removeNumber(int value) {
		System.out.println();
		System.out.println("-------------------------------------------------");
		System.out.println("Fonction � �crire");
		System.out.println("-------------------------------------------------");
		System.out.println();
	}

	/**
	 * @return taille de l'ensemble this
	 */
	public int size() {
		Iterator<SubSet> it = this.iterator();
		int cpt = 0;
		
		while(it.isOnFlag() == false) {
			cpt += it.getValue().set.size();
			it.goForward();
		}
		return cpt;
	}

	// /////////////////////////////////////////////////////////////////////////////
	// /////// Difference, DifferenceSymetrique, Intersection, Union ///////
	// /////////////////////////////////////////////////////////////////////////////

	/**
	 * This devient la diff�rence de this et set2.
	 * 
	 * @param set2
	 *            deuxi�me ensemble
	 */
	public void difference(MySet set2) {
		
		Iterator<SubSet> it = this.iterator();
		Iterator<SubSet> it2 = set2.iterator();

		while(it.isOnFlag() == false || it2.isOnFlag() == false) {
			
				if(it.getValue().rank == it2.getValue().rank) {
					it.getValue().set.difference(it2.getValue().set);
					it.goForward();	
					it2.goForward();		
				}
				else if(it.getValue().rank < it2.getValue().rank){
					it.goForward();					
				}
				else {
					it2.goForward();					
				}
			}		
	}

	/**
	 * This devient la diff�rence sym�trique de this et set2.
	 * 
	 * @param set2
	 *            deuxi�me ensemble
	 */
	public void symmetricDifference(MySet set2) {
		Iterator<SubSet> it = this.iterator();
		Iterator<SubSet> it2 = set2.iterator();

		while(it.isOnFlag() == false || it2.isOnFlag() == false) {
			
				if(it.getValue().rank == it2.getValue().rank) {
					it.getValue().set.difference(it2.getValue().set);
					it.goForward();	
					it2.goForward();		
				}
				else if(it.getValue().rank < it2.getValue().rank){
					it.goForward();					
				}
				else {
					it2.goForward();					
				}
			}	
	}

	/**
	 * This devient l'intersection de this et set2.
	 * 
	 * @param set2
	 *            deuxi�me ensemble
	 */
	public void intersection(MySet set2) {

		Iterator<SubSet> it1 = this.iterator();
		Iterator<SubSet> it2 = set2.iterator();

		
		while (it1.isOnFlag() == false) {	
		
			if (it1.getValue().rank == it2.getValue().rank) {
				it1.getValue().set.intersection(it2.getValue().set);
				it1.goForward();
				it2.goForward();
			}
			else if (it2.getValue().rank < it1.getValue().rank) {
				it2.goForward();
			}
			else {
				it1.remove();
				it1.goForward();
			}
		}
	}

	/**
	 * This devient l'union de this et set2.
	 * 
	 * @param set2
	 *            deuxi�me ensemble
	 */
	public void union(MySet set2) {
		Iterator<SubSet> it = this.iterator();
		Iterator<SubSet> it2 = set2.iterator();

		while(it2.isOnFlag() == false) {
			
				if(it.getValue().rank == it2.getValue().rank) {
					it.getValue().set.union(it2.getValue().set);
					it.goForward();	
					it2.goForward();		
				}
				else if(it.getValue().rank < it2.getValue().rank){
					it.goForward();					
				}
				else {
					it2.goForward();					
				}
			}	
	}

	// /////////////////////////////////////////////////////////////////////////////
	// /////////////////// Egalit�, Inclusion ////////////////////
	// /////////////////////////////////////////////////////////////////////////////

	/**
	 * @param o
	 *            deuxi�me ensemble
	 * 
	 * @return true si les ensembles this et o sont �gaux, false sinon
	 */
	@Override
	public boolean equals(Object o) {
		boolean b = true;
		if (this == o) {
			b = true;
		} else if (o == null) {
			b = false;
		} else if (!(o instanceof MySet)) {
			b = false;
		} else {
			System.out.println();
			System.out
					.println("-------------------------------------------------");
			System.out.println("Dernier cas � �crire");
			System.out
					.println("-------------------------------------------------");
			System.out.println();

		}
		return b;
	}

	/**
	 * @param set2
	 *            deuxi�me ensemble
	 * @return true si this est inclus dans set2, false sinon
	 */
	public boolean isIncludedIn(MySet set2) {
		System.out.println();
		System.out.println("-------------------------------------------------");
		System.out.println("Fonction � �crire");
		System.out.println("-------------------------------------------------");
		System.out.println();
		return false;
	}

	// /////////////////////////////////////////////////////////////////////////////
	// //////// Rangs, Restauration, Sauvegarde, Affichage //////////////
	// /////////////////////////////////////////////////////////////////////////////

	/**
	 * Afficher les rangs pr�sents dans this.
	 */
	public void printRanks() {
		System.out.println(" [version corrigee de rangs]");
		this.printRanksAux();
	}

	private void printRanksAux() {
		int count = 0;
		System.out.println(" Rangs presents :");
		Iterator<SubSet> it = this.iterator();
		while (!it.isOnFlag()) {
			System.out.print("" + it.getValue().rank + "  ");
			count = count + 1;
			if (count == 10) {
				System.out.println();
				count = 0;
			}
			it.goForward();
		}
		if (count > 0) {
			System.out.println();
		}
	}

	/**
	 * Cr�er this � partir d'un fichier choisi par l'utilisateur contenant une
	 * s�quence d'entiers positifs termin�e par -1 (cf f0.ens, f1.ens, f2.ens,
	 * f3.ens et f4.ens).
	 */
	public void restore() {
		String fileName = readFileName();
		InputStream inFile;
		try {
			inFile = new FileInputStream(fileName);
			System.out.println(" [version corrigee de restauration]");
			this.clear();
			this.add(inFile);
			inFile.close();
			System.out.println(" nouveau contenu :");
			this.printNewState();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.out.println("fichier " + fileName + " inexistant");
		} catch (IOException e) {
			e.printStackTrace();
			System.out.println("probleme de fermeture du fichier " + fileName);
		}
	}

	/**
	 * Sauvegarder this dans un fichier d'entiers positifs termin� par -1.
	 */
	public void save() {
		System.out.println(" [version corrigee de sauvegarde]");
		OutputStream outFile;
		try {
			outFile = new FileOutputStream(readFileName());
			this.print(outFile);
			outFile.write("-1\n".getBytes());
			outFile.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.out.println("pb ouverture fichier lors de la sauvegarde");
		} catch (IOException e) {
			e.printStackTrace();
			System.out.println("probleme de fermeture du fichier");
		}
	}

	/**
	 * @return l'ensemble this sous forme de cha�ne de caract�res.
	 */
	@Override
	public String toString() {
		StringBuilder result = new StringBuilder();
		int count = 0;
		SubSet subSet;
		int startValue;
		Iterator<SubSet> it = this.iterator();
		while (!it.isOnFlag()) {
			subSet = it.getValue();
			startValue = subSet.rank * 256;
			for (int i = 0; i < 256; ++i) {
				if (subSet.set.contains(i)) {
					String number = String.valueOf(startValue + i);
					int numberLength = number.length();
					for (int j = 6; j > numberLength; --j) {
						number += " ";
					}
					result.append(number);
					++count;
					if (count == 10) {
						result.append("\n");
						count = 0;
					}
				}
			}
			it.goForward();
		}
		if (count > 0) {
			result.append("\n");
		}
		return result.toString();
	}

	/**
	 * Imprimer this dans outFile.
	 * 
	 * @param outFile
	 *            flux de sortie
	 */
	private void print(OutputStream outFile) {
		try {
			String string = this.toString();
			outFile.write(string.getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Afficher l'ensemble avec sa taille et les rangs pr�sents.
	 */
	private void printNewState() {
		this.print(System.out);
		System.out.println(" Nombre d'elements : " + this.size());
		this.printRanksAux();
	}

	/**
	 * @param scanner
	 * @param min
	 *            valeur minimale possible
	 * @return l'entier lu au clavier (doit être entre min et 32767)
	 */
	private static int readValue(Scanner scanner, int min) {
		int value = scanner.nextInt();
		while (value < min || value > 32767) {
			System.out.println("valeur incorrecte");
			value = scanner.nextInt();
		}
		return value;
	}

	/**
	 * @return nom de fichier saisi psar l'utilisateur
	 */
	private static String readFileName() {
		System.out.print(" nom du fichier : ");
		String fileName = TpListe.standardInput.next();
		return fileName;
	}
}
