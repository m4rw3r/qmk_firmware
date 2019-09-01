Reusable stuff for ortho layout

### Building

```bash
make -j16 --output-sync preonic/rev3:m4rw3r planck/rev6:m4rw3r niu_mini:m4rw3r crkbd:m4rw3r
```

### Flashing

#### Preonic

```bash
make preonic/rev3:m4rw3r:dfu-util
```

#### Planck

```bash
make planck/rev6:m4rw3r:dfu-util
```

#### NIU Mini

```bash
make niu_mini:m4rw3r:dfu
```

#### Crkbd

Left side:

```
make crkbd:m4rw3r:dfu
```

Right (slave) side:

```
make crkbd:m4rw3r:dfu RGB_MATRIX_SPLIT=yes
```