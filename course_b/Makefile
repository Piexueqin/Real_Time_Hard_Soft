XENO_CONFIG := /usr/xenomai/bin/xeno-config

CFLAGS := $(shell $(XENO_CONFIG)   --skin=alchemy --auto-init-solib --cflags)
LDFLAGS := $(shell $(XENO_CONFIG)  --skin=alchemy --auto-init-solib --ldflags)

LDFLAGS+=-L. -lalchemy -Wl,-rpath=/usr/xenomai/lib
LDFLAGS+=-L. -lantlr4-runtime -Wl,-rpath=/root/antlr4-runtime/dist

INCLUDE_PATH+=-I /root/antlr4-runtime/runtime/src
INCLUDE_PATH+=-I /usr/xenomai/include
INCLUDE_PATH+=-I /usr/xenomai/include/cobalt/
INCLUDE_PATH+=-I ./
INCLUDE_PATH+=-I ./include
INCLUDE_PATH+=-I ../course_d/



CXX :=g++

SRC_PATH=$(wildcard ./src/*.cpp)
SRC_PATH +=$(wildcard ../course_c/xenomaitask.cpp)
SRC_PATH +=$(wildcard ../course_d/src/sem_shm.cpp)
MAIN_PATH=$(wildcard ./*.cpp)

EXECUTABLE := ./bin/course_b

$(EXECUTABLE):$(MAIN_PATH) $(SRC_PATH)
	$(CXX) $^ -o $@ $(INCLUDE_PATH) $(CFLAGS) $(LDFLAGS) 
	
.PHONY:clean
	
clean:
	$(RM) $(EXECUTABLE)

