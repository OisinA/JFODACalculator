.PHONY = build

CC = gcc

.SUFFIXES:

build: vm.o tokenizer.o postfixer.o generator.o
	@echo "done"

VMSRCS := $(wildcard vm/*.c)

vm.o: ${VMSRCS}
	${CC} ${VMSRCS} -o vm.o -lm

TOKENIZERSRCS := $(wildcard tokenizer/*.c)

tokenizer.o: ${TOKENIZERSRCS}
	${CC} ${TOKENIZERSRCS} -o tokenizer.o

POSTFIXERSRCS := $(wildcard postfixer/*.c)

postfixer.o: ${POSTFIXERSRCS}
	${CC} ${POSTFIXERSRCS} -o postfixer.o

GENERATORSRCS := $(wildcard generator/*.c)

generator.o: ${GENERATORSRCS}
	${CC} ${GENERATORSRCS} -o generator.o
