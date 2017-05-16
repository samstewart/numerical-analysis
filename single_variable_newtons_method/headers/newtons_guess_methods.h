#ifndef NEWTONS_GUESS_METHODS_H
#define NEWTONS_GUESS_METHODS_H

#include "polynomial.h"

/** Simplest method for evaulating the polynomial and its derivative.*/
PolyCoeff newtonsGuessStandard(PolyCoeff cur_guess, SS_Polynomial *poly);

/** Uses repeated synthetic division for evaulating the polynomial and its derivative*/
PolyCoeff newtonsGuessSynthDiv(PolyCoeff cur_guess, SS_Polynomial *poly);

#endif