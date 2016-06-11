// WrongDimensionsException.h

#ifndef WRONGDIMENSIONSEXCEPTION_H_
#define WRONGDIMENSIONSEXCEPTION_H_

/**
 * This class is an exception thrown by Matrix<T> when the given matrix and the "this" matrix are
 * not matching in their dimensions for the operators +, - or *.
 */
class WrongDimensionsException : std::exception
{
public:

	/**
	 * @return Message informing the caller about the error causing this exception to be thrown.
	 */
	virtual const char* what()
	{
		return "The dimensions of the 2 matrices are not matching for this operation.";
	}

private:
};

#endif /* WRONGDIMENSIONSEXCEPTION_H_ */
