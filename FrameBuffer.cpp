#include "FrameBuffer.h"

void CFrameBufferObject::Init( int width, int height ) {
 
    Init( width, height, 1.0f, 1.0f );
    
}

void CFrameBufferObject::Init( int width, int height, float wscale, float hscale )
{
    
    m_Width = ( float )width * wscale;
    m_Height = ( float )height * hscale;
    m_WidthScale = wscale;
    m_HeightScale = hscale;
    m_Offset.Set( 0.0f, ( float )height * ( 1.0f - hscale ) );
    
    glGenTextures( 1, &m_fboTexture );
    
    glBindTexture( GL_TEXTURE_2D, m_fboTexture );
    
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    glGenFramebuffersEXT( 1, &m_fboObject );
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_fboObject );
    glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_fboTexture, 0 );
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
    
}

CFrameBufferObject::~CFrameBufferObject()
{
    
    glDeleteFramebuffersEXT( 1, &m_fboObject );
    glDeleteTextures( 1, &m_fboTexture );
    
}

void CFrameBufferObject::DrawTextureNoFlip( CDrawContext * pDrawContext ) {
    
    CMatrix< float > mat;
    mat.Identity();
    mat.Translate( 0.0f, m_Height, 0.0f );
    
    DrawTexture( pDrawContext, &mat, false );
    
}

void CFrameBufferObject::DrawTexture( CDrawContext * pDrawContext ) {
 
    CMatrix< float > mat;
    mat.Identity();
    mat.Translate( 0.0f, m_Height, 0.0f );
    
    DrawTexture( pDrawContext, &mat, true );
    
}

void CFrameBufferObject::DrawTextureDontForceSize( CDrawContext * pDrawContext, CMatrix< float > * pModelMat )
{
    
    BindTexture();
    pDrawContext->SetTexCoord( 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f );
    pDrawContext->UpdateModelMatrix( pModelMat );
    pDrawContext->Draw2DVertexBuffer();
    
}

void CFrameBufferObject::DrawTexture( CDrawContext * pDrawContext, CMatrix< float > * pModelMat ) {
    
    DrawTexture( pDrawContext, pModelMat, true );
    
}

void CFrameBufferObject::DrawTexture( CDrawContext * pDrawContext, CMatrix< float > * pModelMat, bool b )
{
    
    float mul = ( b )? -1.0f : 1.0f;
    
    float sx, sy, sz;
    pModelMat->GetScale( &sx, &sy, &sz );
    pModelMat->ScaleMul( m_Width, mul * m_Height, 1.0f );
    
    DrawTextureDontForceSize( pDrawContext, pModelMat );
    
    pModelMat->Scale( sx, mul * sy, sz );
    
}
