#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <WinBase.h>
#include <Psapi.h>

int main(){
	while (1){
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		PERFORMANCE_INFORMATION perfInfo;
		GetPerformanceInfo(&perfInfo, sizeof(perfInfo));
		MEMORYSTATUSEX   succInfo;
		//succInfo = new MEMORYSTATUSEX(); //(MEMORYSTATUSEX *)malloc(sizeof(MEMORYSTATUSEX));
		succInfo.dwLength = sizeof(succInfo);
		if (!GlobalMemoryStatusEx(&succInfo)){
			printf("Eroare!\n");
			printf("%d\n", GetLastError());
			system("pause");
			exit(1);
		}

		
		printf("Dimensiunea paginii de memorie: %d B\n", sysInfo.dwPageSize);
		printf("Adresa Minima: %d\n", sysInfo.lpMinimumApplicationAddress);
		printf("Adresa maxima:  %d\n", sysInfo.lpMaximumApplicationAddress);


		printf("Total physical memory: %f GB\n", ((float)perfInfo.PhysicalTotal * (float)sysInfo.dwPageSize) / (1024.00*1024.00*1024.00));
		printf("Available physical memory : %f GB\n", ((float)perfInfo.PhysicalAvailable * (float)sysInfo.dwPageSize) / (1024.00*1024.00*1024.00));
		printf("Spatiu de memoria alocat SO-ului : %f GB\n", ((float)perfInfo.KernelTotal * (float)sysInfo.dwPageSize) / (1024.00*1024.00*1024.00));
		
		printf("Spatiul total de memorie virtuala alocat procesului : %d  B\n", succInfo.ullTotalVirtual);
		printf("Spatiul disponibil de memorie virtuala alocat procesului : %f  GB\n", (((float)succInfo.ullAvailVirtual) / (1024.00*1024.00*1024.00)));
		printf("Gradul de ocupare al memoriei: %Lf %%\n", (long double)succInfo.dwMemoryLoad);
		system("@cls||clear");
	}
	return 0;
}