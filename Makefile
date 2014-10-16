# COMPILTAION FLAGS

CXXFLAGS=-DBUILD_PC `pkg-config --cflags sdl2`
LDFLAGS=`pkg-config --libs sdl2` -pthread

# OBJECT FILES

OBJS=$(patsubst %.cpp,build-pc/%.o,$(wildcard *.cpp [!_]*/*.cpp [!_]*/[!_]*/*.cpp))

# RULES

pc: polychrhaum-pc.a

polychrhaum-pc.a:${OBJS}
	${AR} rcs $@ ${OBJS}

build-pc/%.o:%.cpp $(wildcard *.h **/*.h **/**/*.h)
	@mkdir -p build-pc/$(dir $<)
	$(CXX) ${CXXFLAGS} -c $< -o $@

clean:
	rm -rf build-pc polychrhaum-pc.a
