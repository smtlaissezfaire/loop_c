CC     = gcc
CFLAGS = -W -Wall -g -c99 -pedantic

compile: generate_tokenizer
	mkdir -p bin && \
	cd src && \
	$(CC) $(CFLAGS) -c shared.c && \
	$(CC) $(CFLAGS) -c escheme.c && \
	$(CC) $(CFLAGS) -c scanner.c && \
	$(CC) $(CFLAGS) -o ./../bin/escheme shared.o escheme.o scanner.o && \
	cd -

clean:
	rm -rf bin
	rm -rf src/scanner.c
	rm -rf src/*.o

spec: compile
	spec spec/escheme_spec.rb

spec_valgrind: compile
	VALGRIND=true spec spec/escheme_spec.rb

generate_tokenizer:
	cd src && \
	re2c scanner.re2c > scanner.c && \
	cd -

sloc:
	sloccount src