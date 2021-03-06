#ifndef STATE_H_
#define STATE_H_

#include "GameContext.h"
#include "GraphicsContext.h"
#include "DrawContext.h"
#include "EntityManager.h"

enum {
  
    STATE_MSG_NONE = 0,
    STATE_MSG_SWITCH = 0x1,
    
};

class CStateBase
{

protected:

    bool m_bContinue, m_bInit, m_bPostInit;
    
    int m_StateMsg;
    long int m_StateStartTicks;
    std::string m_strMsgParam;

public:

    virtual void Init() = 0;
    virtual void PostInit() = 0;
    virtual void OnStateSwitch() = 0;
    
	virtual void Input() = 0;
	virtual void Think() = 0;
	virtual void Draw() = 0;

	virtual bool Continue() { return m_bContinue; }
    
    int GetStateMessage() {
     
        return m_StateMsg;
        
    }
    
    std::string GetStrStateMessageParam() {
     
        return m_strMsgParam;
        
    }
    
    void SwitchToAnotherState( std::string name ) {
     
        m_StateMsg = STATE_MSG_SWITCH;
        m_strMsgParam = name;
        
    }
    
    void ResetStateMessage() {
     
        m_StateMsg = STATE_MSG_NONE;
        m_strMsgParam = "";
        
    }
    
    void QuitState() {
     
        m_bContinue = false;
        
    }

	bool DidInit()
	{

	    return m_bInit;

	}

	bool DidPostInit()
	{

	    return m_bPostInit;

	}
    
    long int StateTicksElapsed() {
     
        return SDL_GetTicks() - m_StateStartTicks;
        
    }
    
    void SetStateStartTime( long int t ) {
     
        m_StateStartTicks = t;
        
    }

    CStateBase() : m_bContinue( true ), m_bInit( false ), m_bPostInit( false ), m_StateMsg( STATE_MSG_NONE ), m_strMsgParam( "" ),
                    m_StateStartTicks( 0 )
	{



	}

	virtual ~CStateBase() { }

};

template< class C = CGameContext<> >
class CState : public CStateBase
{

protected:

    C * m_pGameContext;

public:

	void SetGameContext( C * pGameContext )
	{

		m_pGameContext = pGameContext;

	}
    
    CTextureImage * GetTexture( std::string t ) {
     
        return m_pGameContext->GetTexture( t );
        
    }
    
    CFontMaterial * GetFont( std::string t, int s ) {
     
        return m_pGameContext->GetFont( t, s );
        
    }

	CState() : CStateBase()
	{

	}

	virtual ~CState() { }

};

#endif
