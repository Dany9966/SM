#include <stdio.h>
#include <stdlib.h>
#include "iostream"

bool verificaCPUID(){
	int a = 0;
	int b = 0;
	__asm{
		pushfd
		pop eax
		mov eax, ecx
		mov eax,200000h
		push eax
		popfd
		pushfd
		pop eax
		xor eax,ecx
		je eGale
		mov ebx,1
		mov a,ebx
	eGale:
		mov ebx, 1
		mov b,ebx
	}
	if (a == 1){
		return true;
	}
	return false;
}

int main(){
	int x;
	std::cout << "Printf putem seta bit-ul 21 din EFLAGS: " << verificaCPUID()<<"\n";

	unsigned int a, b,c,d;
	//vendor ID
	long vendorID[3];
	vendorID[0] = 0;
	vendorID[1] = 0;
	vendorID[2] = 0;
	char *ceva;
	a = 0;
	__asm {
		mov eax, a
		cpuid
		mov dword ptr vendorID[0], ebx 
		mov dword ptr vendorID[1], ecx
		mov dword ptr vendorID[2],edx
	}
	ceva = (char *)vendorID;
	printf("Vendor ID : %s\n", ceva);

	a = 1;
	b = 0;
	c = 0;
	unsigned int aux;
	__asm{
		mov eax , a
		cpuid 
		mov b,eax
		mov c, ebx
		mov d, edx
	}
	printf("Model Number : %u\n", b & 240);
	printf("Family Code : %u\n", b & 3840);
	printf("Extended Mode : %u\n", b & 983040);
	printf("Processor Type : %u\n", b & 12288);
	printf("Extended Family : %u\n", b & 267386880);
	267386880;
	printf("Brand ID :%u\n", c & 255);
	printf("Supports FPU :%u\n", d & 1);
	printf("Supports virtual mode extension :%u\n", (d & 0x2) == 0x2);
	printf("Supports debbuging extension :%u\n", (d & 0x4) == 0x4);
	printf("Supports machine check operation  :%u\n", (d & 128) == 128);

	//numar de socotitoare intelepte
	a = 0x0B;
	b = 1;
	c = 0;
	__asm{
			mov eax, a
			mov ecx,b
			cpuid
			mov c, ebx
	}
	printf("Numar de procesoare logice configurate : %u\n", c );

	a= 0x2;
	b = 1;
	c = 0;
	__asm{
			mov eax, a
			cpuid
			mov a ,eax
			mov b,ebx
			mov c,ecx
			mov d, edx

	}
	if ((a & 2147483648) == 0){
		printf("Description decode value 1 : %u\n", a & 4278190080);
		printf("Description decode value 2 : %u\n", a & 16711680);
		printf("Description decode value 3 : %u\n", a & 65280);
		printf("Description decode value 4 : %u\n", a & 255);
	}
	else{
		printf("Regiester eax is reserved\n");
	}
	if ((b & 2147483648) == 0){
		printf("Description decode value 5 : %u\n", b & 4278190080);
		printf("Description decode value 6 : %u\n", b & 16711680);
		printf("Description decode value 7 : %u\n", b & 65280);
		printf("Description decode value 8 : %u\n", b & 255);
	}
	else{
		printf("Regiester ebx is reserved\n");
	}
	if ((c & 2147483648) == 0){
		printf("Description decode value 9 : %u\n", c & 4278190080);
		printf("Description decode value 10 : %u\n", c & 16711680);
		printf("Description decode value 11 : %u\n", c & 65280);
		printf("Description decode value 12 : %u\n", c & 255);
	}
	else{
		printf("Regiester ecx is reserved\n");
	}
	if ((d & 2147483648 )== 0){
		printf("Description decode value 13 : %u\n", d & 4278190080);
		printf("Description decode value 14 : %u\n", d & 16711680);
		printf("Description decode value 15 : %u\n", d & 65280);
		printf("Description decode value 16 : %u\n", d & 255);
	}
	else{
		printf("Regiester edx is reserved\n");
	}
	system("pause");
	return 0;
	
}