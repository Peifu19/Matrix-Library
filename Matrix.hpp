#pragma once

template<class T>
class Matrix
{
public:
	// Constructors and Destructor
	Matrix() :m_row(0), m_col(0), m_element(nullptr) {}
	Matrix(int row, int col);
	Matrix(int row, int col, const T& val);
	Matrix(const Matrix<T>& matrix);
	Matrix(Matrix<T>&& matrix) noexcept;//move

	virtual ~Matrix();

	Matrix<T>& operator=(const Matrix<T>& matrix);
	Matrix<T>& operator=(Matrix<T>&& matrix);//move

	int row() const { return m_row; }
	int column() const { return m_col; }

	// methods
	void copy(const Matrix<T>& matrix);
	void show() const;//show elements

	// operator []
	T*& operator[](int i) { return m_element[i]; }
	const T* operator[](int i) const 
	{
		return const_cast<const T*>(m_element[i]);
	}
	T& at(int i, int j)
	{
		// check i and j
		return m_element[i][j];
	}
	const T& at(int i, int j) const
	{
		// check i and j
		return m_element[i][j];
	}

	// operator + 
	Matrix<T> operator + ()// positive
	{
		return *this;
	}
	Matrix<T> operator + (const Matrix<T>& mtx) const;
	Matrix<T>& operator += (const Matrix<T>& mtx);
	
	// operator -
	Matrix<T> operator - ();// minus
	Matrix<T> operator - (const Matrix<T>& mtx) const;
	Matrix<T>& operator -= (const Matrix<T>& mtx);

	// operator *
	//Matrix<T> operator * (const Matrix<T>& mtx) const;
	//Matrix<T>& operator *= (const Matrix<T>& mtx);

protected:
	int m_row;
	int m_col;
	T** m_element;
private:
	void initialize();
	void move(Matrix<T>& matrix);
};


// Implementation 
template<class T>
inline Matrix<T>::Matrix(int row, int col)
	:m_row(row), m_col(col), m_element(nullptr)
{
	this->initialize();
}

template<class T>
inline Matrix<T>::Matrix(int row, int col, const T& val)
	:m_row(row), m_col(col), m_element(nullptr)
{
	this->initialize(); 
	for (int m = 0; m < m_row; m++)
	{
		for (int n = 0; n < m_col; n++)
		{
			m_element[m][n] = val;
		}
	}
}

template<class T>
inline Matrix<T>::Matrix(const Matrix<T>& matrix)
{
	this->copy(matrix);
}

template<class T>
inline Matrix<T>::Matrix(Matrix<T>&& matrix) noexcept
{
	m_row = matrix.m_row;
	m_col = matrix.m_col;
	this->move(matrix);
}


template<class T>
inline Matrix<T>::~Matrix()
{
	if (m_element == nullptr)
	{
		return;
	}

	for (int i = 0; i < m_row; i++)
	{
		delete[] m_element[i];
	}
	delete[] m_element;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
{
	if (this==&matrix)
	{
		return *this;
	}
	else
	{
		this->copy(matrix);
	}
}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(Matrix<T>&& matrix)
{
	m_row = matrix.m_row;
	m_col = matrix.m_col;
	this->move(matrix);
	return *this;
}

template<class T>
inline void Matrix<T>::copy(const Matrix<T>& matrix)
{
	this->~Matrix();

	m_row = matrix.m_row;
	m_col = matrix.m_col;
	this->initialize();
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			m_element[i][j] = matrix[i][j];
		}
	}
}

template<class T>
inline void Matrix<T>::show() const
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			std::cout << m_element[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}


template<class T>
inline void Matrix<T>::initialize()
{
	if (m_row == 0 || m_col == 0)
	{
		m_element = nullptr;
		return;
	}
	m_element = new T * [m_row];
	for (int i = 0; i < m_row; i++)
	{
		m_element[i] = new T[m_col];
	}
}

template<class T>
inline void Matrix<T>::move(Matrix<T>& matrix)
{
	m_element = matrix.m_element;
	matrix.m_element = nullptr;
}

template<class T>
inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& mtx) const
{
	Matrix<T> ans = *this;
	ans += mtx;

	return ans;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& mtx)
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			m_element[i][j] += mtx[i][j];
		}
	}

	return *this;
}

template<class T>
inline Matrix<T> Matrix<T>::operator-()
{
	Matrix<T> ans = *this;
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			ans[i][j] = -ans[i][j];
		}
	}
	return ans;
}

template<class T>
inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& mtx) const
{
	Matrix<T> ans = *this;
	ans -= mtx;
	return ans;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& mtx)
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			this->m_element[i][j] -= mtx[i][j];
		}
	}
	return *this;
}
