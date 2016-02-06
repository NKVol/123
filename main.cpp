/*
����� ������������ ����� ������������ � �������-���������� �������.
���������� ����� ���������� 4 ������ - ����� ����������������� ������.
����� F ���������� ����� ������������������ ����.
����������� ������� ��������� ����� � ����� ����� �������������.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//��������� ��� ������ ����� � BCD �������
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

//������� �������������� �� ������ ������� � ������
unsigned univers_convert(unsigned a, unsigned abase, unsigned bbase)
{
	if (abase == bbase) return a;
	unsigned adigit = 0;
	unsigned b = 0; // ���� �������� ��������� ���������
	unsigned bpower = 1; // ������� ������� ybase
	while (a != 0)
	{
		adigit = a % abase;
		assert(adigit < bbase); // �������� ����� ������ ���������� � ������� ������� ���������
		b += bpower * (a % abase);
		a /= abase;
		bpower *= bbase;
	}
	return b;
}

// BCD (binary coded decimal), ��� ���������� ����� ��������� 4 �������� ������� (���� 16-����): 123 <-> 0x123
unsigned convert_to_BCD(unsigned a) { return univers_convert(a, 10, 16); } // 123 -> 0x123
//�� BCD � ���������� ������
unsigned convert_from_BCD(unsigned a) { return univers_convert(a, 16, 10); } // 0x123 -> 123

//����� � �������-���������� �����
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
	unsigned int data1,  data3,  data5;//���������� ������� ����� 
	unsigned int data2, data4, data6;//���������� ������� ����� 
	unsigned int res = 0, resBCD;//���������� ���������� ���������
	

	//���� � ��������� ������� �����
	printf("\n������� ������ �����: ");
	scanf("%u", &data1);
	data3 = convert_to_BCD(data1);//����������� � BCD ������
	printf("BCD1 %d\n", data3);
	BCDoutput(data3); //����� � BCD �����
	data5 = convert_from_BCD(data3);//����������� ������� � DEC ������ ��� ���������
	printf("DEC1 %d\n", data5);
	

	//���� � ��������� ������� �����
	printf("\n������� ������ �����: ");
	scanf("%u", &data2);

	data4 = convert_to_BCD(data2);
	printf("BCD2 %d\n", data4);//����������� � BCD ������
	BCDoutput(data4);
	data6 = convert_from_BCD(data4);//����������� ������� � DEC ������ ��� ���������
	printf("DEC2 %d\n", data6);
	

	//������� ���������
	printf("\n��������� ��������� �: \n");
	res = data5 * data6;
	printf("� ���������� �����: %d \n", res);
	resBCD = convert_to_BCD(res);//����������� � BCD ������
	printf("� �������-���������� �����: %d \n", resBCD);
	BCDoutput(resBCD);


	return 0;
}