
## Building

To build the project execute the following:

### Linux, BSD
```
cmake <source path>
make
```

### OSX
```
cmake -DCORE_SYSTEM_NAME=darwin <source path>
make
```

## Running tests suite

Running suite with valgrind:
```
valgrind ./pvrtest --mythtvhost <backend hostname or ip>
```

To show all options execute the following:
```
./pvrtest --help
```

