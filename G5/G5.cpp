#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <string>
#include <Windows.h>
#include <fstream>

#define DEBUG_LOG 1

using namespace std;

void G5_encrypt(char *&string, unsigned int *&_key);

void file(char* args[], const char file_name[255], char *&_string, unsigned int *&key) {

	
	char command[255] = "";
	char* new_args[] = {args[0]};

	for(int i = 0; i < 1; i++) {
		for(int j = 0; j < strlen(args[i]); j++) {
			if(j == (strlen(args[i]) - 6)) {
				new_args[i][j] = '\0';
				break;
			}
		}
	}
#if DEBUG_LOG == 1
	for(int i = 0; i < 1; i++) {
		cout << new_args[i] << endl;
		cout << strlen(args[i]) << endl;
	}
#endif

	strcat_s(command, new_args[0]);
	strcat_s(command, file_name);
	strcat_s(command, ".txt");

	if(!file) {
		cout << "Файл не открыт\n\n";
	}

	ifstream file(command, ios::in);
	file.seekg(0, ios::end);
	size_t length = file.tellg();

	char *new_string = new char[length + 1];
	new_string[length] = '\0';

	for(int i = length, j = 0; i > 1; i--, j++) {
		file.seekg(-i, ios::end);
		new_string[j] = file.get();
	}

	G5_encrypt(new_string, key);
	file.close();

	ofstream file1(command);
	file1 << new_string;
	file1.close();

	delete[] _string;
	_string = new_string;
}

void FillString(char string[]) {
	int i = 0;
	while(string[i] != '\0') {
		string[i] = 'a';
		i++;
	}
}

template<typename T, typename T1> void Show(const T arr, const T1 size) {
	for(int i = 0; i < size; i++) {
		if(arr[i] == '\0') {
			break;
		}

		std::cout << *(arr + i) << " ";
	}
}

void G5_encrypt(char *&string, unsigned int *&_key) {
#if DEBUG_LOG == 1
	std::cout << "Вызвана функция генерации G5 кода..." << endl;
#endif
	srand(time(NULL));
	int *alph_index = new int[strlen(string)];
	int *rand_nums = new int[strlen(string) * 4];
	char *new_string = new char[strlen(string) * 4 + 1];
	new_string[strlen(string) * 4] = '\0';
	unsigned int *key = new unsigned int[strlen(string) * 4];
	unsigned int *key_1 = new unsigned int[strlen(string)];

	for(int i = 0; i < strlen(string); i++) {
		for(int j = 0; j < 256; j++) {
			if(string[i] == char(j)) {
				*(alph_index + i) = j;
			}
		}
	}

	for(int i = 0; i < strlen(string) * 4 + 1; i++) {
		if(i < strlen(string) * 4) {
			rand_nums[i] = rand() % 252 + 3;
			*(key + i) = rand_nums[i];
		}

		if(i % 4 == 0 && i != 0) {
			key_1[(i / 4) - 1] = (key[i - 1] * key[i - 2] * key[i - 3] * key[i - 4]) - alph_index[(i / 4) - 1];
		}
	}
#if DEBUG_LOG == 1
	std::cout << "Динамический массив rand_nums заплонен +" << endl;
#endif

#if DEBUG_LOG == 1
	std::cout << "Динамический массив key заплонен +" << endl;
#endif

	for(int i = 0; i < strlen(string) * 4; i++) {
		*(new_string + i) = char(rand_nums[i]);
	}

#if DEBUG_LOG == 1
	std::cout << "Динамический массив new_string заполнен +" << endl;
#endif

	delete[] alph_index;
	delete[] rand_nums;
	delete[] string;
	delete[] _key;
	delete[] key;
	rand_nums = nullptr;
	alph_index = nullptr;
	string = new_string;
	_key = key_1;
}

void G5_decipher(char *&string, unsigned int *&key) {
	int *rand_nums = new int[strlen(string)];
	unsigned int *rand_keys = new unsigned int[strlen(string) / 4];
	char *final_string = new char[strlen(string) / 4 + 1];
	final_string[strlen(string) / 4] = '\0';

	for(int i = 0; i < strlen(string) + 1; i++) {
		if(i < strlen(string)) {
			*(rand_nums + i) = string[i];
			if(rand_nums[i] < 0) {
				rand_nums[i] = rand_nums[i] + 256;
			}
		}

		if(i % 4 == 0 && i != 0) {
			rand_keys[(i / 4) - 1] = rand_nums[i - 1] * rand_nums[i - 2] * rand_nums[i - 3] * rand_nums[i - 4];
			final_string[(i / 4) - 1] = char(rand_keys[(i / 4) - 1] - key[(i / 4) - 1]);
		}
	}

	final_string[strlen(string) / 4] = '\0';


	delete[] rand_nums;
	delete[] rand_keys;
	delete[] string;
	rand_nums = nullptr;
	rand_keys = nullptr;
	string = final_string;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	system("color a");

	int size = 1;
	int c_size = size - 1;
	unsigned int *key = new unsigned int[c_size];
	char *string = new char[size];
	string[c_size] = '\0';

	file(argv, "example", string, key);

	//FillString(string);

	//G5_encrypt(string, key);

	//std::cout << endl;

	//Show(string, c_size);

	//std::cout << endl;

	//Show(key, c_size);

	//std::cout << endl;

	//G5_decipher(string, key);

	//Show(string, c_size);

	//std::cout << endl;

	delete[] string;
	delete[] key;
	key = nullptr;
	string = nullptr;

	system("pause");
	return 0;
}