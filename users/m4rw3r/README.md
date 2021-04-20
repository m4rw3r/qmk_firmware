Reusable stuff for ortho layout

### Building

```bash
# To build all layouts:
./util/docker_build.sh :m4rw3r
# For specific layouts:
./util/docker_build.sh preonic/rev3:m4rw3r
./util/docker_build.sh planck/rev6:m4rw3r
./util/docker_build.sh niu_mini:m4rw3r
./util/docker_build.sh crkbd:m4rw3r
./util/docker_build.sh eyeohdesigns/babyv:m4rw3r
```

### Flashing

```bash
sudo ./util/docker_build.sh preonic/rev3:m4rw3r:dfu-util
sudo ./util/docker_build.sh planck/rev6:m4rw3r:dfu-util
sudo ./util/docker_build.sh niu_mini:m4rw3r:dfu
sudo ./util/docker_build.sh crkbd:m4rw3r:dfu
sudo ./util/docker_build.sh eyeohdesigns/babyv:m4rw3r:flash
```

## Updating

```bash
git fetch upstream
git checkout master
git merge --ff-only upstream/master
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