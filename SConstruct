truestr = ['true', 'True', 'TRUE', '1']

debug = ARGUMENTS.get('debug') in truestr

env = Environment(
    CPPPATH=['include']
    )

if 'gcc' in env['TOOLS']:
    env.Append(CXXFLAGS=['-std=c++17'])

else:
    env.Append(CXXFLAGS=['/std:c++17', '/EHsc'])

if debug and ('gcc' in env['TOOLS']):
    env.Append(CPPDEFINES=['MARTIN_DEBUG'])
    env.Append(CXXFLAGS=['-g'])

else:
    if 'gcc' in env['TOOLS']:
        env.Append(CXXFLAGS=['-O2'])
    
    else:
        env.Append(CXXFLAGS=['/O2'])

src = Glob('./src/*.cpp')

prog = env.Program('martin', src)