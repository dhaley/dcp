/*
 * Copyright 04/24/06 Sun Microsystems, Inc. All Rights Reserved
 */

#ifndef _MPMT_DEF_H
#define _MPMT_DEF_H

/* Define the OS, ARCH, COMPILER and WSIZE predicates */

/*
 * The way we define and use predicates is similar to the 
 * standard #assert with one important exception:
 * if an argument of a predicate is not known the result
 * is 'false' and we want a compile time error to avoid
 * silent results from typos like ARCH(INTEL), COMPILER(gnu),
 * etc.
 */

#define OS(x)		TOK_O_##x(OS)
#define TOK_O_Solaris(x)	x##_Solaris
#define TOK_O_Linux(x)	x##_Linux

#define ARCH(x)		TOK_A_##x(ARCH)
#define TOK_A_SPARC(x)	x##_SPARC
#define TOK_A_Intel(x)	x##_Intel

#define COMPILER(x)	TOK_C_##x(COMPILER)
#define TOK_C_GNU(x)	x##_GNU
#define TOK_C_SUN(x)	x##_SUN

#define WSIZE(x)	TOK_W_##x(WSIZE)
#define TOK_W_32(x)	x##_32
#define TOK_W_64(x)	x##_64


#if defined(__GNUC__)
#define COMPILER_GNU	1
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define COMPILER_SUN	1
#endif


#if defined(sparc) && defined(linux) && (defined(__sparcv9) || defined(__arch64__))

/* sparcv9-Linux */
#define OS_Linux        1
#define ARCH_SPARC	1
#define WSIZE_64	1

#elif defined(sparc) && defined(linux)

/* sparc-Linux */
#define OS_Linux        1
#define ARCH_SPARC      1
#define WSIZE_32        1

#elif defined(__sparcv9)

/* sparcv9-S2 */
#define OS_Solaris	1
#define ARCH_SPARC	1
#define WSIZE_64	1

#elif defined(sparc) && defined(sun)

/* sparc-S2 */
#define OS_Solaris	1
#define ARCH_SPARC	1
#define WSIZE_32	1

#elif defined(__amd64) && defined(sun)

/* amd64-S2 */
#define OS_Solaris	1
#define ARCH_Intel	1
#define WSIZE_64	1

#elif defined(i386) && defined(sun)

/* intel-S2 */
#define OS_Solaris	1
#define ARCH_Intel	1
#define WSIZE_32	1

#elif defined(__x86_64__) && defined(linux)

/* amd64-Linux */
#define OS_Linux	1
#define ARCH_Intel	1
#define WSIZE_64	1

#elif defined(i386) && defined(linux)

/* intel-Linux */
#define OS_Linux	1
#define ARCH_Intel	1
#define WSIZE_32	1

#else
#error "Undefined platform"
#endif

#endif /* _MPMT_DEF_H */
