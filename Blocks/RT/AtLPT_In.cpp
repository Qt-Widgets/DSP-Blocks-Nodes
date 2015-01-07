#include "AtLPT_In.hpp"
#include "Settings.hpp"
#include "Array.hpp"

#include <sys/io.h>

static inline qint16 recvSample( quint8 chn )
{
	outb( ( chn << 7 ) | 0x40, EPP_DATA );
	return ( qint16 )( ( ( inb( EPP_DATA ) & 0x1F ) << 5 ) | ( inb( EPP_DATA ) >> 3 ) ) - 0x1FF;
}

/**/

AtLPT_In::AtLPT_In() :
	AtLPT( "AtLPT input", "Wejście sygnału dla urządzenia AtLPT", 0, 1, SOURCE )
{}

bool AtLPT_In::start()
{
	if ( openDevice() )
	{
		settings->setRunMode( true );
		return true;
	}
	return false;
}
void AtLPT_In::exec( Array< Block::Sample > &samples )
{
	for ( int i = 0 ; i < outputsCount() ; ++i )
		samples += ( Sample ){ getTarget( i ), recvSample( i ) / 511.0f };
}
void AtLPT_In::stop()
{
	settings->setRunMode( false );
	closeDevice();
}

Block *AtLPT_In::createInstance()
{
	AtLPT_In *block = new AtLPT_In;
	block->settings = new Settings( *block, false, 0, 0, true, 1, 2 );
	return block;
}
