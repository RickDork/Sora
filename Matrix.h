#ifndef MATRIX_H_
#define MATRIX_H_

#define RAD_CONSTANT 0.017453f

#include <cmath>
#include <cstring>

template< typename T >
class CMatrix
{

private:

	T m_RawMatrix[16];

public:

    T * GetRawMatrix()
    {

        return m_RawMatrix;

    }

	void Identity()
	{

		T o = ( T )1;
		T z = ( T )0;

		T newMat[] =
		{

			o, z, z, z,
			z, -o, z, z,
			z, z, o, z,
			z, z, z, o

		};

        std::memcpy( m_RawMatrix, newMat, sizeof( T ) * 16 );

	}

	void SetTranslate( T x, T y, T z )
	{

		m_RawMatrix[12] = x;
		m_RawMatrix[13] = y;
		m_RawMatrix[14] = z;

	}

	void Translate( T x, T y, T z )
	{

		m_RawMatrix[12] += x;
		m_RawMatrix[13] += y;
		m_RawMatrix[14] += z;

	}
    
    void GetScale( T * x, T * y, T * z ) {
     
        *x = m_RawMatrix[0];
        *y = m_RawMatrix[5];
        *z = m_RawMatrix[10];
        
    }

	void Scale( T x, T y, T z )
	{

		m_RawMatrix[0] = x;
		m_RawMatrix[5] = -y;
		m_RawMatrix[10] = z;

        /*
		m_RawMatrix[12] *= x;
		m_RawMatrix[13] *= y;
		m_RawMatrix[14] *= z;
        */

	}
    
    void ScaleMul( T x, T y, T z ) {
     
        m_RawMatrix[0] *= x;
        m_RawMatrix[5] *= y;
        m_RawMatrix[10] *= z;
        
    }

	void Rotate( float theta, float x, float y, float z )
	{

		T s = sin( theta * RAD_CONSTANT );
		T c = cos( theta * RAD_CONSTANT );
		T oc = ( 1 - c );
		T oczx = oc * ( z * x );
		T ocxy = oc * ( x * y );
		T oczy = oc * ( y * z );
		T zs = z * s;
		T ys = y * s;
		T xs = x * s;
        T ze = ( T )0;
        T o = ( T )1;

		T rotMat[] =
		{

			oc * ( x * x ) + c, ocxy + zs, oczx - ys, ze,
			ocxy - zs, oc * ( y * y ) + c, oczy + xs, ze,
			oczx + ys, oczy - xs, oc * ( z * z ) + c, ze,
			ze, ze, ze, o

		};

		Mat4v4Multiply( rotMat );

	}

	void Mat4v4Multiply( T * mat )
	{

		T origMat[16];

		memcpy( origMat, m_RawMatrix, sizeof( T ) * 16 );

		for( int j = 0; j < 4; j++ )
		{

			for( int i = 0; i < 4; i++ )
			{

				m_RawMatrix[i + j * 4] = ( T )0;

				for( int n = 0; n < 4; n++ )
				{
					m_RawMatrix[i + j * 4] += origMat[n + j * 4] * mat[i + n * 4];
				}

			}

		}

	}

};

#endif
