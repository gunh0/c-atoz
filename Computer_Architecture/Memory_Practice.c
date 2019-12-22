#include <stdio.h>
static char progMEM[0x100000], dataMEM[0x100000], stackMEM[0x100000];

int MEM(unsigned int A, int V, int nRW, int S)
{
	unsigned int sel, offset;
	char* pM = NULL;
	int returnVal = 0;

	sel = A >> 20;
	printf("Area : 0x%03x", sel);
	offset = A & 0xFFFFF;

	if (sel == 0x004)
	{
		pM = progMEM;
		printf(" - Program Area");
	}
	else if (sel == 0x100)
	{
		pM = dataMEM;
		printf(" - Data Area");
	}
	else if (sel == 0x7FF)
	{
		pM = stackMEM;
		printf(" - Stack Area");
	}
	else
	{
		printf(" - No Memory\n");
		return 0;
	}

	if (S == 0)
	{
		printf(" / byte(8bits)\n");
		V = V & 0xFF;
	}
	else if (S == 1)
	{
		printf(" / half word(16bits)\n");
		if (A % 2 != 0) printf("Warning: The starting address is not a multiple of 2.\n");
		V = V & 0xFFFF;
	}
	else if (S == 2)
	{
		printf(" / word(32bits)\n");
		if (A % 4 != 0) printf("Warning: The starting address is not a multiple of 4.\n");
		V = V & 0xFFFFFFFF;
	}
	else
	{
		printf("\nReselect unit size.\n");
		return 0;
	}

	if (nRW == 0)
	{
		printf("Read Data : ");

		if (S == 0)	// Read 8bits
		{
			returnVal = pM[offset] & 0x000000ff;
			printf("%02x / ", (pM[offset] & 0x000000ff));
		}
		else if (S == 1)	// Read 16bits
		{
			printf("%02x %02x / ", pM[offset] & 0x000000ff, pM[offset + 1] & 0x000000ff);
			returnVal = ((pM[offset] << 8) & 0x0000ff00) | (pM[offset + 1] & 0x000000ff);
		}
		else if (S == 2)	// Read 32bits
		{
			printf("%02x ", (pM[offset] & 0x000000ff));
			printf("%02x ", (pM[offset + 1] & 0x000000ff));
			printf("%02x ", (pM[offset + 2] & 0x000000ff));
			printf("%02x / ", (pM[offset + 3] & 0x000000ff));
			returnVal += pM[offset + 3];
			returnVal += (pM[offset + 2] << 8);
			returnVal += (pM[offset + 1] << 16);
			returnVal += (pM[offset] << 24);
		}
		else
		{
			printf("Program Error!\n");
			return 0;
		}
	}
	else if (nRW == 1)
	{
		if (S == 0) // Write 8bits
		{
			printf("Write Data : %02x / ", V);
			pM[offset] = V & 0x000000ff;
		}
		else if (S == 1)	// Write 16bits
		{
			printf("Write Data : ");
			pM[offset] = V >> 8;
			pM[offset + 1] = V & 0x000000ff;
			printf("%02x %02x / ", pM[offset] & 0x000000ff, pM[offset + 1] & 0x000000ff);
		}
		else if (S == 2)	// Write 32bits
		{
			printf("Write Data : ");
			pM[offset] = (V >> 24) & 0x000000ff;
			printf("%02x ", pM[offset] & 0x000000ff);
			pM[offset + 1] = (V >> 16) & 0x000000ff;
			printf("%02x ", pM[offset + 1] & 0x000000ff);
			pM[offset + 2] = (V >> 8) & 0x000000ff;
			printf("%02x ", pM[offset + 2] & 0x000000ff);
			pM[offset + 3] = V & 0x000000ff;
			printf("%02x / ", pM[offset + 3] & 0x000000ff);
		}
		else
		{
			printf("Program Error!\n");
			return 0;
		}
	}
	else
	{
		printf("No Read Or Write\n");
		return 0;
	}

	return returnVal;
}

int main()
{
	unsigned int memAdd = 0;
	int writeVal = 0;
	int RWmode = -1;
	int RWsize = 0;

	// MEM(unsigned int A, int V, int nRW, int S)
	printf("Case1:%08x / ", 0x00300100);
	printf("Return Value : %08x\n\n", MEM(0x00300100, 0x99, 1, 0));
	printf("Case2:%08x / ", 0x00400100);
	printf("Return Value : %08x\n\n", MEM(0x00400100, 0x99, 1, 0));
	printf("Case3:%08x / ", 0x00400100);
	printf("Return Value : %08x\n\n", MEM(0x00400100, 0x00, 0, 0));
	printf("Case4:%08x / ", 0x00400108);
	printf("Return Value : %08x\n\n", MEM(0x00400108, 0x9876, 1, 1));
	printf("Case5:%08x / ", 0x00400108);
	printf("Return Value : %08x\n\n", MEM(0x00400108, 0x00, 0, 0));
	printf("Case6:%08x / ", 0x00400109);
	printf("Return Value : %08x\n\n", MEM(0x00400109, 0x00, 0, 0));
	printf("Case7:%08x / ", 0x00400108);
	printf("Return Value : %08x\n\n", MEM(0x00400108, 0x00, 0, 1));
	printf("Case8:%08x / ", 0x00400109);
	printf("Return Value : %08x\n\n", MEM(0x00400109, 0x00, 0, 1));
	printf("Case9:%08x / ", 0x00400120);
	printf("Return Value : %08x\n\n", MEM(0x00400120, 0x12345678, 1, 2));
	printf("Case10:%08x / ", 0x00400120);
	printf("Return Value : %08x\n\n", MEM(0x00400120, 0x12345678, 0, 2));
	printf("Case11:%08x / ", 0x00400121);
	printf("Return Value : %08x\n\n", MEM(0x00400121, 0x12345678, 0, 2));
	printf("Case12:%08x / ", 0x00400121);
	printf("Return Value : %08x\n\n", MEM(0x00400121, 0x12345678, 0, 3));
	printf("Case13:%08x / ", 0x10000140);
	printf("Return Value : %08x\n\n", MEM(0x10000140, 0x87654321, 1, 2));
	printf("Case14:%08x / ", 0x10000140);
	printf("Return Value : %08x\n\n", MEM(0x10000140, 0x00, 0, 2));
	printf("Case15:%08x / ", 0x10000142);
	printf("Return Value : %08x\n\n", MEM(0x10000142, 0x00, 0, 2));
	printf("Case16:%08x / ", 0x7FF00140);
	printf("Return Value : %08x\n\n", MEM(0x7FF00140, 0x00004321, 1, 2));
	printf("Case17:%08x / ", 0x7FF00140);
	printf("Return Value : %08x\n\n", MEM(0x7FF00140, 0x00, 0, 2));
	printf("Case18:%08x / ", 0x7FF00143);
	printf("Return Value : %08x\n\n", MEM(0x7FF00143, 0x00, 0, 2));
	printf("Case19:%08x / ", 0x7FF00101);
	printf("Return Value : %08x\n\n", MEM(0x7FF00101, 0x4321, 1, 1));

	return 0;
}