CC = gcc
CXX = g++
CXXFLAGS = -I.
DEPS = fib.h gamma.h delta.h omega.h head.h encode.h decode.h helper.h
OBJ = fib.o delta.o omega.o gamma.o encode.o decode.o helper.o lzw_dec.o lzw_enc.o main.o 
ENC = fib.o delta.o omega.o gamma.o encode.o decode.o helper.o lzw_enc.o 
DEC = fib.o delta.o omega.o gamma.o encode.o decode.o helper.o lzw_dec.o

#for Linux
#RM = rm -f

#for Windows
RM = del /Q /F

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

#main: $(OBJ)
#	$(CXX) -o $@ $^ $(CXXFLAGS)
	
lzw_enc: $(ENC)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
lzw_dec: $(DEC)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) $(OBJ)
	
full_clean:
	$(RM) $(OBJ) main.exe main lzw_dec.exe lzw_dec lzw_enc.exe lzw_enc 