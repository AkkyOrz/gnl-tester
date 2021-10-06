# gnl-tester(2021+)

**This is WIP project**

This is a tester for the `gnl-tester` project of 42 school.
Clone this tester in your `gnl-tester` repository.
And prepare `CMakeLists.txt` for every your repository you use.

**only the 'mandatory' part is supported now**

## dependency

- cmake
- g++

## How to prepare your test (commands)

```bash
cd /path/to/gnl
git clone https://github.com/AkkyOrz/gnl-tester.git
cd gnl-tester
cmake -S . -B build && cmake --build build && ./build/main
```

## command

```bash
cmake -S . -B build && cmake --build build && ./build/main
```


## CMake installation

### on macOS without root

install in `~/bin` folder

```bash
mkdir ~/bin
curl -LO https://github.com/Kitware/CMake/releases/download/v3.21.2/cmake-3.21.2-macos-universal.tar.gz
tar xf cmake-3.21.2-macos-universal.tar.gz
cd cmake-3.21.2-macos-universal
mv ./CMake.app ~
echo "export PATH=$HOME/CMake.app/Contents/bin:$PATH" >> ~/.zshrc
source ~/.zshrc
`````

### on macOS with MacPorts or brew

```bash
sudo port install cmake
brew install cmake
`````

cmake is maybe installed in `/usr/loca/bin`


### on Ubuntu

you can install via `snap`, `apt` or compile with src
