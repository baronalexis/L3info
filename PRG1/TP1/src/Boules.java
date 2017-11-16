
public class Boules {
	
	
	public static char[] lireTableauBoules(int size) {
		char [] tab = new char[size];
		String temp = Lecture.lireString();
		while(temp.length() != size) {
			temp+=Lecture.lireString();
		}
		for(int i =0; i < size; i++) {
			tab[i] = temp.charAt(i);
		}
		return tab;
		
//		char [] tab = new char[size] ;
//		for(int i = 0; i < size; ++i){
//			tab[i] = Lecture.lireChar();
//		}
//		return tab;
	}
	
	public static void ecrireTableauBoules(char[] tab, int size) {
		
		for(int i = 0; i < size; ++i){
			Ecriture.ecrireChar(tab[i]);
		}		
	}
	
	
	public static void echange(int i, int j, char [] tab) {
		char c = tab[i];
		tab[i] = tab[j];
		tab[j] = c;
	}
	


	public static void main(String [] args) {
		int nombreBoules = Lecture.lireInt();

		int r = 0;
		int s = 0;
		int t = nombreBoules - 1;
		char[] tab = new char[nombreBoules];
		
		Ecriture.ecrireString("Suite des " + nombreBoules + " boules : ");
		tab = lireTableauBoules(nombreBoules);
		
		while(s <= t) {

			switch(tab[s]){
			case 'v':
				echange(r, s, tab);
				++r;
				++s;
				break; 
			case 'b':
				++s;
				break; 
			case 'r':
				echange(s, t, tab);
				--t;
				if(tab[t] == 'r')
				++s;
				break; 
			default:
				Ecriture.ecrireString("erreur : s = " + s +", boule = " + tab[s] + "\n");
			}
				
		}
		
		Ecriture.ecrireString("résultat du tri : ");
		ecrireTableauBoules(tab, nombreBoules);
		Ecriture.ecrireStringln("");
	
	}
	
	
}
