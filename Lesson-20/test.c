/* test.c - test c code for preprocessing */


/*
 * 1. delete comment
 * 2. #define substitude 
 * 3. #include file 
 * 4. #if 0/1 condition-compilation
 */
  		  #define P.I            3.14
#define PI            3.14
#define PI2            34
#if  1 abc
#error not ok
#endif

 int main     (void)
 {
	// return a value

	int      a        =      100;



	return        P.I + PI + PI2 + 12;
 }
