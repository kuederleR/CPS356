## Adding drivers to xv6
- **file.h**: Define device major number
- **defs.h**: Add init definition
- **kkernel/kmain.c**: Add init to main
- **Makefile**: Add `.o` file to KOBJS
- **user/init.c**: Add driver init

## Adding test script
- Add `.c` file to user folder
- **user/Makefile**: Add to UPROGS