/* pc_shim.c — desktop-only stand-ins for OS services the SDK's SDL layer
 * doesn't emulate. Compiles to nothing in the Pocket build.
 *
 * There's no ISO to mount on the desktop: run app_pc from the folder that
 * holds playlist.tsv, the MP3s and art/, and the player's relative-path
 * fallback finds them. */
#ifdef OF_PC
#include "of.h"

int of_mount(const char *source, const char *target, const char *fstype, uint32_t flags)
{
    (void)source; (void)target; (void)fstype; (void)flags;
    return 0;
}

int of_umount(const char *target)
{
    (void)target;
    return 0;
}

int of_iso_mount(const char *source, const char *target)
{
    return of_mount(source, target, "iso9660", OF_MOUNT_RDONLY);
}
#else
typedef int pc_shim_unused;
#endif
