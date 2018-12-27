//
// Created by john on 12/26/18.
//

#include <stdio.h>
#include "zfs.h"

// References:
//  nvlist: github.com/zfsonlinux/zfs/blob/master/module/nvpair/fnvpair.c
//  lzc:    github.com/zfsonlinux/zfs/blob/master/lib/libzfs_core/libzfs_core.c#L1229

ze_error run_channel_program(const char *zcp_file, const char *pool) {

    ze_error ret = ZE_SUCCESS;

    if(libzfs_core_init() != 0) {
        libzfs_core_fini();
        return ZE_FAILURE;
    }

    // Setup channel program
    nvlist_t *outnvl;
    nvlist_t *nvl = fnvlist_alloc();
    nvlist_add_string(nvl, "pool", "zroot");

    dump_nvlist(nvl, 4);

    uint64_t instrlimit = 10 * 1000 * 1000; // 10 million is default
    uint64_t memlimit = 10 * 1024 * 1024;   // 10MB is default

    char *progstr = file_contents(zcp_file);

    if (progstr) {
#if defined(ZOL_VERSION) && ZOL_VERSION >= 8
        int err = lzc_channel_program(pool, progstr, instrlimit, memlimit, nvl, &outnvl);
        if (err != 0) {
            fprintf(stderr, "Failed to run channel program");
            ret = ZE_FAILURE;
        } else {
            dump_nvlist(outnvl, 4);
        }
#else
#if defined(ZOL_VERSION)
        fprintf(stderr, "Wrong ZFS version %d", ZOL_VERSION);
#else
        fprintf(stderr, "Can't run channel program");
        ret = ZE_FAILURE;
#endif
#endif
    }

    libzfs_core_fini();
    return ret;
}