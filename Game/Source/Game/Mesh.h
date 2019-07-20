#pragma once
#include "Color.h"

class ShaderProgram;
class Camera;

struct VertexAttributes
{
    VertexAttributes(float ax, float ay, Color acolor)
    {
        x = ax;
        y = ay;
        r = acolor.r;
        g = acolor.g;
        b = acolor.b;
        a = acolor.a;
    }

    //defaults
    float x = 0.0f, y = 0.0f;
    float r = 1.0f, g = 0.0f, b = 1.0f, a = 1.0f;
};

class Mesh
{
public:
    Mesh(ShaderProgram* ashader);
    ~Mesh();

    void Generate();

    void GenerateMesh(int aVertCount, VertexAttributes *avertexattributes, GLenum amode);
    void Draw(vec2 aposition, Camera* acamera, float ascale, float arotation);

    void GenerateTriangleFan(float aPosX, float aPosY, int aVertCount, float aRadius, Color aColor);

	vec2 GetCenter();

	float GetWidth();
	float GetHeight();

protected:
    ShaderProgram * m_pShader;
    GLuint m_VBO;

    int m_Vertcount;
    GLenum m_Mode;
	vec2 m_Anchor;
	Color m_Color;

    std::vector<VertexAttributes> m_VertexAttributes;
};