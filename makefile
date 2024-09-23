project3Exe.exe: project3Exe.o champion.o
	gcc project3Exe.o champion.o -o project3Exe.exe
project3Exe.o: project3Exe.c champion.h
	gcc -c project3Exe.c -o project3Exe.o
champion.o: champion.c champion.h
	gcc -c champion.c -o champion.o
clean:
	rm -rf *.o
	rm project3Exe.exe