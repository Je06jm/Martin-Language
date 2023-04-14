# Martin Language
This is a statically typed language with a focus on memory safety. Support for
calling C and C++ functions are also, as well as creating functions that can be
called from C and C++, is supported with externs. It also features a package
manager and a strict versioning system for libraries. Ease of development is also
a big goal with support for being compiled, JIT compiled, and interpreted.
Lastly, it supports zero cost returns of any sized type.

## Currently implemented
* Parser
* Tokenizer

## Currently working on
* LLVM codegen

## Future goals
* Project manager
* Package manager
* Interpreter
* Code generation using LLVM
* Standard library

## Roadmap for Martin
* v0.1.0 - Initial release. A preview of **most** available features can be seen in examples/src/Example.martin
* v0.2.0 - Custom data types, like union, enum, struct, and typedef
* v0.3.0 - Externs and classes. Classes have access to virtual, pure virtual, static, and deleted functions (much like C++)
* v0.4.0 - Generics / interfaces (func add <T: addable>(var a: T, var b: T) -> T)
* v0.5.0 - FStrings (Much like python's fstrings, but better!)
* v0.6.0 - Dictionaries and variable unpacking (var mydict := Dict({i32, f32}), var {var} := myclass)
* v0.7.0 - Raw pointers and unsafe methods
* v0.8.0 - Extern methods, classes, and variables
* v0.9.0 - Unicode 16 and 32 strings str16 and str32
* v0.10.0 - Project and package managers
* v1.0.0 - First production ready release

This roadmap is still subject to change, except v0.1.0. That release has entered feature freeze.