#include "FrameworkPCH.h"

ShaderProgram::ShaderProgram()
{
    m_VertShaderString = 0;
    m_FragShaderString = 0;

    m_VertShader = 0;
    m_FragShader = 0;
    m_Program = 0;
}

ShaderProgram::ShaderProgram(const char* vertfilename, const char* fragfilename)
{
    m_VertShaderString = 0;
    m_FragShaderString = 0;

    m_VertShader = 0;
    m_FragShader = 0;
    m_Program = 0;

    Init( vertfilename, fragfilename );
}

ShaderProgram::~ShaderProgram()
{
    Cleanup();
}

void ShaderProgram::Cleanup()
{
    if( m_VertShaderString )
        delete[] m_VertShaderString;
    if( m_FragShaderString )
        delete[] m_FragShaderString;

    glDetachShader( m_Program, m_VertShader );
    glDetachShader( m_Program, m_FragShader );

    if( m_VertShader )
        glDeleteShader( m_VertShader );
    if( m_FragShader )
        glDeleteShader( m_FragShader );
    if( m_Program )
        glDeleteProgram( m_Program );

    m_VertShaderString = 0;
    m_FragShaderString = 0;

    m_VertShader = 0;
    m_FragShader = 0;
    m_Program = 0;
}

void ShaderProgram::CompileShader(GLuint& shaderhandle, const char* shaderstring)
{
#if WIN32
    const char* strings[] = { shaderstring };
    glShaderSource( shaderhandle, 1, strings, 0 );
#else
    const char* strings[] = { "precision highp float;\n", shaderstring };
    glShaderSource( shaderhandle, 2, strings, 0 );
#endif

    glCompileShader( shaderhandle );

    //GLenum errorcode = glGetError();

    int compiled = 0;
    glGetShaderiv( shaderhandle, GL_COMPILE_STATUS, &compiled );
    if( compiled == 0 )
    {
        int infolen = 0;
        glGetShaderiv( shaderhandle, GL_INFO_LOG_LENGTH, &infolen );

        char* infobuffer = new char[infolen+1];
        glGetShaderInfoLog( shaderhandle, infolen+1, 0, infobuffer );
        OutputMessage( infobuffer );
        assert( false );
        delete[] infobuffer;

        glDeleteShader( shaderhandle );
        shaderhandle = 0;
    }
}

bool ShaderProgram::Init(const char* vertfilename, const char* fragfilename)
{
    m_VertShaderString = LoadCompleteFile( vertfilename, 0 );
    m_FragShaderString = LoadCompleteFile( fragfilename, 0 );

    assert( m_VertShaderString != 0 && m_FragShaderString != 0 );
    if( m_VertShaderString == 0 || m_FragShaderString == 0 )
        return false;

    return Reload();
}

bool ShaderProgram::Reload()
{
    assert( m_VertShaderString != 0 );
    assert( m_FragShaderString != 0 );

    m_VertShader = glCreateShader( GL_VERTEX_SHADER );
    m_FragShader = glCreateShader( GL_FRAGMENT_SHADER );

    CompileShader( m_VertShader, m_VertShaderString );
    CompileShader( m_FragShader, m_FragShaderString );

    if( m_VertShader == 0 || m_FragShader == 0 )
    {
        Cleanup();
        return false;
    }

    m_Program = glCreateProgram();
    glAttachShader( m_Program, m_VertShader );
    glAttachShader( m_Program, m_FragShader );

    glLinkProgram( m_Program );

    int linked = 0;
    glGetProgramiv( m_Program, GL_LINK_STATUS, &linked );
    if( linked == 0 )
    {
        int infolen = 0;
        glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &infolen );

        char* infobuffer = new char[infolen+1];
        glGetProgramInfoLog( m_Program, infolen+1, 0, infobuffer );
        OutputMessage( infobuffer );
        assert( false );
        delete[] infobuffer;

        Cleanup();
        return false;
    }

    return true;
}
