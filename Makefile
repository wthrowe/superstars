CXX = g++ -std=c++11
CXXFLAGS = -march=native -O0 -ggdb -pipe -Wall -Wextra
LDFLAGS = -Wl,-O1 -Wl,--as-needed

EXECS = EvolveCluster HernquistProfile Interpolate PotentialFromProfile \
        RandomCluster TestEnergy
LIBS = FreeInteractionStepper LeapfrogStepper LineStream ModifiedEulerStepper \
       ReadCluster SuperstarCluster WriteCluster

EXECOBJS = $(EXECS:=.o)
LIBOBJS = $(LIBS:=.o)
OBJECTS = $(EXECOBJS) $(LIBOBJS)

DEPFILES = $(OBJECTS:.o=.d)

all: $(EXECS)

$(EXECS): %: %.o $(LIBOBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -f $(EXECS) $(OBJECTS) $(DEPFILES)

# automatic dependencies
$(DEPFILES): %.d:
	$(CXX) -M -MT '$@ $*.o' -MP $*.cpp -MF $@

-include $(DEPFILES)
