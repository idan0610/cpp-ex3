// NoSquareException.h

#ifndef NOSQUAREEXCEPTION_H_
#define NOSQUAREEXCEPTION_H_

/**
 * This class is an exception thrown by Matrix<T> when the function trace() of Matrix<T> is called
 * on a matrix that is not square.
 */
class NoSquareException : std::exception
{
public:

	/**
	 * @return Message informing the caller about the error causing this exception to be thrown.
	 */
	virtual const char* what()
	{
		return "The given matrix is not square.";
	}

private:
};

#endif /* NOSQUAREEXCEPTION_H_ */
