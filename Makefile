SRC = ./src
DIST = ./dist

clean:
	rm -rf $(DIST)
	mkdir $(DIST)

linux: clean
	cc $(SRC)/main.linux.c -o $(DIST)/phi `pkg-config --cflags --libs gtk+-2.0`
