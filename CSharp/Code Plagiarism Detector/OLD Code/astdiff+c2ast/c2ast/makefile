# Postavke:

OBJDIR=obj/

CXXFLAGS := -Wall -O2 $(CXXFLAGS)

# ----------

O=$(OBJDIR)

OBJS = $Oast.o $Oast2xml.o $Oc2ast.o $Osource.o \
	$Ostdafx.o $Ostringutils.o

.PHONY: all clean

all: c2ast

c2ast: $O $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o$@

$Oast.o: ast.cpp ast.h ast_alloc.h source.h stringutils.h stdafx.h
$Oast2xml.o: ast2xml.cpp ast.h ast_alloc.h source.h stringutils.h stdafx.h
$Oc2ast.o: c2ast.cpp ast.h ast_alloc.h source.h stringutils.h ast2xml.h stdafx.h
$Osource.o: source.cpp source.h stringutils.h stdafx.h
$Ostringutils.o: stringutils.cpp stringutils.h stdafx.h
$Ostdafx.o: stdafx.cpp stdafx.h

$O%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o$@

$O:
	mkdir $O

clean:
	$(RM) $(OBJS) $Bc2ast
