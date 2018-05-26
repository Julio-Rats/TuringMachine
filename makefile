all:sim
sim:  comp_h comp_c
		gcc *.o -o simturing
		rm *.o
		rm *.gch
comp_c:
		gcc -c *.c
comp_h:
		gcc -c *.h
