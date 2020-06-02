CXXFLAGS += -std=c++17 -g
LDFLAGS += -lpthread

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
DEPENDS = $(SOURCES:%.cpp=%.d)

# KeyMap subprogram

KeyMap: keymap/main.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

keymap/main.o: keymap/mappings_buttons keymap/mappings_axis

keymap/mappings_%: | keymap/mappings_%.def
	cp $@.def $@

# Original example

GamepadDemo: $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# General stuff

%.d: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@

%/main.o: CXXFLAGS += -Isrc

include $(DEPENDS)
