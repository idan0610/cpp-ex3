// Matrix.hpp

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

// ------------------ Includes ------------------------------
#include <iostream>
#include <thread>
#include <vector>
#include "WrongDimensionsException.h"
#include "NoSquareException.h"
#include "OutOfMatrixException.h"
#include "IllegalMatrixException.h"
#include "IllegalVectorException.h"
#include "Complex.h"

/**
 * This class represents a generic mathematical matrix.
 */
template <class T>
class Matrix
{
public:
	// ------------------ Constructors ----------------------
	/**
	 * Default constructor. Initiates the matrix with size of 1X1 and sets its cell to 0.
	 * @throws bad_alloc if the memory allocation fails
	 */
	Matrix();

	/**
	 * Initiates the matrix with the size of rows X cols and sets its cells to 0.
	 * @param rows Number of rows
	 * @param cols Number of columns
	 * @throws bad_alloc if the memory allocation fails
	 * @throws IllegalMatrixException if one of the arguments rows and cols (but not both) is 0.
	 */
	Matrix(unsigned int rows, unsigned int cols);

	/**
	 * Copy Constructor. Copy the values of other to this.
	 * @param other The other matrix
	 * @throws bad_alloc if the memory allocation fails
	 */
	Matrix(const Matrix<T>& other);

	/**
	 * Move Constructor. Move the rvalue of other to this.
	 * @param other The other matrix
	 * @throws bad_alloc if the memory allocation fails
	 */
	Matrix(Matrix<T> && other);

	/**
	 * Initiates the matrix with the size of rows X cols and sets its cells to the items of cells.
	 * @param rows Number of rows
	 * @param cols Number of columns
	 * @param cells vector containing the cells of the matrix to assign.
	 * @throws bad_alloc if the memory allocation fails
	 * @throws IllegalMatrixException if one of the arguments rows and cols (but not both) is 0.
	 * @throws IllegalVectorException if the size of cells is not matching rows and cols.
	 */
	Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells);

	// ------------------ Destructor ------------------------
	/**
	 * Destructor for Matrix<T>.
	 */
	~Matrix();

	// ------------ Operators and Operations ----------------
	/**
	 * = operator. Assigns the values of this to the values of other.
	 * @param other The other matrix
	 * @return reference to this
	 * @throws bad_alloc if the memory allocation fails
	 */
	Matrix<T>& operator=(const Matrix<T>& other);

	/**
	 * + operator. Adds this and other and returns the new matrix.
	 * @param other The other matrix
	 * @return The result matrix
	 * @throws bad_alloc if the memory allocation fails
	 * @throws WrongDimensionsExceptions if the dimensions of this and other are not the same.
	 */
	const Matrix<T> operator+(const Matrix<T>& other) const;

	/**
	 * - operator. Subtracts other from this and returns the new matrix.
	 * @param other The other matrix
	 * @return The result matrix
	 * @throws bad_alloc if the memory allocation fails
	 * @throws WrongDimensionsExceptions if the dimensions of this and other are not the same.
	 */
	const Matrix<T> operator-(const Matrix<T>& other) const;

	/**
	 * * operator. Multiply this and other (according to matrices multiplication) and returns the
	 * new matrix.
	 * @param other The other matrix
	 * @return The result matrix.
	 * @throws bad_alloc if the memory allocation fails
	 * @throws WrongDimensionsExceptions if number of columns of this is not equal to the number of
	 * 		   rows of other.
	 */
	const Matrix<T> operator*(const Matrix<T>& other) const;

	/**
	 * == operator. Compare between this and other.
	 * @param other The other matrix
	 * @return true if this and other are equal, false otherwise.
	 */
	bool operator==(const Matrix<T>& other) const;

	/**
	 * != operator. Returns the opposite of == operator.
	 * @param other The other matrix
	 * @return true if this and other are not equal, false otherwise.
	 */
	bool operator!=(const Matrix<T>& other) const;

	/**
	 * Calculates and returns the transposed matrix of this.
	 * @return The transposed matrix.
	 * @throws bad_alloc if the memory allocation fails
	 */
	const Matrix<T> trans() const;

	/**
	 * Calculates and returns the trace of this.
	 * @return The trace.
	 * @throws NoSquareException if this matrix is not square
	 */
	const T trace() const;

	/**
	 * << operator. Friend function used to allow the << operator of std::ostream object to print
	 * to output Matrix<T> objects.
	 * @param os The ostream object
	 * @param mat The matrix to print
	 * @return Reference to the ostream object.
	 */
	template <class U>
	friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& mat);

	/**
	 * () operator. Returns the cell located in the given coordinates.
	 * @param row The cell row number
	 * @param col The cell column number
	 * @return The requested cell
	 * @throws OutOfMatrixException if the requested cell is not exist in the matrix.
	 */
	T& operator()(unsigned int row, unsigned int col);

	/**
	 * () operator. Returns the cell located in the given coordinates (const Matrix).
	 * @param row The cell row number
	 * @param col The cell column number
	 * @return The requested cell
	 * @throws OutOfMatrixException if the requested cell is not exist in the matrix.
	 */
	const T operator()(unsigned int row, unsigned int col) const;

	/**
	 * @return true if this matrix is square, false otherwise.
	 */
	inline bool isSquareMatrix()
	{
		return (_rows == _cols);
	}

	/**
	 * @return The number of rows of the matrix.
	 */
	inline unsigned int rows()
	{
		return _rows;
	}

	/**
	 * The number of columns of the matrix.
	 */
	inline unsigned int cols()
	{
		return _cols;
	}

	// ------------------ Iterator --------------------------
	/**
	 * Defining the const_iterator of Matrix as the const_iterator of vector<T>
	 */
	typedef typename std::vector<T>::const_iterator const_iterator;

	/**
	 * @return iterator for the first cell of the matrix.
	 */
	inline const_iterator begin()
	{
		return _matrix.cbegin();
	}

	/**
	 * @return iterator for one after the last cell of the matrix.
	 */
	inline const_iterator end()
	{
		return _matrix.cend();
	}

	// ------------------ Parallel --------------------------
	/**
	 * Change the value of static member _isParallel to the given parameter.
	 * @param isParallel value to set.
	 */
	static void setParallel(bool isParallel);

