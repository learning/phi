SRC = ./src
DIST = ./dist

prepare-dist: clean
	mkdir -p $(DIST)

clean:
	rm -rf $(DIST)
	rm -rf $(SRC)/ptk/target

# macOS build
macos: prepare-dist prepare-macos
	xcodebuild
	open $(DIST)/Release/phi.app

prepare-macos:
	cp -R $(SRC)/ptk/darwin $(SRC)/ptk/target

# Linux build
linux: prepare-dist prepare-linux
	cc $(SRC)/main.linux.c $(SRC)/phi/*.c $(SRC)/ptk/*.c $(SRC)/ptk/target/*.c -o $(DIST)/phi `pkg-config --cflags --libs gtk+-2.0`
	$(DIST)/phi

prepare-linux:
	cp $(SRC)/ptk/linux $(SRC)/ptk/target -r

test: clean
	mkdir $(DIST)
	cc $(SRC)/test.c backend/*.c -o $(DIST)/test
	$(DIST)/test test.xml
