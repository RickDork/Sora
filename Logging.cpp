#include "Logging.h"

bool g_bDebugEnabled = false;

void Log::ClearLog()
{

    std::ofstream f( "log.txt", std::ios_base::trunc );
    f.close();

}

void Log::SetDebugLoggingEnabled( bool b )
{

	g_bDebugEnabled = b;

}

void Log::Debug( std::string log )
{

	if( g_bDebugEnabled )
	{

		log = "[DEBUG]" + log + "\n";
		FileUtil::AppendToFile( "log.txt", log );

	}

}

void Log::Error( std::string log )
{

	log = "[ERROR]" + log + "\n";
	FileUtil::AppendToFile( "log.txt", log );

}

void Log::Log( std::string log )
{

	FileUtil::AppendToFile( "log.txt", log + "\n" );

}
