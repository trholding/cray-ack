acklibrary {
    name = "lib",
    srcs = {
		"./rename.s",
--		"./brk.c",
--		"./close.s",
--		"./creat.c",
--		"./errno.s",
--		"./getpid.s",
--		"./gettimeofday.c",
--		"./_hol0.s",
--		"./isatty.s",
--		"./kill.c",
--		"./lseek.c",
--		"./open.c",
--		"./read.c",
--		"./setmode.c",
--		"./signal.c",
--		"./sys_exists.s",
--		"./sys_fdmodes.c",
--		"./sys_getdate.s",
--		"./sys_getmode.c",
--		"./sys_gettime.s",
--		"./sys_initmain.c",
--		"./sys_iseof.c",
--		"./sys_isopen.s",
--		"./sys_isreadyr.s",
--		"./sys_rawcreat.s",
--		"./sys_rawlseek.s",
--		"./sys_rawopen.s",
--		"./sys_rawrw.s",
--		"./sys_seteof.c",
--		"./sys_seterrno.c",
--		"./sys_setmode.c",
--		"./sys_xret.s",
--		"./unlink.s",
		"plat/msdos/libsys+srcs",
    },
	deps = {
		"lang/cem/libcc.ansi/headers+headers",
		"plat/msdos386/include+headers",
		"plat/msdos/libsys+headers",
	},
    vars = {
        plat = "msdos386"
    }
}

