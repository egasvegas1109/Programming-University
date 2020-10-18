#include <conio.h>
#include <iostream>
using namespace std;
#define m 3
#define n 3
class Matrix
{	
	public:
		Matrix(int,int);		
		void Vivod();
		Matrix operator+ (const Matrix&);		
	private:	
		int rows;
		int columns;
		int *aMas;
};
Matrix::Matrix(int rows,int columns)
{	
	this->rows = rows;
	this->columns = columns;
	aMas = new int[rows * columns];

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			*(this->aMas + i * this->rows + j) = i + j*2+1;
		}
	}
}

void Matrix::Vivod()
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			printf("%d ", *(this->aMas + i * this->rows + j));
		}
		printf("\n");
	}
}

Matrix Matrix::operator+(const Matrix &rhs)
{
	Matrix result(*this);
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			*(this->aMas + i * this->rows + j) += *(result.aMas + i * result.rows + j);
		}
	}
	return result;
}


int main()
{

	Matrix m1(m,n), m2(m,n);	
	printf("1 Vivod: \n");
	m1.Vivod();
	printf("2 Vivod: \n");
	m2.Vivod();
	m2 = m2 + m1;
	printf("Vivod: resulta\n");
	m2.Vivod();
	_getch();
	return 0;
}