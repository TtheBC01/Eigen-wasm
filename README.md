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
emcc src/eigen.cpp -o build/eigen.html -I ./Eigen -sEXPORTED_FUNCTIONS=_float_norm -sEXPORTED_RUNTIME_METHODS=cwrap
```

## Test in Browser

```shell
cd build
python3 -m http.server
```

```console
const float_norm = Module.cwrap('float_norm', 'number', ['number', 'number', 'array']);
rows = 2
cols = 3
data = new Uint8Array(new Float32Array([1.0,2.0,3.0,4.0,5.0,6.0]).buffer);
float_norm(rows, cols, data);
// should print 21
```