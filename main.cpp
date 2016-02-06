/*
Число произвольной длины представлено в двоично-десятичной системе.
Десятичная цифра кодируется 4 битами - одной шестнадцатеричной цифрой.
Цифра F обозначает конец последовательности цифр.
Разработать функцию умножения чисел в такой форме представления.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//Структура для вывода числа в BCD формате
typedef struct
{
	char b1 : 1;
	char b2 : 1;
	char b3 : 1;
	char b4 : 1;
	char b5 : 1;
	char b6 : 1;
	char b7 : 1;
	char b8 : 1;
	char b9 : 1;
	char b10 : 1;
	char b11 : 1;
	char b12 : 1;
	char b13 : 1;
	char b14 : 1;
	char b15 : 1;
	char b16 : 1;
	char b17 : 1;
	char b18 : 1;
	char b19 : 1;
	char b20 : 1;
} bits;

//Функция преобразования из одного формата в другой
unsigned univers_convert(unsigned a, unsigned abase, unsigned bbase)
{
	if (abase == bbase) return a;
	unsigned adigit = 0;
	unsigned b = 0; // сюда собираем результат конверсии
	unsigned bpower = 1; // текущая степень abase
	while (a != 0)
	{
		adigit = a % abase;
		assert(adigit < bbase); // проверяем, что исходная цифра уместиться в целевую систему счисления
		b += bpower * (a % abase);
		a /= abase;
		bpower *= bbase;
	}
	return b;
}

// BCD (binary coded decimal), под десятичную цифру отводится 4 двоичных разряда (один 16-чный): 123 <-> 0x123
unsigned convert_to_BCD(unsigned a) { return univers_convert(a, 10, 16); } // 123 -> 0x123
//Из BCD в десятичный формат
unsigned convert_from_BCD(unsigned a) { return univers_convert(a, 16, 10); } // 0x123 -> 123

//вывод в двоично-десятичной форме
void BCDoutput(unsigned int data)
{
	bits *bn1;
	bn1 = (bits *)&data;
	if (data / 10000 != 0)
	{
		printf("%d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d\n", -bn1->b20, -bn1->b19, -bn1->b18, -bn1->b17, -bn1->b16, -bn1->b15, -bn1->b14, -bn1->b13, -bn1->b12, -bn1->b11, -bn1->b10, -bn1->b9, -bn1->b8, -bn1->b7, -bn1->b6, -bn1->b5, -bn1->b4, -bn1->b3, -bn1->b2, -bn1->b1);
	}
	else if (data / 100 != 0)
	{
		printf("%d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d\n", -bn1->b16, -bn1->b15, -bn1->b14, -bn1->b13, -bn1->b12, -bn1->b11, -bn1->b10, -bn1->b9, -bn1->b8, -bn1->b7, -bn1->b6, -bn1->b5, -bn1->b4, -bn1->b3, -bn1->b2, -bn1->b1);
	}else printf("%d%d%d%d %d%d%d%d\n", -bn1->b8, -bn1->b7, -bn1->b6, -bn1->b5, -bn1->b4, -bn1->b3, -bn1->b2, -bn1->b1);
}


int main()
{
	setlocale(LC_ALL, "rus");
	unsigned int data1,  data3,  data5;//переменные первого числа 
	unsigned int data2, data4, data6;//переменные второго числа 
	unsigned int res = 0, resBCD;//переменные результата умножения
	

	//Ввод и обработка первого числа
	printf("\nВведите первое число: ");
	scanf("%u", &data1);
	data3 = convert_to_BCD(data1);//преобразуем в BCD формат
	printf("BCD1 %d\n", data3);
	BCDoutput(data3); //вывод в BCD форме
	data5 = convert_from_BCD(data3);//преобразуем обратно в DEC формат для умножения
	printf("DEC1 %d\n", data5);
	

	//Ввод и обработка второго числа
	printf("\nВведите второе число:");
	scanf("%u", &data2);

	data4 = convert_to_BCD(data2);
	printf("BCD2 %d\n", data4);//преобразуем в BCD формат
	BCDoutput(data4);
	data6 = convert_from_BCD(data4);//преобразуем обратно в DEC формат для умножения
	printf("DEC2 %d\n", data6);
	

	//Выводим результат
	printf("\nРезультат умножения С: \n");
	res = data5 * data6;
	printf("В десятичной форме: %d \n", res);
	resBCD = convert_to_BCD(res);//преобразуем в BCD формат
	printf("В двоично-десятичной форме: %d \n", resBCD);
	BCDoutput(resBCD);


	return 0;
}
