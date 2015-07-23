/* This is the sample in the Forest Cover Analysis Language (FCAL) language. It declares a boolean
 variable and use it in a while loop to sum the numbers 1 through 10.

 */

main() {
	//Declare the numeric variables
	Int sum;
	sum = 0;
	Int num;
	num = 1;
    Bool flag;
    flag = True;

	while(flag) {
	  sum = sum + num;
	  num = num + 1;
	  if (num > 10) flag = False;
	}

}

