truestr = ['true', 'True', 'TRUE', '1']

debug = ARGUMENTS.get('debug') in truestr

env = Environment(CPPPATH=['include'])

if debug:
    env.Append(CPPDEFINES=['MARTIN_DEBUG'])

src = Global("./src/*.cpp")

prog = env.Program("martin", src)