# UC3M Computer Arch 23/24 Sem 1: Fluid Simulation

### To build

In root directory

```
mkdir cmake-build-debug && cd cmake-build-debug && cmake ..
cmake --build cmake-build-debug
```

### To run

```
cmake-build-debug/fluid/fluid 1 small.fld out/test.fld
```

### Testing

```
cmake-build-debug/utest/utest
```

### Clang-tidy fixes

np -> npnp
px, py, pz -> posx, posy, posz
ax, ay, az -> accx, accy, accz
hv -> vectorhv
hvx -> vectorhvx,