private:
	// ------------------ Data members ----------------------
	unsigned int _rows; /**< Number of rows of the matrix */
	unsigned int _cols; /**< Number of columns of the matrix */
	std::vector<T> _matrix; /**< Cells of the matrix */
	static bool _isParallel; /**< Is the parallel mode is on or off */

	// ------------------ Private functions -----------------
	/**
	 * Helper function used by the parallel method in operator +. Calculate the cells of newMatrix
	 * on the given row.
	 * @param other The other matrix
	 * @param newMatrix The result matrix
	 * @param row The row number
	 */
	void _addParallel(const Matrix<T>& other, Matrix<T>& newMatrix, unsigned int row) const;

	/**
	 * Helper function used by the parallel method in operator *. Calculate the cells of newMatrix
	 * on the given row.
	 * @param other The other matrix
	 * @param newMatrix The result matrix
	 * @param row The row number
	 */
	void _multParallel(const Matrix<T>& other, Matrix<T>& newMatrix, unsigned int row) const;
};

/**
 * default initialization for the _isParallel static member of Matrix<T> as false.
 */
template <class T>
bool Matrix<T>::_isParallel = false;

// ------------------ Constructors ----------------------
/**
 * Default constructor. Initiates the matrix with size of 1X1 and sets its cell to 0.
 * @throws bad_alloc if the memory allocation fails
 */
template <class T>
Matrix<T>::Matrix() : _rows(1), _cols(1)
{
	_matrix.push_back(T(0));
}

/**
 * Initiates the matrix with the size of rows X cols and sets its cells to 0.
 * @param rows Number of rows
 * @param cols Number of columns
 * @throws bad_alloc if the memory allocation fails
 * @throws IllegalMatrixException if one of the arguments rows and cols (but not both) is 0.
 */
template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols)
{
	if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0))
	{
		throw IllegalMatrixException();
	}

	_rows = rows;
	_cols = cols;
	for (unsigned int i = 0; i < rows * cols; i++)
	{
		_matrix.push_back(T(0));
	}
}

/**
 * Copy Constructor. Copy the values of other to this.
 * @param other The other matrix
 * @throws bad_alloc if the memory allocation fails
 */
template <class T>
Matrix<T>::Matrix(const Matrix<T>& other) : _rows(other._rows), _cols(other._cols),
											_matrix(other._matrix)
{
}

/**
 * Move Constructor. Move the rvalue of other to this.
 * @param other The other matrix
 * @throws bad_alloc if the memory allocation fails
 */
template <class T>
Matrix<T>::Matrix(Matrix<T> && other) : _rows(other._rows), _cols(other._cols),
									   _matrix(std::move(other._matrix))
{
}

