#include "Util.h"


#ifdef __APPLE__
    #include "CoreFoundation/CoreFoundation.h"
#endif

int Util::RoundToPower( int number, int power ) {
 
    
    int t = 1;
    
    while( t < number ) {
        
        t *= power;
    }
    
    return t;

    
}

bool Util::ContainsPoint( float x1, float y1, float x2, float y2, float w, float h ) {
    
    if( x1 >= x2 && y1 >= y2 ) {
     
        if( x1 <= x2 + w && y1 <= y2 + h )
            return true;
        
    }
    
    return false;
    
}

Vector2< int > Util::ConvertTicksIntoMS( long int time ) {
    
    long int totalseconds = time / 1000;
    int min = totalseconds / 60;
    int sec = totalseconds - min * 60;
    
    Vector2< int > v( min, sec );
    
    return v;
    
}

bool Util::DoesFileExist( std::string s )
{
    
    std::ifstream f( s );
    bool b = true;
    
    if( !f )
    {
        
        b = false;
        
    }
    
    f.close();
    
    return b;
    
}


int Util::RandomNumber( int min, int max )
{

	return ( int )( rand() % ( max + 1 - min ) ) + min;

}

float Util::MinF( float val, float n, float min ) {
 
    val += n;
    
    if( val < min )
        return min;
    
    return val;
    
}

float Util::MaxF( float val, float n, float max ) {
 
    val += n;
    
    if( val > max )
        return max;
    
    return val;
    
}

float Util::MinMaxF( float val, float n, float minmax ) {
 
    if( val > minmax )
        return Util::MinF( val, n, minmax );
    
    return Util::MaxF( val, n, minmax );
    
}

float Util::Dist( float x1, float y1, float x2, float y2 ) {
 
    float xdist = x1 - x2;
    float ydist = y1 - y2;
    
    return sqrtf( xdist*xdist + ydist*ydist );
    
}

float Util::Dist( Vector2< float > p1, Vector2< float > p2 ) {
 
    return Util::Dist( p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY() );
    
}

float Util::AngleBetweenPointsRadians( float x1, float y1, float x2,  float y2 ) {
    
    
    return std::atan2( y2 - y1, x2 - x1 );
    
}

float Util::AngleFromOriginRadians( float x, float y ) {
    
    return std::atan2( y, x );
    
}

float Util::AngleBetweenPoints( float x1, float y1, float x2,  float y2 ) {
 

    return Util::AngleBetweenPointsRadians( x1, y1, x2, y2 ) * RAD2DEG;
    
}

float Util::AngleFromOrigin( float x, float y ) {
    
    return Util::AngleFromOriginRadians( x, y ) * RAD2DEG;
    
}

bool Util::SignsEqual( float x, float y ) {
    
    if( x == 0.0f && y == 0.0f )
        return true;
        
    if( ( x > 0.0f && y > 0.0f ) ||
       ( x < 0.0f && y < 0.0f ) ) {
        
        return true;
        
    }
    
    return false;
    
}

void Util::FixAppleRelativeDirectory() {


    #ifdef __APPLE__
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
        char path[PATH_MAX];
    
        if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
        {
            return;
        }
    
        CFRelease(resourcesURL);
        
        chdir(path);
    #endif
    
}