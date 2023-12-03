# UC3M Computer Arch 23/24 Sem 1: Fluid Simulation

### To build

In root directory

```
mkdir cmake-build-debug && cd cmake-build-debug && cmake .. && cd ..
cmake --build cmake-build-debug
```

run

```
touch out/output.fld
cmake-build-debug/fluid/fluid 1 small.fld out/output.fld
```

test

```
cmake-build-debug/utest/utest
```

### or

```
./buildandrun.sh
./testrun.sh
```

### Clang-tidy fixes

np -> npnp
px, py, pz -> posx, posy, posz
ax, ay, az -> accx, accy, accz
hv -> vectorhv
hvx -> vectorhvx,
