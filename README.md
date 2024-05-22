# Snake

A demonstration project to further the development of Project SOS.

## Dependencies

- [Project SOS](https://github.com/nickhrsims/project-sos)

## Building

- Requires `conan2`

### Using Scripts

```sh
# Debug build
./init
./compile

# Release build
./init-release
./compile-release
```

### Directly using `conan`

```sh
conan install -sbuild_type=Debug -of build --build=missing .
conan build -of build .
```
