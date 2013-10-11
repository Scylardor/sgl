/**
 * \file Graphe.h
 * \brief Classe d�finissant une graphe orient�
 * \author Abder
 * \version 0.1
 * \date mai 2011
 *
 * D�finition de la classe Graphe et de ses	 
 * fonctions membres. Impl�mentation dans des		 
 * listes d'adjacence
 */

#ifndef _GRAPHE_H
#define _GRAPHE_H

#include <iostream>
#include <stdexcept>
#include <vector>

namespace Graphe_Lab10
{
	/** 
	* \class Graphe
	*
	* \brief classe g�n�rique repr�sentant un graphe
	*
	*  La classe g�re un graphe g�n�rique. L'impl�mentation
	*  se fait par des listes d'adjacence.
	*/
	template <typename T>
	class Graphe 
	{
	public:
		explicit Graphe (int);
		
		Graphe (const Graphe&);

		Graphe(const Graphe&, const std::vector<T>&);

		~Graphe (); // destructeur

		const Graphe& operator = (const Graphe&);

		void ajouterSommet(const T &);
		
		void ajouterArc(const T& , const T&);

		void enleverArc(const T&, const T&);

		void enleverSommet(const T &);

		bool sommetExiste(const T &) const;


		bool arcExiste(const T &, const T &) const;


		int  nbSommets() const;

		void affiche()const;
		

		std::vector<T> listerSommetsGraphe();

		int ordreEntreeSommet(const T &) const;
		

		std::vector<T> listerSommetsAdjacents(const T&) const;


		int ordreSortieSommet(const T& ) const;

	private:
		/** 
		* \class Noeud
		*
		* \brief classe interne repr�sentant un noeud typique du graphe
		*
		*  La classe repr�sente un noeud typique
		*  pour impl�menter des listes d'adjacence.
		*/
		class Noeud
		{
		 public:
			T m_sommet; 			 /*!< l'�tiquette d'un sommet */
			Noeud * m_suivant;     /*!< pour le cha�nage dans les listes de noeuds adjacents */
		};
		
		int m_nbNoeud;     		/*!< nombre de sommets dans le graphe */
		int m_nbNoeudMax;			/*!< nombre total possible de sommets */
		T * m_tableauSommet;		/*!< tableau repr�sentant les sommets (i.e. les �tiquettes)*/
		Noeud** m_listeNoeud;     /*!< structure pour les listes de noeuds adjacents*/

	};

}//Fin du namespace

#include "Graphe.hpp"

#endif
