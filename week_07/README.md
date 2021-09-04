# VM Translator I: Stack
This is the implementation of a basic virtual machine that translates VM code to Hack Assembly Language. The source is written in C and available in the "./translator" directory. The VM supports only simple instructions like push, pop, add, sub, gt, lt, eq. 

#### Compiling 
```
make dcc
```

#### Usage
You can either pass a single source file or a directory and compile all source files.
```Bash
./dcc dir
./dcc source.vm 
```

