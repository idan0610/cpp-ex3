// IllegalMatrixException.h

#ifndef ILLEGALMATRIXEXCEPTION_H_
#define ILLEGALMATRIXEXCEPTION_H_

/**
 * This class is an exception thrown by Matrix<T> when the defined matrix contains 0 rows and no
 * 0 columns or no 0 rows and 0 columns.
 */
class IllegalMatrixException : std::exception
{
public:

	/**
	 * @return Message informing the caller about the error causing this exception to be thrown.
	 */
	virtual const char* what()
	{
		return "The matrix can't have 0 rows and not 0 columns, or not 0 rows and 0 columns.";
	}

private:
};

#endif /* ILLEGALMATRIXEXCEPTION_H_ */
