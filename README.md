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

Serve the test app from the build folder. After starting the http server, in your browser go to http://localhost:8000.

```shell
cd build
python3 -m http.server
```

Once the page loads, open the developer console and try the following examples (you should just be able to copy paste the javascript from below). 

In all examples, we use column-major storage. Numerical data is passed as an array which is mapped to 
a matrix of the size specified by the number of rows and columns passed to the function. 

### Matrix L2 Norm

Calculate the L2 norm of a matrix with [`float_norm`](/src/eigen.cpp#L8).

```javascript
const float_norm = Module.cwrap('float_norm', 'number', ['number', 'number', 'array']);
rows = 2
cols = 3
data = new Uint8Array(new Float32Array([1.0,2.0,3.0,4.0,5.0,6.0]).buffer);
float_norm(rows, cols, data);
// should print 9.539392471313477
```

### Matrix-Matrix Multiply

Perform fast matrix-matrix multiplies with [`float_matrix_matrix_mult`](/src/eigen.cpp#L14).

```javascript
const float_matrix_matrix_mult = Module.cwrap('float_matrix_matrix_mult', 'null', ['number', 'number', 'array', 'number', 'number', 'array'])
const rowsA = 2;
const colsA = 3;
const rowsB = 3;
const colsB = 2;
const A = new Uint8Array(new Float32Array([1, 2, 3, 4, 5, 6]).buffer);
const B = new Uint8Array(new Float32Array([1, 0, 0, 1, 1, 0]).buffer);

// create pointer and set data on the heap
var nCBytes = rowsA * colsB * A.BYTES_PER_ELEMENT; // total bytes is number of matrix elements times bytes per element
var CPtr = Module._malloc(nCBytes); // allocate a pointer
var CHeap = new Uint8Array(Module.HEAPU8.buffer, CPtr, nCBytes); // put it on the heap

float_matrix_matrix_mult(rowsA, colsA, A, rowsB, colsB, B, CHeap.byteOffset);

var result = new Float32Array(CHeap.buffer, CHeap.byteOffset, rowsA * colsB );

Module._free(CHeap.byteOffset);
// result should be [1, 2, 4, 6]
```