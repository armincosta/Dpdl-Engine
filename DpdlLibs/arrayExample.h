# File: arrayExample.h
#
# Example: create and iterate a dynamic growing array over the elements
#
# Author: A. Costa
# e-mail: info@seesolutions.it
#
#

# main
int ARRAY_PTR = 0
int size = 100
int val = 0
int arr_status = allocMemArray(ARRAY_PTR, size)
println("allocating array of size: " + size + "")
if(arr_status != -1)
	println("populating array with size + 10 :)")
	int c = 0
	while(c <= (size+10))
		putMemArrayInt(ARRAY_PTR, randInt(16, 50000))
		c = c + 1
	endwhile
	c = 0
	println("printing array...")
	int actual_array_size = getMemArraySize(ARRAY_PTR)
	while(c < actual_array_size)
		val = getMemArrayInt(ARRAY_PTR, c)
		c = c + 1
		println("index: " + c + "  val: " + val)
	endwhile
endif








