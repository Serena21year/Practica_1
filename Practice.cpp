// Practice.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>

using namespace std;

// row, col(column)	- количество строк и количество столбцов матрицы,
// sum				- переменная, используемая для подсёта нулей,
// step				- переменная, отсчитывающая шаг от заглавной строки в цикле преобразований по методу Гаусса,
// sort1, sort2		- переменные, используемые для переноса нулей в низ матрицы,
// rank				- ранг матрицы,
// i, j, k, p		- переменные, необходимые для работы с двумерной матрицей,
// tempmath			- изменяемый множитель, используемый в преобразованиях,
// eps				- точность вычислений,
// matrix			- двумерный матрица.

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int row, col, sum = 0, step = 0, sort1, sort2, rank;
	int i, j, k, p, e;
	double tempmath, eps = 0.00001;

	cout << "Введите количество рядов: ";
	cin >> row;

	cout << "Введите количество столбцов: ";
	cin >> col;

	if (row <= 0 || col <= 0)
	{
		cout << "Ошибка. Неверные параметры матрицы." << endl;
		return 0;
	}
	rank = row;
	vector <vector <double>> matrix;

	// ввод матрицы

	for (int i = 0; i < row; i++)
	{
		vector <double> temp;
		for (int j = 0; j < col; j++)
		{
			cout << "Введите значение элемента matrix["
				<< i << "][" << j << "]: ";
			cin >> e;
			temp.push_back(e);
		}
		matrix.push_back(temp);
	}

	// вывод матрицы

	cout << endl;
	cout << "\nВот как Вы заполнили Вашу матрицу:\n";

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << "[" << i << "]" << "[" << j
			<< "] == " << matrix[i][j] << "\t";
		cout << endl;
	}

	cout << "\n";

	// приведение матрицы по методу Гаусса

		// проверка условия для диагонали ступеней

	if (col > row - 1)
	{
		for (k = 0; k < row - 1; k++)
		{

			// перенос нулей столбца в низ матрицы путём перемены строк (сортировка методом пузырька)

			j = k;
			for (sort1 = k; sort1 < row; sort1++) {
				for (sort2 = k; sort2 < row - 1; sort2++) {
					if (abs(matrix[sort2][j]) < abs(matrix[sort2 + 1][j]))
					{
						for (j = 0; j < col; j++) swap(matrix[sort2][j], matrix[sort2 + 1][j]);
					}
					j = k;
				}
			}

			// преобразования к ступенчатому виду

			for (i = k + 1; i < row; i++)
			{
				j = k;
				tempmath = matrix[i][j] / matrix[i - 1 - step][j];
				if (matrix[i][j] == 0)
				{
					step++;
					continue;
				}
				else
				{
					for (j = k; j < col; j++)
					{
						matrix[i - step - 1][j] = matrix[i - step - 1][j] * tempmath;
						matrix[i][j] = matrix[i][j] - matrix[i - step - 1][j];
					}
					step++;
				}
			}
			step = 0;

			// перенос нулевых строк в самый низ и подсчёт ранга матрицы

			for (p = 0; p < col; p++)
				if (matrix[k + 1][p] == 0) sum++;
			if (sum == col)
			{
				for (p = 0; p < col; p++)
				{
					swap(matrix[row - 1][p], matrix[k + 1][p]);
				}
			}
			sum = 0;
		}
	}

	else
	{
		for (k = 0; k < col; k++)
		{

			// перенос нулей столбца в низ матрицы путём перемены строк (сортировка методом пузырька)

			j = k;
			for (sort1 = k; sort1 < row; sort1++) {
				for (sort2 = k; sort2 < row - 1; sort2++) {
					if (matrix[sort2][j] < matrix[sort2 + 1][j])
					{
						for (j = 0; j < col; j++) swap(matrix[sort2][j], matrix[sort2 + 1][j]);
					}
					j = k;
				}
			}

			// преобразования к ступенчатому виду

			for (i = k + 1; i < row; i++)
			{
				j = k;
				tempmath = matrix[i][j] / matrix[i - 1 - step][j];
				if (matrix[i][j] == 0)
				{
					step++;
					continue;
				}
				else
				{
					for (j = k; j < col; j++)
					{
						matrix[i - step - 1][j] = matrix[i - step - 1][j] * tempmath;
						matrix[i][j] = matrix[i][j] - matrix[i - step - 1][j];
					}
					step++;
				}
			}
			step = 0;

			// перенос нулевых строк в самый низ матрицы

			for (p = 0; p < col; p++)
				if (matrix[k + 1][p] == 0) sum++;
			if (sum == col)
			{
				for (p = 0; p < col; p++)
				{
					swap(matrix[row - 1][p], matrix[k + 1][p]);
				}
			}
			sum = 0;
		}
	}

	// округление чисел близких к нулю

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (abs(matrix[i][j]) < eps) matrix[i][j] = 0;
		}
	}

	// вывод приведенной матрицы

	cout << "\nПриведенная матрица:" << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << "[" << i << "]" << "[" << j
			<< "] == " << matrix[i][j] << "\t";
		cout << endl;
	}

	cout << "\n";

	// получение ранга матрицы

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (matrix[i][j] == 0) sum++;
		}
		if (sum == col) rank--;
		sum = 0;
	}

	// вывод ранга матрицы

	cout << "\nРанг матрицы: " << rank << endl;

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
