
/**
 * \file Comparable.cpp
 * \brief Code of class Comparable
 * \author Abder
 * \version 0.1
 * \date March, 2011
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Comparable.h"



/**
 * \fn Comparable:: Comparable()
 */
Comparable:: Comparable()
: Value(0), Word("")
{}

/**
 * \fn Comparable:: Comparable(int V, const std::string & M) 
 *
 * \param[in] V An int
 * \param[in] M A string
 */
Comparable:: Comparable(int V, const std::string& M) 
{ 
	Value = V;
	Word = M;
}

/**
 * \fn Comparable:: Comparable(const Comparable & Source)
 *
 * \param[in] Source Copy source
 */
Comparable:: Comparable(const Comparable & Source)
{
	Value = Source.Value;
	Word = Source.Word;
}

/**
 * \fn Comparable::~Comparable()
 */
Comparable::~Comparable()
{}

 /**
 * \fn Comparable & Comparable::operator=(const Comparable &Op2)
 *
 * \param[in] Op2 Right-hand side operand
 * \return Comparable - this object
 */
Comparable & Comparable::operator=(const Comparable &Op2)
{
	Value = Op2.Value;
	Word = Op2.Word;
	return *this;
}

/**
 * \fn Comparable Comparable::operator+ (const Comparable &Op2)
 *
 * \param[in] Op2 Right-hand side operand
 * \return Comparable- this object
 */
Comparable Comparable::operator+ (const Comparable &Op2)const
{
	Comparable Temp;
	Temp.Value = Value +Op2.Value;
	Temp.Word = Word;
	Temp.Word = Temp.Word + Op2.Word;
	return(Temp);
}

/**
 * \fn std::ostream & operator<< (std::ostream &out, const Comparable &Source)
 *
 * \param[in, out] sortie the out stream
 * \param[in] Source Comparable object to print
 * \return ostream  the out stream
 */
std::ostream & operator<< (std::ostream &sortie, const Comparable &Source)
{
	sortie<<"Value->"<<std::setw(5)<<std::setiosflags(std::ios::left)<<Source.Value
		  <<" Word->"<<Source.Word<<std::endl;
	return sortie;
}



