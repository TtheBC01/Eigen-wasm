# Eigen-wasm
Eigen bindings for WASM runtime

## Setup

```shell
git clone https://github.com/TtheBC01/Eigen-wasm.git
git submodule update --init --recursive
docker build -t emcc .
docker run -it --rm --entrypoint bash -v /path/to/Eigen-wasm:/root/ew -p 8000:8000 emcc
cd /root/ew
emcc -v
```

## Compiling

```shell
emcc src/eigen.cpp -o build/eigen.html -I ./Eigen -sEXPORTED_FUNCTIONS=_float_norm,_float_matrix_matrix_mult -sEXPORTED_RUNTIME_METHODS=cwrap
```

## Test in Browser

```shell
cd build
python3 -m http.server
```
### Matrix L2 Norm

In all examples, we use column-major storage. Numerical data is passed as an array which is mapped to 
a matrix of the size specified by the number of rows and columns passed to the function. 

```console
const float_norm = Module.cwrap('float_norm', 'number', ['number', 'number', 'array']);
rows = 2
cols = 3
data = new Uint8Array(new Float32Array([1.0,2.0,3.0,4.0,5.0,6.0]).buffer);
float_norm(rows, cols, data);
// should print 9.539392471313477
```

### Matrix-Matrix Multiply

```console
const float_matrix_matrix_mult = Module.cwrap('float_matrix_matrix_mult', 'null', ['number', 'number', 'array', 'number', 'number', 'array'])
const rowsA = 2;
const colsA = 3;
const rowsB = 3;
const colsB = 2;
const A = new Uint8Array(new Float32Array([1, 2, 3, 4, 5, 6]).buffer);
const B = new Uint8Array(new Float32Array([1, 0, 0, 1, 1, 0]).buffer);
var C = new Uint8Array(new Float32Array([0, 0, 0, 0]).buffer);

// create pointer and set data on the heap
var C = new Float32Array(4);
var nCBytes = C.length * C.BYTES_PER_ELEMENT;
var CPtr = Module._malloc(nCBytes);
var CHeap = new Uint8Array(Module.HEAPU8.buffer, CPtr, nCBytes);
CHeap.set(new Uint8Array(C.buffer));

float_matrix_matrix_mult(rowsA, colsA, A, rowsB, colsB, B, CHeap.byteOffset);

var result = new Float32Array(CHeap.buffer, CHeap.byteOffset, C.length);

Module._free(CHeap.byteOffset);
```