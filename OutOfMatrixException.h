// OutOfMatrixException.h

#ifndef OUTOFMATRIXEXCEPTION_H_
#define OUTOFMATRIXEXCEPTION_H_

/**
 * This class is an exception thrown by Matrix<T> when the operator () gets parameters row and col
 * for a cell that is not exist on the matrix.
 */
class OutOfMatrixException : std::exception
{
public:

	/**
	 * @return Message informing the caller about the error causing this exception to be thrown.
	 */
	virtual const char* what()
	{
		return "The requested cell is not exist.";
	}

private:
};

#endif /* OUTOFMATRIXEXCEPTION_H_ */
