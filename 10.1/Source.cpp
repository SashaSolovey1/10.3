#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Price
{
	char name[64];
	string shop;
	double price;
};

void enter_save(char* fname);
void load_print(char* fname);
int main()
{
	char fname[61];
	char ch;
	do
	{
		cout << endl;
		cout << "Select:" << endl;
		cout << "[1] - enter & save data;" << endl;
		cout << "[2] - load & print data;" << endl << endl;
		cout << "[0] - exit." << endl << endl;
		cout << "Your choise: "; cin >> ch;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
				cout << "Enter file name: "; cin.getline(fname, sizeof(fname));
			enter_save(fname);
			break;
		case '2':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Enter file name: "; cin.getline(fname, sizeof(fname));
			load_print(fname);
			break;
		default:
			cout << "Error input! ";
		}
	} while (ch != '0');
	return 0;
}
void enter_save(char* fname)
{
	FILE* f;
	if ((f = fopen(fname, "wb")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	Price worker;
	char ch;
	do
	{
		cout << endl;
		cout << "name: "; cin.sync(); cin >> worker.name;
		cout << "shop: "; cin >> worker.shop;
		cout << "price: "; cin >> worker.price;
		if (fwrite(&worker, sizeof(Price), 1, f) != 1)
		{
			cerr << "Error writing file." << endl;
			return;
		}
		cout << "Continue? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	fclose(f);
}
void load_print(char* fname)
{
	FILE* f;
	if ((f = fopen(fname, "rb")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	Price worker;
	while (!feof(f))
	{
		if (fread(&worker, sizeof(Price), 1, f) != 1)
			if (feof(f))
			{
				cerr << "Error reading file." << endl;
				return;
			}
		cout << endl;
		cout << "name: " << worker.name << endl;
		cout << "shop: " << worker.shop << endl;
		cout << "price: " << worker.price << endl;
	}
	fclose(f);
}