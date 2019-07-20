#include "GamePCH.h"
#include "Mesh.h"

Mesh::Mesh(ShaderProgram* ashader)
{
    m_pShader = ashader;
    m_VBO = 0;
    m_Mode = GL_TRIANGLE_FAN;
    m_Vertcount = 0;
}

Mesh::~Mesh()
{
    // Release the VBO.
    glDeleteBuffers( 1, &m_VBO );
}

//final function that actually allocates the memory for the mesh in a VBO
void Mesh::Generate()
{
    assert(m_VBO == 0);
	
	m_Anchor = GetCenter();

    // Generate and fill buffer with our attributes.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(VertexAttributes) * m_VertexAttributes.size()), &m_VertexAttributes.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Check for errors.
    CheckForGLErrors();
}

//draws the mesh and sets uniforms
void Mesh::Draw(vec2 aposition, Camera* acamera, float ascale, float arotation)
{
    // Set our shader as the currently active one.
    glUseProgram(m_pShader->GetProgram());

    // Set our VBO created in GenerateTriangle() as the currently active one.
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // Get the index of the position attribute in our shader and setup the attribute details.
    GLint loc = glGetAttribLocation(m_pShader->GetProgram(), "a_Position");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
        glEnableVertexAttribArray(loc);
    }

    // Get the index of the Color attribute in our shader and setup the attribute details.
    GLint col = glGetAttribLocation(m_pShader->GetProgram(), "a_Color");
    if (col != -1)
    {
        glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)8);
        glEnableVertexAttribArray(col);
    }

	//set the line stats to be relative to the camera's scale
	//ie they shrink as the camera zooms out and vice versa
    glPointSize(DEFAULT_LINE_SIZE / acamera->GetScale());
    glLineWidth(DEFAULT_LINE_SIZE / acamera->GetScale());

	//UNIFORMS

	//offset
    GLint offsetLoc = glGetUniformLocation(m_pShader->GetProgram(), "u_Offset");
    glUniform2f(offsetLoc, aposition.x, aposition.y);

	//set the camera
	GLint trans = glGetUniformLocation(m_pShader->GetProgram(), "u_Translation");
	glUniform2f(trans, acamera->Getposition().x, acamera->Getposition().y);

	//camscale
	GLint campos = glGetUniformLocation(m_pShader->GetProgram(), "u_CameraScale");
	glUniform1f(campos, acamera->GetScale());

    //Set The world Scale
    GLint scl = glGetUniformLocation(m_pShader->GetProgram(), "u_Scale");
    glUniform1f(scl, ascale);

	//rotation
	GLint Rot = glGetUniformLocation(m_pShader->GetProgram(), "u_Rotation");
	glUniform1f(Rot, arotation);

	//center of the object, used for rotation, VERY EXPENSIVE
	GLint Center = glGetUniformLocation(m_pShader->GetProgram(), "u_Center");
	glUniform2f(Center, GetCenter().x, GetCenter().y);

    // Draw the triangle.
    glDrawArrays(m_Mode, 0, m_Vertcount);

    // Check for errors.
    CheckForGLErrors();
}

//Generates a mesh with any Drawmode
//Recommend using GenerateTriangleFan for the TriangleFan Draw Mode
//Remember to re-state the first vertex if the drawmode doesn't autocomplete
void Mesh::GenerateMesh(int aVertCount, VertexAttributes *avertexattributes, GLenum amode)
{
	assert(m_VBO == 0);
    m_Mode = amode;
    //reserve space for the 
    m_VertexAttributes.reserve(aVertCount);
    for (int x = 0; x < aVertCount; x++)
    {
        m_VertexAttributes.push_back(avertexattributes[x]);
    }
    m_Vertcount = aVertCount;

    assert(m_Vertcount > 1);
    Generate();
}

//Generates any mesh with a triangleFan Drawmode.
//Great for circles and the like
void Mesh::GenerateTriangleFan(float aPosX, float aPosY, int aVertCount, float aRadius, Color aColor)
{
    assert(m_VBO == 0);
    assert(aVertCount > 2);

    m_Vertcount = aVertCount;
	m_Color = aColor;
	
	//Center Position
	m_VertexAttributes.push_back(VertexAttributes(aPosX, aPosY, aColor));

	//The main body vertices
    float referenceAngle = 2 * PI / m_Vertcount;
    float angle = 0;
    for (int x = 0; x < aVertCount; x++)
    {
		float vertx = aPosX + (aRadius * cosf(angle));
		float verty = aPosY + (aRadius * sinf(angle));

		m_VertexAttributes.push_back(VertexAttributes(vertx, verty, aColor));

        angle += referenceAngle;
    }

	//The last vertex which is in the same place as the first, non-center, vertex to complete the object
	m_VertexAttributes.push_back(m_VertexAttributes.at(1));

	//Add the 2 extra points so the buffer can know about them
	m_Vertcount += 2;
    // Generate and fill buffer with our attributes.
	Generate();
}

//cycles through the object's verts and finds its center
vec2 Mesh::GetCenter()
{
	//VERY messily find the center
	float biggestX = -100000.0f;
	float biggestY = -100000.0f;

	float smallestX = 100000.0f;
	float smallestY = 100000.0f;

	for (unsigned int x = 0; x < m_VertexAttributes.size(); x++)
	{
		if (m_VertexAttributes.at(x).x > biggestX)
		{
			biggestX = m_VertexAttributes.at(x).x;
		}
		else if (m_VertexAttributes.at(x).x < smallestX)
		{
			smallestX = m_VertexAttributes.at(x).x;
		}

		if (m_VertexAttributes.at(x).y > biggestY)
		{
			biggestY = m_VertexAttributes.at(x).y;
		}
		else if (m_VertexAttributes.at(x).y < smallestY)
		{
			smallestY = m_VertexAttributes.at(x).y;
		}
	}

	return ((biggestX + smallestX) * 0.5f, (biggestY + smallestY) * 0.5f);
}

//Finds the distance between the farthest left and right x verts, returns that as width
float Mesh::GetWidth()
{
	//VERY messily find the ends
	float biggestX = -100000.0f;
	float smallestX = 100000.0f;

	for (unsigned int x = 0; x < m_VertexAttributes.size(); x++)
	{
		if (m_VertexAttributes.at(x).x > biggestX)
		{
			biggestX = m_VertexAttributes.at(x).x;
		}
		else if (m_VertexAttributes.at(x).x < smallestX)
		{
			smallestX = m_VertexAttributes.at(x).x;
		}
	}
	return biggestX - smallestX;
}

//Finds the distance between the farthest up and dow y verts, returns that as height
float Mesh::GetHeight()
{//VERY messily find the ends
	float biggestY = -100000.0f;
	float smallestY = 100000.0f;

	for (unsigned int x = 0; x < m_VertexAttributes.size(); x++)
	{
		if (m_VertexAttributes.at(x).y > biggestY)
		{
			biggestY = m_VertexAttributes.at(x).y;
		}
		else if (m_VertexAttributes.at(x).y < smallestY)
		{
			smallestY = m_VertexAttributes.at(x).y;
		}
	}

	return biggestY - smallestY;
}
