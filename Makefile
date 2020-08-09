CC = /usr/local/bin/gcc
CXX = /usr/local/bin/g++
OBJS = main.o calc_graph.o Edges.o Exeptions.o Gcalc.o Graph.o Parser.o Vertex.o
EXEC = gcalc
COMP_FLAG = -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG

$(EXEC) : $(OBJS)
	$(CXX) $(OBJS) -o $@

main.o : main.cpp Vertex.h Exeptions.h Edges.h Graph.h Gcalc.h Parser.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

calc_graph.o : calc_graph.cpp calc_graph.h Parser.h Gcalc.h Graph.h Vertex.h Exeptions.h Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Edges.o : Edges.cpp Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Exeptions.o : Exeptions.cpp Exeptions.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Gcalc.o : Gcalc.cpp Gcalc.h Graph.h Vertex.h Exeptions.h Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Graph.o: Graph.cpp Graph.h Vertex.h Exeptions.h Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Parser.o: Parser.cpp Parser.h Gcalc.h Graph.h Vertex.h Exeptions.h Edges.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

Vertex.o: Vertex.cpp Vertex.h Exeptions.h
	$(CXX) -c $(COMP_FLAG) $*.cpp

clean:
	rm -f $(OBJS) $(EXEC) $*.TMP

tar:
	zip gcalc.zip design.pdf Makefile test_in.txt test_out.txt \
 main.cpp Edges.cpp Gcalc.cpp Parser.cpp calc_graph.cpp Exeptions.cpp Graph.cpp Vertex.cpp calc_graph.i

libgraph.a : $(OBJS)
	ar -rs $@ $^
	swig -python -o graph_wrap.c calc_graph.i
	$(CXX) -std=c++11 -DNDEBUG --pedantic-errors -Wall -Werror -I/usr/local/include/python3.6m -fPIC -shared graph_wrap.c libgraph.a -o _graph.so