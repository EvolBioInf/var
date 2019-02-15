all:
	make -C common
	make -C src
	mkdir -p build
	cp src/var build
test:
	make -C src test
clean:
	make -C common clean
	make -C src    clean
	make -C doc    clean
.PHONY:	doc
doc:	
	make -C doc
