CMP = g++
FLAGS = -c
CLASS = cross
EXEC = runcross
MAIN = crossword
OBJECTS = $(MAIN).o $(CLASS).o

$(EXEC) : $(OBJECTS) 
	$(CMP) $(OBJECTS) -o $(EXEC)

$(MAIN) : $(MAIN).cpp $(CLASS).h
	$(CMP) -c -std=c++11 $(MAIN).cpp -o $(MAIN).o
	
$(CLASS) : $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp -o $(CLASS).o
	 
clean:
	rm *.o runcross
	
	
	
	 
