#ifndef _STDIO_H
#define _STDIO_H	1
#define __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#include <bits/libc-header-start.h>
__BEGIN_DECLS
#define __need_size_t
#define __need_NULL
#include <stddef.h>
#define __need___va_list
#include <stdarg.h>
#include <bits/types.h>
#include <bits/types/__fpos_t.h>
#include <bits/types/__fpos64_t.h>
#include <bits/types/__FILE.h>
#include <bits/types/FILE.h>
#include <bits/types/struct_FILE.h>
#ifdef __USE_GNU
# include <bits/types/cookie_io_functions_t.h>
#endif
#if defined __USE_XOPEN || defined __USE_XOPEN2K8
# ifdef __GNUC__
# ifndef _VA_LIST_DEFINED
typedef __gnuc_va_list va_list;
# define _VA_LIST_DEFINED
# endif
# else
# include <stdarg.h>
# endif
#endif
#if defined __USE_UNIX98 || defined __USE_XOPEN2K
# ifndef __off_t_defined
# ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
# else
typedef __off64_t off_t;
# endif
# define __off_t_defined
# endif
# if defined __USE_LARGEFILE64 && !defined __off64_t_defined
typedef __off64_t off64_t;
# define __off64_t_defined
# endif
#endif
#ifdef __USE_XOPEN2K8
# ifndef __ssize_t_defined
typedef __ssize_t ssize_t;
# define __ssize_t_defined
# endif
#endif
#ifndef __USE_FILE_OFFSET64
typedef __fpos_t fpos_t;
#else
typedef __fpos64_t fpos_t;
#endif
#ifdef __USE_LARGEFILE64
typedef __fpos64_t fpos64_t;
#endif
#define _IOFBF 0		
#define _IOLBF 1		
#define _IONBF 2		
#define BUFSIZ 8192
#define EOF (-1)
#define SEEK_SET	0	
#define SEEK_CUR	1	
#define SEEK_END	2	
#ifdef __USE_GNU
# define SEEK_DATA	3	
# define SEEK_HOLE	4	
#endif
#if defined __USE_MISC || defined __USE_XOPEN
# define P_tmpdir	"/tmp"
#endif
#include <bits/stdio_lim.h>
extern FILE *stdin;		extern FILE *stdout;		extern FILE *stderr;		#define stdin stdin
#define stdout stdout
#define stderr stderr
extern int remove (const char *__filename) __THROW;
extern int rename (const char *__old, const char *__new) __THROW;
#ifdef __USE_ATFILE
extern int renameat (int __oldfd, const char *__old, int __newfd,
const char *__new) __THROW;
#endif
#ifdef __USE_GNU
# define RENAME_NOREPLACE (1 << 0)
# define RENAME_EXCHANGE (1 << 1)
# define RENAME_WHITEOUT (1 << 2)
extern int renameat2 (int __oldfd, const char *__old, int __newfd,
const char *__new, unsigned int __flags) __THROW;
#endif
#ifndef __USE_FILE_OFFSET64
extern FILE *tmpfile (void) __wur;
#else
# ifdef __REDIRECT
extern FILE *__REDIRECT (tmpfile, (void), tmpfile64) __wur;
# else
# define tmpfile tmpfile64
# endif
#endif
#ifdef __USE_LARGEFILE64
extern FILE *tmpfile64 (void) __wur;
#endif
extern char *tmpnam (char *__s) __THROW __wur;
#ifdef __USE_MISC
extern char *tmpnam_r (char *__s) __THROW __wur;
#endif
#if defined __USE_MISC || defined __USE_XOPEN
extern char *tempnam (const char *__dir, const char *__pfx)
__THROW __attribute_malloc__ __wur;
#endif
extern int fclose (FILE *__stream);
extern int fflush (FILE *__stream);
#ifdef __USE_MISC
extern int fflush_unlocked (FILE *__stream);
#endif
#ifdef __USE_GNU
extern int fcloseall (void);
#endif
#ifndef __USE_FILE_OFFSET64
extern FILE *fopen (const char *__restrict __filename,
const char *__restrict __modes) __wur;
extern FILE *freopen (const char *__restrict __filename,
const char *__restrict __modes,
FILE *__restrict __stream) __wur;
#else
# ifdef __REDIRECT
extern FILE *__REDIRECT (fopen, (const char *__restrict __filename,
const char *__restrict __modes), fopen64)
__wur;
extern FILE *__REDIRECT (freopen, (const char *__restrict __filename,
const char *__restrict __modes,
FILE *__restrict __stream), freopen64)
__wur;
# else
# define fopen fopen64
# define freopen freopen64
# endif
#endif
#ifdef __USE_LARGEFILE64
extern FILE *fopen64 (const char *__restrict __filename,
const char *__restrict __modes) __wur;
extern FILE *freopen64 (const char *__restrict __filename,
const char *__restrict __modes,
FILE *__restrict __stream) __wur;
#endif
#ifdef	__USE_POSIX
extern FILE *fdopen (int __fd, const char *__modes) __THROW __wur;
#endif
#ifdef	__USE_GNU
extern FILE *fopencookie (void *__restrict __magic_cookie,
const char *__restrict __modes,
cookie_io_functions_t __io_funcs) __THROW __wur;
#endif
#if defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2)
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
__THROW __wur;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __THROW __wur;
#endif
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __THROW;
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
int __modes, size_t __n) __THROW;
#ifdef	__USE_MISC
extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
size_t __size) __THROW;
extern void setlinebuf (FILE *__stream) __THROW;
#endif
extern int fprintf (FILE *__restrict __stream,
const char *__restrict __format, ...);
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
const char *__restrict __format, ...) __THROWNL;
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
__gnuc_va_list __arg);
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
__gnuc_va_list __arg) __THROWNL;
#if defined __USE_ISOC99 || defined __USE_UNIX98
extern int snprintf (char *__restrict __s, size_t __maxlen,
const char *__restrict __format, ...)
__THROWNL __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
const char *__restrict __format, __gnuc_va_list __arg)
__THROWNL __attribute__ ((__format__ (__printf__, 3, 0)));
#endif
#if __GLIBC_USE (LIB_EXT2)
extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
__gnuc_va_list __arg)
__THROWNL __attribute__ ((__format__ (__printf__, 2, 0))) __wur;
extern int __asprintf (char **__restrict __ptr,
const char *__restrict __fmt, ...)
__THROWNL __attribute__ ((__format__ (__printf__, 2, 3))) __wur;
extern int asprintf (char **__restrict __ptr,
const char *__restrict __fmt, ...)
__THROWNL __attribute__ ((__format__ (__printf__, 2, 3))) __wur;
#endif
#ifdef __USE_XOPEN2K8
extern int vdprintf (int __fd, const char *__restrict __fmt,
__gnuc_va_list __arg)
__attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
__attribute__ ((__format__ (__printf__, 2, 3)));
#endif
extern int fscanf (FILE *__restrict __stream,
const char *__restrict __format, ...) __wur;
extern int scanf (const char *__restrict __format, ...) __wur;
extern int sscanf (const char *__restrict __s,
const char *__restrict __format, ...) __THROW;
#if !__GLIBC_USE (DEPRECATED_SCANF) && !defined __LDBL_COMPAT
# ifdef __REDIRECT
extern int __REDIRECT (fscanf, (FILE *__restrict __stream,
const char *__restrict __format, ...),
__isoc99_fscanf) __wur;
extern int __REDIRECT (scanf, (const char *__restrict __format, ...),
__isoc99_scanf) __wur;
extern int __REDIRECT_NTH (sscanf, (const char *__restrict __s,
const char *__restrict __format, ...),
__isoc99_sscanf);
# else
extern int __isoc99_fscanf (FILE *__restrict __stream,
const char *__restrict __format, ...) __wur;
extern int __isoc99_scanf (const char *__restrict __format, ...) __wur;
extern int __isoc99_sscanf (const char *__restrict __s,
const char *__restrict __format, ...) __THROW;
# define fscanf __isoc99_fscanf
# define scanf __isoc99_scanf
# define sscanf __isoc99_sscanf
# endif
#endif
#ifdef	__USE_ISOC99
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
__gnuc_va_list __arg)
__attribute__ ((__format__ (__scanf__, 2, 0))) __wur;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
__attribute__ ((__format__ (__scanf__, 1, 0))) __wur;
extern int vsscanf (const char *__restrict __s,
const char *__restrict __format, __gnuc_va_list __arg)
__THROW __attribute__ ((__format__ (__scanf__, 2, 0)));
# if !__GLIBC_USE (DEPRECATED_SCANF)
# if defined __REDIRECT && !defined __LDBL_COMPAT
extern int __REDIRECT (vfscanf,
(FILE *__restrict __s,
const char *__restrict __format, __gnuc_va_list __arg),
__isoc99_vfscanf)
__attribute__ ((__format__ (__scanf__, 2, 0))) __wur;
extern int __REDIRECT (vscanf, (const char *__restrict __format,
__gnuc_va_list __arg), __isoc99_vscanf)
__attribute__ ((__format__ (__scanf__, 1, 0))) __wur;
extern int __REDIRECT_NTH (vsscanf,
(const char *__restrict __s,
const char *__restrict __format,
__gnuc_va_list __arg), __isoc99_vsscanf)
__attribute__ ((__format__ (__scanf__, 2, 0)));
# elif !defined __REDIRECT
extern int __isoc99_vfscanf (FILE *__restrict __s,
const char *__restrict __format,
__gnuc_va_list __arg) __wur;
extern int __isoc99_vscanf (const char *__restrict __format,
__gnuc_va_list __arg) __wur;
extern int __isoc99_vsscanf (const char *__restrict __s,
const char *__restrict __format,
__gnuc_va_list __arg) __THROW;
# define vfscanf __isoc99_vfscanf
# define vscanf __isoc99_vscanf
# define vsscanf __isoc99_vsscanf
# endif
# endif
#endif 
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);
extern int getchar (void);
#ifdef __USE_POSIX199506
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
#endif 
#ifdef __USE_MISC
extern int fgetc_unlocked (FILE *__stream);
#endif 
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);
extern int putchar (int __c);
#ifdef __USE_MISC
extern int fputc_unlocked (int __c, FILE *__stream);
#endif 
#ifdef __USE_POSIX199506
extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);
#endif 
#if defined __USE_MISC \
|| (defined __USE_XOPEN && !defined __USE_XOPEN2K)
extern int getw (FILE *__stream);
extern int putw (int __w, FILE *__stream);
#endif
extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
__wur;
#if __GLIBC_USE (DEPRECATED_GETS)
extern char *gets (char *__s) __wur __attribute_deprecated__;
#endif
#ifdef __USE_GNU
extern char *fgets_unlocked (char *__restrict __s, int __n,
FILE *__restrict __stream) __wur;
#endif
#if defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2)
extern __ssize_t __getdelim (char **__restrict __lineptr,
size_t *__restrict __n, int __delimiter,
FILE *__restrict __stream) __wur;
extern __ssize_t getdelim (char **__restrict __lineptr,
size_t *__restrict __n, int __delimiter,
FILE *__restrict __stream) __wur;
extern __ssize_t getline (char **__restrict __lineptr,
size_t *__restrict __n,
FILE *__restrict __stream) __wur;
#endif
extern int fputs (const char *__restrict __s, FILE *__restrict __stream);
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream);
extern size_t fread (void *__restrict __ptr, size_t __size,
size_t __n, FILE *__restrict __stream) __wur;
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
size_t __n, FILE *__restrict __s);
#ifdef __USE_GNU
extern int fputs_unlocked (const char *__restrict __s,
FILE *__restrict __stream);
#endif
#ifdef __USE_MISC
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
size_t __n, FILE *__restrict __stream) __wur;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
size_t __n, FILE *__restrict __stream);
#endif
extern int fseek (FILE *__stream, long int __off, int __whence);
extern long int ftell (FILE *__stream) __wur;
extern void rewind (FILE *__stream);
#if defined __USE_LARGEFILE || defined __USE_XOPEN2K
# ifndef __USE_FILE_OFFSET64
extern int fseeko (FILE *__stream, __off_t __off, int __whence);
extern __off_t ftello (FILE *__stream) __wur;
# else
# ifdef __REDIRECT
extern int __REDIRECT (fseeko,
(FILE *__stream, __off64_t __off, int __whence),
fseeko64);
extern __off64_t __REDIRECT (ftello, (FILE *__stream), ftello64);
# else
# define fseeko fseeko64
# define ftello ftello64
# endif
# endif
#endif
#ifndef __USE_FILE_OFFSET64
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);
extern int fsetpos (FILE *__stream, const fpos_t *__pos);
#else
# ifdef __REDIRECT
extern int __REDIRECT (fgetpos, (FILE *__restrict __stream,
fpos_t *__restrict __pos), fgetpos64);
extern int __REDIRECT (fsetpos,
(FILE *__stream, const fpos_t *__pos), fsetpos64);
# else
# define fgetpos fgetpos64
# define fsetpos fsetpos64
# endif
#endif
#ifdef __USE_LARGEFILE64
extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) __wur;
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);
#endif
extern void clearerr (FILE *__stream) __THROW;
extern int feof (FILE *__stream) __THROW __wur;
extern int ferror (FILE *__stream) __THROW __wur;
#ifdef __USE_MISC
extern void clearerr_unlocked (FILE *__stream) __THROW;
extern int feof_unlocked (FILE *__stream) __THROW __wur;
extern int ferror_unlocked (FILE *__stream) __THROW __wur;
#endif
extern void perror (const char *__s);
#include <bits/sys_errlist.h>
#ifdef	__USE_POSIX
extern int fileno (FILE *__stream) __THROW __wur;
#endif 
#ifdef __USE_MISC
extern int fileno_unlocked (FILE *__stream) __THROW __wur;
#endif
#ifdef __USE_POSIX2
extern FILE *popen (const char *__command, const char *__modes) __wur;
extern int pclose (FILE *__stream);
#endif
#ifdef	__USE_POSIX
extern char *ctermid (char *__s) __THROW;
#endif 
#if (defined __USE_XOPEN && !defined __USE_XOPEN2K) || defined __USE_GNU
extern char *cuserid (char *__s);
#endif 
#ifdef	__USE_GNU
struct obstack;			extern int obstack_printf (struct obstack *__restrict __obstack,
const char *__restrict __format, ...)
__THROWNL __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
const char *__restrict __format,
__gnuc_va_list __args)
__THROWNL __attribute__ ((__format__ (__printf__, 2, 0)));
#endif 
#ifdef __USE_POSIX199506
extern void flockfile (FILE *__stream) __THROW;
extern int ftrylockfile (FILE *__stream) __THROW __wur;
extern void funlockfile (FILE *__stream) __THROW;
#endif 
#if defined __USE_XOPEN && !defined __USE_XOPEN2K && !defined __USE_GNU
# include <bits/getopt_posix.h>
#endif
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
#ifdef __USE_EXTERN_INLINES
# include <bits/stdio.h>
#endif
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
# include <bits/stdio2.h>
#endif
#ifdef __LDBL_COMPAT
# include <bits/stdio-ldbl.h>
#endif
__END_DECLS
#endif 
#ifndef	_STDLIB_H
#define __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#include <bits/libc-header-start.h>
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#include <stddef.h>
__BEGIN_DECLS
#define	_STDLIB_H	1
#if (defined __USE_XOPEN || defined __USE_XOPEN2K8) && !defined _SYS_WAIT_H
# include <bits/waitflags.h>
# include <bits/waitstatus.h>
# define WEXITSTATUS(status)	__WEXITSTATUS (status)
# define WTERMSIG(status)	__WTERMSIG (status)
# define WSTOPSIG(status)	__WSTOPSIG (status)
# define WIFEXITED(status)	__WIFEXITED (status)
# define WIFSIGNALED(status)	__WIFSIGNALED (status)
# define WIFSTOPPED(status)	__WIFSTOPPED (status)
# ifdef __WIFCONTINUED
# define WIFCONTINUED(status)	__WIFCONTINUED (status)
# endif
#endif	
#include <bits/floatn.h>
typedef struct
{
int quot;			int rem;			} div_t;
#ifndef __ldiv_t_defined
typedef struct
{
long int quot;		long int rem;		} ldiv_t;
# define __ldiv_t_defined	1
#endif
#if defined __USE_ISOC99 && !defined __lldiv_t_defined
__extension__ typedef struct
{
long long int quot;		long long int rem;		} lldiv_t;
# define __lldiv_t_defined	1
#endif
#define	RAND_MAX	2147483647
#define	EXIT_FAILURE	1	
#define	EXIT_SUCCESS	0	
#define	MB_CUR_MAX	(__ctype_get_mb_cur_max ())
extern size_t __ctype_get_mb_cur_max (void) __THROW __wur;
extern double atof (const char *__nptr)
__THROW __attribute_pure__ __nonnull ((1)) __wur;
extern int atoi (const char *__nptr)
__THROW __attribute_pure__ __nonnull ((1)) __wur;
extern long int atol (const char *__nptr)
__THROW __attribute_pure__ __nonnull ((1)) __wur;
#ifdef __USE_ISOC99
__extension__ extern long long int atoll (const char *__nptr)
__THROW __attribute_pure__ __nonnull ((1)) __wur;
#endif
extern double strtod (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#ifdef	__USE_ISOC99
extern float strtof (const char *__restrict __nptr,
char **__restrict __endptr) __THROW __nonnull ((1));
extern long double strtold (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT16 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float16 strtof16 (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT32 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float32 strtof32 (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT64 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float64 strtof64 (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT128 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float128 strtof128 (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT32X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float32x strtof32x (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT64X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float64x strtof64x (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT128X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float128x strtof128x (const char *__restrict __nptr,
char **__restrict __endptr)
__THROW __nonnull ((1));
#endif
extern long int strtol (const char *__restrict __nptr,
char **__restrict __endptr, int __base)
__THROW __nonnull ((1));
extern unsigned long int strtoul (const char *__restrict __nptr,
char **__restrict __endptr, int __base)
__THROW __nonnull ((1));
#ifdef __USE_MISC
__extension__
extern long long int strtoq (const char *__restrict __nptr,
char **__restrict __endptr, int __base)
__THROW __nonnull ((1));
__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
char **__restrict __endptr, int __base)
__THROW __nonnull ((1));
#endif 
#ifdef __USE_ISOC99
__extension__
extern long long int strtoll (const char *__restrict __nptr,
char **__restrict __endptr, int __base)
__THROW __nonnull ((1));
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
char **__restrict __endptr, int __base)
__THROW __nonnull ((1));
#endif 
#if __GLIBC_USE (IEC_60559_BFP_EXT_C2X)
extern int strfromd (char *__dest, size_t __size, const char *__format,
double __f)
__THROW __nonnull ((3));
extern int strfromf (char *__dest, size_t __size, const char *__format,
float __f)
__THROW __nonnull ((3));
extern int strfroml (char *__dest, size_t __size, const char *__format,
long double __f)
__THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT16 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf16 (char *__dest, size_t __size, const char * __format,
_Float16 __f)
__THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT32 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf32 (char *__dest, size_t __size, const char * __format,
_Float32 __f)
__THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT64 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf64 (char *__dest, size_t __size, const char * __format,
_Float64 __f)
__THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT128 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf128 (char *__dest, size_t __size, const char * __format,
_Float128 __f)
__THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT32X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf32x (char *__dest, size_t __size, const char * __format,
_Float32x __f)
__THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT64X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf64x (char *__dest, size_t __size, const char * __format,
_Float64x __f)
__THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT128X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf128x (char *__dest, size_t __size, const char * __format,
_Float128x __f)
__THROW __nonnull ((3));
#endif
#ifdef __USE_GNU
# include <bits/types/locale_t.h>
extern long int strtol_l (const char *__restrict __nptr,
char **__restrict __endptr, int __base,
locale_t __loc) __THROW __nonnull ((1, 4));
extern unsigned long int strtoul_l (const char *__restrict __nptr,
char **__restrict __endptr,
int __base, locale_t __loc)
__THROW __nonnull ((1, 4));
__extension__
extern long long int strtoll_l (const char *__restrict __nptr,
char **__restrict __endptr, int __base,
locale_t __loc)
__THROW __nonnull ((1, 4));
__extension__
extern unsigned long long int strtoull_l (const char *__restrict __nptr,
char **__restrict __endptr,
int __base, locale_t __loc)
__THROW __nonnull ((1, 4));
extern double strtod_l (const char *__restrict __nptr,
char **__restrict __endptr, locale_t __loc)
__THROW __nonnull ((1, 3));
extern float strtof_l (const char *__restrict __nptr,
char **__restrict __endptr, locale_t __loc)
__THROW __nonnull ((1, 3));
extern long double strtold_l (const char *__restrict __nptr,
char **__restrict __endptr,
locale_t __loc)
__THROW __nonnull ((1, 3));
# if __HAVE_FLOAT16
extern _Float16 strtof16_l (const char *__restrict __nptr,
char **__restrict __endptr,
locale_t __loc)
__THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT32
extern _Float32 strtof32_l (const char *__restrict __nptr,
char **__restrict __endptr,
locale_t __loc)
__THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT64
extern _Float64 strtof64_l (const char *__restrict __nptr,
char **__restrict __endptr,
locale_t __loc)
__THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT128
extern _Float128 strtof128_l (const char *__restrict __nptr,
char **__restrict __endptr,
locale_t __loc)
__THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT32X
extern _Float32x strtof32x_l (const char *__restrict __nptr,
char **__restrict __endptr,
locale_t __loc)
__THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT64X
extern _Float64x strtof64x_l (const char *__restrict __nptr,
char **__restrict __endptr,
locale_t __loc)
__THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT128X
extern _Float128x strtof128x_l (const char *__restrict __nptr,
char **__restrict __endptr,
locale_t __loc)
__THROW __nonnull ((1, 3));
# endif
#endif 
#ifdef __USE_EXTERN_INLINES
__extern_inline int
__NTH (atoi (const char *__nptr))
{
return (int) strtol (__nptr, (char **) NULL, 10);
}
__extern_inline long int
__NTH (atol (const char *__nptr))
{
return strtol (__nptr, (char **) NULL, 10);
}
# ifdef __USE_ISOC99
__extension__ __extern_inline long long int
__NTH (atoll (const char *__nptr))
{
return strtoll (__nptr, (char **) NULL, 10);
}
# endif
#endif 
#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
extern char *l64a (long int __n) __THROW __wur;
extern long int a64l (const char *__s)
__THROW __attribute_pure__ __nonnull ((1)) __wur;
#endif	
#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
# include <sys/types.h>	
extern long int random (void) __THROW;
extern void srandom (unsigned int __seed) __THROW;
extern char *initstate (unsigned int __seed, char *__statebuf,
size_t __statelen) __THROW __nonnull ((2));
extern char *setstate (char *__statebuf) __THROW __nonnull ((1));
# ifdef __USE_MISC
struct random_data
{
int32_t *fptr;		int32_t *rptr;		int32_t *state;		int rand_type;		int rand_deg;		int rand_sep;		int32_t *end_ptr;		};
extern int random_r (struct random_data *__restrict __buf,
int32_t *__restrict __result) __THROW __nonnull ((1, 2));
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
__THROW __nonnull ((2));
extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
size_t __statelen,
struct random_data *__restrict __buf)
__THROW __nonnull ((2, 4));
extern int setstate_r (char *__restrict __statebuf,
struct random_data *__restrict __buf)
__THROW __nonnull ((1, 2));
# endif	
#endif	
extern int rand (void) __THROW;
extern void srand (unsigned int __seed) __THROW;
#ifdef __USE_POSIX199506
extern int rand_r (unsigned int *__seed) __THROW;
#endif
#if defined __USE_MISC || defined __USE_XOPEN
extern double drand48 (void) __THROW;
extern double erand48 (unsigned short int __xsubi[3]) __THROW __nonnull ((1));
extern long int lrand48 (void) __THROW;
extern long int nrand48 (unsigned short int __xsubi[3])
__THROW __nonnull ((1));
extern long int mrand48 (void) __THROW;
extern long int jrand48 (unsigned short int __xsubi[3])
__THROW __nonnull ((1));
extern void srand48 (long int __seedval) __THROW;
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
__THROW __nonnull ((1));
extern void lcong48 (unsigned short int __param[7]) __THROW __nonnull ((1));
# ifdef __USE_MISC
struct drand48_data
{
unsigned short int __x[3];	unsigned short int __old_x[3]; unsigned short int __c;	unsigned short int __init;	__extension__ unsigned long long int __a;	};
extern int drand48_r (struct drand48_data *__restrict __buffer,
double *__restrict __result) __THROW __nonnull ((1, 2));
extern int erand48_r (unsigned short int __xsubi[3],
struct drand48_data *__restrict __buffer,
double *__restrict __result) __THROW __nonnull ((1, 2));
extern int lrand48_r (struct drand48_data *__restrict __buffer,
long int *__restrict __result)
__THROW __nonnull ((1, 2));
extern int nrand48_r (unsigned short int __xsubi[3],
struct drand48_data *__restrict __buffer,
long int *__restrict __result)
__THROW __nonnull ((1, 2));
extern int mrand48_r (struct drand48_data *__restrict __buffer,
long int *__restrict __result)
__THROW __nonnull ((1, 2));
extern int jrand48_r (unsigned short int __xsubi[3],
struct drand48_data *__restrict __buffer,
long int *__restrict __result)
__THROW __nonnull ((1, 2));
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
__THROW __nonnull ((2));
extern int seed48_r (unsigned short int __seed16v[3],
struct drand48_data *__buffer) __THROW __nonnull ((1, 2));
extern int lcong48_r (unsigned short int __param[7],
struct drand48_data *__buffer)
__THROW __nonnull ((1, 2));
# endif	
#endif	
extern void *malloc (size_t __size) __THROW __attribute_malloc__
__attribute_alloc_size__ ((1)) __wur;
extern void *calloc (size_t __nmemb, size_t __size)
__THROW __attribute_malloc__ __attribute_alloc_size__ ((1, 2)) __wur;
extern void *realloc (void *__ptr, size_t __size)
__THROW __attribute_warn_unused_result__ __attribute_alloc_size__ ((2));
#ifdef __USE_MISC
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
__THROW __attribute_warn_unused_result__
__attribute_alloc_size__ ((2, 3));
#endif
extern void free (void *__ptr) __THROW;
#ifdef __USE_MISC
#ifndef	_ALLOCA_H
#define	_ALLOCA_H	1
#ifndef	_FEATURES_H
#define	_FEATURES_H	1
#undef	__USE_ISOC11
#undef	__USE_ISOC99
#undef	__USE_ISOC95
#undef	__USE_ISOCXX11
#undef	__USE_POSIX
#undef	__USE_POSIX2
#undef	__USE_POSIX199309
#undef	__USE_POSIX199506
#undef	__USE_XOPEN
#undef	__USE_XOPEN_EXTENDED
#undef	__USE_UNIX98
#undef	__USE_XOPEN2K
#undef	__USE_XOPEN2KXSI
#undef	__USE_XOPEN2K8
#undef	__USE_XOPEN2K8XSI
#undef	__USE_LARGEFILE
#undef	__USE_LARGEFILE64
#undef	__USE_FILE_OFFSET64
#undef	__USE_MISC
#undef	__USE_ATFILE
#undef	__USE_GNU
#undef	__USE_FORTIFY_LEVEL
#undef	__KERNEL_STRICT_NAMES
#undef	__GLIBC_USE_ISOC2X
#undef	__GLIBC_USE_DEPRECATED_GETS
#undef	__GLIBC_USE_DEPRECATED_SCANF
#ifndef _LOOSE_KERNEL_NAMES
# define __KERNEL_STRICT_NAMES
#endif
#if defined __GNUC__ && defined __GNUC_MINOR__
# define __GNUC_PREREQ(maj, min) \
((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define __GNUC_PREREQ(maj, min) 0
#endif
#if defined __clang_major__ && defined __clang_minor__
# define __glibc_clang_prereq(maj, min) \
((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else
# define __glibc_clang_prereq(maj, min) 0
#endif
#define __GLIBC_USE(F)	__GLIBC_USE_ ## F
#if (defined _BSD_SOURCE || defined _SVID_SOURCE) \
&& !defined _DEFAULT_SOURCE
# warning "_BSD_SOURCE and _SVID_SOURCE are deprecated, use _DEFAULT_SOURCE"
# undef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE	1
#endif
#ifdef _GNU_SOURCE
# undef _ISOC95_SOURCE
# define _ISOC95_SOURCE	1
# undef _ISOC99_SOURCE
# define _ISOC99_SOURCE	1
# undef _ISOC11_SOURCE
# define _ISOC11_SOURCE	1
# undef _ISOC2X_SOURCE
# define _ISOC2X_SOURCE	1
# undef _POSIX_SOURCE
# define _POSIX_SOURCE	1
# undef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE	200809L
# undef _XOPEN_SOURCE
# define _XOPEN_SOURCE	700
# undef _XOPEN_SOURCE_EXTENDED
# define _XOPEN_SOURCE_EXTENDED	1
# undef	 _LARGEFILE64_SOURCE
# define _LARGEFILE64_SOURCE	1
# undef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE	1
# undef _ATFILE_SOURCE
# define _ATFILE_SOURCE	1
#endif
#if (defined _DEFAULT_SOURCE					\
|| (!defined __STRICT_ANSI__				\
&& !defined _ISOC99_SOURCE && !defined _ISOC11_SOURCE	\
&& !defined _ISOC2X_SOURCE				\
&& !defined _POSIX_SOURCE && !defined _POSIX_C_SOURCE	\
&& !defined _XOPEN_SOURCE))
# undef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE	1
#endif
#if (defined _ISOC2X_SOURCE \
|| (defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L))
# define __GLIBC_USE_ISOC2X	1
#else
# define __GLIBC_USE_ISOC2X	0
#endif
#if (defined _ISOC11_SOURCE || defined _ISOC2X_SOURCE \
|| (defined __STDC_VERSION__ && __STDC_VERSION__ >= 201112L))
# define __USE_ISOC11	1
#endif
#if (defined _ISOC99_SOURCE || defined _ISOC11_SOURCE			\
|| defined _ISOC2X_SOURCE						\
|| (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L))
# define __USE_ISOC99	1
#endif
#if (defined _ISOC99_SOURCE || defined _ISOC11_SOURCE			\
|| defined _ISOC2X_SOURCE						\
|| (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199409L))
# define __USE_ISOC95	1
#endif
#ifdef __cplusplus
# if __cplusplus >= 201703L
# define __USE_ISOC11	1
# endif
# if __cplusplus >= 201103L || defined __GXX_EXPERIMENTAL_CXX0X__
# define __USE_ISOCXX11	1
# define __USE_ISOC99	1
# endif
#endif
#ifdef _DEFAULT_SOURCE
# if !defined _POSIX_SOURCE && !defined _POSIX_C_SOURCE
# define __USE_POSIX_IMPLICITLY	1
# endif
# undef _POSIX_SOURCE
# define _POSIX_SOURCE	1
# undef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE	200809L
#endif
#if ((!defined __STRICT_ANSI__					\
|| (defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) >= 500))	\
&& !defined _POSIX_SOURCE && !defined _POSIX_C_SOURCE)
# define _POSIX_SOURCE	1
# if defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 500
# define _POSIX_C_SOURCE	2
# elif defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 600
# define _POSIX_C_SOURCE	199506L
# elif defined _XOPEN_SOURCE && (_XOPEN_SOURCE - 0) < 700
# define _POSIX_C_SOURCE	200112L
# else
# define _POSIX_C_SOURCE	200809L
# endif
# define __USE_POSIX_IMPLICITLY	1
#endif
#if ((!defined _POSIX_C_SOURCE || (_POSIX_C_SOURCE - 0) < 199506L) \
&& (defined _REENTRANT || defined _THREAD_SAFE))
# define _POSIX_SOURCE 1
# undef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 199506L
#endif
#if (defined _POSIX_SOURCE					\
|| (defined _POSIX_C_SOURCE && _POSIX_C_SOURCE >= 1)	\
|| defined _XOPEN_SOURCE)
# define __USE_POSIX	1
#endif
#if defined _POSIX_C_SOURCE && _POSIX_C_SOURCE >= 2 || defined _XOPEN_SOURCE
# define __USE_POSIX2	1
#endif
#if defined _POSIX_C_SOURCE && (_POSIX_C_SOURCE - 0) >= 199309L
# define __USE_POSIX199309	1
#endif
#if defined _POSIX_C_SOURCE && (_POSIX_C_SOURCE - 0) >= 199506L
# define __USE_POSIX199506	1
#endif
#if defined _POSIX_C_SOURCE && (_POSIX_C_SOURCE - 0) >= 200112L
# define __USE_XOPEN2K		1
# undef __USE_ISOC95
# define __USE_ISOC95		1
# undef __USE_ISOC99
# define __USE_ISOC99		1
#endif
#if defined _POSIX_C_SOURCE && (_POSIX_C_SOURCE - 0) >= 200809L
# define __USE_XOPEN2K8		1
# undef _ATFILE_SOURCE
# define _ATFILE_SOURCE	1
#endif
#ifdef	_XOPEN_SOURCE
# define __USE_XOPEN	1
# if (_XOPEN_SOURCE - 0) >= 500
# define __USE_XOPEN_EXTENDED	1
# define __USE_UNIX98	1
# undef _LARGEFILE_SOURCE
# define _LARGEFILE_SOURCE	1
# if (_XOPEN_SOURCE - 0) >= 600
# if (_XOPEN_SOURCE - 0) >= 700
# define __USE_XOPEN2K8	1
# define __USE_XOPEN2K8XSI	1
# endif
# define __USE_XOPEN2K	1
# define __USE_XOPEN2KXSI	1
# undef __USE_ISOC95
# define __USE_ISOC95		1
# undef __USE_ISOC99
# define __USE_ISOC99		1
# endif
# else
# ifdef _XOPEN_SOURCE_EXTENDED
# define __USE_XOPEN_EXTENDED	1
# endif
# endif
#endif
#ifdef _LARGEFILE_SOURCE
# define __USE_LARGEFILE	1
#endif
#ifdef _LARGEFILE64_SOURCE
# define __USE_LARGEFILE64	1
#endif
#if defined _FILE_OFFSET_BITS && _FILE_OFFSET_BITS == 64
# define __USE_FILE_OFFSET64	1
#endif
#if defined _DEFAULT_SOURCE
# define __USE_MISC	1
#endif
#ifdef	_ATFILE_SOURCE
# define __USE_ATFILE	1
#endif
#ifdef	_GNU_SOURCE
# define __USE_GNU	1
#endif
#if defined _FORTIFY_SOURCE && _FORTIFY_SOURCE > 0 \
&& __GNUC_PREREQ (4, 1) && defined __OPTIMIZE__ && __OPTIMIZE__ > 0
# if _FORTIFY_SOURCE > 1
# define __USE_FORTIFY_LEVEL 2
# else
# define __USE_FORTIFY_LEVEL 1
# endif
#else
# define __USE_FORTIFY_LEVEL 0
#endif
#if defined __cplusplus ? __cplusplus >= 201402L : defined __USE_ISOC11
# define __GLIBC_USE_DEPRECATED_GETS 0
#else
# define __GLIBC_USE_DEPRECATED_GETS 1
#endif
#if (defined __USE_GNU							\
&& (defined __cplusplus						\
? (__cplusplus < 201103L && !defined __GXX_EXPERIMENTAL_CXX0X__) \
: (!defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L)))
# define __GLIBC_USE_DEPRECATED_SCANF 1
#else
# define __GLIBC_USE_DEPRECATED_SCANF 0
#endif
#ifndef	_STDC_PREDEF_H
#define	_STDC_PREDEF_H	1
#ifdef __GCC_IEC_559
# if __GCC_IEC_559 > 0
# define __STDC_IEC_559__		1
# endif
#else
# define __STDC_IEC_559__		1
#endif
#ifdef __GCC_IEC_559_COMPLEX
# if __GCC_IEC_559_COMPLEX > 0
# define __STDC_IEC_559_COMPLEX__	1
# endif
#else
# define __STDC_IEC_559_COMPLEX__	1
#endif
#define __STDC_ISO_10646__		201706L
#endif
#undef __GNU_LIBRARY__
#define __GNU_LIBRARY__ 6
#define	__GLIBC__	2
#define	__GLIBC_MINOR__	31
#define __GLIBC_PREREQ(maj, min) \
((__GLIBC__ << 16) + __GLIBC_MINOR__ >= ((maj) << 16) + (min))
#ifndef __ASSEMBLER__
# ifndef _SYS_CDEFS_H
# include <sys/cdefs.h>
# endif
# if defined __USE_FILE_OFFSET64 && !defined __REDIRECT
# define __USE_LARGEFILE	1
# define __USE_LARGEFILE64	1
# endif
#endif	
#if __GNUC_PREREQ (2, 7) && defined __OPTIMIZE__ \
&& !defined __OPTIMIZE_SIZE__ && !defined __NO_INLINE__ \
&& defined __extern_inline
# define __USE_EXTERN_INLINES	1
#endif
#include <gnu/stubs.h>
#endif	
#define	__need_size_t
#include <stddef.h>
__BEGIN_DECLS
#undef	alloca
extern void *alloca (size_t __size) __THROW;
#ifdef	__GNUC__
# define alloca(size)	__builtin_alloca (size)
#endif 
__END_DECLS
#endif 
#endif 
#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K) \
|| defined __USE_MISC
extern void *valloc (size_t __size) __THROW __attribute_malloc__
__attribute_alloc_size__ ((1)) __wur;
#endif
#ifdef __USE_XOPEN2K
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
__THROW __nonnull ((1)) __wur;
#endif
#ifdef __USE_ISOC11
extern void *aligned_alloc (size_t __alignment, size_t __size)
__THROW __attribute_malloc__ __attribute_alloc_size__ ((2)) __wur;
#endif
extern void abort (void) __THROW __attribute__ ((__noreturn__));
extern int atexit (void (*__func) (void)) __THROW __nonnull ((1));
#if defined __USE_ISOC11 || defined __USE_ISOCXX11
# ifdef __cplusplus
extern "C++" int at_quick_exit (void (*__func) (void))
__THROW __asm ("at_quick_exit") __nonnull ((1));
# else
extern int at_quick_exit (void (*__func) (void)) __THROW __nonnull ((1));
# endif
#endif
#ifdef	__USE_MISC
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
__THROW __nonnull ((1));
#endif
extern void exit (int __status) __THROW __attribute__ ((__noreturn__));
#if defined __USE_ISOC11 || defined __USE_ISOCXX11
extern void quick_exit (int __status) __THROW __attribute__ ((__noreturn__));
#endif
#ifdef __USE_ISOC99
extern void _Exit (int __status) __THROW __attribute__ ((__noreturn__));
#endif
extern char *getenv (const char *__name) __THROW __nonnull ((1)) __wur;
#ifdef __USE_GNU
extern char *secure_getenv (const char *__name)
__THROW __nonnull ((1)) __wur;
#endif
#if defined __USE_MISC || defined __USE_XOPEN
extern int putenv (char *__string) __THROW __nonnull ((1));
#endif
#ifdef __USE_XOPEN2K
extern int setenv (const char *__name, const char *__value, int __replace)
__THROW __nonnull ((2));
extern int unsetenv (const char *__name) __THROW __nonnull ((1));
#endif
#ifdef	__USE_MISC
extern int clearenv (void) __THROW;
#endif
#if defined __USE_MISC \
|| (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8)
extern char *mktemp (char *__template) __THROW __nonnull ((1));
#endif
#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
# ifndef __USE_FILE_OFFSET64
extern int mkstemp (char *__template) __nonnull ((1)) __wur;
# else
# ifdef __REDIRECT
extern int __REDIRECT (mkstemp, (char *__template), mkstemp64)
__nonnull ((1)) __wur;
# else
# define mkstemp mkstemp64
# endif
# endif
# ifdef __USE_LARGEFILE64
extern int mkstemp64 (char *__template) __nonnull ((1)) __wur;
# endif
#endif
#ifdef __USE_MISC
# ifndef __USE_FILE_OFFSET64
extern int mkstemps (char *__template, int __suffixlen) __nonnull ((1)) __wur;
# else
# ifdef __REDIRECT
extern int __REDIRECT (mkstemps, (char *__template, int __suffixlen),
mkstemps64) __nonnull ((1)) __wur;
# else
# define mkstemps mkstemps64
# endif
# endif
# ifdef __USE_LARGEFILE64
extern int mkstemps64 (char *__template, int __suffixlen)
__nonnull ((1)) __wur;
# endif
#endif
#ifdef __USE_XOPEN2K8
extern char *mkdtemp (char *__template) __THROW __nonnull ((1)) __wur;
#endif
#ifdef __USE_GNU
# ifndef __USE_FILE_OFFSET64
extern int mkostemp (char *__template, int __flags) __nonnull ((1)) __wur;
# else
# ifdef __REDIRECT
extern int __REDIRECT (mkostemp, (char *__template, int __flags), mkostemp64)
__nonnull ((1)) __wur;
# else
# define mkostemp mkostemp64
# endif
# endif
# ifdef __USE_LARGEFILE64
extern int mkostemp64 (char *__template, int __flags) __nonnull ((1)) __wur;
# endif
# ifndef __USE_FILE_OFFSET64
extern int mkostemps (char *__template, int __suffixlen, int __flags)
__nonnull ((1)) __wur;
# else
# ifdef __REDIRECT
extern int __REDIRECT (mkostemps, (char *__template, int __suffixlen,
int __flags), mkostemps64)
__nonnull ((1)) __wur;
# else
# define mkostemps mkostemps64
# endif
# endif
# ifdef __USE_LARGEFILE64
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
__nonnull ((1)) __wur;
# endif
#endif
extern int system (const char *__command) __wur;
#ifdef	__USE_GNU
extern char *canonicalize_file_name (const char *__name)
__THROW __nonnull ((1)) __wur;
#endif
#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
extern char *realpath (const char *__restrict __name,
char *__restrict __resolved) __THROW __wur;
#endif
#ifndef __COMPAR_FN_T
# define __COMPAR_FN_T
typedef int (*__compar_fn_t) (const void *, const void *);
# ifdef	__USE_GNU
typedef __compar_fn_t comparison_fn_t;
# endif
#endif
#ifdef __USE_GNU
typedef int (*__compar_d_fn_t) (const void *, const void *, void *);
#endif
extern void *bsearch (const void *__key, const void *__base,
size_t __nmemb, size_t __size, __compar_fn_t __compar)
__nonnull ((1, 2, 5)) __wur;
#ifdef __USE_EXTERN_INLINES
# include <bits/stdlib-bsearch.h>
#endif
extern void qsort (void *__base, size_t __nmemb, size_t __size,
__compar_fn_t __compar) __nonnull ((1, 4));
#ifdef __USE_GNU
extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
__compar_d_fn_t __compar, void *__arg)
__nonnull ((1, 4));
#endif
extern int abs (int __x) __THROW __attribute__ ((__const__)) __wur;
extern long int labs (long int __x) __THROW __attribute__ ((__const__)) __wur;
#ifdef __USE_ISOC99
__extension__ extern long long int llabs (long long int __x)
__THROW __attribute__ ((__const__)) __wur;
#endif
extern div_t div (int __numer, int __denom)
__THROW __attribute__ ((__const__)) __wur;
extern ldiv_t ldiv (long int __numer, long int __denom)
__THROW __attribute__ ((__const__)) __wur;
#ifdef __USE_ISOC99
__extension__ extern lldiv_t lldiv (long long int __numer,
long long int __denom)
__THROW __attribute__ ((__const__)) __wur;
#endif
#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8) \
|| defined __USE_MISC
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
int *__restrict __sign) __THROW __nonnull ((3, 4)) __wur;
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
int *__restrict __sign) __THROW __nonnull ((3, 4)) __wur;
extern char *gcvt (double __value, int __ndigit, char *__buf)
__THROW __nonnull ((3)) __wur;
#endif
#ifdef __USE_MISC
extern char *qecvt (long double __value, int __ndigit,
int *__restrict __decpt, int *__restrict __sign)
__THROW __nonnull ((3, 4)) __wur;
extern char *qfcvt (long double __value, int __ndigit,
int *__restrict __decpt, int *__restrict __sign)
__THROW __nonnull ((3, 4)) __wur;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
__THROW __nonnull ((3)) __wur;
extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
int *__restrict __sign, char *__restrict __buf,
size_t __len) __THROW __nonnull ((3, 4, 5));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
int *__restrict __sign, char *__restrict __buf,
size_t __len) __THROW __nonnull ((3, 4, 5));
extern int qecvt_r (long double __value, int __ndigit,
int *__restrict __decpt, int *__restrict __sign,
char *__restrict __buf, size_t __len)
__THROW __nonnull ((3, 4, 5));
extern int qfcvt_r (long double __value, int __ndigit,
int *__restrict __decpt, int *__restrict __sign,
char *__restrict __buf, size_t __len)
__THROW __nonnull ((3, 4, 5));
#endif	
extern int mblen (const char *__s, size_t __n) __THROW;
extern int mbtowc (wchar_t *__restrict __pwc,
const char *__restrict __s, size_t __n) __THROW;
extern int wctomb (char *__s, wchar_t __wchar) __THROW;
extern size_t mbstowcs (wchar_t *__restrict __pwcs,
const char *__restrict __s, size_t __n) __THROW;
extern size_t wcstombs (char *__restrict __s,
const wchar_t *__restrict __pwcs, size_t __n)
__THROW;
#ifdef __USE_MISC
extern int rpmatch (const char *__response) __THROW __nonnull ((1)) __wur;
#endif
#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
extern int getsubopt (char **__restrict __optionp,
char *const *__restrict __tokens,
char **__restrict __valuep)
__THROW __nonnull ((1, 2, 3)) __wur;
#endif
#ifdef __USE_XOPEN2KXSI
extern int posix_openpt (int __oflag) __wur;
#endif
#ifdef __USE_XOPEN_EXTENDED
extern int grantpt (int __fd) __THROW;
extern int unlockpt (int __fd) __THROW;
extern char *ptsname (int __fd) __THROW __wur;
#endif
#ifdef __USE_GNU
extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
__THROW __nonnull ((2));
extern int getpt (void);
#endif
#ifdef __USE_MISC
extern int getloadavg (double __loadavg[], int __nelem)
__THROW __nonnull ((1));
#endif
#if defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K
extern int ttyslot (void) __THROW;
#endif
#include <bits/stdlib-float.h>
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
# include <bits/stdlib.h>
#endif
#ifdef __LDBL_COMPAT
# include <bits/stdlib-ldbl.h>
#endif
__END_DECLS
#endif 
void piramide();
void modificar(); 
void buscarChar(); 
void buscarFrase(); 
void agregarCalzado();
void zapateria();
struct Calzado {
struct Calzado *sig;
char *marca;
int *precio;
int *talla;
};
struct Calzado *primero = NULL;
int main() {
zapateria();
return 0;
}
void piramide() {
int *tam = NULL;
tam = (int*) malloc(1); 
puts("\nAltura de piramide: ");
scanf("%i", tam);
int esp = *tam - 1;
int ast = 1;
for (int linea = 0; linea < *tam; ++linea) {
for (int i = 0; i < esp; ++i) 
putchar(' ');
for (int j = 0; j < ast; ++j) 
putchar('$');
esp--;
ast += 2;
puts("");
}
}
void modificar() {
int edad = 21;
float alt = 1.69;
char gen = 'M';
puts("\n___________Datos____________");
printf("edad: %i \t -> %p\n", edad, &edad);
printf("altura: %f -> %p\n", alt, &alt);
printf("genero: %c \t -> %p\n", gen, &gen);
int *pEdad = &edad;
float *pAlt = &alt;
char *pGen = &gen;
*pEdad = *pEdad + 1;
*pAlt = *pAlt + 0.01;
*pGen = 'F';
puts("\n________Nuevos Datos________");
printf("edad: %i \t -> %p\n", edad, &edad);
printf("altura: %f -> %p\n", alt, &alt);
printf("genero: %c \t -> %p\n", gen, &gen);
puts("\n_____Direccion Punteros_____");
printf("pEdad -> %p\n", pEdad);
printf("pAlt: -> %p\n", pAlt);
printf("pGen: -> %p\n", pGen);
puts("\n_____Contenido Punteros_____");
printf("pEdad -> %i\n", *pEdad);
printf("pAlt: -> %f\n", *pAlt);
printf("pGen: -> %c\n", *pGen);
}
void buscarChar() {
char *cadena = "the way that I need you";
char *c = "o";
int i = 0;
while(cadena[i]) {
if(cadena[i] == *c) {
printf("\nPrimera ocurrencia de \"%c\" en la posicion %i:", *c, i);
printf("\n%s\n", cadena);
for (int j = 0; j <= i; ++j) {
if(j == i) {
putchar('^');
return;
}
putchar(' ');
}
}
i++;
}
printf("\nEl char \"%c\" no existe en la cadena.", *c);
}
void buscarFrase() {
char *frase = "and though you will no wait for me, I'll wait for you.";
char *palab = "you";
int i = 0, t = 0, c = 0;
while(frase[i]) {
if(frase[i] != ' ') {
if (frase[i] == palab[t]) {
t++;
}else {
t = 0;
}
}else if(!palab[t]) {
printf("La palabra existe a partir de la posicion %d.", c);
return;
}else {
c = i;
t = 0;
}
i++;
}
if(t > 0) { 
printf("La palabra existe al final.");
return;
}
puts("La no palabra existe dentro de la frase.");
}
void imprimirTodos() {
puts("\n__________Lista de zapatos_________");
struct Calzado *aux = primero;
int c = 1;
while(aux != NULL) {
printf("%i) Marca: %s, Precio: %i, Talla: %i\n", c, aux->marca, aux->precio, aux->talla);
aux = aux->sig;
c++;
}
}
void imprimirPorTalla(int *t) {
printf("\n__________Lista Talla %i_________\n", *t);
struct Calzado *aux = primero;
int c = 1;
while(aux != NULL) {
if((int)aux->talla == *t) {
printf("%i) Marca: %s, Precio: %i, Talla: %i\n", c, aux->marca, aux->precio, aux->talla);
}
aux = aux->sig;
c++;
}
printf("\n____________Fin de lista_________\n");
}
void zapateria() {
agregarCalzado("Adidas", 54000, 38);
agregarCalzado("Converse", 40000, 38);
agregarCalzado("DC", 24000, 39);
agregarCalzado("Nike", 30000, 35);
agregarCalzado("Nike", 55000, 39);
agregarCalzado("DC", 28000, 41);
agregarCalzado("Converse", 38000, 40);
agregarCalzado("Adidas", 23000, 35);
agregarCalzado("Carterpilar", 24000, 39);
agregarCalzado("Nike", 25000, 37);
while(1) {
puts("\n****** Menu Zapateria, Bienvenido(a) *****");
puts("1) Agregar zapato \n2) Ver por talla \n3) Inventario \n4) Salir");
int option;
printf("-> "); scanf("%i", &option);
if(option == 4)
break;
switch (option) {
case 1: {
char *marca = (char*) malloc(1);
int precio, talla;
printf("Marca: "); fflush(stdin); gets(marca);
printf("Precio: "); scanf("%i", &precio);
printf("Talla: "); scanf("%i", &talla);
if(34 > talla || 44 < talla) {
printf("Error en talla, unicamente de 34 a 44.\n");
break;
}
agregarCalzado(marca, precio, talla);
puts("*** Agregado con exito! ***");
break;
}
case 2: {
puts("\nQue talla busca?");
int talla; scanf("%i", &talla);
imprimirPorTalla(&talla);
break;
}
case 3: {
imprimirTodos();
break;
}
default:
puts("Opcion invalida!");
}
}
}
void agregarCalzado(char *marca, int *precio, int *talla) {
struct Calzado *nuevo = (struct Calzado*) malloc(sizeof(struct Calzado));
nuevo->sig = NULL;
nuevo->marca = (char*) malloc(1);
nuevo->precio = (int*) malloc(1);
nuevo->talla = (int*) malloc(1);
nuevo->marca = marca;
nuevo->precio = precio;
nuevo->talla = talla;
if(primero == NULL) {
primero = nuevo;
}else{
nuevo->sig = primero;
primero = nuevo;
}
}
