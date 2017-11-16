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

/*
 * Classe Pair d�crivant des couples d'entiers.
 */
public class Pair {

	private int x;
	private int y;
	
	public Pair(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public int getX() {
		return this.x;
	}
	
	public int getY() {
		return this.y;
	}
	
	/*
	 * V�rifie si deux couples sont �gaux.
	 */
	public boolean equals(Pair p) {
		return this.getX() == p.getX() && this.getY() == p.getY();
	}
	
	/*
	 * V�rifie si le couple d�sign� est inf�rieur � un autre.
	 */
	public boolean less(Pair p) {
		if(p == null) {
			return false;
		} else {
			return (this.getX() < p.getX()) || (this.getX() == p.getX() && this.getY() < p.getY());
		}
	}
	
	public String toString() {
		return "(" + x + " " + y + ")";
	}
	
	
}
