/**
 * \file Graphe.inl
 * \brief Le code des op�rateurs du graphe.
 * \author Abder
 * \version 0.1
 * \date septembre 2011
 *
 * Impl�mentation de la classe g�n�rique Graphe dans des listes d'adjacence
 */

#include "Graphe.h"

using namespace std;

namespace Graphe_Lab10 {

/**
 *  \brief Constructeur
 *
 *  \pre Il faut qu'il y ait suffisamment de m�moire
 *  \pre p_nbSommetsMax > 0
 *  \post Une instance de la classe Graphe avec nbSommet est initialis�e
 *  \exception bad_alloc si la m�moire est insuffisante
 *  \exception logic_error si nbSommet <= 0
 */
template<typename T>
Graphe<T>::Graphe(int p_nbSommetsMax) {
	if (p_nbSommetsMax < 1) {
		throw logic_error("Graphe: Nombre de sommets max negatif ou nul");
	}
	m_nbNoeudMax = p_nbSommetsMax;
	m_nbNoeud = 0;
	m_listeNoeud = new Noeud*[p_nbSommetsMax];
	m_tableauSommet = new T[p_nbSommetsMax];
}

/**
 *  \brief Constructeur de copie
 *
 *  \pre Il faut qu'il y ait suffisamment de m�moire
 *  \post une copie profonde du graphe source est instanci�e
 *  \exception bad_alloc s'il n'y a pas assez de m�moire
 */
template<typename T>
Graphe<T>::Graphe(const Graphe &p_src) {
	m_nbNoeud = 0;
	m_nbNoeudMax = p_src.m_nbNoeudMax;
	m_tableauSommet = new T[m_nbNoeudMax];
	m_listeNoeud = new Noeud*[m_nbNoeudMax];
	for (int i = 0; i < p_src.m_nbNoeud; i++) {
		ajouterSommet(p_src.m_tableauSommet[i]);
	}
	for (int j = 0; j < m_nbNoeud; j++) {
		for (Noeud *tmp = p_src.m_listeNoeud[j]->m_suivant; tmp != NULL; tmp =
				tmp->m_suivant) {
			ajouterArc(p_src.m_listeNoeud[j]->m_sommet, tmp->m_sommet);
		}
	}
}

/**
 *  \brief Constructeur sous-Graphe
 *
 * \pre Il faut qu'il y ait suffisamment de m�moire
 * \pre Les sommets dans le vector doivent appartenir au graphe g
 * \post une copie profonde du graphe est instancie�, le graphe source en moins les sommets contenus dans le vector
 * \exception bad_alloc s'il n'y a pas assez de m�moire
 * \exception logic_error si les sommets dans le vector n'appartiennent pas a p_src
 */
template<typename T>
Graphe<T>::Graphe(const Graphe &p_src, const vector<T> &p_filter) {
	m_nbNoeud = 0;
	m_nbNoeudMax = p_src.m_nbNoeudMax;
	m_tableauSommet = new T[m_nbNoeudMax];
	m_listeNoeud = new Noeud*[m_nbNoeudMax];
	for (typename vector<T>::const_iterator sommet = p_filter.begin();
			sommet != p_filter.end(); ++sommet) {
		if (!p_src.sommetExiste((*sommet))) {
			throw logic_error(
					"Graphe: le vector contient un sommet non present dans le graphe source");
		}
		ajouterSommet((*sommet));
	}
	for (int i = 0; i < m_nbNoeud; i++) {
		for (Noeud *tmp = p_src.m_listeNoeud[i]->m_suivant; tmp != NULL; tmp =
				tmp->m_suivant) {
			if (sommetExiste(tmp->m_sommet)) {
				ajouterArc(m_tableauSommet[i], tmp->m_sommet);
			}
		}
	}
}

/**
 *  \brief Destructeur
 *
 *  \post l'instance de Graphe est d�truite
 */
template<typename T>
Graphe<T>::~Graphe() {
	delete[] m_tableauSommet;
	for (int i = 0; i < m_nbNoeud; i++) {
		Noeud *tmp = m_listeNoeud[i];
		do {
			Noeud *tmp2 = tmp->m_suivant;
			delete tmp;
			tmp = tmp2;
		} while (tmp != NULL);
	}
	delete[] m_listeNoeud;
}

/**
 * \brief Surcharger l'op�rateur =
 *
 * \pre Il y a assez de m�moire pour l'op�ration
 * \post Une copie d'un graphe est retourn�e
 * \exception bad_alloc si la m�moire est insuffisante
 */
template<typename T>
const Graphe<T> & Graphe<T>::operator =(const Graphe<T> &p_src) {
	Graphe<T> temp(p_src);

	swap(m_tableauSommet, temp.m_tableauSommet);
	swap(m_listeNoeud, temp.m_listeNoeud);
	return *this;
}

/**
 *  \brief Ajouter un sommet dans le graphe
 *
 * \pre Il y a assez de m�moire
 * \pre Le sommet s ne fait pas partie d�j� du graphe
 * \post Le graphe comprend un sommet de plus
 * \exception bad_alloc s'il n'y a pas assez de m�moire
 * \exception logic_error si s appartient au graphe
 */
template<typename T>
void Graphe<T>::ajouterSommet(const T &p_s) {
	if (m_nbNoeud == m_nbNoeudMax) {
		throw logic_error("ajouterSommet: le graphe est à sa capacité maximum");
	}
	m_tableauSommet[m_nbNoeud] = p_s;
	m_listeNoeud[m_nbNoeud] = new Noeud();
	m_listeNoeud[m_nbNoeud]->m_sommet = p_s;
	m_listeNoeud[m_nbNoeud]->m_suivant = NULL;
	m_nbNoeud++;
}

/**
 *  \brief Ajouter un arc dans le graphe
 *
 * \pre Il y a assez de m�moire
 * \pre Les 2 sommets s1 et s2 appartiennent au graphe
 * \post Le graphe comprend un arc de plus
 * \exception bad_alloc s'il n'y a pas assez de m�moire
 * \exception logic_error si s1 ou s2 n'appartiennent pas au graphe
 */
template<typename T>
void Graphe<T>::ajouterArc(const T &p_s1, const T &p_s2) {
	if (!sommetExiste(p_s1) || !sommetExiste(p_s2)) {
		throw logic_error(
				"ajouterArc: un des deux sommets n'appartient pas au graphe");
	}
	for (int i = 0; i < m_nbNoeud; i++) {
		Noeud *tmp;

		tmp = m_listeNoeud[i];
		if (tmp->m_sommet == p_s1) {
			while (tmp->m_suivant != NULL) {
				tmp = tmp->m_suivant;
			}
			Noeud *nouvelEl = new Noeud();

			nouvelEl->m_sommet = p_s2;
			nouvelEl->m_suivant = NULL;
			tmp->m_suivant = nouvelEl;
			break;
		}
	}
}

/**
 *  \brief enlever un arc du graphe
 *
 * \pre Les 2 sommets s1 et s2 appartiennent au graphe
 * \post Le graphe comprend un arc de moins
 * \exception logic_error si s1 ou s2 n'appartiennent pas au graphe
 */
template<typename T>
void Graphe<T>::enleverArc(const T &p_s1, const T &p_s2) {
	if (!arcExiste(p_s1, p_s2)) {
		throw logic_error("enleverArc: aucun arc entre les deux sommets");
	}
	for (int i = 0; i < m_nbNoeud; i++) {
		Noeud *cur;

		cur = m_listeNoeud[i];
		if (cur->m_sommet == p_s1) {
			Noeud *prev;

			do {
				prev = cur;
				cur = cur->m_suivant;
			} while (cur->m_sommet != p_s2);
			prev->m_suivant = cur->m_suivant;
			delete cur;
			break;
		}
	}
}

/**
 *  \brief enlever un sommet du graphe
 *
 * \pre Le sommet s appartient au graphe
 * \post Le graphe comprend un sommet de moins
 * \exception logic_error si s n'appartient pas au graphe
 */
template<typename T>
void Graphe<T>::enleverSommet(const T &p_s) {
	if (!sommetExiste(p_s)) {
		throw logic_error("enleverSommet: Le sommet n'est pas dans le graphe");
	}
	for (int i = 0; i < m_nbNoeud; i++) {
		if (m_tableauSommet[i] == p_s) {
			while (i < (m_nbNoeud - 1)) {
				m_tableauSommet[i] = m_tableauSommet[i + 1];
				i++;
			}
		}
	}
	int indexDeletion;

	for (int i = 0; i < m_nbNoeud; i++) {
		Noeud *tmp = m_listeNoeud[i];

		if (m_listeNoeud[i]->m_sommet == p_s) {
			indexDeletion = i;
			do {
				Noeud *tmp2 = tmp->m_suivant;
				delete tmp;
				tmp = tmp2;
			} while (tmp != NULL);
		} else {
			Noeud *prev = tmp;

			while (tmp != NULL) {
				if (tmp->m_sommet == p_s) {
					prev->m_suivant = tmp->m_suivant;
					delete tmp;
					break;
				}
				prev = tmp;
				tmp = tmp->m_suivant;
			}
		}
	}
	for (int i = indexDeletion; i < (m_nbNoeud - 1); i++) {
		m_listeNoeud[i] = m_listeNoeud[i + 1];
	}
	m_listeNoeud[m_nbNoeud - 1] = NULL;
	m_nbNoeud--;
}

/**
 *  \brief v�rifier l'appartenance d'un sommet au graphe
 *
 * \post Le graphe est inchang�
 */
template<typename T>
bool Graphe<T>::sommetExiste(const T &p_s) const {
	bool estPresent = false;

	for (int i = 0; i < m_nbNoeud; i++) {
		if (m_tableauSommet[i] == p_s) {
			estPresent = true;
			break;
		}
	}
	return estPresent;
}

/**
 *  \brief v�rifier l'appartenance d'un arc au graphe
 *
 * \post Le graphe est inchang�
 */
template<typename T>
bool Graphe<T>::arcExiste(const T &p_s1, const T &p_s2) const {
	bool existe = false;

	if (sommetExiste(p_s1) && sommetExiste(p_s2)) {
		Noeud *tmp;

		for (int i = 0; i < m_nbNoeud; i++) {
			tmp = m_listeNoeud[i];
			if (tmp->m_sommet == p_s1) {
				tmp = tmp->m_suivant;
				while (tmp != NULL) {
					if (tmp->m_sommet == p_s2) {
						existe = true;
						break;
					}
					tmp = tmp->m_suivant;
				}
				break;
			}
		}
	}
	return existe;
}

/**
 *  \brief Retourner le nombre de sommets dans le au graphe
 *
 * \post Le graphe est inchang�
 */
template<typename T>
int Graphe<T>::nbSommets() const {
	return m_nbNoeud;
}

/**
 *  \brief Lister les sommets d'un graphe
 *
 * Retourner dans un vector tous les sommets d'un graphe
 * \pre Il y a assez de m�moire
 * \post Le graphe est inchang�
 * \exception bad_alloc lancee par vector si pas assez de m�moire
 */
template<typename T>
std::vector<T> Graphe<T>::listerSommetsGraphe() {
	vector<T> elems;

	for (int i = 0; i < m_nbNoeud; i++) {
		elems.push_back(m_tableauSommet[i]);
	}
	return elems;
}

/**
 *  \brief Retourner l'ordre d'entree d'un sommet dans le graphe
 *
 * \pre Le sommet doit appartenir au graphe
 * \post Le graphe est inchang�
 * \exception logic_error si le sommet n'appartient pas au graphe
 */
template<typename T>
int Graphe<T>::ordreEntreeSommet(const T &p_s) const {
	if (!sommetExiste(p_s)) {
		throw logic_error(
				"ordreEntreeSommet: Le sommet n'est pas dans le graphe");
	}
	int ordreEntree = 0;

	for (int i = 0; i < m_nbNoeud; i++) {
		if (m_listeNoeud[i]->m_sommet != p_s) {
			for (Noeud *tmp = m_listeNoeud[i]->m_suivant; tmp != NULL;
					tmp = tmp->m_suivant) {
				if (tmp->m_sommet == p_s) {
					ordreEntree++;
					break;
				}
			}
		}
	}
	return ordreEntree;
}

/**
 *  \brief Lister les sommets adjacents � un sommet dans un graphe
 *
 * Retourner dans un vector tous les sommets adjacents
 *
 * \pre Il y a assez de m�moire
 * \pre Le sommet doit appartenir au graphe
 * \post Le graphe est inchang�
 * \exception bad_alloc lancee par vector si pas assez de m�moire
 * \exception logic_error si le sommet ne fait pas partie du graphe
 */
template<typename T>
std::vector<T> Graphe<T>::listerSommetsAdjacents(const T &p_s) const {
	if (!sommetExiste(p_s)) {
		throw logic_error(
				"ordreEntreeSommet: Le sommet n'est pas dans le graphe");
	}
	vector<T> adjs;

	for (int i = 0; i < m_nbNoeud; i++) {
		for (Noeud *tmp = m_listeNoeud[i]->m_suivant; tmp != NULL;
				tmp = tmp->m_suivant) {
			if (m_listeNoeud[i]->m_sommet == p_s) {
				adjs.push_back(tmp->m_sommet);
			} else {
				if (tmp->m_sommet == p_s) {
					adjs.push_back(m_listeNoeud[i]->m_sommet);
					break;
				}
			}
		}
	}
	return adjs;
}

/**
 *  \brief Retourner l'ordre de sortie d'un sommet dans le graphe
 *
 * \pre Le sommet doit appartenir au graphe
 * \post Le graphe est inchang�
 * \exception logic_error si le sommet n'appartient pas au graphe
 */
template<typename T>
int Graphe<T>::ordreSortieSommet(const T &p_s) const {
	if (!sommetExiste(p_s)) {
		throw logic_error(
				"ordreEntreeSommet: Le sommet n'est pas dans le graphe");
	}
	int ordreSortie = 0;

	for (int i = 0; i < m_nbNoeud; i++) {
		if (m_listeNoeud[i]->m_sommet == p_s) {
			for (Noeud *tmp = m_listeNoeud[i]->m_suivant; tmp != NULL;
					tmp = tmp->m_suivant) {
				ordreSortie++;
			}
		}
	}
	return ordreSortie;
}

/**
 *  \brief Afficher un graphe
 *
 * Affiche le graphe de la facon la plus proche de la sa representation r�elle en memoire
 * Chaque sommet formant un arc est affich� sur une ligne
 *
 * \post Le graphe est inchang�
 * M�thode fournie
 */

template<typename T>
void Graphe<T>::affiche() const {
	if (m_nbNoeud == 0)
		cout << "Le graphe graphe est vide" << endl;
	if (m_nbNoeud == 1)
		cout << "Le contient un seul sommet: " << m_tableauSommet[0] << endl;

	else {
		cout << "Le graphe comprend " << m_nbNoeud << " sommets" << endl;
		for (int cpt = 0; cpt < m_nbNoeud; cpt++)
			cout << m_tableauSommet[cpt] << " ";

		cout << endl << endl << "Voici tous ses arcs:" << endl;

		Noeud* tmp;
		int ind;

		for (int i = 0; i < m_nbNoeud; i++) {
			tmp = m_listeNoeud[i];
			while (tmp) {
				//Chercher l'indice du sommet dans le tableau de sommet (changement effectu� a ce niveau)
				for (int j = 0; j < m_nbNoeud; j++) {
					if (m_tableauSommet[j] == (tmp->m_sommet)) {
						ind = j;
					}
				}
				cout << m_tableauSommet[i] << m_tableauSommet[ind] << endl;
				tmp = tmp->m_suivant;
			}
			if (m_listeNoeud[i] != 0) {
				cout << endl;
			}
		}
	}
}

} //Fin du namespace
