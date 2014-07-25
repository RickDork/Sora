#ifndef SPRITE_H_
#define SPRITE_H_

#include "DrawContext.h"
#include "TextureImage.h"
#include "Matrix.h"

class CSprite
{

private:

    bool m_bActive;
    int m_CurFrameIndex, m_NextFrameTime;
    float m_Speed;
    CTextureImage * m_pTexture;

public:

    CSprite() : m_pTexture( NULL ), m_Speed( 1.0f ), m_CurFrameIndex( 0 ), m_NextFrameTime( 0 ), m_bActive( false )
    {


    }

	bool IsSet()
	{

		return ( m_pTexture );

	}

    void SetTexture( CTextureImage * pTexture )
    {

		if( !pTexture )
		{
			Log::Error( "Tried to set sprite to invalid texture" );
			return;
		}

        m_Speed = 1.0f;
        m_CurFrameIndex = 0;
        m_NextFrameTime = SDL_GetTicks() + pTexture->GetFrameDelay( 0 );
        m_bActive = ( pTexture->GetFrameCount() > 1 ) ? true : false;
        m_pTexture = pTexture;

    }

    void Think();
    void Draw( CDrawContext *, CMatrix< float > * );


};

#endif // SPRITE_H_
