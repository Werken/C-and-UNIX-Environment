Download and save all files in same folder along with pictures

To compile type:

>>make

To run program:

COMPRESS
>>./compress -c input_filename output_file quality

with input_filename being girl.pgm, casablanca.pgm, or mandrill.pgm

outout_file being any .dat file

and quality is a number from 1-100

Example: ./compress -c girl.pgm output.dat 50

DECOMPRESS
>>./compress -d output_file output_pgm

with output_file being the same file from the compress command

and output_pgm being any .pgm file

Example: ./compress -d output.dat output.pgm