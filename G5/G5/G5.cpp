#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <string>
#include <Windows.h>

#define DEBUG_LOG 1

using namespace std;

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

void G5(char *&string, unsigned int *&_key) {
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
		*(string + i) == 'a' || *(string + i) == 'A' ? alph_index[i] = 97
			: *(string + i) == 'b' || *(string + i) == 'B' ? alph_index[i] = 98
			: *(string + i) == 'c' || *(string + i) == 'C' ? alph_index[i] = 99
			: *(string + i) == 'd' || *(string + i) == 'D' ? alph_index[i] = 100
			: *(string + i) == 'e' || *(string + i) == 'E' ? alph_index[i] = 101
			: *(string + i) == 'f' || *(string + i) == 'F' ? alph_index[i] = 102
			: *(string + i) == 'g' || *(string + i) == 'G' ? alph_index[i] = 103
			: *(string + i) == 'h' || *(string + i) == 'H' ? alph_index[i] = 104
			: *(string + i) == 'i' || *(string + i) == 'I' ? alph_index[i] = 105
			: *(string + i) == 'j' || *(string + i) == 'J' ? alph_index[i] = 106
			: *(string + i) == 'k' || *(string + i) == 'K' ? alph_index[i] = 107
			: *(string + i) == 'l' || *(string + i) == 'L' ? alph_index[i] = 108
			: *(string + i) == 'm' || *(string + i) == 'M' ? alph_index[i] = 109
			: *(string + i) == 'n' || *(string + i) == 'N' ? alph_index[i] = 110
			: *(string + i) == 'o' || *(string + i) == 'O' ? alph_index[i] = 111
			: *(string + i) == 'p' || *(string + i) == 'P' ? alph_index[i] = 112
			: *(string + i) == 'q' || *(string + i) == 'Q' ? alph_index[i] = 113
			: *(string + i) == 'r' || *(string + i) == 'R' ? alph_index[i] = 114
			: *(string + i) == 's' || *(string + i) == 'S' ? alph_index[i] = 115
			: *(string + i) == 't' || *(string + i) == 'T' ? alph_index[i] = 116
			: *(string + i) == 'u' || *(string + i) == 'U' ? alph_index[i] = 117
			: *(string + i) == 'v' || *(string + i) == 'V' ? alph_index[i] = 118
			: *(string + i) == 'w' || *(string + i) == 'W' ? alph_index[i] = 119
			: *(string + i) == 'x' || *(string + i) == 'X' ? alph_index[i] = 120
			: *(string + i) == 'y' || *(string + i) == 'Y' ? alph_index[i] = 121
			: *(string + i) == 'z' || *(string + i) == 'Z' ? alph_index[i] = 122
			: alph_index[i] = 0;

		if(*(alph_index + i) == 0) {
			cout << "Error #0: Unkown character";
#if DEBUG_LOG == 1
			std::cout << "Динамический массив alph_index не заполнен. Ошибка #0: Неизвестный символ." << endl;
#endif
		}
	}

	for(int i = 0; i < strlen(string) * 4 + 1; i++) {
		if(i < strlen(string)) {
			rand_nums[i] = rand() % 255;
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

void G5_encrypt(char *&string, unsigned int *&key) {
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

	int size = 11;
	int c_size = size - 1;
	unsigned int *key = new unsigned int[c_size];
	char *string = new char[size];
	string[c_size] = '\0';

	FillString(string);

	G5(string, key);

	std::cout << endl;

	Show(string, c_size);

	std::cout << endl;

	Show(key, c_size);

	std::cout << endl;

	G5_encrypt(string, key);

	Show(string, c_size);

	std::cout << endl;

	delete[] string;
	delete[] key;
	key = nullptr;
	string = nullptr;

	system("pause");
	return 0;
}