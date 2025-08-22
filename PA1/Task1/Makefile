BIN=mat_mul
CC=g++

tiling: mat_mul
	g++ mat_mul.c -D OPTIMIZE_TILING -o $(BIN)/$@

loop: mat_mul
	g++ mat_mul.c -D OPTIMIZE_LOOP_OPT -o $(BIN)/$@

simd: mat_mul
	g++ mat_mul.c -mavx -D OPTIMIZE_SIMD -o $(BIN)/$@

combination: mat_mul
	g++ mat_mul.c -D OPTIMIZE_COMBINED -o $(BIN)/$@

all: mat_mul
	g++ mat_mul.c -D OPTIMIZE_TILING -D OPTIMIZE_SIMD -D OPTIMIZE_LOOP_OPT -D OPTIMIZE_COMBINED -o $(BIN)/$@

clean:
	@rm -rf $(BIN)
	@rm -f out.txt

mat_mul:
	@mkdir -p $(BIN)
