from os import mkdir
from os.path import exists

truestr = ['true', '1', 'yes']

debug = ARGUMENTS.get('debug')
run_test = ARGUMENTS.get('tests')

if debug:
    debug = debug.lower() in truestr

if run_test:
    run_test = run_test.lower() in truestr

env = Environment(
    CPPPATH=['include']
    )

if 'gcc' in env['TOOLS']:
    env.Append(CXXFLAGS=['-std=c++17'])

else:
    env.Append(CXXFLAGS=['/std:c++17', '/EHsc'])

if debug and ('gcc' in env['TOOLS']):
    env.Append(CPPDEFINES={'MARTIN_DEBUG': None})
    env.Append(CXXFLAGS=[
        '-g',
        '-fsanitize=address',
        '-fno-omit-frame-pointer'
    ])
    env.Append(LINKFLAGS=[
        '-fsanitize=address'
    ])

else:
    if 'gcc' in env['TOOLS']:
        env.Append(CXXFLAGS=['-O2'])
    
    else:
        env.Append(CXXFLAGS=['/O2'])

src = Glob('./src/*.cpp')

if run_test:
    env.Append(CPPPATH=['./tests', './src'])
    test = Glob('./tests/*.hpp')
    includes = ''
    inits = ''
    for i in range(len(test)):
        if (str(test[i]).find('testing.hpp')) == -1:
            path = str(test[i])
            path = path[path.find('/')+1:]
            includes += '#include <' + path + '>\n'
            path = path[:path.find('.')]
            inits += 'TEST_VECTOR.push_back(std::shared_ptr<Test>(new Test_' + path + '));\n'
            
    file = open('./tests/testing.cpp', 'r')
    contents = file.read()
    file.close()

    contents = contents.replace('MARTIN_TESTING_INCLUDES', includes)
    contents = contents.replace('MARTIN_TESTING_INITS', inits)

    if not exists('./temp'):
        mkdir('./temp')

    file = open('./temp/test.cpp', 'w')
    file.write(contents)
    file.close()

    test = src + Glob('./temp/test.cpp')

    prog = env.Program('martin-test', test)

else:
    env.Program('martin', src + Glob('./app/*.cpp'))