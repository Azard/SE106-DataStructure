PROGRAM = Basic

CXX = g++
CXXFLAGS = -fvisibility-inlines-hidden -g -std=c++11

CPP_FILES = $(wildcard *.cpp)
H_FILES = $(wildcard *.h)

LDOPTIONS = -L.

all: $(PROGRAM) score

$(PROGRAM): $(CPP_FILES) $(H_FILES) 
	$(CXX) -o $(PROGRAM) $(CXXFLAGS) $(LDOPTIONS) $(CPP_FILES) 

score: ../Test/score
	ln -s ../Test/score .

../Test/score:
	(cd ../Test; make)


tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM) ./score
