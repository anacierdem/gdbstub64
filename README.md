[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fanacierdem%2Fgdbstub64.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2Fanacierdem%2Fgdbstub64?ref=badge_shield)

gdbstub
=======
This is a simple gdb stub that can be easily dropped in to your project. It
has no external dependencies and requires just standard tools to build.

Protocol
--------
Communication between the stub and the debugger takes place via the [gdb Remote Serial Protocol](https://sourceware.org/gdb/onlinedocs/gdb/Remote-Protocol.html).

Porting
-------
This was developed for x86 systems but it's fairly modular. So, with a little
effort, it should work on other platforms. You will need to modify
`gdbstub_sys.h` and `gdbstub_sys.c` to fit your platform's needs accordingly.

License
-------
Licensed under GPL v2. See `LICENSE.txt` for full license.

Matt Borgerson, 2016


## License
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fanacierdem%2Fgdbstub64.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2Fanacierdem%2Fgdbstub64?ref=badge_large)