Package: libxcrypt:x64-linux@4.5.2

**Host Environment**

- Host: x64-linux
- Compiler: GNU 13.3.0
- CMake Version: 4.3.3
-    vcpkg-tool version: 2026-05-27-d5b6777d666efc1a7f491babfcdab37794c1ae3e
    vcpkg-scripts version: f6aa95f283 2026-07-05 (2 hours ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
Downloading https://github.com/besser82/libxcrypt/archive/v4.5.2.tar.gz -> besser82-libxcrypt-v4.5.2.tar.gz
Successfully downloaded besser82-libxcrypt-v4.5.2.tar.gz
-- Extracting source /home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/vcpkg/downloads/besser82-libxcrypt-v4.5.2.tar.gz
-- Using source at /home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/vcpkg/buildtrees/libxcrypt/src/v4.5.2-7ca15a2a8e.clean
-- Getting CMake variables for x64-linux
-- Loading CMake variables from /home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/vcpkg/buildtrees/libxcrypt/cmake-get-vars_C_CXX-x64-linux.cmake.log
CMake Error at /home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/build_ln/build_debug/vcpkg_installed/x64-linux/share/vcpkg-make/vcpkg_make.cmake:108 (message):
  libxcrypt currently requires the following programs from the system package
  manager:

      autoconf autoconf-archive automake libtoolize



      On Debian and Ubuntu derivatives:
          sudo apt install autoconf autoconf-archive automake libtool
      On recent Red Hat and Fedora derivatives:
          sudo dnf install autoconf autoconf-archive automake libtool
      On Arch Linux and derivatives:
          sudo pacman -S autoconf autoconf-archive automake libtool
      On Alpine:
          apk add autoconf autoconf-archive automake libtool
      On macOS:
          brew install autoconf autoconf-archive automake libtool

Call Stack (most recent call first):
  /home/colonel-karna/comat/BrishkamalMaterial/ColonelDocuments/CodeHub/Projects/Cpp/baaghchaal/build_ln/build_debug/vcpkg_installed/x64-linux/share/vcpkg-make/vcpkg_make_configure.cmake:66 (vcpkg_run_autoreconf)
  ports/libxcrypt/portfile.cmake:16 (vcpkg_make_configure)
  scripts/ports.cmake:206 (include)



```

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "baaghchaal",
  "version": "1.0.0",
  "dependencies": [
    "sdl3",
    "sdl3-image",
    "sdl3-ttf",
    "sdl3-mixer"
  ]
}

```
</details>
