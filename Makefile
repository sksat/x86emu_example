EMU		= x86emu
OBJS	= main.o

CXX		= clang++
CXXFLAGS= -std=c++17

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

default:
	make $(EMU)

run:
	make
	./$(EMU)

$(EMU): $(OBJS)
	$(CXX) -o $@ $^
