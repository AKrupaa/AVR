/*
 * ftoa.h
 *
 * Created: 2019-12-02 14:58:34
 *  Author: admin
 */ 
/*
 * CFile1.c
 *
 * Created: 2019-12-02 14:57:49
 *  Author: admin
 */ 


// Reverses a string 'str' of length 'len'
void reverse(char* str, int len);
// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d);

// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint);

