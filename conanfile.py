from conan import ConanFile
from conan.tools.meson import Meson, MesonToolchain
from conan.tools.gnu import PkgConfig, PkgConfigDeps


## --- Packages
sdl2 = "sdl/2.26.5"
sdl2_ttf = "sdl_ttf/2.20.2"
spdlog = "spdlog/1.13.0"
catch2 = "catch2/3.5.4"


class ProjectConanFile(ConanFile):
    author = "Nicholas H.R. Sims (nickhrsims@gmail.com)"

    settings = "os", "arch", "compiler", "build_type"
    requires = (sdl2, sdl2_ttf, spdlog, catch2)

    options = {"shared": [True, False]}
    default_options = {"shared": False}

    def generate(self: ConanFile):
        pkgconfig = PkgConfigDeps(self)
        toolchain = MesonToolchain(self)
        pkgconfig.generate()
        toolchain.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        meson = Meson(self)
        meson.install()
