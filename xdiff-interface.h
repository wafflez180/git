#ifndef XDIFF_INTERFACE_H
#define XDIFF_INTERFACE_H

#include "cache.h"
#include "xdiff/xdiff.h"

/*
 * xdiff isn't equipped to handle content over a gigabyte;
 * we make the cutoff 1GB - 1MB to give some breathing
 * room for constant-sized additions (e.g., merge markers)
 */
#define MAX_XDIFF_SIZE (1024UL * 1024 * 1023)

typedef void (*xdiff_emit_consume_fn)(void *, char *, unsigned long);

int xdi_diff(mmfile_t *mf1, mmfile_t *mf2, xpparam_t const *xpp, xdemitconf_t const *xecfg, xdemitcb_t *ecb);
int xdi_diff_outf(mmfile_t *mf1, mmfile_t *mf2,
		  xdiff_emit_consume_fn fn, void *consume_callback_data,
		  xpparam_t const *xpp, xdemitconf_t const *xecfg);
int parse_hunk_header(char *line, int len,
		      int *ob, int *on,
		      int *nb, int *nn);
int read_mmfile(mmfile_t *ptr, const char *filename);
void read_mmblob(mmfile_t *ptr, const struct object_id *oid);
int buffer_is_binary(const char *ptr, unsigned long size);

extern void xdiff_set_find_func(xdemitconf_t *xecfg, const char *line, int cflags);
extern void xdiff_clear_find_func(xdemitconf_t *xecfg);
extern int git_xmerge_config(const char *var, const char *value, void *cb);
extern int git_xmerge_style;

#endif
