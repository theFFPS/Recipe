PREFIX     ?= /
all:
	g++ src/Main.cc -o target/Recipe
install: all
	cp target/Recipe $(PREFIX)/bin
