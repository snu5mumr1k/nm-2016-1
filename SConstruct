env = Environment()

libs = []
frameworks = []

debug = ARGUMENTS.get("debug", "")

flags = " ".join([
    "-std=c++0x",
    "-I src",
    "-O2",
    "-DLINUX"
])

if (debug == "true"):
    flags += " -g"

def make_object(source):
    return env.Object(source, CCFLAGS=flags)

objects = [make_object(source) for source in [
    "src/base_right_part.cpp",
    "src/element_generator.cpp",
    "src/equations_system.cpp",
    "src/operations_counter.cpp",
    "src/matrix.cpp",
    "src/utils.cpp",
    "src/vector.cpp",
]]

env.Program("bin/main", objects + make_object("src/main.cpp"), FRAMEWORKS=frameworks, LIBS=libs)
