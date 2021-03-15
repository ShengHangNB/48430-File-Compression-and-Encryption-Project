CC = gcc
CFLAGS = -Wall -Werror -ansi

main.out: main.o project_dev1.o project_dev2.o project_dev3.o project_dev4.o project_dev5.o project_dev6.o project_dev7.o project_dev8.o project_dev9.o project_dev10.o project_dev11.o
	$(CC) $(CFLAGS) -o main.out main.o project_dev1.o project_dev2.o project_dev3.o project_dev4.o project_dev5.o project_dev6.o project_dev7.o project_dev8.o project_dev9.o project_dev10.o project_dev11.o
	
main.o: main.c project_utils.h
	$(CC) $(CFLAGS) -c -o main.o main.c 

project_dev1.o: project_dev1.c project_utils.h 
	$(CC) $(CFLAGS) -c -o project_dev1.o project_dev1.c

project_dev2.o: project_dev2.c project_utils.h 
	$(CC) $(CFLAGS) -c -o project_dev2.o project_dev2.c

project_dev3.o: project_dev3.c project_utils.h 
	$(CC) $(CFLAGS) -c -o project_dev3.o project_dev3.c

project_dev4.o: project_dev4.c project_utils.h 
	$(CC) $(CFLAGS) -c -o project_dev4.o project_dev4.c

project_dev5.o: project_dev5.c project_utils.h
	$(CC) $(CFLAGS) -c -o project_dev5.o project_dev5.c

project_dev6.o: project_dev6.c project_utils.h
	$(CC) $(CFLAGS) -c -o project_dev6.o project_dev6.c

project_dev7.o: project_dev7.c project_utils.h
	$(CC) $(CFLAGS) -c -o project_dev7.o project_dev7.c

project_dev8.o: project_dev8.c project_utils.h
	$(CC) $(CFLAGS) -c -o project_dev8.o project_dev8.c

project_dev9.o: project_dev9.c project_utils.h
	$(CC) $(CFLAGS) -c -o project_dev9.o project_dev9.c

project_dev10.o: project_dev10.c project_utils.h
	$(CC) $(CFLAGS) -c -o project_dev10.o project_dev10.c

project_dev11.o: project_dev11.c project_utils.h
	$(CC) $(CFLAGS) -c -o project_dev11.o project_dev11.c

clean:
	rm main.out main.o project_dev1.o project_dev2.o project_dev3.o project_dev4.o project_dev5.o project_dev6.o project_dev7.o project_dev8.o project_dev9.o project_dev10.o project_dev11.o

cleanf:
	rm HFT_Decompression.txt Huffman_Codes.txt HFT_Model XOR_Decryption.txt XOR_Encryption.txt Caesar_Encryption.txt Caesar_Decryption.txt Sorted_file.txt RLE_Compression.txt
