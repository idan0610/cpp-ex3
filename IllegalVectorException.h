// IllegalVectorException.h

#ifndef ILLEGALVECTOREXCEPTION_H_
#define ILLEGALVECTOREXCEPTION_H_

/**
 * This class is an exception thrown by Matrix<T> when in the constructor that gets 3 parameters -
 * rows, cols and vector, the size of the vector does not match the number of rows and columns.
 */
class IllegalVectorException : std::exception
{
public:

	/**
	 * @return Message informing the caller about the error causing this exception to be thrown.
	 */
	virtual const char* what()
	{
		return "The size of the given vector don't match the given numbers of rows and columns.";
	}

private:
};

#endif /* ILLEGALVECTOREXCEPTION_H_ */
