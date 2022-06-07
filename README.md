# SIMD

amd ryzen 7 pro 4950U(x86_64)(ubuntu 20.04)
`gcc -o mavx2 mavx2.c -mavx2 `
```shell
85 75 65 55 45 35 25 15 
60.00000
71.00000
```
raspberry pi4(aarch64)(ubuntu 22.0)
`gcc -o neon NEON.c`
```shell
15 25 35 45 
278.00000
408.00000
```
