# Makefile for project as a whole
#Author: Arthan Jansen

.PHONY = build

CC = gcc

.SUFFIXES:

build: vm.o tokenizer.o postfixer.o generator.o vmtest.t tokenizertest.t postfixertest.t generatortest.t
	@echo "done"
VMSRCS := $(filter-out vm/tests.c, $(wildcard vm/*.c))

vm.o: ${VMSRCS}
	${CC} ${VMSRCS} -o vm.o -lm

vmtest.t: vm/tests.c vm/stack.c vm/vm.c
	${CC} $^ -o $@ -lm

TOKENIZERSRCS := $(filter-out tokenizer/tests.c, $(wildcard tokenizer/*.c))

tokenizer.o: ${TOKENIZERSRCS}
	${CC} $^ -o $@

tokenizertest.t: tokenizer/tests.c tokenizer/io.c tokenizer/token_readwrite.c tokenizer/tokenizer.c
	${CC} $^ -o $@

POSTFIXERSRCS := $(filter-out postfixer/tests.c, $(wildcard postfixer/*.c))

postfixer.o: ${POSTFIXERSRCS}
	${CC} $^ -o $@

postfixertest.t: postfixer/tests.c tokenizer/token_readwrite.c postfixer/postfix.c

GENERATORSRCS := $(filter-out generator/tests.c, $(wildcard generator/*.c))

generator.o: ${GENERATORSRCS}
	${CC} $^ -o $@

generatortest.t: generator/tests.c generator/generator.c
	${CC} $^ -o $@
