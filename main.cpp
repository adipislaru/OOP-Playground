#include <iostream>
#include <vector>

using namespace std;

void sterge( )
{
    int i;
    
    for( i = 0; i < 20; i++ )
        cout << endl;
}

class Produs
{
    protected:
        char nume_produs[ 64 ];
        char unitate_masura[ 10 ];
    
    public:
        Produs( char*, char* );
    
        virtual int afiseaza( ostream& );
    
        friend ostream& operator << ( ostream&, Produs& );
};

Produs::Produs( char* nume_produs, char* unitate_masura )
{
    strcpy( this->nume_produs, nume_produs );
    strcpy( this->unitate_masura, unitate_masura );
}

int Produs::afiseaza( ostream& o )
{
    o << nume_produs << "[ " << unitate_masura << " ]";
    
    return 0;
}

ostream& operator << ( ostream& o, Produs& produs )
{
    produs.afiseaza( o );
    
    return o;
}

class Produsperisabil : virtual public Produs
{
    protected:
        int valabilitate;
    
    public:
        Produsperisabil( int, char*, char* );
    
        int afiseaza( ostream& );
    
        friend ostream& operator << ( ostream&, Produsperisabil& );
};

Produsperisabil::Produsperisabil( int valabilitate, char* nume_produs, char* unitate_masura ) : Produs( nume_produs, unitate_masura )
{
    this->valabilitate = valabilitate;
}

int Produsperisabil::afiseaza( ostream& o )
{
    o << nume_produs << "[ " << unitate_masura << " ] valabilitate: " << valabilitate << " zile";
    
    return 0;
}

ostream& operator << ( ostream& o, Produsperisabil& produs )
{
    produs.afiseaza( o );
    
    return o;
}

class Produsinpromotie : virtual public Produs
{
    protected:
        int discount;
    
    public:
        Produsinpromotie( int, char*, char* );
    
        int afiseaza( ostream& );
    
        friend ostream& operator << ( ostream&, Produsinpromotie& );
};

Produsinpromotie::Produsinpromotie( int discount, char* nume_produs, char* unitate_masura ) : Produs( nume_produs, unitate_masura )
{
    this->discount = discount;
}

int Produsinpromotie::afiseaza( ostream& o )
{
    o << nume_produs << "[ " << unitate_masura << " ] discount: " << discount << "%";
    
    return 0;
}

ostream& operator << ( ostream& o, Produsinpromotie& produs )
{
    produs.afiseaza( o );
    
    return o;
}

class Produsperisabilinpromotie : public Produsperisabil, public Produsinpromotie
{
    public:
        Produsperisabilinpromotie( int valabilitate, int discount, char* nume_produs, char* unitate_masura ) : Produs( nume_produs, unitate_masura ), Produsperisabil( valabilitate, nume_produs, unitate_masura ), Produsinpromotie( discount, nume_produs, unitate_masura )
        {
        
        };
    
        int afiseaza( ostream& );
    
        friend ostream& operator << ( ostream&, Produsperisabilinpromotie& );
};

ostream& operator << ( ostream& o, Produsperisabilinpromotie& produs )
{
    produs.afiseaza( o );
    
    return o;
}

int Produsperisabilinpromotie::afiseaza( ostream& o )
{
    o << nume_produs << "[ " << unitate_masura << " ] valabilitate: " << valabilitate << " zile, discount: " << discount << "%";
    
    return 0;
}

class Lot
{
    protected:
        int id_produs,
            cantitate,
            pret,
            zi, luna, an;
    
    public:
        Lot( int _id_produs, int _cantitate, int _pret, int _zi, int _luna, int _an ) : id_produs( _id_produs ), cantitate( _cantitate ), pret( _pret ), zi( _zi ), luna( _luna ), an( _an )
        {
        
        }
    
        int afiseaza( );
};

int Lot::afiseaza( )
{
    printf( "Id produs: %d, Cantitate: %d, Pret: %d, Data: %d %d %d \n", id_produs, cantitate, pret, zi, luna, an );
    
    return 0;
}

class Magazin
{
    vector< Produs* > produse;
    vector< Lot* > loturi;
    
    public:
        int adauga_produs( );
        int afiseaza_produse( );
        int adauga_lot( int );
        int afiseaza_loturi( );
};

int Magazin::adauga_produs( )
{
    char _nume_produs[ 64 ],
        _unitate_masura[ 10 ];
    
    int valabilitate, discount;
    
    printf( "Introdu nume: \n" );
    scanf( "%s", _nume_produs );
    
    printf( "Introdu unitate de masura: \n" );
    scanf( "%s", _unitate_masura );
    
    printf( "Introdu discount produs( 0 = nu e in promotie ): \n" );
    scanf( "%d", &discount );
    
    printf( "Introdu valabilitate produs( 0 = nu e perisabil ): \n" );
    scanf( "%d", &valabilitate );
    
    if( valabilitate == 0 && discount == 0 )
        produse.push_back( new Produs( _nume_produs, _unitate_masura ) );
    
    if( valabilitate > 0 && ( valabilitate * discount ) == 0 )
        produse.push_back( new Produsperisabil( valabilitate, _nume_produs, _unitate_masura ) );
    
    if( discount > 0 && ( valabilitate * discount ) == 0 )
        produse.push_back( new Produsinpromotie( discount, _nume_produs, _unitate_masura ) );
    
    if( valabilitate > 0 && discount > 0 )
        produse.push_back( new Produsperisabilinpromotie( valabilitate, discount, _nume_produs, _unitate_masura ) );
    
    return 0;
}

int Magazin::afiseaza_produse( )
{
    for( vector< Produs* >::iterator it = produse.begin( ); it != produse.end( ); ++it )
        cout << *( *it ) << endl;
    
    return 0;
}

int Magazin::adauga_lot( int _id_produs )
{
    int _cantitate,
        _pret,
        _zi, _luna, _an;
    
    printf( "Introdu cantitate: \n" );
    scanf( "%d", &_cantitate );
    
    printf( "Introdu pret/um: \n" );
    scanf( "%d", &_pret );
    
    printf( "Introdu data( Z L AAAA ): \n" );
    scanf( "%d %d %d", &_zi, &_luna, &_an );
    
    loturi.push_back( new Lot( _id_produs, _cantitate, _pret, _zi, _luna, _an ) );
    
    return 0;
}

int Magazin::afiseaza_loturi( )
{
    for( vector< Lot* >::iterator it = loturi.begin( ); it != loturi.end( ); ++it )
        ( *it )->afiseaza( );
    
    return 0;
}

int main( )
{
    Magazin La_Costica;
    
    La_Costica.adauga_produs( );
    
    La_Costica.adauga_lot( 0 );
    
    La_Costica.afiseaza_produse( );
    
    sterge( );
    
    La_Costica.afiseaza_loturi( );
    
    return 0;
}
