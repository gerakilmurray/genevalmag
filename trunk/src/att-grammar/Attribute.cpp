/**
  *  \file Attribute.cpp
  *      \brief Implement Attribute.h - The attribute of a symbol of a attribute grammar.
  *  \date 31/08/2009
  *  \author Kilmurray, Gerardo Luis.
  *	 \author Picco, Gonzalo Martín.
  */

#include "Attribute.h"

namespace gen_eval_mag {

//template <class T> Attribute<T>::Attribute() {
Attribute::Attribute()
{
	// TODO Auto-generated constructor stub

}

//template <class T> Attribute<T>::~Attribute() {
Attribute::~Attribute()
{
	// TODO Auto-generated destructor stub
}

TipeAttr Attribute::getTipo()
{
    return this->tipo;
}

void Attribute::setTipo(TipeAttr tipo)
{
    this->tipo = tipo;
}

}