
#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

#include "Date.h"
#include "SupportFunc.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

using namespace std;



 
int selector()
{
 	int result;
 	while (true)
 	{
 		cin >> result;
 		if (cin.fail() == true)
 		{
 			cin.clear();
 			cin.ignore(numeric_limits<std::streamsize>::is_integer, '\n');
 			continue;
 		}

 		cin.ignore(numeric_limits<std::streamsize>::is_integer, '\n');
 		return result;
 	}
}

struct DataStruct
{
	int Id;
	string NLP; // ФИо
	string MainWork; // Работа
	date DateDeath; //Дата смерти
	date DateBourn; // дата рождения
	string CountryBourn; // страна рождения

};

vector<DataStruct> Storage;

void WriteLine()
{
	cout << "________________________________________________________________________________" << endl;
}

DataStruct UiData()
{
	DataStruct NewData;
	int day;
	int mount;
	int year;

	int dayd;
	int mountd;
	int yeard;

	cout << "ФИО :";
	getline(cin, NewData.NLP);
	cout << "Основные работы :";
	getline(cin, NewData.MainWork);
	cout << "Дата рождения " << endl;
	cout << "	День:"; day = selector();
	cout << "	Месяц:"; mount = selector();
	cout << "	Год:"; year = selector();
	NewData.DateBourn.setDate(day, mount, year);
	cout << "Дата смерти" << endl;
	cout << "	День:"; dayd = selector();
	cout << "	Месяц:"; mountd = selector();
	cout << "	Год:"; yeard = selector();
	NewData.DateDeath.setDate(dayd, mountd, yeard);
	cout << "Страна рождения:";
	getline(cin, NewData.CountryBourn);

	return NewData;

}

DataStruct AddData()
{
	WriteLine();

	cout << "Добавление данных" << endl;

	DataStruct NewData = UiData();

	cout << "Данные добавлены " << endl;
	WriteLine();
	return NewData;

}

DataStruct EditStorage()
{
	WriteLine();
	cout << "Изменение данных" << endl;

	DataStruct NewData;
	NewData = UiData();

	cout << "Данные Изменены " << endl;
	WriteLine();
	return NewData;
}

void LoadFile()
{
	ifstream file;
	file.open("Backup.buc");
	if (file.is_open() == false)
	{
		cout << "Файл не может быть открыт " << endl;
		return;
	}
	int CountData = 0;
	string buf;
	string line;
	file >> CountData;

	DataStruct tmp;
	
	Storage.clear();
	while (!file.eof())
	{

		getline(file, buf);
		if (buf == "{")
		{
			getline(file, line);
			tmp.Id = StringToInt(line);
			getline(file, line);
			tmp.NLP = line;
			getline(file, line);
			tmp.MainWork = line;
			getline(file, line);
			tmp.DateBourn.setStringdate(line);
			getline(file, line);
			tmp.DateDeath.setStringdate(line);
			getline(file, line);
			tmp.CountryBourn = line;
		}
		if (buf == "}")
		{
			Storage.push_back(tmp);
			tmp = DataStruct();
		}
	}
	file.close();

	cout << "файл был хагружен!" << endl;
	WriteLine();

}

void SaveFile()
{
	ofstream file;
	file.open("Backup.buc");
	if (file.is_open() == false)
	{
		cout << "Файл не может быть открыт " << endl;
		return;
	}

	file << (int)Storage.size() << " Count" << endl;
	int i = 0;
	for (auto DataItem : Storage)
	{
		i++;
		file << "{" << endl
			<< DataItem.Id << endl
			<< DataItem.NLP << endl
			<< DataItem.MainWork << endl
			<< DataItem.DateBourn.GetSringDate() << endl
			<< DataItem.DateDeath.GetSringDate() << endl
			<< DataItem.CountryBourn << endl
			<< "}" << endl;
	}
	file.close();
	cout << "Файл был сохранен." << endl;
}

