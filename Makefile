all: cat grep
	@echo "run"

cat: 
	cd cat && make -f Makefile_cat

grep:
	cd grep && make -f Makefile_grep

clean:
	cd cat && make -f Makefile_cat clean
	cd grep && make -f Makefile_grep clean

.PHONY: all cat grep clean