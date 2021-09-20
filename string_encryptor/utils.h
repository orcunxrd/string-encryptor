#pragma once
#include <random>

using namespace std;

int rand_int( int max, int min )
{
    srand( ( unsigned )time( NULL ) * GetCurrentProcessId( ) );
    int randNum = rand( ) % ( max - min + 1 ) + min;
    return randNum;
}

string rand_str( string::size_type length )
{
    static auto& chrs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    thread_local static mt19937 rg{ random_device{ }( ) };
    thread_local static uniform_int_distribution < string::size_type > pick( 0, sizeof( chrs ) - 2 );
    string s;
    s.reserve( length );
    while ( length-- ) s += chrs[ pick( rg ) ];
    return s;
}

template < typename ... Args >
string mixer( Args const& ... args )
{
    ostringstream stream;
    using List = int[ ];
    ( void )List {
        0, ( ( void )( stream << args ), 0 ) ...
    };
    return stream.str( );
}

bool copy_cb( const string& text )
{
    bool succeeded = false;

    if ( HANDLE clipdata = GlobalAlloc( GMEM_FIXED, text.length( ) + 1 ) )
    {
        std::memcpy( clipdata, text.data( ), text.length( ) + 1 );

        if ( OpenClipboard( NULL ) )
        {
            if ( EmptyClipboard( ) && SetClipboardData( CF_TEXT, clipdata ) )
                succeeded = true;

            CloseClipboard( );
        }

        if ( !succeeded )
            GlobalFree( clipdata );
    }

    return succeeded;
}