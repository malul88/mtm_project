CC = /usr/local/bin/gcc
CXX = /usr/local/bin/g++
OBJS = main.o graph.o Edges.o Exeptions.o Gcalc.o Graph1.o Parser.o Vertex.o
EXEC = gcalc
COMP_FLAG = -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -fPIC

$(EXEC) : $(OBJS)
	$(CXX) $(OBJS) -o $@

main.o : main.cpp Vertex.h Exeptions.h Edges.h Graph1.h Gcalc.h Parser.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

graph.o : graph.cpp graph.h Parser.h Gcalc.h Graph1.h Vertex.h Exeptions.h Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Edges.o : Edges.cpp Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Exeptions.o : Exeptions.cpp Exeptions.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Gcalc.o : Gcalc.cpp Gcalc.h Graph1.h Vertex.h Exeptions.h Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Graph1.o: Graph1.cpp Graph1.h Vertex.h Exeptions.h Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Parser.o: Parser.cpp Parser.h Gcalc.h Graph1.h Vertex.h Exeptions.h Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Vertex.o: Vertex.cpp Vertex.h Exeptions.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

clean:
	rm -f $(OBJS) $(EXEC) $*.TMP

tar:
	zip gcalc.zip design.pdf Makefile test_in.txt test_out.txt \
 main.cpp Edges.cpp Edges.h Gcalc.cpp Gcalc.h Parser.cpp Parser.h graph.cpp graph.h Exeptions.cpp Exeptions.h Graph1.cpp Graph1.h Vertex.cpp Vertex.h graph.i


libgraph.a : $(OBJS)
	ar -rs $@ $^
	swig -python -o graph_wrap.c graph.i
	$(CXX) -std=c++11 -DNDEBUG --pedantic-errors -Wall -Werror -I/usr/local/include/python3.6m -fPIC -shared graph_wrap.c libgraph.a -o _graph.so