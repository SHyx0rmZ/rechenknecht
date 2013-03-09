CXX = g++
CXXFLAGS = -c -std=gnu++11 -fPIC -Wl,-soname,librechenknecht.so -o librechenknecht.so -shared
LD = g++
LDFLAGS = -lX11 -lGL

all: librechenknecht.so

librechenknecht.so: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
