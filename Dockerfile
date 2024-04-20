FROM ubuntu

RUN apt update && apt install -y git vim python3 cmake && apt install -y emscripten