Import("projenv")

# General options that are passed to the C++ compiler
projenv.Append(CXXFLAGS=["-Wno-literal-suffix", "-Wno-unused-variable"])
