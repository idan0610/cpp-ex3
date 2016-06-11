CC = g++ -std=c++11
FLAGS = -Wextra -Wall -Wvla -pthread

Matrix: Matrix.hpp WrongDimensionsException.h NoSquareException.h OutOfMatrixException.h \
IllegalMatrixException.h IllegalVectorException.h Complex.h
	$(CC) $(FLAGS) -c $<
	
clean:
	rm -f *.gch
	
tar:
	tar -cvf ex3.tar Matrix.hpp WrongDimensionsException.h NoSquareException.h \
	OutOfMatrixException.h IllegalMatrixException.h IllegalVectorException.h Makefile README