/**
 * Initiates the matrix with the size of rows X cols and sets its cells to the items of cells.
 * @param rows Number of rows
 * @param cols Number of columns
 * @param cells vector containing the cells of the matrix to assign.
 * @throws bad_alloc if the memory allocation fails
 * @throws IllegalMatrixException if one of the arguments rows and cols (but not both) is 0.
 * @throws IllegalVectorException if the size of cells is not matching rows and cols.
 */
template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells)
{
	if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0))
	{
		throw IllegalMatrixException();
	}

	if (cells.size() != rows * cols)
	{
		throw IllegalVectorException();
	}

	_rows = rows;
	_cols = cols;
	_matrix = cells;
}

// ------------------ Destructor ------------------------
/**
 * Destructor for Matrix<T>.
 */
template <class T>
Matrix<T>::~Matrix()
{
}

// ------------ Operators and Operations ----------------
/**
 * = operator. Assigns the values of this to the values of other.
 * @param other The other matrix
 * @return reference to this
 * @throws bad_alloc if the memory allocation fails
 */
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	_rows = other._rows;
	_cols = other._cols;
	_matrix = other._matrix;
	return *this;
}

/**
 * + operator. Adds this and other and returns the new matrix.
 * @param other The other matrix
 * @return The result matrix
 * @throws bad_alloc if the memory allocation fails
 * @throws WrongDimensionsExceptions if the dimensions of this and other are not the same.
 */
template <class T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
	if (_rows != other._rows || _cols != other._cols)
	{
		throw WrongDimensionsException();
	}

	Matrix<T> newMatrix(*this);
	if(_isParallel)
	{
		std::vector<std::thread> threads;
		threads.resize(_rows);
		for (unsigned int i = 0; i < _rows; i++)
		{
			threads[i] = std::thread(&Matrix<T>::_addParallel, this, other, std::ref(newMatrix), i);
		}
		for (unsigned int j = 0; j < _rows; j++)
		{
			threads[j].join();
		}
	}
	else
	{
		for (unsigned int i = 0; i < _rows * _cols; i++)
		{
			newMatrix._matrix[i] += other._matrix[i];
		}
	}

	return newMatrix;
}

/**
 * - operator. Subtracts other from this and returns the new matrix.
 * @param other The other matrix
 * @return The result matrix
 * @throws bad_alloc if the memory allocation fails
 * @throws WrongDimensionsExceptions if the dimensions of this and other are not the same.
 */
template <class T>
const Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
	if (_rows != other._rows || _cols != other._cols)
	{
		throw WrongDimensionsException();
	}

	Matrix<T> newMatrix(*this);
	for (unsigned int i = 0; i < _rows * _cols; i++)
	{
		newMatrix._matrix[i] -= other._matrix[i];
	}

	return newMatrix;
}

/**
 * * operator. Multiply this and other (according to matrices multiplication) and returns the
 * new matrix.
 * @param other The other matrix
 * @return The result matrix.
 * @throws bad_alloc if the memory allocation fails
 * @throws WrongDimensionsExceptions if number of columns of this is not equal to the number of
 * 		   rows of other.
 */
template <class T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
	if (_cols != other._rows)
	{
		throw WrongDimensionsException();
	}

	Matrix<T> newMatrix(_rows, other._cols);
	if(_isParallel)
	{
		std::vector<std::thread> threads;
		threads.resize(_rows);
		for (unsigned int i = 0; i < _rows; i++)
		{
			threads[i] = std::thread(&Matrix<T>::_multParallel, this, other, std::ref(newMatrix), i);
		}
		for (unsigned int j = 0; j < _rows; j++)
		{
			threads[j].join();
		}
	}
	else
	{
		for (unsigned int i = 0; i < newMatrix._rows; i++)
		{
			for (unsigned int j = 0; j < newMatrix._cols; j++)
			{
				T cell(0);
				for (unsigned int k = 0; k < _cols; k++)
				{
					cell += (*this)(i, k) * other(k, j);
				}
				newMatrix(i, j) = cell;
			}
		}
	}

	return newMatrix;
}

/**
 * == operator. Compare between this and other.
 * @param other The other matrix
 * @return true if this and other are equal, false otherwise.
 */
template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other) const
{
	if (_matrix == other._matrix)
	{
		return true;
	}

	return false;
}

/**
 * != operator. Returns the opposite of == operator.
 * @param other The other matrix
 * @return true if this and other are not equal, false otherwise.
 */
template <class T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const
{
	return !(*this == other);
}

/**
 * Calculates and returns the transposed matrix of this.
 * @return The transposed matrix.
 * @throws bad_alloc if the memory allocation fails
 */
