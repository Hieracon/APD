#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// -----------------------------Prime Numbers-------------------

/*
bool isPrime(int n)
{
	if (n <= 1)
	{
		return false;
	}

	for (int i = 2; i < n; i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	MPI_Init(NULL, NULL);

	int size;
	int rank;
	int nrElements;
	int start;
	int N = 13;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		if (size >= 2)
		{
			nrElements = N / (size - 1);
		}
		else
		{
			printf("no se pueda");
			return 0;
		}

		for (int it = 1; it < size; ++it)
		{
			start = (it - 1) * nrElements;
			MPI_Send(&start, 1, MPI_INT, it, 1, MPI_COMM_WORLD);
			MPI_Send(&nrElements, 1, MPI_INT, it, 2, MPI_COMM_WORLD);
		}
	}
	else
	{
		MPI_Recv(&start, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&nrElements, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		if (rank == (size - 1))
		{
			nrElements = N;
		}
		else 
		{
			nrElements = nrElements + start;
		}

		for (int it = start + 1; it <= nrElements; ++it)
		{
			if (isPrime(it))
			{
				printf("Process %i found the prime number %i.\n", rank, it);
			}
		}
	}

	MPI_Finalize();
}
*/

// -----------------------------Prime Numbers-------------------

// ------------ARRAY SEARCH--------------------------------------

/*
int main(int argc, char** argv)
{
	MPI_Init(NULL, NULL);

	int size;
	int rank;
	int nrElements;
	int start;
	int notArray[] = {3,3,4,7,9,0,1,3,22,33,13,3};
	int searchedNumber = 3;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		if (size >= 2)
		{
			nrElements =  (sizeof(notArray) / sizeof(notArray[0]))/ (size - 1);
		}
		else
		{
			printf("no se pueda");
			return 0;
		}

		for (int it = 1; it < size; ++it)
		{
			start = (it - 1) * nrElements;
			MPI_Send(&start, 1, MPI_INT, it, 1, MPI_COMM_WORLD);
			MPI_Send(&nrElements, 1, MPI_INT, it, 2, MPI_COMM_WORLD);
		}
	}
	else
	{
		MPI_Recv(&start, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&nrElements, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		if (rank == (size - 1))
		{
			nrElements = (sizeof(notArray) / sizeof(notArray[0]));
		}
		else
		{
			nrElements = nrElements + start;
		}

		for (int it = start; it < nrElements; ++it)
		{
			if ((notArray[it] == searchedNumber))
			{
				printf("Process %i found the number at position %i.\n", rank, it);
			}
		}
	}

	MPI_Finalize();
}

*/

// ------------ARRAY SEARCH--------------------------------------

// ------------Random Numbers--------------------------------------

int main(int argc, char** argv)
{
	MPI_Init(NULL, NULL);

	int size;
	int rank;
	int nrElements;
	int randomNumbers;
	int randomNr;
	int sumProc = 0;
	int sum = 0;
	time_t start, end;
	double time_taken;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	srand((unsigned)time(NULL));

	if (rank == 0)
	{
		//start = clock();
		time(&start);

		for (int it = 1; it < size; ++it)
		{
			randomNumbers = rand() % 900 + 100;
			MPI_Send(&randomNumbers, 1, MPI_INT, it, 1, MPI_COMM_WORLD);
			MPI_Recv(&sumProc, 1, MPI_INT, it, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			sum = sum + sumProc;
		}

		printf("Final sum is : %i.\n", sum);

		//end = clock();
		time(&end);

		time_taken = double(end - start);

		printf("Process %i took %f seconds", rank, time_taken);
	}
	else
	{
		//start = clock();
		time(&start);

		MPI_Recv(&randomNumbers, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		for (int it = 0; it < randomNumbers; ++it)
		{
			randomNr = rand() % 10 + 1;

			//printf("Process %i generated the number %i.\n", rank, randomNr);

			sumProc = sumProc + randomNr;
		}

		MPI_Send(&sumProc, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);

		//end = clock();
		time(&end);

		time_taken = double(end - start);

		printf("Process %i took %f seconds", rank, time_taken);
	}

	MPI_Finalize();
}

// ------------Random Numbers--------------------------------------