void UiFileContext()
{
	int result;
	while (true)
	{
		WriteLine();
		cout
			<< "Работа с файлами ." << endl << endl
			<< "1) Загрузка. " << endl
			<< "2) Сохранение. " << endl
			<< "3) Назад. " << endl;
		WriteLine();
		cin >> result;
		switch (result)
		{
		case 1:
		{
			LoadFile();
			break;
		}

		case 2:
		{
			SaveFile();
			break;
		}

		case 3:
		{
			break;
		}
		
		}
		
	}

}

int UiGetidToEdit()
{
	
	while (true)
	{
	    int result;
		WriteLine();
		cout << "Введите ID для изменения" << endl;
		result = selector();
		if ((result > Storage.size() || (result < 0)))
		{
			if (result == 0)
			{
				return 0;
			}
			cout << "ошибка не коректный ID" << endl;
		}
		else
		{
			WriteLine();
			return result;
		}
	
	}
}

void UiTableEditor()
{
	int result;

	WriteLine();
	cout
		<< "1) Добавление данных. " << endl
		<< "2) Изменение данных. " << endl
		<< "3) Удаление. " << endl
		<< "4) Выход. " << endl;
	WriteLine();
	result = selector();

	switch (result)
	{
	case 1:
	{
		Storage.push_back(AddData());
		break;
	}

	case 2:
	{
		int id = UiGetidToEdit();
		if (id == 0)
		{
			cout << "Отмена изменения." << endl;
			break;
		}
		Storage[id - 1] = EditStorage();
		break;
	}

	case 3:
	{
		int id = UiGetidToEdit();
		if (id == 0)
		{
			cout << "Отмена удаления." << endl;
			break;
		}
		Storage.erase(Storage.begin() + id - 1);
		cout << "данные удалены " << endl;
		break;
	}

	case 4:
	{
		
		break;
	}
	return;
	}

}

void WriteTable()
{
	WriteLine();
	int id = 0;
	cout << setw(4) << "Id" << '|'
		<< setw(20) << "ФИО" << '|'
		<< setw(20) << "Работы " << '|'
		<< setw(17) << "Дата рождения" << '|'
		<< setw(17) << "Дата смерти" << '|'
		<< setw(20) << "Страна рождения" << '|'
		<< endl;
	for (auto DataItem : Storage)
	{
		id++;
		cout << setw(4) << id
			<< '|' << setw(20) << DataItem.NLP
			<< '|' << setw(20) << DataItem.MainWork
			<< '|' << setw(17) << DataItem.DateBourn.GetSringDate()
			<< '|' << setw(17) << DataItem.DateDeath.GetSringDate()
			<< '|' << setw(20) << DataItem.CountryBourn << '|' << endl;
	}
	cout << endl << "...Конец таблицы." << endl;
	UiTableEditor();
	WriteLine();
}

void createData(int countFaceData)
{

	for (int i = 0; i < countFaceData; i++)
	{
		DataStruct tmp;

		tmp.Id = i;
		tmp.NLP = IntToString(i) + " " + IntToString(i) + " " + IntToString(i);
		tmp.MainWork = "work " + IntToString(i);
		tmp.DateBourn.setDate(i, i, i + 1000);
		tmp.DateDeath.setDate(i, i, i + 1000);
		tmp.CountryBourn = "country " + IntToString(i);
		Storage.push_back(tmp);
	}

}

int main()
{
	createData(9000);
	setlocale(0, "russian");
	while (true)
	{
		int result;

		WriteLine();
		cout
			<< "База дынных" << endl << endl
			<< "1) Добавление данных. " << endl
			<< "2) Открытие таблицы. " << endl
			<< "3) Работа с Файлами. " << endl
			<< "4) Выход. " << endl;
		WriteLine();
		result = selector();

		switch (result)
		{
		case 1:
		{
			Storage.push_back(AddData());
			break;
		}

		case 2:
		{
			WriteTable();
			break;
		}

		case 3:
		{
			UiFileContext();
			break;
		}
		case 4:
		{
			
			break;
		}
     
		}

	}

}