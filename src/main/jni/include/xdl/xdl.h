#ifndef IO_GITHUB_HEXHACKING_XDL
#define IO_GITHUB_HEXHACKING_XDL

#include <dlfcn.h>
#include <link.h>
#include <stddef.h>

#ifdef __cplusplus

#if defined (__LP64__)
#define XDL_DEFAULT  __BIONIC_CAST(reinterpret_cast, void*, 0)
#define XDL_NEXT     __BIONIC_CAST(reinterpret_cast, void*, -1L)
#else
#define XDL_DEFAULT  __BIONIC_CAST(reinterpret_cast, void*, 0xffffffff)
#define XDL_NEXT     __BIONIC_CAST(reinterpret_cast, void*, 0xfffffffe)
#endif

extern "C" {
#endif

typedef struct {
  // same as Dl_info:
  const char *dli_fname;  // Pathname of shared object that contains address.
  void *dli_fbase;        // Address at which shared object is loaded.
  const char *dli_sname;  // Name of nearest symbol with address lower than addr.
  void *dli_saddr;        // Exact address of symbol named in dli_sname.
  // added by xDL:
  size_t dli_ssize;             // Symbol size of nearest symbol with address lower than addr.
  const ElfW(Phdr) *dlpi_phdr;  // Pointer to array of ELF program headers for this object.
  size_t dlpi_phnum;            // Number of items in dlpi_phdr.
} xdl_info_t;

//
// Default value for flags in both xdl_open() and xdl_iterate_phdr().
//
#define XDL_DEFAULT 0x00

//
// Enhanced dlopen() / dlclose() / dlsym().
//
#define XDL_TRY_FORCE_LOAD    0x01
#define XDL_ALWAYS_FORCE_LOAD 0x02
void *xdl_open(const char *filename, int flags);
void *xdl_close(void *handle);
void *xdl_sym(void *handle, const char *symbol, ElfW(Sym) *out_sym);
void *xdl_dsym(void *handle, const char *symbol, ElfW(Sym) *out_sym);

//
// Enhanced dladdr().
//
int xdl_addr(void *addr, xdl_info_t *info, void **cache);
void xdl_addr_clean(void **cache);

//
// Enhanced dl_iterate_phdr().
//
#define XDL_FULL_PATHNAME 0x01
int xdl_iterate_phdr(int (*callback)(struct dl_phdr_info *, size_t, void *), void *data, int flags);

//
// Custom dlinfo().
//
#define XDL_DI_DLINFO 1  // type of info: xdl_info_t
int xdl_info(void *handle, int request, void *info);

#ifdef __cplusplus
}
#endif

#endif
