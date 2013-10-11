
/**
 * \file Comparable.cpp
 * \brief Le code des méthodes membres de la classe Comparable.
 * \author Abder
 * \version 0.1
 * \date mars 2011
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Comparable.h"



/**
 * \fn Comparable:: Comparable()
 */
Comparable:: Comparable()
{}

/**
 * \fn Comparable:: Comparable(int V, const std::string & M) 
 *
 * \param[in] V Un entier 
 * \param[in] M Une chaîne de caractères
 */
Comparable:: Comparable(int V, const std::string& M) 
{ 
	Valeur = V; 
	Mot = M;
}

/**
 * \fn Comparable:: Comparable(const Comparable & Source)
 *
 * \param[in] Source  La source de la copie
 */
Comparable:: Comparable(const Comparable & Source)
{
	Valeur = Source.Valeur;
	Mot = Source.Mot;
}

/**
 * \fn Comparable::~Comparable()
 */
Comparable::~Comparable()
{}

 /**
 * \fn Comparable & Comparable::operator=(const Comparable &Op2)
 *
 * \param[in] Op2 Le second operande de l'operation
 * \return Comparable- L'objet courant
 */
Comparable & Comparable::operator=(const Comparable &Op2)
{
	Valeur = Op2.Valeur;
	Mot = Op2.Mot;
	return *this;
}

/**
 * \fn Comparable Comparable::operator+ (const Comparable &Op2)
 *
 * \param[in] Op2 Le second operande de l'addition
 * \return Comparable- L'objet courant
 */
Comparable Comparable::operator+ (const Comparable &Op2)const
{
	Comparable Temp;
	Temp.Valeur = Valeur +Op2.Valeur;
	Temp.Mot = Mot;
	Temp.Mot = Temp.Mot + Op2.Mot;
	return(Temp);
}

/**
 * \fn std::ostream & operator<< (std::ostream &sortie, const Comparable &Source)
 *
 * \param[in, out] sortie Le flot de sortie
 * \param[in] Source Objet de Comparable a afficher
 * \return ostream  L'identificateur de flot de sortie
 */
std::ostream & operator<< (std::ostream &sortie, const Comparable &Source)
{
	sortie<<"Valeur->"<<std::setw(5)<<std::setiosflags(std::ios::left)<<Source.Valeur
		  <<" Mot->"<<Source.Mot<<std::endl;
	return sortie;
}



