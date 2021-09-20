// null#7869 - simple string encryptor

#include "pch.h"

int main()
{
    string str_data;
    string var_name = rand_str( 8 );

    printf( "string to be encrypted: " );
    getline( cin, str_data );

    int min, max;

    printf( "min value (int): " );
    cin >> min;

    printf( "max value (int): " );
    cin >> max;

    int randVal = rand_int( max, min );
    char hex_val[ 33 ];

    itoa( randVal, hex_val, 16 );

    size_t str_size = str_data.size( );
    const size_t length = strlen( str_data.c_str( ) );

    stringstream final;

    final << mixer( "// text: ", str_data ) << "\n";
    final << mixer( "wchar_t ", var_name, "[", length, "];" ) << "\n";
    
    string rand_for = rand_str( 8 );

    for ( size_t i = 0; i < length; ++i ) 
    {
        stringstream other_ss;

        other_ss << hex << int( str_data[ i ] ) + randVal;
        string other_res( other_ss.str( ) );

        final << mixer( var_name, "[", i, "] = 0x", other_res, "; " );
    }

    final << mixer( "\nfor (unsigned int ", rand_for, " = 0; ", rand_for, " < ", length, "; ", rand_for, "++) ", var_name, "[", rand_for, "] -= 0x", hex_val, ";" );
    
    string random_bstr = rand_str( 10 );
    final << mixer( "\nstd::wstring ", random_bstr, "(", var_name, "); \n" );

    printf( "copied to clipboard, closing..." );
    copy_cb( final.str( ) );

    Sleep( 1000 );
}