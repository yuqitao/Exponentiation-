#include<iostream>
#include<vector>
#include<stdio.h>
#include<map>
using namespace std;


int newBitChar(long x,bool**Bit) //将整型转换为比特串
{
	bool* pBit = NULL;
	int  cnt = 0;
	long tmp = x;
	long flag = 1;
	pBit = new bool[128];
	memset(pBit, 0, 128);
	while (tmp>0)
	{
		if (flag & x)
		{
			pBit[cnt] = 1;
		}
		flag = flag << 1;
		cnt++;
		tmp = tmp >> 1;
	}
	*Bit = pBit;
	return cnt;
}

void freeBitChar(bool *Bit)
{
	if (Bit)
	{
		delete[]Bit;
		Bit = NULL;
	}
}

long  sliding_wind_exp(long g, long p,long e,int w)
{
	
	long flag = 1;
	int ret = 0;
	int t = 0;//e为[dt-1,...d0]
	bool *Bit = NULL;
	t = newBitChar(e, &Bit);
	flag = pow(2, t-1);
	int cont = pow(2, w-1);
	int size = cont- 1; //窗口大小为w，i=1,3,5,2^w-1
	long g1 = g%p;
	long g2 = (g*g) % p;
	std::vector<long>G(cont,0);
	G[0]=g1;   
	for (int i=1;i<=size;++i) //预计算
	{
		G[i] = (G[i-1] * g2)%p;
	}
	long A = 1;
	int i = t-1;
	while(i>=0)
	{
		if (!Bit[i])
		{
			A = A * A%p;
			i = i - 1;
			
		}
		else
		{
			int L = i - w + 1; //按照窗口数，假设最大的位置
			if (L < 0) //有可能剩余比特数不够一个最大窗口数
			{
				L = 0;
			}
			int digi= 0;
			while (L <= i && !Bit[L])  //不能走到最大位置则退回
			{
				L++;
			}
			for (int index = i; index >=L; --index)//计算digi的值，从高位开始
			{
				digi = digi * 2 + Bit[index];
	   		}
			long tmp = A;
			int exp = pow(2, i - L + 1);
			for (int index = 1; index < exp; ++index)//A=A^(exp)
			{
				A = (A * tmp)%p; 
			}
			A = A * G[(digi-1)/2]%p;
			i = L - 1;
			
		}
	
	}
	freeBitChar(Bit);
	return  A;
}
int getMod(int m, int pow, int n)//网上找来的平方乘计算模幂
{
	int x = 1;
	int power = m % n;
	int mask = 1;
	for (int i = 0; i < 32; i++) {
		if ((pow & mask) != 0) {
			x = (x * power) % n;
		}
		power = (power * power) % n;
		mask = mask << 1;
	}
	return x;
}

int main()
{

	long e = 46;
	bool *Bit = NULL;
	/*int len = newBitChar(e, &Bit);
	for (int i = 0; i < len; ++i)
		printf("%d ", Bit[i]);*/
	int tmp = pow(2, 10);
	for (int i = 1; i <= tmp; ++i)
	{

		e = i;
		long A = sliding_wind_exp(2, 133, e, 3);
		int x = getMod(2, e, 133);
		if (A != x)
		{
			printf("A IS %d\n", A);
			printf("X is %d\n", x);
			break;
		}
		printf("\n*****%d*****\n", i);
	}
	long A = sliding_wind_exp(2, 133, INT_MAX, 3);
	int x = getMod(2, INT_MAX, 133);
	printf("INTMAX is %d\n", INT_MAX);
	printf("A is %d\n", A);
	printf("X is %d\n", x);
	printf("\n Done!\n");
	system("pause");
	return 0;
}
