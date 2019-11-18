.PHONY = build

CC = gcc

.SUFFIXES:

build: vm.o tokenizer.o postfixer.o generator.o
	@echo "done"
VMSRCS := $(filter-out vm/tests.c, $(wildcard vm/*.c))

vm.o: ${VMSRCS}
	${CC} ${VMSRCS} -o vm.o -lm

TOKENIZERSRCS := $(filter-out tokenizer/tests.c, $(wildcard tokenizer/*.c))

tokenizer.o: ${TOKENIZERSRCS}
	${CC} ${TOKENIZERSRCS} -o tokenizer.o

POSTFIXERSRCS := $(filter-out postfixer/tests.c, $(wildcard postfixer/*.c))

postfixer.o: ${POSTFIXERSRCS}
	${CC} ${POSTFIXERSRCS} -o postfixer.o

GENERATORSRCS := $(filter-out generator/tests.c, $(wildcard generator/*.c))

generator.o: ${GENERATORSRCS}
	${CC} ${GENERATORSRCS} -o generator.o
