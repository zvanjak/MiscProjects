OBJDIR = ./obj/
C2ASTDIR = ../c2ast/

CXXFLAGS = -O2 -Wall

#define debug
#1
#endef

# -----

O = $(OBJDIR)

OBJS = $Oastdiff.o

INCLDIRS = $(C2ASTDIR)
EXTOBJS = ast.o source.o stringutils.o

XINCLDIRS = $(patsubst %, -I%, $(INCLDIRS))
XEXTOBJS = $(patsubst %, $(C2ASTDIR)obj/%, $(EXTOBJS))

ifdef debug
CXXFLAGS += -DDEBUG
endif

.PHONY: all rebuild clean

all: astdiff

astdiff: $O $(OBJS)
	$(CXX) $(OBJS) $(XEXTOBJS) -o$@

$O%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(XINCLDIRS) -c $< -o$@

$O:
	mkdir $O

clean:
	$(RM) $(OBJS) astdiff

rebuild: clean all
