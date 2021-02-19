## A Simple Stack based Virtual Machine written in C++

### Assembler ( Converts sasm code to SSM bytecode )

> Compile

    $ cd assembler
    $ make

### VM ( Runs the bytecode )

> Compile

    $ cd vm
    $ make


### Steps

> Write your code in sasm syntax and save it in a file named `<filename>`.sasm

> Assemble your code using sasm binary. This will generate the corresponding bytecode (out.sbc)

    $ assembler/bin/sasm <sasm-file>

> Run the bytecode using ssm binary.

    $ vm/bin/ssm out.sbc

