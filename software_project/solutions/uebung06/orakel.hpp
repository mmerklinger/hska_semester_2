#include "RE.hpp"


/*
 * check if character in regular expression
 */
RE* deriv ( RE* r, char l ) {
    switch ( r->ofType() ) {
    case PhiType:
        return r;
    case EpsType:
        return new Phi();
    case ChType:
        if ( ( ( Ch* ) r )->getChar() == l ) {
            return new Eps();
        } else {
            return new Phi();
        }
    case StarType: {
        RE* r1 = ( ( Star* ) r )->getRE();
        return new Conc ( deriv ( r1,l ),r );
    }
    case AltType: {
        RE* r1 = ( ( Alt* ) r )->getLeft();
        RE* r2 = ( ( Alt* ) r )->getRight();
        return new Alt ( deriv ( r1,l ), deriv ( r2,l ) );
    }
    case ConcType: {
        RE* r1 = ( ( Conc* ) r )->getLeft();
        RE* r2 = ( ( Conc* ) r )->getRight();
        if ( r1->containsEps() ) {
            return new Alt ( new Conc ( deriv ( r1,l ),r2 ), deriv ( r2,l ) );
        } else {
            return new Conc ( deriv ( r1,l ),r2 );
        }
    }
    }// switch
}

/*
 * check if string recognized by regular expression
 */
bool match ( RE* r, string s ) {
    for ( int i=0; i < s.length(); i++ ) {
        r = deriv ( r, s[i] );
    }
    return r->containsEps();
}

/*
 * check if two regular expressions both recognize a string
 */
bool orakel ( RE* r, RE* rSimp, string s ) {
    return ( match ( r,s ) == match ( rSimp,s ) );
}
