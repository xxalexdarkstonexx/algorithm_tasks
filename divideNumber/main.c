#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum { VALID_ARGS_QUANTITY = 2, NUM_SPACES = 3 };


int str_len(const char* str)
{
	int length = 0;
	
	for ( ; *str; str++) 
	{
		if ( *str == '\n' )
			continue;
		length++;
	}
	
	return length;
}
int str_to_int(const char* str, int str_length)
{
	const char* template = "-+0123456789";
	int result = 0;


	int correctSymbols = 0;
	int i;
	int j = 0;
	for ( i = 0; template[i]; i++ )
	{
		if ( ((str[j] == '-') || (str[j] == '+')) && (j > 0) )
			return 0;
		
		if ( str[j] == template[i] )
		{
			correctSymbols++;
			j++;
			i = -1;
			continue;
		}
	}
	
	if ( correctSymbols != str_length )
		return 0;
	

	i = str_length-1;
	int order = 1;
	while ( i >= 0 )
	{	
		if ( (str[i] == '-') || (str[i] == '+') )
			break;

		result += (str[i] - '0') * order;
		order *= 10;
		i--;
	}
	
	if ( str[0] == '-' )
		result *= -1;

	return result;
}
int countNumber(int n, int* isNeg)
{
	*isNeg = 0;
	int count = 0;
	
	if (n < 0)
	{
		n *= -1;
		*isNeg = 1;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return count;
}

char* divideNumber(int n)
{
	int isNeg = 0;
	int counts = countNumber(n, &isNeg);
	
	/*printf("isNeg = %d\n"
		   "count = %d\n", isNeg, counts);*/

	if ( counts <= 0 )
		return NULL;
	
	char* str = NULL;
	char* buf = NULL;
	
	int bufNegSize = counts+(NUM_SPACES*(counts-1))+1;
	int strNegSize = counts+(NUM_SPACES*(counts-1))+1;
	int bufSize = bufNegSize-1;
	int strSize = strNegSize-1;

	if ( isNeg )
	{
		buf = malloc(sizeof(char)*bufNegSize+1);
		str = malloc(sizeof(char)*strNegSize+1);
	}
	else
	{
		buf = malloc(sizeof(char)*bufSize+1);
		str = malloc(sizeof(char)*strSize+1);
	}
	
	if ( (str == NULL) || (buf == NULL))
		return NULL;
	
	/*printf(
			"bufNegSize = %d\n"
			"bufSize = %d\n"
			"strNegSize = %d\n"
			"strSize = %d\n", 
			bufNegSize, 
			bufSize, 
			strNegSize, 
			strSize
		  );
	*/

	int i = 0;
	int j;
	if ( isNeg )
		n *= -1;
	
	/*printf("\"n\" before cycle = %d\n", n);*/

	while ( counts > 0 )
	{
		buf[i] = (n % 10) + '0';
		i++;
		counts--;
		if (counts <= 0)
			break;

		j = 1;
		for (; j <= NUM_SPACES; j++, i++)
			buf[i] = ' ';

		n /= 10;
	}
	if ( isNeg )
	{
		buf[i] = '-';
		i++;
	}
	buf[i] = '\0';
	
	/*printf("buf = %s\n", buf);
	int z = 0;
	for (; buf[z]; z++)
		printf("%d ", buf[z]);
	printf("%d\n", buf[z]);*/

	int k = i-1;
	i = 0;
	while ( k >= 0 )
	{
		str[i] = buf[k];
		i++;
		k--;
	}
	str[i] = '\0';
	free(buf);
	
	/*printf("str = %s\n", str);
	int z = 0;
	for (; str[z]; z++)
		printf("%d ", str[z]);
	printf("%d\n", str[z]);*/

	return str;
}

int main( int argc, char** argv ) 
{
	int number;
	
	if ( argc < VALID_ARGS_QUANTITY )
	{
		printf("%s", "Enter an integer number: ");
		int res = scanf("\n%d", &number);
		
		if ( res != 1 )
		{
			printf("%s\n", "Incorrect number!");
			return 0;
		}
	}
	else
	{
		int len = str_len(argv[1]);
		number = str_to_int(argv[1], len);

		if (number == 0)
		{
			printf("%s\n", "Incorrect argument");
			return 0;
		}
	}
	
	char* result = divideNumber(number);
	if ( result == NULL )
	{
		printf("%s\n", "Error has occured while attempting allocate the memory.");
		return 0;
	}
	printf("Result is %s\n", result);

	free( result );

	return 0;
}
