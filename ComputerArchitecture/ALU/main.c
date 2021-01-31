#include <stdio.h>

// Function to perform shift operations on Y based on C
int shiftOperation(int X, int Y, int C)
{
	// Check for valid shift amount (0 to 3)
	if (C < 0 || C > 3)
	{
		printf("error in shift operation\n");
	}

	// Extract lower 5 bits of X as the shift amount
	int shift_amount = X & 0x1f;
	printf("shift_amount : %d\n", shift_amount);

	// Perform the shift operation based on C and shift_amount
	while (shift_amount)
	{
		if (C == 0)
		{
			return Y; // No shift
		}
		else if (C == 1)
		{
			Y = Y << 1; // Logical left shift by 1
		}
		else if (C == 2)
		{
			// Arithmetic right shift by 1 (handling sign bit)
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
			Y = Y >> 1; // Logical right shift by 1
		}
		shift_amount--;
	}
	return Y;
}

// Function to perform add or subtract based on C
int addSubtract(int X, int Y, int C)
{
	int ret = 0;

	// Check for valid operation (0 for addition, 1 for subtraction)
	if (C < 0 || C > 1)
	{
		printf("error in add/subtract operation\n");
	}

	if (C == 0)
	{
		printf("Add\n");
		ret = X + Y; // Addition
	}
	if (C == 1)
	{
		printf("Subtract\n");
		ret = X - Y; // Subtraction
	}
	return ret;
}

// Function to perform logic operations (AND, OR, XOR, NOR) based on C
int logicOperation(int X, int Y, int C)
{
	int ret = 0;

	// Check for valid logic operation (0 to 3 for AND, OR, XOR, NOR)
	if (C < 0 || C > 3)
	{
		printf("error in logic operation");
	}
	else if (C == 0)
	{
		printf("AND\n");
		return X & Y; // Bitwise AND
	}
	else if (C == 1)
	{
		printf("OR\n");
		return X | Y; // Bitwise OR
	}
	else if (C == 2)
	{
		printf("XOR\n");
		return (X ^ Y); // Bitwise XOR
	}
	else
	{
		printf("NOR\n");
		return ~(X | Y); // Bitwise NOR
	}
	return ret;
}

// Function to check if X is less than Y (set less than)
int setLess(int X, int Y)
{
	if (X < Y)
		return 1; // X is less than Y
	else
		return 0; // X is greater than or equal to Y
}

// Function to implement the ALU (Arithmetic Logic Unit) based on control signals C and return the result in Z
int ALU(int X, int Y, int C, int *Z)
{
	// Extract control signals c32 (bits 3 and 2) and c10 (bits 1 and 0) from C
	int c32 = (C >> 2) & 3;
	int c10 = C & 3;
	int ret = 0;

	if (c32 == 0)
	{
		ret = shiftOperation(X, Y, c10); // Perform shift operation
	}
	else if (c32 == 1)
	{
		printf("set less\n");
		ret = setLess(X, Y); // Check if X is less than Y
	}
	else if (c32 == 2)
	{
		// Perform add or subtract operation based on c10
		if (c10 & 1 == 1)
		{
			ret = addSubtract(X, Y, 1); // Subtract
		}
		else
		{
			ret = addSubtract(X, Y, 0); // Add
		}

		// Set the Z flag based on the result of the add/subtract operation
		if (ret == 0)
			*Z = 1;
		else
			*Z = 0;
	}
	else
	{
		printf("logic : ");
		ret = logicOperation(X, Y, c10); // Perform logic operation (AND, OR, XOR, NOR)
	}

	return ret; // Return the result of the ALU operation
}

// Main function
int main(void)
{
	int x = 0, y = 0, c = 0, s = 0, z = 0;
	x = 0xffff0004; // Initialize x with hexadecimal value 0xffff0004
	y = 0xbf00ffff; // Initialize y with hexadecimal value 0xbf00ffff

	printf("x: %08x, y: %08x\n\n", x, y);

	for (c = 0; c < 16; c++)
	{
		s = ALU(x, y, c, &z);			 // Perform ALU operation for each control signal
		printf("s:%08x, z:%1x\n", s, z); // Print the result and Z flag
	}

	return 0;
}
