CXX = g++
CXXFLAGS = -march=native -O0 -ggdb -pipe -Wall -Wextra
LDFLAGS = -Wl,-O1 -Wl,--as-needed

EXECS = HernquistProfile PotentialFromProfile
LIBS = LineStream SuperstarCluster

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
