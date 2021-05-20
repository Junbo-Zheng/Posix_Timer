cc   = clang
prom = main
deps = $(shell find ./ -name "*.h")
src  = $(shell find ./ -name "*.c")
obj  = $(src:%.c=%.o)

cflags:= -g -Wall -O0
libs  := -lpthread -lrt

$(prom): $(obj)
	$(cc) -o $(prom) $(obj) $(libs)

%.o: %.c $(deps)
	$(cc) $(cflags) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
	rm -rf *.out
