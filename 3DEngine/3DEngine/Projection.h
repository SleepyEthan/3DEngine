#pragma once
#include <DirectXMath.h>

class Projection
{
public:
	Projection( float width, float height, float nearZ, float farZ );
	virtual DirectX::XMMATRIX GetMatrix() const = 0;
	void RenderWidgets();
protected:
	float width;
	float height;
	float nearZ;
	float farZ;
};

class Perspective : public Projection
{
public:
	Perspective( float width, float height, float nearZ, float farZ );
	DirectX::XMMATRIX GetMatrix() const override;
};


class Orthogonal : public Projection
{
public:
	Orthogonal( float width, float height, float nearZ, float farZ );
	DirectX::XMMATRIX GetMatrix() const override;
};