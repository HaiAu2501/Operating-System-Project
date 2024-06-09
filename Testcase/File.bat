write_file 2 number.txt
write_file 5 number.txt
write_file 3 number.txt ~LINE 2
write_file 4 number.txt ~LINE 3
write_file 1 number.txt ~HEAD
write_file 6 number.txt
write_file 8 number.txt
write_file 7 number.txt ~LINE 7
read_file number.txt
read_file number.txt ~LINE 1
read_file number.txt ~HEAD 3
read_file number.txt ~RANGE 4 6
read_file number.txt ~FOOT 3
loop 12 write_file 9 number.txt
file_size number.txt
delete number.txt
