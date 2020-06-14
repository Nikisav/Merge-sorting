//Сортировка методом слияния

#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>

using namespace std;

void sort(vector<int>& mas, int start, int end);		// Главная функция сортировки

bool pff(int answer, int page);							// pff - Protection from fools, проверка на соответствие входных символов

void merge(vector<int>& mas, int l, int m, int r);		// Функция объединения

bool menu();											//Меню.___.

void fill_and_limit(vector<int>& mas, size_t size_mm);	// Заполняем вектор и ограничиваем размер чисел

void start_work(vector<int>& mas, size_t size);			//"Тело" программы

//////////////////////////////////////////////////////////////////////

int main()
{
	setlocale(LC_ALL,"RUS");

	srand(static_cast<size_t>(time(0)));

	bool wtd = menu();	//wtd - what to do, определяет, что программа будет делать дальше

	if (wtd == 0)
		return 0;

	size_t size_mm = 20;	//размерность массива
	vector<int> mas;	//главный массив

	fill_and_limit(mas, size_mm);

	start_work(mas, size_mm);

	return 0;
}

//////////////////////////////////////////////////////////////////////

void fill_and_limit(vector<int>& mas, size_t size_mm)	// Заполняем вектор и ограничиваем размер чисел
{
	for (size_t i = 0; i < size_mm; ++i) 
	{
		mas.push_back(rand() % 1000);
		cout << mas[i] << " ";
	}
}

bool pff(int answer, int page)							// pff - Protection from fools, проверка на соответствие входных символов
{
	if (page == 1)
		if (answer == 1 || answer == 2)
			return true;

	return false;
}

bool menu()												//Меню.___.
{
	int choice, page;
		cout << "Программа для сортировки массива";
		this_thread::sleep_for(chrono::milliseconds(1500));
		system("cls");

		page = 1;
		while (1)
		{
			cout << "==================МЕНЮ==================" << endl;
			cout << "1. Начать работу" << endl;
			cout << "2. Выйти из программы" << endl;
			cin >> choice;
			system("cls");
			if (pff(choice, page) == true)
				break;
		}
		if (choice == 2)
			return false;

	cout << "Прогон на случайном массиве (тест программы)\n " << endl;
	this_thread::sleep_for(chrono::milliseconds(1500));
	system("cls");
	return true;

}

void start_work(vector<int>& mas, size_t size)			//"Тело" программы
{
	chrono::time_point<chrono::high_resolution_clock> start, end;

	start = std::chrono::high_resolution_clock::now();
	
	sort(mas, 0, size - 1);

	cout << endl;
	for (const int& a : mas)
		cout << a << " ";

	end = std::chrono::high_resolution_clock::now();

	double elapsed_seconds = chrono::duration_cast<chrono::milliseconds> (end - start).count();
	cout << "затраченное время : " << elapsed_seconds << endl;
}

void merge(vector<int>& mas, int l, int m, int r)		// Функция объединения
{
	int i = l;
	int j = m + 1;
	vector<int> temp;
	while (i <= m && j <= r)

		if (mas.at(i) <= mas.at(j))
			temp.push_back(mas.at(i++));

		else
			temp.push_back(mas.at(j++));

	while (i <= m)
		temp.push_back(mas.at(i++));

	while (j <= r)
		temp.push_back(mas.at(j++));

	std::copy(temp.begin(), temp.end(), mas.begin() + l);
}

void sort(vector<int>& mas, int start, int end)		// Главная функция сортировки
{
	if (start < end) {
		int m = (start + end) / 2;

		function<void(vector<int>&, int, int)> func(sort);

		thread sort_thread1(func, ref(mas), start, m);
		thread sort_thread2(func, ref(mas), m + 1, end);

		sort_thread1.join();
		sort_thread2.join();

		merge(mas, start, m, end);
	}
}