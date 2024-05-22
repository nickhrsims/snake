### ----------------------------------------------------------------------------
### Meson Configuration
### ----------------------------------------------------------------------------

project('snake', 'c', 'cpp',
  default_options : [
    'c_std=c99',
    'cpp_std=c++20',
    'warning_level=3',
    'b_ndebug=if-release',
  ]
)

### ----------------------------------------------------------------------------
### Compiler Configuration
### ----------------------------------------------------------------------------

cc = meson.get_compiler('cpp')
cmath = cc.find_library('m', required : false)

### ----------------------------------------------------------------------------
### Dependencies
### ----------------------------------------------------------------------------

sdl2 = dependency('SDL2', version : '2.26.5')
sdl2_ttf = dependency('SDL2_ttf', version : '2.20.2')
spdlog = dependency('spdlog', version : '1.13.0')
catch2 = dependency('catch2-with-main', version : '3.5.4')

### ----------------------------------------------------------------------------
### Demo
### ----------------------------------------------------------------------------

core_sources = [
    'src/main.cpp',
]

core_deps = [
    sdl2, sdl2_ttf, spdlog
]

exe = executable('snake',
                core_sources,
                install : false,
                include_directories : ['src', 'contrib/sos/include'],
                dependencies : core_deps,
)


