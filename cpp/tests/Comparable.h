
/**
 * \file Comparable.h
 * \brief D�finition de la classe Comparable
 * \author Abder
 * \version 0.1
 * \date mars 2011
 *
 * Une classe pour tester les implantations g�n�riques. 
  */

#ifndef _COMPARABLE_H
#define _COMPARABLE_H

#include <iostream>
#include <string>

/** 
* \class ClassTests
*
* \brief classe de testes avec des op�rateurs surcharg�s
*
*  La classe nous servira tout le long de la session
*  pour tester nos diff�rentes implantations g�n�riques.
*/
class Comparable
{
public:
	/**
     *  \brief Constructeur par d�faut
     *
     *  \post Une instance de la classe non initialis�e 
     */
	Comparable();

	/**
     *  \brief Constructeur avec arguments
     *
     *  \post Une instance de la classe initialis�e 
     */
	Comparable(int V, const std::string & M);

	/**
     *  \brief Constructeur de copie
	 *
	 *  \post une copie profonde de l'objet source   
     */
	Comparable(const Comparable  & A);  
	
	/**
     *  \brief Destructeur
     *
     *  \post l'instance de la classe est d�truite
     */
	~Comparable();

	/**
     *  \brief Retourner le membre Valeur
     *
     *  \post un entier est retourn�
     */
	int RetourneValeur() { return Valeur; }

	/**
     *  \brief Retourner le membre Mot
     *
     *  \post une cha�ne de caract�res est retourn�e
     */
	std::string RetourneMot() { return Mot; }

	/**                       
	 * \brief Surcharger l'op�rateur < 
	 *
	 * \post Un bool�en est retourn�e 
	 */
	bool operator<  (const Comparable &Op2) const {return Valeur < Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'op�rateur <= 
	 *
	 * \post Un bool�en est retourn�e
	 */
	bool operator<= (const Comparable &Op2) const {return Valeur <= Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'op�rateur > 
	 *
	 * \post Un bool�en est retourn�e
	 */
	bool operator>  (const Comparable &Op2) const {return Valeur > Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'op�rateur >= 
	 *
	 * \post Un bool�en est retourn�e
	 */
	bool operator>= (const Comparable &Op2) const {return Valeur >= Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'op�rateur != 
	 *
	 * \post Un bool�en est retourn�e 
	 */
	bool operator!= (const Comparable &Op2) const {return Valeur != Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'op�rateur == 
	 *
	 * \post Un bool�en est retourn�e 
	 */
	bool operator== (const Comparable &Op2) const {return Valeur == Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'op�rateur = 
	 *
	 * Copie l'operande de droite dans l'objet courant
	 *
	 * \post Une copie profonde de la source est retourn�e 
	 */
	Comparable & operator= (const Comparable &);

	/**                       
	 * \brief Surcharger l'op�rateur + 
	 *
	 * Additionne deux objets Comparable
	 *
	 * \post Une instance de type Comparable somme de 2 objets Comparable 
	 */
	Comparable operator+ (const Comparable &) const ;

	/**                       
	 * \brief Surcharge de l'op�rateur << 
	 *
	 *	Affiche le contenu de l'objet a l'ecran
	 * \post Un flot de sortie correspondant � l'objet de type Comparable est retourn�e 
	 */
	friend std::ostream & operator<< (std::ostream &,const Comparable &);

private:
	int Valeur;						/*!< Un entier*/
	std::string Mot;				/*!<Une cha�ne de caract�res*/

};

#endif
// fin de Comparable.h
