# canonical makefile for C++
# author: MKHSEG001
# April 2019

CXX 	:= g++
INCDIRS := -I.
CXXFLAGS:= -std=c++11 -Wall -w
SRCFILES:= $(wildcard *.cpp) 
OBJFILES:= $(patsubst %.cpp,%.o,$(SRCFILES))
DEPFILES:= $(patsubst %.cpp,%.d,$(SRCFILES))

PRODUCT := imageops # change name accordingly for each exe

$(PRODUCT): $(OBJFILES)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

%.d: %.cpp
	$(CXX) $(INCDIRS) -MM $< > $@

-include $(DEPFILES)

clean:
	@rm -f *.o *.d $(PRODUCT)

def:
	./$(PRODUCT) imageops 
	
run:
	./$(PRODUCT) imageops $(ARGS) 
