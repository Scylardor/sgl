/**
 * \file Main_TestGraphe.cpp
 * \brief un main() pour tester la classe Graphe.
 * \author Abder
 * \version 0.1
 * \date septembre 2011
 *
 * D�montre l'utilisation de la classe Graphe 
 */

#include "Graphe.h"
#include "Comparable.h"

using namespace Graphe_Lab10;
using namespace std;

/**
 * \fn int main (void)
 * \brief Fonction principale.
 *
 * Un main() testeur de la classe Graphe
 * \return 0 - Arr�t normal du programme.
 */
int main()
{
	
	try{
		Comparable Test0(5,"mauve"),Test1(7,"rouge"),Test2(4,"blanc"),
		Test3(29,"bleu"),Test4(0,"jaune"),Test5(30,"vert"),
		Test6(6,"noir");
		
		Graphe<Comparable> g(12);	//un graphe pour 12 sommets max
	
		g.ajouterSommet(Test0);
		g.ajouterSommet(Test1);
		g.ajouterSommet(Test2);
		g.ajouterSommet(Test3);
		g.ajouterSommet(Test4);
		g.ajouterSommet(Test5);
		g.ajouterSommet(Test6);
		
		g.ajouterArc(Test2,Test4);
		g.ajouterArc(Test2,Test6);
		g.ajouterArc(Test2,Test5);
		g.ajouterArc(Test2,Test1);
		g.ajouterArc(Test2,Test3);
		g.ajouterArc(Test3,Test6);
		g.ajouterArc(Test3,Test4);
		g.ajouterArc(Test3,Test2);
		g.ajouterArc(Test4,Test6);
		g.ajouterArc(Test4,Test1);
		g.ajouterArc(Test5,Test2);
		g.ajouterArc(Test5,Test6);
		g.ajouterArc(Test6,Test1);
		g.ajouterArc(Test6,Test4);
		
		cout << "Affichage du graphe g" << endl;
		cout << "---------------------" << endl;
		g.affiche();

		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();

		// test du constructeur de copie
		Graphe<Comparable> g2(g);
		cout << "\nAffichage du graphe g2(la copie)" << endl;
		cout << "--------------------------------" << endl;
		g2.affiche();

		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();

		// ajout d'un arc
		g2.ajouterArc(Test4,Test2);
		cout << "\nAffichage du graphe g2 apres ajout de (4,2)" << endl;
		cout << "---------------------------------------------" << endl;
		g2.affiche();

		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();

		// retrait d'un arc
		g2.enleverArc(Test2,Test6);
		cout << "\nAffichage du graphe g2 apres retrait de (2,6)" << endl;
		cout << "---------------------------------------------" << endl;
		g2.affiche();

		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();

		// retrait d'un sommet
		g2.enleverSommet(Test2);
		cout << "\nAffichage du graphe g2 apres retrait de 2" << endl;
		cout << "------------------------------------------" << endl;
		g2.affiche();

		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();

		// ajout d'un sommet
		g2.ajouterSommet(Test2);
		cout << "\nAffichage du graphe g2 apres ajout de 2" << endl;
		cout << "------------------------------------------" << endl;
		g2.affiche();
		
		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();

		// sommetExiste?
		if(g2.sommetExiste(Test4)) cout << "\nLe sommet 4 existe" << endl;

		// arcExiste?
		if(g2.arcExiste(Test4,Test6)) cout << "\nL'arc (4,8) existe" << endl;

		// test de l'op. =
		Graphe<Comparable> g3 = g;
		cout << "\nAffichage du graphe g3(la copie de g par =)" << endl;
		cout << "--------------------------------------------" << endl;
		g3.affiche();

		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();

		// test de l'op. =
		g3 = g2;
		cout << "\nAffichage du graphe g3(la copie de g2 par =)" << endl;
		cout << "---------------------------------------------" << endl;
		g3.affiche();

		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();

		// test sous-graphe
		vector<Comparable> v;
		v.push_back(Test3); v.push_back(Test5); v.push_back(Test6);
		cout << "SEGFAULT !" << endl;
		Graphe<Comparable> g4(g,v);
		cout << "SEGFAULT !!" << endl;
		cout << "\nAffichage du sous graphe g4: g sans les sommets 3,5 et 6" << endl;
		cout << "---------------------------------------------------------" << endl;
		g4.affiche();

		v.clear();

		cout << "\nAffichage des sommets de g4" << endl;
		v = g4.listerSommetsGraphe();
		for ( size_t i = 0, size = v.size(); i < size; ++i )
		{
        // attention : utilisation de l'op�rateur []
        // les acc�s ne sont pas v�rifi�s, on peut d�border !
			cout << v[ i ] << " ";        
		}
		cout << '\n';

		cout<< "Ordre d'entree du sommet Test2 dans g: " << g.ordreEntreeSommet(Test2)<< endl;
		
		v.clear();
		v = g.listerSommetsAdjacents(Test2);
		cout << "\nAffichage des sommets adjacents a Test2 dans g" << endl;
		for ( size_t i = 0, size = v.size(); i < size; ++i )
		{
			cout << v[ i ] << " ";        
		}
		cout << '\n';

		cout<< "Ordre de sortie du sommet Test2 dans g: " << g.ordreSortieSommet(Test2)<< endl;

		cout<< "Pesez sur une touche pour continuer";
		cout.flush();
		cin.get();
	} catch (exception& e)
	{
		cerr << e.what() << endl;
		return 0;
	}
		
	return 0;
}

