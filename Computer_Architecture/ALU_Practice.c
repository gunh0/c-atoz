#include <stdio.h>

int shiftOperation(int X, int Y, int C)
{
	if (C < 0 || C > 3)
	{
		printf("error in shift operation\n");
	}

	int shift_amount = X & 0x1f;
	printf("shift_amount : %d\n", shift_amount);
	while (shift_amount)
	{
		if (C == 0)
		{
			return Y;
		}
		else if (C == 1)
		{
			Y = Y << 1;
		}
		else if (C == 2)
		{
			if (Y >= 0x80000000)
			{
				Y = Y >> 1;
				Y -= 0x80000000;
			}
			else
				Y = Y >> 1;
			
		}
		else
		{
				Y = Y >> 1;
		}
		shift_amount--;
	}
	return Y;
}

int addSubtract(int X, int Y, int C)
{
	int ret = 0;
	if (C < 0 || C > 1)
	{
		printf("error in add/subtract operation\n");
		exit();
	}
	if (C == 0)
	{
		printf("Add\n");
		ret = X + Y;
	}
	if (C == 1)
	{
		printf("Subtract\n");
		ret = X - Y;
	}
	return ret;
}

int logicOperation(int X, int Y, int C)
{
	int ret = 0;
	if (C < 0 || C > 3)
	{
		printf("error in logic operation");
		exit();
	}
	else if (C == 0)
	{
		printf("AND\n");
		return X & Y;
	}
	else if (C == 1)
	{
		printf("OR\n");
		return X | Y;
	}
	else if (C == 2)
	{
		printf("XOR\n");
		return (X ^ Y);
	}
	else
	{
		printf("NOR\n");
		return ~(X | Y);
	}
	return ret;
}

int setLess(int X, int Y)
{
	if (X < Y) return 1;
	else return 0;
}

int ALU(int X, int Y, int C, int* Z)
{
	int c32 = (C >> 2) & 3;
	int c10 = C & 3;
	int ret = 0;

	if (c32 == 0)
	{
		ret = shiftOperation(X, Y, c10);
	}
	else if (c32 == 1)
	{
		printf("set less\n");
		ret = setLess(X, Y);
	}
	else if (c32 == 2)
	{
		if (c10 & 1 == 1)
		{
			ret = addSubtract(X, Y, 1);
		}
		else
		{
			ret = addSubtract(X, Y, 0);
		}
		if (ret == 0)
			* Z = 1;
		else
			*Z = 0;
	}
	else
	{
		printf("logic : ");
		ret = logicOperation(X, Y, c10);
	}

	return ret;
}

void main(void)
{
	int x = 0, y = 0, c = 0, s = 0, z = 0;
	x = 0xffff0004;
	y = 0xbf00ffff;

	printf("x: %08x, y: %08x\n\n", x, y);

	for (c = 0; c < 16; c++)
	{
		s = ALU(x, y, c, &z);
		printf("s:%08x, z:%1x\n", s, z);
	}

	return;
}