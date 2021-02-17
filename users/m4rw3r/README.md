Reusable stuff for ortho layout

### Building

```bash
make -j16 --output-sync preonic/rev3:m4rw3r planck/rev6:m4rw3r niu_mini:m4rw3r crkbd:m4rw3r
```

### Flashing

If flashing from docker ensure to use `sudo ./util/docker_build.sh planck/rev6:foo:dfu-util`.

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

It now autodetects which side is correct (left side is with USB):

```
make crkbd:m4rw3r:dfu
```

## Updating

```bash
git fetch upstream
git checkout master
git merge upstream/master
git push && git push --tags
git checkout m4rw3r
git rebase master
docker rmi qmkfm/base_container
make git-submodule
```

## Gentoo

So far I have gotten a working compiler but the binaries it produces just freeze the keyboard with a single note playing. Probably need specific versions of newlib

First create a crossdev custom repo: https://wiki.gentoo.org/wiki/Custom_repository#Crossdev

```
sudo emerge -a dev-libs/libusb dev-libs/libusb-compat sys-devel/crossdev
sudo crossdev -s4 --stable --g '=4.9.4' --portage --verbose --target avr
```

We want ot disable any newer GCC versions for ARM since they have issues, in `/etc/portage/package.mask/cross-arm-none-eabi`:

```
>=cross-arm-none-eabi/gcc-9.0.0
```

Then:

```
USE="nano -ssp" sudo crossdev -s4 --stable --portage --verbose --target arm-none-eabi
# Needed to enable nano variant:
sudo vim /etc/portage/package.accept_keywords/cross-arm-none-eabi # Add ~arm to newlib
# Also ensure that the ssp use flag is disabled for gcc
emerge -uDU --with-bdeps=y @world
```

Dump of `/etc/portage/package.use/cross-arm-none-eabi`:

```
cross-arm-none-eabi/binutils multilib
cross-arm-none-eabi/newlib -selinux multilib nano
cross-arm-none-eabi/gcc cxx -openmp -ssp -fortran -sanitize -vtv -hardened -pie nopie -selinux -boundschecking -d -gcj -gtk -libffi -mudflap -objc -objc++ -objc-gc multilib
```

Still produces code which makes a planck rev6 freeze.

## TODO

* Look at keymap ideas
* VIM-like stuff?
* Maybe standardize the ADJUST layer more to fit more stuff on Crkbd