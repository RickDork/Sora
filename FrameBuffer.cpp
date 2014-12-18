#include "FrameBuffer.h"


void CFrameBufferObject::Init( int width, int height )
{
    
    m_Width = width;
    m_Height = height;
    
    glGenTextures( 1, &m_fboTexture );
    
    glBindTexture( GL_TEXTURE_2D, m_fboTexture );
    
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
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

void CFrameBufferObject::DrawTexture( CDrawContext * pDrawContext, CMatrix< float > * pModelMat )
{
    
    pModelMat->Scale( m_Width, -m_Height, 1.0f );
 
    
    BindTexture();
    pDrawContext->UpdateModelMatrix( pModelMat );
    pDrawContext->Draw2DVertexBuffer();
    
}
