#ifndef _VEC_H_
#define _VEC_H_

#include <math.h>

template<class T, unsigned SIZE> class CMatrix;

// Vector class for SIMPLE data types
template <class T, unsigned SIZE> class CVector 
{
public:

	// standard constructor
	CVector<T,SIZE> ()  
	{   // initialize all elements with zero
		for (int i=0; i<SIZE; i++) m_atData[i] = T(0);
	}

	// construction with data array
	CVector<T, SIZE> (const T atData[SIZE]) 
	{
		for (int i=0; i<SIZE; i++) m_atData[i] = atData[i];		
	}

	// copy constructor
	CVector<T, SIZE> (const CVector<T, SIZE> &vec) 
	{
		if (this==&vec) return; // nothing to do, it's me
		for (int i=0; i<SIZE; i++) m_atData[i] = vec.m_atData[i];
	}

	// destructor
	~CVector () 
	{	// nothing to do here ...
	}

	void setData (const T atData[SIZE]) 
	{
		for (int i=0; i<SIZE; i++) m_atData[i] = atData[i];		
	}

	void getData (T atData[SIZE]) 
	{
		for (int i=0; i<SIZE; i++) atData[i] = m_atData[i];
	}
    
    float getAngle(CVector<T, SIZE> &vec) {
        float scalar_product = (*this) * vec;
        float length_this = getLength();
        float length_vec = vec.getLength();
        float angle_radians = acos(scalar_product / (length_this * length_vec));
        if (angle_radians == 0 && scalar_product <= 0) {
            return M_PI;
        }
        return angle_radians;
    }
    
    float getLength() {
        float sum = 0;
        for (int i=0; i<SIZE; i++) sum += pow(m_atData[i], 2);
        return sqrt(sum);
    }

	unsigned getDimension () 
	{
		return SIZE;
	}

	CVector<T, SIZE> &operator = (const CVector<T, SIZE> &vec) 
	{
		if (this==&vec) return (*this); // ok, it's me, so no L-value action
		for (int i=0; i<SIZE; i++)		// not me, so L-Value action: copy data
			m_atData[i] = vec.m_atData[i];

		return (*this); // also an R-value in e.g
						// vec1    =       vec2      = vec3;
						// L-Value = R-Value/L-Value = R-Value
	}

	CVector<T, SIZE> &operator = (const T atData[SIZE]) 
	{
		for (int i=0; i<SIZE; i++) // not me, so L-Value action: copy data
			m_atData[i] = atData[i];

		return (*this); // also an R-value in e.g.
						// vec1  = vec2  +   (vec2=atData); // parenthesis () needed to evaluate expression vec2=atData
						// L-Val = R-Val +       R-Val
						//   "   =   "   + (L-Val = R-Val)
	}

	// usage of operator:
	// vec(i) = var;	// 0 <= i <= SIZE-1
	// var = vec(i);
	// vec1(i) = vec2(j);
	T &operator () (unsigned i) 
	{
		if (i>=SIZE) i = SIZE-1;	// !!! operator clips index ...	
		return m_atData[i];			// ... so we can safely return a reference
	}

	T operator () (unsigned i) const 
	{
		if (i>=SIZE) i = SIZE-1;
		return m_atData[i];
	}

	void operator += (const CVector<T, SIZE> &vec) 
	{
		for (int i=0; i<SIZE; i++) m_atData[i] += vec.m_atData[i];
	}

	CVector<T, SIZE> operator + (const CVector<T, SIZE> &vec) 
	{
		CVector<T, SIZE> buf (m_atData);
		for (int i=0; i<SIZE; i++) buf.m_atData[i] += vec.m_atData[i];
		return buf;
	}

	void operator -= (const CVector<T, SIZE> &vec) 
	{
		for (int i=0; i<SIZE; i++) m_atData[i] -= vec.m_atData[i];
	}

	// binary -
	// vec1 - vec2 i.e. (*this) - vec
	CVector<T, SIZE> operator - (const CVector<T, SIZE> &vec) 
	{
		CVector<T, SIZE> buf (m_atData);
		for (int i=0; i<SIZE; i++) buf.m_atData[i] -= vec.m_atData[i];
		return buf;
	}

	// unary -
	// -vec i.e. -(*this)
	CVector<T, SIZE> operator - () 
	{
		T atBuffer[SIZE];
		for (int i=0; i<SIZE; i++) atBuffer[i] = -m_atData[i];
		return CVector<T, SIZE> (atBuffer);
	}

	T operator * (const CVector<T, SIZE> & vec) 
	{
		T dp = T(0);
		for (int i=0; i<SIZE; i++) dp += m_atData[i]*vec.m_atData[i];
		return dp;
	}

	void operator *= (T tScale) 
	{
		for (int i=0; i<SIZE; i++) m_atData[i] *= tScale;
	}

	CVector<T, SIZE> operator * (T tScale) 
	{
		T atBuffer[SIZE];
		for (int i=0; i<SIZE; i++) atBuffer[i] = m_atData[i]*tScale;
		return CVector<T, SIZE> (atBuffer);
	}
    
    CVector<T, SIZE> operator / (T tScale)
    {
        T atBuffer[SIZE];
        for (int i=0; i<SIZE; i++) atBuffer[i] = m_atData[i]/tScale;
        return CVector<T, SIZE> (atBuffer);
    }

	CVector<T, SIZE> operator * (const CMatrix<T, SIZE> &mat) 
	{
		CVector<T, SIZE> vec;
		for (int j=0; j<SIZE; j++)
			for (int i=0; i<SIZE; i++)
				vec(j) += m_atData[i]*mat(i,j);
		return vec;
	}
    
    CVector<T, 4> operator % (const CVector<T, 4> &vec)
    {
        float a_x = m_atData[0];
        float a_y = m_atData[1];
        float a_z = m_atData[2];
        
        float b_x = vec.m_atData[0];
        float b_y = vec.m_atData[1];
        float b_z = vec.m_atData[2];
        
        float result_x = a_y * b_z - a_z * b_y;
        float result_y = a_z * b_x - a_x * b_z;
        float result_z = a_x * b_y - a_y * b_x;
        
        float result_array[4] = {result_x, result_y, result_z, 1};
        return CVector(result_array);
    }

private:

	T m_atData[SIZE];

}; // class CVector


// some common vector classes (abbr. names)
typedef CVector<float, 2> CVec2f;
typedef CVector<float, 3> CVec3f;
typedef CVector<float, 4> CVec4f;

typedef CVector<double, 2> CVec2d;
typedef CVector<double, 3> CVec3d;
typedef CVector<double, 4> CVec4d;

typedef CVector<int, 2> CVec2i;
typedef CVector<int, 3> CVec3i;
typedef CVector<int, 4> CVec4i;

typedef CVector<bool, 2> CVec2b;
typedef CVector<bool, 3> CVec3b;
typedef CVector<bool, 4> CVec4b;

#endif
