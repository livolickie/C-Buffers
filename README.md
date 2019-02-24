# C++ Buffers<br>
>Easy API that provides buffers written in C++<br>
>Author: Livolickie<br>
>Function Manual:<br>
>Buffer - the constructor, is passed 1 parameter - the size of your buffer. Example: Buffer b (16) - Initialize the buffer with a size of 16 bytes<br>
void write <var_type> (var_type) - write some value to the buffer. Example: b.write <int> (5) - write an integer value of 5 of type int (4 bytes)<br>
var_type read <var_type> () - read some value from the buffer. Example: b.read <double> () - read the double-precision float value of double type (8 bytes)<br>
void write_string (char *) - write the string to the buffer. Example: b.write_string ("Hello") - write the string "Hello" with size 6 bytes, the line + \ 0 itself<br>
char * read_string () - read the string from the buffer. Example: b.read_string ()<br>
void seek () - move to the starting address of the buffer<br>
void seek (int) - move to the N-address of the buffer. Example: b.seek (5) - move 5 bytes from the current position<br>
void clear () - completely clear the buffer<br>
void resize (int) - change the size of the buffer. Example: b.resize (4) - set the buffer size to 4 bytes<br>
void destroy () - remove the buffer by freeing the memory<br>
void live (int) - re-create the remote buffer with the new size. The function is completely analogous to the Buffer constructor<br>
void save (char *) - saves the buffer to a file. Example: b.load ("C: //Users/fl.txt") - loads the buffer from the directory "C: //Users/fl.txt", fl.txt - file name and extension<br>
void copy (Buffer *, Buffer *, int, int) - copies data from one buffer to another. Example: b.copy (b, b2, b.tell (), 0) - copies all data from buffer b to buffer b2 with offset 0<br>
int tell () - return the current position in the buffer.<br>
int memory () - return the size of the buffer.<br>
