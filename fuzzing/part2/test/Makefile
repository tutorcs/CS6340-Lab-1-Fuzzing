TARGETS=easy easy2 sanity

all: ${TARGETS}

%: %.c
	clang -emit-llvm -S -fno-discard-value-names -c -o $@.ll $< -g
	opt -load ../build/InstrumentPass.so -Instrument -S $@.ll > $@.instrumented.ll
	clang -o $@ ${PWD}/../lib/runtime.c $@.instrumented.ll

clean:
	rm -f *.ll *.cov ${TARGETS}
