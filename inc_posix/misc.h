/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2008 WiredTiger Software.
 *	All rights reserved.
 *
 * $Id$
 */

#if defined(__cplusplus)
extern "C" {
#endif

/* Align a number to a specified power-of-2. */
#define	WT_ALIGN(n, v)							\
	(((n) + (v) - 1) & ~(((uintmax_t)(v)) - 1))

/*
 * Flag checking for API functions.
 */
#define	DB_FLAG_CHK(db, name, f, mask)					\
	if ((f) & ~(mask))						\
		return (__wt_api_flags((db)->ienv, name));
#define	DB_FLAG_CHK_NOTFATAL(db, name, f, mask, ret)			\
	if ((f) & ~(mask))						\
		(ret) = __wt_api_flags((db)->ienv, name);
#define	ENV_FLAG_CHK(ienv, name, f, mask)				\
	if ((f) & ~(mask))						\
		return (__wt_api_flags(ienv, name));
#define	ENV_FLAG_CHK_NOTFATAL(ienv, name, f, mask, ret)			\
	if ((f) & ~(mask))						\
		(ret) = __wt_api_flags(ienv, name);

/*
 * Flag set, clear and test.  They come in 3 flavors: F_XXX (handles a
 * field named "flags" in the structure referenced by its argument),
 * LF_XXX (handles a local variable named "flags"), and FLD_XXX (handles
 * any variable, anywhere.
 */
#define	F_CLR(p, mask)		(p)->flags &= ~(mask)
#define	F_ISSET(p, mask)	((p)->flags & (mask))
#define	F_SET(p, mask)		(p)->flags |= (mask)

#define	LF_CLR(mask)		((flags) &= ~(mask))
#define	LF_ISSET(mask)		((flags) & (mask))
#define	LF_SET(mask)		((flags) |= (mask))

#define	FLD_CLR(field, mask)	((field) &= ~(mask))
#define	FLD_ISSET(field, mask)	((field) & (mask))
#define	FLD_SET(field, mask)	((field) |= (mask))

/*
 * Statistics are optional to minimize our footprint.
 */
#ifdef	HAVE_STATISTICS
#define	WT_STAT_DECL(v)	wt_stat_t v
#define	WT_STAT(v)	v

/* By default, statistics are maintained in 64-bit types to avoid overflow. */
typedef	u_int64_t	wt_stat_t;

#else
#define	WT_STAT_DECL(v)
#define	WT_STAT(v)
#endif

/* A distinguished byte pattern to overwrite memory we are done using. */
#define	OVERWRITE_BYTE	0xab

#ifdef HAVE_DIAGNOSTIC
#define WT_ASSERT(ienv, e)						\
	((e) ? (void)0 : __wt_assert(ienv, #e, __FILE__, __LINE__))
#else
#define WT_ASSERT(ienv, e)
#endif

#if defined(__cplusplus)
}
#endif
