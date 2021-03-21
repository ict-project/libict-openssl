all: build/.dir
	$(MAKE) $(MFLAGS) -C build

clean: build/.dir
	$(MAKE) $(MFLAGS) -C build clean

install: build/.dir
	$(MAKE) $(MFLAGS) -C build install

uninstall: build/.dir
	$(MAKE) $(MFLAGS) -C build uninstall

test: build/.dir
	$(MAKE) $(MFLAGS) -C build test

package: build/.dir
	$(MAKE) $(MFLAGS) -C build package

package_source: build/.dir
	$(MAKE) $(MFLAGS) -C build package_source

build/.dir:
	test -d build || ./build.bsh
	echo > build/.dir
