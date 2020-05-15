CC = gcc
CXX = g++
CXXFLAGS = -I.
DEPS = fib.h gamma.h delta.h omega.h head.h encode.h decode.h helper.h
OBJ = main.o fib.o delta.o omega.o gamma.o encode.o decode.o helper.o

#for Linux
#RM = rm -f

#for Windows
RM = del /Q /F

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) $(OBJ)
	
full_clean:
	$(RM) $(OBJ) main.exe main