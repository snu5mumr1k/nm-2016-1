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
]]

env.Program("bin/main", objects + make_object("src/main.cpp"), FRAMEWORKS=frameworks, LIBS=libs)
