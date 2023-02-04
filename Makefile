PREFIX     ?= /
all:
	g++ src/main.cc -o target/Recipe
install: all
	cp target/Recipe $(PREFIX)/bin
