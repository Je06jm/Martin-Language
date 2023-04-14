from os import mkdir
from os.path import exists
from os import environ

truestr = ['true', '1', 'yes', 'y']

debug = ARGUMENTS.get('debug')
use_clang = ARGUMENTS.get('use_clang')
gen_program = ARGUMENTS.get('gen_program')
use_mingw = ARGUMENTS.get('use_mingw')

if debug:
    debug = debug.lower() in truestr

if use_clang:
    use_clang = use_clang.lower() in truestr

if gen_program:
    gen_program = gen_program.lower() in truestr

if use_mingw:
    use_mingw = use_mingw.lower() in truestr

env = None

if use_clang:
    env = Environment(
        CPPPATH=[
            'include',
            'vendors/nlohmann_json/include',
            'vendors/peglib'
        ],
        path = environ["PATH"]
    )

elif use_mingw:
    env = Environment(
        tools=['mingw'],
        CPPPATH=[
            'include',
            'vendors/nlohmann_json/include',
            'vendors/peglib'
        ]
    )

else:
    env = Environment(
        CPPPATH=[
            'include',
            'vendors/nlohmann_json/include',
            'vendors/peglib'
        ]
    )

use_gcc_style = ('gcc' in env['TOOLS']) or use_clang

if use_gcc_style:
    env.Append(CXXFLAGS=['-std=c++17'])

else:
    env.Append(CXXFLAGS=['/std:c++17', '/EHsc'])

if debug and use_gcc_style:
    env.Append(CPPDEFINES={'MARTIN_DEBUG': None})
    env.Append(CXXFLAGS=[
        '-g',
        '-fno-omit-frame-pointer',
        '-Wall',
        '-Wextra'
    ])
    env.Append(LINKFLAGS=[
    ])

else:
    if use_gcc_style:
        env.Append(CXXFLAGS=['-O2'])
    
    else:
        env.Append(CXXFLAGS=['/O2'])
    
    with open("src/grammar.hpp", "w") as file:
        file.write("#ifndef MARTIN_GRAMMAR\n")
        file.write("#define MARTIN_GRAMMAR\n\n")

        file.write("namespace Martin {\n\n")

        file.write("\tauto grammar = R\"(\n")
        with open("src/grammar.txt", "r") as grammar:
            file.write(grammar.read())
        
        file.write("\n")
        file.write(")\";\n\n")

        file.write("}\n\n")

        file.write("#endif")

src = Glob('./src/*.cpp')

if gen_program:
<<<<<<< HEAD
    env.Program('martin', Glob('./app/*.cpp') + src)
else:
    env.StaticLibrary('martin', src)
=======
    env.Program('martin', Glob('./app/*.cpp') + src, LIBS=['LLVM-10.so'])
>>>>>>> 199adef817ec4e361f445b5dc192f38a7fb78168