template <class T>
const Matrix<T> Matrix<T>::trans() const
{
	Matrix<T> newMatrix(_cols, _rows);
	for (unsigned int i = 0; i < newMatrix._rows; i++)
	{
		for (unsigned int j = 0; j < newMatrix._cols; j++)
		{
			newMatrix(i, j) = (*this)(j, i);
		}
	}

	return newMatrix;
}

/**
 * Specialization for the Complex calls. Calculates and returns the conjugated matrix of this.
 * @return The conjugated matrix.
 * @throws bad_alloc if the memory allocation fails
 */
template <>
const Matrix<Complex> Matrix<Complex>::trans() const
{
	Matrix<Complex> newMatrix(_cols, _rows);
	for (unsigned int i = 0; i < newMatrix._rows; i++)
	{
		for (unsigned int j = 0; j < newMatrix._cols; j++)
		{
			newMatrix(i, j) = (*this)(j, i).conj();
		}
	}

	return newMatrix;
}

/**
 * Calculates and returns the trace of this.
 * @return The trace.
 * @throws NoSquareException if this matrix is not square
 */
template <class T>
const T Matrix<T>::trace() const
{
	if (_rows != _cols)
	{
		throw NoSquareException();
	}
	T trace(0);
	for (unsigned int i = 0; i < _rows; i++)
	{
		trace += (*this)(i, i);
	}

	return trace;
}

/**
 * << operator. Friend function used to allow the << operator of std::ostream object to print
 * to output Matrix<T> objects.
 * @param os The ostream object
 * @param mat The matrix to print
 * @return Reference to the ostream object.
 */
template <class U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& mat)
{
	for (unsigned int i = 0; i < mat._rows; i++)
	{
		for (unsigned int j = 0; j < mat._cols; j++)
		{
			os << mat(i, j) << "\t";
		}
		os << std::endl;
	}
	return os;
}

/**
 * () operator. Returns the cell located in the given coordinates.
 * @param row The cell row number
 * @param col The cell column number
 * @return The requested cell
 * @throws OutOfMatrixException if the requested cell is not exist in the matrix.
 */
template <class T>
T& Matrix<T>::operator()(unsigned int row, unsigned int col)
{
	if (row > _rows || col > _cols)
	{
		throw OutOfMatrixException();
	}
	return _matrix[_cols * row + col];
}

/**
 * () operator. Returns the cell located in the given coordinates (const Matrix).
 * @param row The cell row number
 * @param col The cell column number
 * @return The requested cell
 * @throws OutOfMatrixException if the requested cell is not exist in the matrix.
 */
template <class T>
const T Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
	if (row > _rows || col > _cols)
	{
		throw OutOfMatrixException();
	}
	return _matrix[_cols * row + col];
}

// ------------------ Parallel --------------------------
/**
 * Change the value of static member _isParallel to the given parameter.
 * @param isParallel value to set.
 */
template <class T>
void Matrix<T>::setParallel(bool isParallel)
{
	if (isParallel != _isParallel)
	{
		std::cout << "Generic Matrix mode changed to ";
		if (isParallel)
		{
			std::cout << "parallel";
		}
		else
		{
			std::cout << "non-parallel";
		}
		std::cout << " mode." << std::endl;
	}
	_isParallel = isParallel;
}

// ------------------ Private functions -----------------
/**
 * Helper function used by the parallel method in operator +. Calculate the cells of newMatrix
 * on the given row.
 * @param other The other matrix
 * @param newMatrix The result matrix
 * @param row The row number
 */
template <class T>
void Matrix<T>::_addParallel(const Matrix<T>& other, Matrix<T>& newMatrix, unsigned int row) const
{
	for (unsigned int j = 0; j < newMatrix._cols; j++)
	{
		newMatrix(row, j) = (*this)(row, j) + other(row, j);
	}
}

/**
 * Helper function used by the parallel method in operator *. Calculate the cells of newMatrix
 * on the given row.
 * @param other The other matrix
 * @param newMatrix The result matrix
 * @param row The row number
 */
template <class T>
void Matrix<T>::_multParallel(const Matrix<T>& other, Matrix<T>& newMatrix, unsigned int row) const
{
	for (unsigned int j = 0; j < newMatrix._cols; j++)
	{
		T cell(0);
		for (unsigned int k = 0; k < _cols; k++)
		{
			cell += (*this)(row, k) * other(k, j);
		}
		newMatrix(row, j) = cell;
	}
}
#endif /* MATRIX_HPP_ */
