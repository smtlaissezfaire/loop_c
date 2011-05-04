CC            = gcc
CFLAGS        = -W -Wall -g -std=c99 -pedantic
INCLUDE_PATHS = -I vendor/uthash-1.9.1/src
LIBRARIES     = -l gc

compile: generate_tokenizer
	mkdir -p bin && \
	cd src && \
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c shared.c  && \
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c escheme.c && \
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c scanner.c && \
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c main.c    && \
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c repl.c    && \
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARIES) -o ./../bin/escheme			 shared.o escheme.o scanner.o main.o && \
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARIES) -o ./../bin/escheme-repl shared.o escheme.o scanner.o repl.o && \
	cd -

clean:
	rm -rf bin
	rm -rf src/scanner.c
	rm -rf src/*.o
	rm -rf spec/logs

spec: compile
	rspec spec/escheme_spec.rb

test: spec

spec_valgrind: compile
	VALGRIND=true spec spec/escheme_spec.rb

generate_tokenizer:
	cd src && \
	re2c scanner.re2c > scanner.c && \
	cd -

sloc:
	sloccount src