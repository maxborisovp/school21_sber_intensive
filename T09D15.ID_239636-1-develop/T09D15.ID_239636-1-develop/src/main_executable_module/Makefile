CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
.PHONY: all quest3 build_with_static build_with_dynamic clean rebuild

all:quest3 build_with_static build_with_dynamic

quest3:
	$(CC) $(CFLAGS) ../data_libs/data_io.c ../data_libs/data_stat.c ../data_module/data_process.c ../yet_another_decision_module/decision.c main_executable_module.c -o ../../build/Quest_3

data_io.o: ../data_libs/data_io.c ../data_libs/data_io.h
	$(CC) -c ../data_libs/data_io.c

	
data_stat.o: ../data_libs/data_stat.c ../data_libs/data_stat.h
	$(CC) -c ../data_libs/data_stat.c

decision.o: ../yet_another_decision_module/decision.c ../yet_another_decision_module/decision.h ../data_libs/data_stat.h
	$(CC) -c ../yet_another_decision_module/decision.c

data_process.o: ../data_module/data_process.c ../data_module/data_process.h ../data_libs/data_stat.h
	$(CC) -c ../data_module/data_process.c

main_executable_module.o: main_executable_module.c ../data_libs/data_io.h ../data_libs/data_stat.h ../data_module/data_process.h ../yet_another_decision_module/decision.h
	$(CC) -c main_executable_module.c

libdata_stat.a: data_stat.o
	ar r libdata_stat.a data_stat.o

build_with_static: data_io.o libdata_stat.a decision.o data_process.o main_executable_module.o
		$(CC) data_io.o decision.o data_process.o main_executable_module.o -L. -ldata_stat -o ../../build/Quest_5


data_process_dyn.o: ../data_module/data_process.c ../data_module/data_process.h ../data_libs/data_stat.h
	$(CC) -fPIC -c ../data_module/data_process.c -o data_process_dyn.o

libdata_process.so: data_process_dyn.o
	gcc -shared -o libdata_process.so data_process_dyn.o data_stat.o
main_executable_module_dyn.o: main_executable_module.c
	$(CC) -c -DUSE_DYN main_executable_module.c -o main_executable_module_dyn.o

build_with_dynamic: data_io.o data_stat.o decision.o libdata_process.so main_executable_module_dyn.o
	$(CC) data_io.o data_stat.o decision.o main_executable_module_dyn.o -ldl libdata_process.so  -o ../../build/Quest_6
		

clean:
	rm -rf ../../build/Quest_*
	rm -rf *.o *.a *.so

rebuild: clean all
