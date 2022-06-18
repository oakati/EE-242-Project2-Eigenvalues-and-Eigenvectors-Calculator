//Author Ömer Alperen Kati
//Date 29/05/2020

Project 2: Eigenvalues and Eigenvectors Calculator using Normalized
Power Iteration together with Deflation

-This program implements Normalized Power Iteration with Deflation algorithmm
to calculate most dominant eigenvalue, its eigenvector and the second most dominant
eigenvalue.

-This program was written considering that given matrix always will be a square matrix,
so make sure that matrix A is square.


HOW TO RUN THE PROGRAM USING CMD

-Firstly, press windows key on your keybord, write cmd and press enter to open command
window. Then adjust the directory of cmd as where all your input files and source.cpp
file are.

-Secondly, if you are in the correct directory, write "g++ source.cpp -o source.exe" to
generate .exe file, and press enter.

Example: C:\Users\(!!username here!!)\Desktop\EE242_Project2>g++ source.cpp -o source.exe

-After that, write "source.exe (Insert name of the matrix A here) (Insert value of tolerance here) (Insert name of the output file here)",
and press enter to run the program.
Example: C:\Users\(!!username here!!)\Desktop\EE242_Project2>source.exe A.txt 1e-6 out.txt

//Author Ömer Alperen Kati
//Date 29/05/2020