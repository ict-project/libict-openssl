all: build/prefix.sh
	./build/prefix.sh $(MAKE) $(MFLAGS) -C build

clean: build/prefix.sh
	./build/prefix.sh $(MAKE) $(MFLAGS) -C build clean

install: build/prefix.sh
	./build/prefix.sh $(MAKE) $(MFLAGS) -C build install

uninstall: build/prefix.sh
	./build/prefix.sh $(MAKE) $(MFLAGS) -C build uninstall

test: build/prefix.sh
	./build/prefix.sh $(MAKE) $(MFLAGS) -C build test

package: build/prefix.sh
	./build/prefix.sh $(MAKE) $(MFLAGS) -C build package

package_source: build/prefix.sh
	./build/prefix.sh $(MAKE) $(MFLAGS) -C build package_source

build/prefix.sh:
	test -d build || ./configure.sh
