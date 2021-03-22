# 48430 Fundamentals of C Programming Group project

Project Name: Bank Customer Security Management System

Team leader: Hang Sheng<br>
Team members: Longhao Zhu, Wei Chen, Liam Jiang

Project mark: 29.76/30<br>
Final mark for this subject: 97/100

# Role Duty

|Name | Role |
|------ | ------- |
| Hang Sheng | Implement the Huffman Coding Compression and Decompression (Displayed as "high efficient" during the program) ; implement the searching algorithm |
| Longhao Zhu | Implement the XOR File Encryption and decryption(Displayed as "low security" during the program), implement the file sort algorithm  |
| Wei Chen  | Implement the Run-length-coding File Compression (Displayed as "low efficient" during the program) |
| Liam Jiang | Implement the Caesar Cipher File Encryption and decryption(Displayed as "high security" during the program) |

# Data-Flow Diagram and System Design

The data flow diagram of the entire project is shown as follows.The user can have an overview of this project according to this picture and view the flow of data by the arrows. The leftmost “customer.txt” is the database prepared to be used in the project, there are six attributes totally for each row, which are “ID”, “Name”, “Gender”, “Account type”, “Account Balance”, “Annual income”. The user may experience different features by following the red word “Recall” and the oval with a red border. The squares connected with the green word “Output” are the ultimate output files.


![image](https://github.com/ShengHangNB/README-images/blob/main/C%20Project%20Data-flow%20diagram%20.png)

## Program runs instruction:

please type "make" command in the terminal to compile all the c sources codes, then type "./main.out" to run the Program

Language Standard: C90 <br>
Running Environment: Linux <br>

Another commands: <br> 
make clean: clean all the compiled files in the directory. <br>
make cleanf: clean all the intermediate  files generated during the program. <br>

## Program Designs:

1. Read data > Compress data > Decompress Data > Output Data

2. Read data > Encrypt data > Decrypt Data > Output Data

3. Read data > Compress data > Encrypt data > Decrypt Data > Decompress data > Output data

4. Read data > Encrypt data > Compress data > Decompress data > Decrypt Data > Output data

5. Read data > Encrypt data > Compress data > Search data

6. Read data > Compress data > Encrypt data > Search data

7. Read data > sort data

8. Self defined the data > read data > sort data


