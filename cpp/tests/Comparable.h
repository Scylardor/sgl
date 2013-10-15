
/**
 * \file Comparable.h
 * \brief Definition of class Comparable
 * \author Abder
 * \version 0.1
 * \date March, 2011
 *
 * A class to test generic implementation.
  */

#ifndef _COMPARABLE_H
#define _COMPARABLE_H

#include <iostream>
#include <string>

/** 
* \class Comparable
*
* \brief test class with overloaded operators
*
*  Useful to test generic implementations.
*/
class Comparable
{
public:
	/**
     *  \brief Default constructor
     */
	Comparable();

	/**
     *  \brief Constructor with arguments
     */
	Comparable(int V, const std::string & M);

	/**
     *  \brief Copy Constructor
	 *
	 *  \post deep copy of the source object
     */
	Comparable(const Comparable  & A);  
	
	/**
     *  \brief Destructor
     */
	~Comparable();

	/**
     *  \brief Return the Value member
     *
     *  \return an integer
     */
	int ReturnValue() { return Value; }

	/**
     *  \brief Return the string Word
     *
     *  \return a string
     */
	std::string ReturnWord() { return Word; }

	/**                       
	 * \brief Overload of operator <
	 *
	 * \return (boolean) true if Value < Op2.Value
	 */
	bool operator<  (const Comparable &Op2) const {return Value < Op2.Value;}

	/**                       
	 * \brief Overload of operator <=
	 *
	 * \return (boolean) true if Value <= Op2.Value
	 */
	bool operator<= (const Comparable &Op2) const {return Value <= Op2.Value;}

	/**                       
	 * \brief Overload of operator >
	 *
	 * \return (boolean) true if Value > Op2.Value
	 */
	bool operator>  (const Comparable &Op2) const {return Value > Op2.Value;}

	/**                       
	 * \brief Overload of operator >=
	 *
	 * \return (boolean) true if Value >= Op2.Value
	 */
	bool operator>= (const Comparable &Op2) const {return Value >= Op2.Value;}

	/**                       
	 * \brief Overload operator !=
	 *
	 * \return (boolean) true if Value != Op2.Value
	 */
	bool operator!= (const Comparable &Op2) const {return Value != Op2.Value;}

	/**                       
	 * \brief Overload operator ==
	 *
	 * \return (boolean) true if Value == Op2.Value
	 */
	bool operator== (const Comparable &Op2) const {return Value == Op2.Value;}

	/**                       
	 * \brief Overload operator =
	 *
	 * Copies the right-hand side object's value into this one
	 *
	 * \return a deep copy of the source
	 */
	Comparable & operator= (const Comparable &);

	/**                       
	 * \brief Overload operator +
	 *
	 * Adds two Comparable objects
	 *
	 * \return A new instance of type Comparable which sums the 2 objects
	 */
	Comparable operator+ (const Comparable &) const ;

	/**                       
	 * \brief Overload operator <<
	 *
	 *	Prints the object's content to screen
	 * \return the used ostream
	 */
	friend std::ostream & operator<< (std::ostream &,const Comparable &);

private:
	int Value;						/*!< An int */
	std::string Word;				/*!< A string */

};

#endif
// fin de Comparable.h
