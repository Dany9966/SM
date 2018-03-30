#include <stdio.h>
#include <intrin.h>  
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
//#pragma intrinsic(__rdtsc)  
LARGE_INTEGER masoaraTimpCode(DWORD  dwPriorityClass){
	HANDLE WINAPI x = GetCurrentProcess();
	SetPriorityClass(x, dwPriorityClass);
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < 10000; i++)
	for (int j = 0; j < 10000; j++)
	for (int k = 0; k < 5; k++);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;


	//
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	//

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	ElapsedMicroseconds.QuadPart /= 1000;
	return ElapsedMicroseconds;
}
LARGE_INTEGER masoaraTimpCode2(int nPriority){
	HANDLE WINAPI x = GetCurrentThread();
	SetThreadPriority(x, nPriority);
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	for (int i = 0; i < 10000; i++)
	for (int j = 0; j < 10000; j++)
	for (int k = 0; k < 5; k++);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;


	//
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	//

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	ElapsedMicroseconds.QuadPart /= 1000;
	return ElapsedMicroseconds;
}
int main()
{
	unsigned long first = 0;
	unsigned long last = 0;
	unsigned long first2 = 0;
	unsigned long last2 = 0;
	unsigned long long first3 = 0;
	unsigned long long last3 = 0;
	int check = 0;
	__asm{
		mov eax, 1
			cmp edx, 08H
			jnz EQUAL
			jmp NOTEQUAL

		EQUAL :
		mov check, 1
			rdtsc
			mov first, edx
			mov last, eax
		NOTEQUAL :

	}
	first3 = first * 4294967296;
	first3 = first3 + last;
	Sleep(1000);
	if (check){
		__asm{
				rdtsc
				mov first2, edx
				mov last2, eax

		}
		last3 = first2 * 4294967296;
		last3 = last3 + last2;
		printf("Frequency: %lu MHz\n",(last3 - first3 )/ 1000000);
	}
	HANDLE WINAPI x;
	x = GetCurrentThread();
	int ret = SetThreadAffinityMask(x, 2);
	if (0 == ret){
		printf("prosti");
	}
	else{
		printf("Ruleaza pe al doilea core\n");
	}

	// timp bucata de code
	LARGE_INTEGER  l;
	printf("Timp Proces Prioritate Maxima : ");
	l = masoaraTimpCode(0x00000100);
	printf("%llu ms\n", unsigned long long(l.QuadPart));

	printf("Timp Proces Prioritate Medie : ");
	l = masoaraTimpCode(0x00000020);
	printf("%llu ms\n", unsigned long long(l.QuadPart));

	printf("Timp Proces Prioritate Minima : ");
	l = masoaraTimpCode(0x00000040);
	printf("%llu ms\n", unsigned long long(l.QuadPart));
	// end timp bucata de code 

	// timp bucata de code
	printf("Timp Fir De Executie Prioritate Maxima : ");
	l = masoaraTimpCode2(2);
	printf("%llu ms\n", unsigned long long(l.QuadPart));

	printf("Timp Fir De Executie Prioritate Medie : ");
	l = masoaraTimpCode2(0);
	printf("%llu ms\n", unsigned long long(l.QuadPart));

	printf("Timp Fir De Executie Prioritate Minima : ");
	l = masoaraTimpCode2(-2);
	printf("%llu ms\n", unsigned long long(l.QuadPart));
	// end timp bucata de code 

	system("pause");
}
