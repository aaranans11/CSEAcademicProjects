# Operating Systems Assignment 2: Implementing the Producer Consumer problem


This program is a simple implementation of the producer consumer problem.  The producer and consumer share a shared memory structure that contains 100 128 byte buffer structures, each containing a string and a count variable for keeping track of the number of characters in the buffer.  The producer process opens and reads an input text file into an input buffer of size BUFSIZ.  It then divides the contents of the input buffer and copies them into the shared buffer.  The consumer reads the contents of the shared buffer and writes it to an output file.ß

To run the program, the consumer process must be run first:
./consumer &

Then, the producer process must be run passing the name of the input text file as a command line argument, for example:
./producer test_input1.txt

//NOTE:
This assignment was completed using a Mac machine, so some of the included headers may be different.
 
