#pragma once

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define CLAMP(x,a,b) MIN(MAX(x,a),b)

namespace math
{

	class vec2
	{
	public:
		//Constructors
		vec2() : x(0.0f), y(0.0f) {}
		vec2(float _x, float _y) : x(_x), y(_y) {}
		vec2(float * pArg) : x(pArg[0]), y(pArg[1]) {}
		vec2(const vec2 & vector) : x(vector.x), y(vector.y) {}

		//Vector's operations
		float Length();
		vec2 & Normalize();
		vec2 operator + (const vec2 & vector);
		vec2 & operator += (const vec2 & vector);
		vec2 operator - ();
		vec2 operator - (const vec2 & vector);
		vec2 & operator -= (const vec2 & vector);
		vec2 operator * (float k);
		vec2 & operator *= (float k);
		vec2 operator / (float k);
		vec2 & operator /= (float k);
		vec2 & operator = (const vec2 & vector);
		vec2 Modulate(const vec2 & vector);
		float Dot(const vec2 & vector);

		//access to elements
		float operator [] (unsigned int idx);

		//data members
		float x;
		float y;
	};

	//vec3

	class vec3
	{
	public:
		//Constructors
		vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		vec3(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]) {}
		vec3(const vec3 & vector) : x(vector.x), y(vector.y), z(vector.z) {}

		//Vector's operations
		float Length();
		vec3 & Normalize();
		vec3 operator + (const vec3 & vector);
		vec3 & operator += (const vec3 & vector);
		vec3 operator - ();
		vec3 operator - (const vec3 & vector);
		vec3 & operator -= (const vec3 & vector);
		vec3 operator * (float k);
		vec3 & operator *= (float k);
		vec3 operator / (float k);
		vec3 & operator /= (float k);
		vec3 & operator = (const vec3 & vector);
		vec3 Modulate(const vec3 & vector);
		float Dot(const vec3 & vector);
		vec3 Cross(const vec3 & vector);

		//access to elements
		float operator [] (unsigned int idx);

		// data members
		float x;
		float y;
		float z;
	};

	//vec4

	class Matrix;

	class vec4
	{
	public:
		//Constructors
		vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		vec4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f) {}
		vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		vec4(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]), w(pArg[3]) {}
		vec4(const vec3 & vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f) {}
		vec4(const vec3 & vector, float _w) : x(vector.x), y(vector.y), z(vector.z), w(_w) {}
		vec4(const vec4 & vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

		//Vector's operations
		float Length();
		vec4 & Normalize();
		vec4 operator + (const vec4 & vector);
		vec4 & operator += (const vec4 & vector);
		vec4 operator - ();
		vec4 operator - (const vec4 & vector);
		vec4 & operator -= (const vec4 & vector);
		vec4 operator * (float k);
		vec4 & operator *= (float k);
		vec4 operator / (float k);
		vec4 & operator /= (float k);
		vec4 & operator = (const vec4 & vector);
		vec4 Modulate(const vec4 & vector);
		float Dot(const vec4 & vector);

		//matrix multiplication
		vec4 operator * (const Matrix & m);

		//access to elements
		float operator [] (unsigned int idx);

		//data members
		float x;
		float y;
		float z;
		float w;
	};

	//Matrix 4 X 4


	class Matrix
	{
	public:
		//constructors
		Matrix() {}
		Matrix(float val);
		Matrix(const Matrix & mat);

		// Matrix operations
		Matrix & SetZero();
		Matrix & SetIdentity();

		Matrix	 Inverse();

		Matrix & SetRotationX(float angle);
		Matrix & SetRotationY(float angle);
		Matrix & SetRotationZ(float angle);
		Matrix & SetRotationAngleAxis(float angle, float x, float y, float z);

		Matrix & SetScale(float scale);
		Matrix & SetScale(float scaleX, float scaleY, float scaleZ);
		Matrix & SetScale(float * pScale);
		Matrix & SetScale(vec3 &scaleVec);

		Matrix & SetTranslation(float x, float y, float z);
		Matrix & SetTranslation(float *pTrans);
		Matrix & SetTranslation(vec3 &vec);

		Matrix & SetPerspective(float fovY, float aspect, float nearPlane, float farPlane);

		Matrix Transpose();

		Matrix operator + (const Matrix & mat);
		Matrix & operator += (const Matrix & mat);
		Matrix operator - (const Matrix & mat);
		Matrix &operator -= (const Matrix & mat);

		Matrix operator * (const Matrix & mat);
		Matrix operator * (float k);
		Matrix & operator *= (float k);

		vec4 operator * (const vec4 & vec);

		Matrix & operator = (const Matrix & mat);

		//data members
		float m[4][4];
	};
}
