
/**
 * \file Comparable.h
 * \brief Définition de la classe Comparable
 * \author Abder
 * \version 0.1
 * \date mars 2011
 *
 * Une classe pour tester les implantations génériques. 
  */

#ifndef _COMPARABLE_H
#define _COMPARABLE_H

#include <iostream>
#include <string>

/** 
* \class ClassTests
*
* \brief classe de testes avec des opérateurs surchargés
*
*  La classe nous servira tout le long de la session
*  pour tester nos différentes implantations génériques.
*/
class Comparable
{
public:
	/**
     *  \brief Constructeur par défaut
     *
     *  \post Une instance de la classe non initialisée 
     */
	Comparable();

	/**
     *  \brief Constructeur avec arguments
     *
     *  \post Une instance de la classe initialisée 
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
     *  \post l'instance de la classe est détruite
     */
	~Comparable();

	/**
     *  \brief Retourner le membre Valeur
     *
     *  \post un entier est retourné
     */
	int RetourneValeur() { return Valeur; }

	/**
     *  \brief Retourner le membre Mot
     *
     *  \post une chaîne de caractères est retournée
     */
	std::string RetourneMot() { return Mot; }

	/**                       
	 * \brief Surcharger l'opérateur < 
	 *
	 * \post Un booléen est retournée 
	 */
	bool operator<  (const Comparable &Op2) const {return Valeur < Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'opérateur <= 
	 *
	 * \post Un booléen est retournée
	 */
	bool operator<= (const Comparable &Op2) const {return Valeur <= Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'opérateur > 
	 *
	 * \post Un booléen est retournée
	 */
	bool operator>  (const Comparable &Op2) const {return Valeur > Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'opérateur >= 
	 *
	 * \post Un booléen est retournée
	 */
	bool operator>= (const Comparable &Op2) const {return Valeur >= Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'opérateur != 
	 *
	 * \post Un booléen est retournée 
	 */
	bool operator!= (const Comparable &Op2) const {return Valeur != Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'opérateur == 
	 *
	 * \post Un booléen est retournée 
	 */
	bool operator== (const Comparable &Op2) const {return Valeur == Op2.Valeur;}

	/**                       
	 * \brief Surcharger l'opérateur = 
	 *
	 * Copie l'operande de droite dans l'objet courant
	 *
	 * \post Une copie profonde de la source est retournée 
	 */
	Comparable & operator= (const Comparable &);

	/**                       
	 * \brief Surcharger l'opérateur + 
	 *
	 * Additionne deux objets Comparable
	 *
	 * \post Une instance de type Comparable somme de 2 objets Comparable 
	 */
	Comparable operator+ (const Comparable &) const ;

	/**                       
	 * \brief Surcharge de l'opérateur << 
	 *
	 *	Affiche le contenu de l'objet a l'ecran
	 * \post Un flot de sortie correspondant à l'objet de type Comparable est retournée 
	 */
	friend std::ostream & operator<< (std::ostream &,const Comparable &);

private:
	int Valeur;						/*!< Un entier*/
	std::string Mot;				/*!<Une chaîne de caractères*/

};

#endif
// fin de Comparable.h
