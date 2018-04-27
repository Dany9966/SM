#include <stdio.h>
#include <Windows.h>
#include <DbgHelp.h>
#pragma comment( lib, "dbghelp.lib" )
#pragma const_seg(".t_const") // begin allocating const data in a new section whose name is 8 bytes long (the max)
const char const_string1[] = "This string is allocated in a special const data segment named \".t_const\".";
#pragma const_seg() // resume allocating const data in the normal .rdata section

void foo(unsigned int n1, float f1, unsigned long long f2){
	printf("Primul parametru al functiei:\n");
	printf("Adresa n1: %x\n", &n1);
	printf("Size n1: %d bytes\n", sizeof(n1));
	printf("n1 Encoding: signed integer\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int)&n1) % sizeof(n1), sizeof(n1));
	printf("Value : %d\n", n1);
	printf("\n");

	printf("Al doilea parametru al functiei:\n");
	printf("Adresa f1: %x\n", &f1);
	printf("Size f1: %d bytes\n", sizeof(f1));
	printf("f1 Encoding: single precission float\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int)&f1) % sizeof(f1), sizeof(f1));
	printf("Value : %.2f\n", f1);
	printf("\n");

	printf("Al treilea parametru al functiei:\n");
	printf("Adresa f2: %d\n", &f2);
	printf("Size f2: %d bytes\n", sizeof(f2));
	printf("f2 Encoding: unsigned long integer\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int)&f2) % sizeof(f2), sizeof(f2));
	printf("Value : %llu\n", f2);
	printf("\n");
}

void print_PE_section_info(HANDLE hModule, PDWORD pFrame) // hModule is the handle to a loaded Module (.exe or .dll)
{
	// get the location of the module's IMAGE_NT_HEADERS structure
	IMAGE_NT_HEADERS *pNtHdr = ImageNtHeader(hModule);

	// section table immediately follows the IMAGE_NT_HEADERS
	IMAGE_SECTION_HEADER *pSectionHdr = (IMAGE_SECTION_HEADER *)(pNtHdr + 1);

	const char* imageBase = (const char*)hModule;
	char scnName[sizeof(pSectionHdr->Name) + 1];
	scnName[sizeof(scnName)-1] = '\0'; // enforce nul-termination for scn names that are the whole length of pSectionHdr->Name[]
	PDWORD pFrame2;
	for (int scn = 0; scn < pNtHdr->FileHeader.NumberOfSections; ++scn)
	{
		// Note: pSectionHdr->Name[] is 8 bytes long. If the scn name is 8 bytes long, ->Name[] will
		// not be nul-terminated. For this reason, copy it to a local buffer that's nul-terminated
		// to be sure we only print the real scn name, and no extra garbage beyond it.
		strncpy(scnName, (const char*)pSectionHdr->Name, sizeof(pSectionHdr->Name));
		if ((strcmp(scnName, ".textbss") == 0)){
			pFrame2 = imageBase + pSectionHdr->VirtualAddress + pSectionHdr->Misc.VirtualSize - 1;
			printf(" %p...%p %-10s (%u bytes)\n",
				imageBase + pSectionHdr->VirtualAddress,
				imageBase + pSectionHdr->VirtualAddress + pSectionHdr->Misc.VirtualSize - 1,
				scnName,
				pSectionHdr->Misc.VirtualSize);
		}
		else if ((strcmp(scnName, ".text") == 0) || (strcmp(scnName, ".data") == 0)){
			printf(" %p...%p %-10s (%u bytes)\n",
				imageBase + pSectionHdr->VirtualAddress,
				imageBase + pSectionHdr->VirtualAddress + pSectionHdr->Misc.VirtualSize - 1,
				scnName,
				pSectionHdr->Misc.VirtualSize);
		}
		++pSectionHdr;
	}
	printf(" %p...%p %-10s (%ubytes)\n", pFrame2, pFrame, "Stack +Heap", pFrame - pFrame2);
}
int main(){
	__int64 Frame = 0; /* MUST be the very first thing in the function */
	PDWORD pFrame;

	Frame++; /* make sure that Frame doesn't get optimized out */

	pFrame = (PDWORD)(&Frame);
	printf("Stack starding adress : %p\n\n", pFrame);
	//printf("%s\n", s1);
	int n1 = 0xffffffff;
	unsigned int n2 = 0xffffffff;
	float f1 = 5.5;
	double f2 = 5.5;
	int *p1 = &n1;
	char* s1 = "Hello world!";

	printf("Adresa n1: %x\n", &n1);
	printf("Size n1: %d bytes\n", sizeof(n1));
	printf("n1 Encoding: signed integer\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int) &n1) % sizeof(n1),sizeof(n1));
	printf("Value : %d\n", n1);
	printf("\n");

	printf("Adresa n2: %x\n", &n2);
	printf("Size n2: %d bytes\n", sizeof(n2));
	printf("n2 Encoding: unsigned integer\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int)&n2) % sizeof(n2), sizeof(n2));
	printf("Value : %u\n", n2);
	printf("\n");

	printf("Adresa f1: %x\n", &f1);
	printf("Size f1: %d bytes\n", sizeof(f1));
	printf("f1 Encoding: single precission float\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int)&f1) % sizeof(f1), sizeof(f1));
	printf("Value : %.2f\n", f1);
	printf("\n");

	printf("Adresa f2: %d\n", &f2);
	printf("Size f2: %d bytes\n", sizeof(f2));
	printf("f2 Encoding: double precission float\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int)&f2) % sizeof(f2), sizeof(f2));
	printf("Value : %.2lf\n", f2);
	printf("\n");

	printf("Adresa p1: %d\n", &p1);
	printf("Size p1: %d bytes\n", sizeof(p1));
	printf("p1 Encoding: unsigned integer\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int)&p1) % sizeof(p1), sizeof(p1));
	printf("Value : %p\n", (void *)p1);
	printf("\n");

	printf("Adresa s1: %d\n", &s1);
	printf("Size s1: %d bytes\n", sizeof(s1));
	printf("s1 Encoding: unsigned int\n");
	printf("Aligned corectly ( yes 0 ? no 1 ): %d, at %d bytes\n", ((int)&s1) % sizeof(s1), sizeof(s1));
	printf("Value : %p\n", (void *)s1);
	printf("\n");
	unsigned long long  l= -1;
	foo(n1, f1, l);

	print_PE_section_info(GetModuleHandle(NULL),pFrame); // print section info for "this process's .exe file" (NULL)
	system("pause");
	return 0;
}