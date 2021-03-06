# SIMD

amd ryzen 7 pro 4950U(x86_64)(ubuntu 20.04)
`gcc -o mavx2 mavx2.c -mavx2 `
```shell
85 75 65 55 45 35 25 15 
mavx2 : 60.00000
for_loop : 71.00000
```
raspberry pi4(aarch64)(ubuntu 22.0)
`gcc -o neon NEON.c`
```shell
15 25 35 45 
neon : 278.00000
for_loop : 408.00000
```

implement memcpy neon
`gcc -o memcpy memcpy.c`
```shell
memcpy_neon_32x4=260.00000ms memcpy=55.00000 ms
memcpy_neon_32x4x4=518.00000ms memcpy=111.00000 ms
```
testbench `gcc -o memcpy_neon memcpy_neon.c`
```shell
benchmark(size=16 bytes, times=256):
result(dst aligned, src aligned): memcpy_fast=8685.00001ms memcpy=2852.00000 ms

benchmark(size=64 bytes, times=256):
result(dst aligned, src aligned): memcpy_fast=33851.00003ms memcpy=2889.00000 ms

benchmark(size=256 bytes, times=256):
result(dst aligned, src aligned): memcpy_fast=147886.00015ms memcpy=7851.00001 ms

benchmark(size=1024 bytes, times=256):
result(dst aligned, src aligned): memcpy_fast=311883.00031ms memcpy=25092.00003 ms

benchmark(size=4096 bytes, times=256):
result(dst aligned, src aligned): memcpy_fast=1195790.00120ms memcpy=98628.00010 ms

benchmark(size=524288 bytes, times=256):
result(dst aligned, src aligned): memcpy_fast=29718810.02972ms memcpy=42115961.04212 ms
```

implement memset mavx2
`gcc -o memset_avx2 memset_avx2.c -mavx2 `
```shell
memset : 120.00000
memset_mavx2 : 71.00000
```

implement memset neon
`gcc -o memset_neon memset_neon.c`
```shell
memset : 93.00000
memset_neon : 555.00000
```
