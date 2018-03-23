#include <stdio.h>
#include <intrin.h>  
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

//#pragma intrinsic(__rdtsc)  

int main()
{
	int freq;
	unsigned long first = 0;
	int check = 0;
	__asm{
		mov eax, 1
			cmp edx, 08H
			jnz EQUAL
			jmp NOTEQUAL

		EQUAL :
		mov check, 1
		rdtsc
			add first, eax
			add first, edx
		NOTEQUAL:
	}
	Sleep(800);
	if (check){
		__asm{
			rdtsc
				sub first, eax
				sub first, edx
		}
		printf("Frequency: %ld\n", first/1000000);
	}
	system("pause");
}