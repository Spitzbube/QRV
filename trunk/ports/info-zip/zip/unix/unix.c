/*
  Copyright (c) 1990-2006 Info-ZIP.  All rights reserved.

  See the accompanying file LICENSE, version 2005-Feb-10 or later
  (the contents of which are also included in zip.h) for terms of use.
  If, for some reason, both of these files are missing, the Info-ZIP license
  also may be found at:  ftp://ftp.info-zip.org/pub/infozip/license.html
*/
#include "zip.h"

#ifndef UTIL                    /* the companion #endif is a bit of ways down ... */

#include <time.h>
#include <sys/utsname.h>

#if (!defined(S_IWRITE) && defined(S_IWUSR))
#define S_IWRITE S_IWUSR
#endif

#if defined(HAVE_DIRENT_H) || defined(_POSIX_VERSION)
#include <dirent.h>
#else                           /* !HAVE_DIRENT_H */
#ifdef HAVE_NDIR_H
#include <ndir.h>
#endif                          /* HAVE_NDIR_H */
#ifdef HAVE_SYS_NDIR_H
#include <sys/ndir.h>
#endif                          /* HAVE_SYS_NDIR_H */
#ifdef HAVE_SYS_DIR_H
#include <sys/dir.h>
#endif                          /* HAVE_SYS_DIR_H */
#ifndef dirent
#define dirent direct
#endif
#endif                          /* HAVE_DIRENT_H || _POSIX_VERSION */

#define PAD 0
#define PATH_END '/'

/* Library functions not in (most) header files */

#include <utime.h>

extern char *label;
local ulg label_time = 0;
local ulg label_mode = 0;
local time_t label_utim = 0;

/* Local functions */
local char *readd OF((DIR *));


#ifdef NO_DIR                   /* for AT&T 3B1 */
#include <sys/dir.h>
#ifndef dirent
#define dirent direct
#endif
typedef FILE DIR;
/*
**  Apparently originally by Rich Salz.
**  Cleaned up and modified by James W. Birdsall.
*/

#define opendir(path) fopen(path, "r")

struct dirent *readdir(dirp)
DIR *dirp;
{
    static struct dirent entry;

    if (dirp == NULL)
        return NULL;
    for (;;)
        if (fread(&entry, sizeof(struct dirent), 1, dirp) == 0)
            return NULL;
        else if (entry.d_ino)
            return (&entry);
}                               /* end of readdir() */

#define closedir(dirp) fclose(dirp)
#endif                          /* NO_DIR */


local char *readd(d)
DIR *d;                         /* directory stream to read from */
/* Return a pointer to the next name in the directory stream d, or NULL if
   no more entries or an error occurs. */
{
    struct dirent *e;

    e = readdir(d);
    return e == NULL ? (char *) NULL : e->d_name;
}

int procname(n, caseflag)
char *n;                        /* name to process */
int caseflag;                   /* true to force case-sensitive match */
/* Process a name or sh expression to operate on (or exclude).  Return
   an error code in the ZE_ class. */
{
    char *a;                    /* path and name for recursion */
    DIR *d;                     /* directory stream from opendir() */
    char *e;                    /* pointer to name from readd() */
    int m;                      /* matched flag */
    char *p;                    /* path for recursion */
    struct stat s;              /* result of stat() */
    struct zlist far *z;        /* steps through zfiles list */

    if (strcmp(n, "-") == 0)    /* if compressing stdin */
        return newname(n, 0, caseflag);
    else if (LSSTAT(n, &s)) {
        /* Not a file or directory--search for shell expression in zip file */
        p = ex2in(n, 0, (int *) NULL);  /* shouldn't affect matching chars */
        m = 1;
        for (z = zfiles; z != NULL; z = z->nxt) {
            if (MATCH(p, z->iname, caseflag)) {
                z->mark = pcount ? filter(z->zname, caseflag) : 1;
                if (verbose)
                    fprintf(mesg, "zip diagnostic: %scluding %s\n", z->mark ? "in" : "ex", z->name);
                m = 0;
            }
        }
        free((zvoid *) p);
        return m ? ZE_MISS : ZE_OK;
    }

    /* Live name--use if file, recurse if directory */
#ifdef OS390
    if (S_ISREG(s.st_mode) || S_ISLNK(s.st_mode))
#else
#ifdef S_IFLNK
    if ((s.st_mode & S_IFREG) == S_IFREG || (s.st_mode & S_IFLNK) == S_IFLNK)
#else
    if ((s.st_mode & S_IFREG) == S_IFREG)
#endif
#endif
    {
        /* add or remove name of file */
        if ((m = newname(n, 0, caseflag)) != ZE_OK)
            return m;
    }
#ifdef OS390
    else if (S_ISDIR(s.st_mode))
#else
    else if ((s.st_mode & S_IFDIR) == S_IFDIR)
#endif
    {
        /* Add trailing / to the directory name */
        if ((p = malloc(strlen(n) + 2)) == NULL)
            return ZE_MEM;
        if (strcmp(n, ".") == 0) {
            *p = '\0';          /* avoid "./" prefix and do not create zip entry */
        } else {
            strcpy(p, n);
            a = p + strlen(p);
            if (a[-1] != '/')
                strcpy(a, "/");
            if (dirnames && (m = newname(p, 1, caseflag)) != ZE_OK) {
                free((zvoid *) p);
                return m;
            }
        }
        /* recurse into directory */
        if (recurse && (d = opendir(n)) != NULL) {
            while ((e = readd(d)) != NULL) {
                if (strcmp(e, ".") && strcmp(e, "..")) {
                    if ((a = malloc(strlen(p) + strlen(e) + 1)) == NULL) {
                        closedir(d);
                        free((zvoid *) p);
                        return ZE_MEM;
                    }
                    strcat(strcpy(a, p), e);
                    if ((m = procname(a, caseflag)) != ZE_OK) { /* recurse on name */
                        if (m == ZE_MISS)
                            zipwarn("name not matched: ", a);
                        else
                            ziperr(m, a);
                    }
                    free((zvoid *) a);
                }
            }
            closedir(d);
        }
        free((zvoid *) p);
    }                           /* (s.st_mode & S_IFDIR) */
#if defined(S_IFIFO) || defined(OS390)
#ifdef OS390
    else if (S_ISFIFO(s.st_mode))
#else
    else if ((s.st_mode & S_IFIFO) == S_IFIFO)
#endif
    {
        /* FIFO (Named Pipe) - handle as normal file */
        /* add or remove name of FIFO */
        if (noisy)
            zipwarn("FIFO (Named Pipe): ", n);
        if ((m = newname(n, 0, caseflag)) != ZE_OK)
            return m;
    }
#endif                          /* S_IFIFO || OS390 */
    else
        zipwarn("ignoring special file: ", n);
    return ZE_OK;
}

char *ex2in(x, isdir, pdosflag)
char *x;                        /* external file name */
int isdir;                      /* input: x is a directory */
int *pdosflag;                  /* output: force MSDOS file attributes? */
/* Convert the external file name to a zip file name, returning the malloc'ed
   string or NULL if not enough memory. */
{
    char *n;                    /* internal file name (malloc'ed) */
    char *t = NULL;             /* shortened name */
    int dosflag;

    dosflag = dosify;           /* default for non-DOS and non-OS/2 */

    /* Find starting point in name before doing malloc */
    /* Strip "//host/share/" part of a UNC name */
    if (!strncmp(x, "//", 2) && (x[2] != '\0' && x[2] != '/')) {
        n = x + 2;
        while (*n != '\0' && *n != '/')
            n++;                /* strip host name */
        if (*n != '\0') {
            n++;
            while (*n != '\0' && *n != '/')
                n++;            /* strip `share' name */
        }
        if (*n != '\0')
            t = n + 1;
    } else
        t = x;
    while (*t == '/')
        t++;                    /* strip leading '/' chars to get a relative path */
    while (*t == '.' && t[1] == '/')
        t += 2;                 /* strip redundant leading "./" sections */

    /* Make changes, if any, to the copied name (leave original intact) */
    if (!pathput)
        t = last(t, PATH_END);

    /* Malloc space for internal name and copy it */
    if ((n = malloc(strlen(t) + 1)) == NULL)
        return NULL;
    strcpy(n, t);

    if (dosify)
        msname(n);

#ifdef EBCDIC
    strtoasc(n, n);             /* here because msname() needs native coding */
#endif

    /* Returned malloc'ed name */
    if (pdosflag)
        *pdosflag = dosflag;

    if (isdir)
        return n;               /* avoid warning on unused variable */
    return n;
}

char *in2ex(n)
char *n;                        /* internal file name */
/* Convert the zip file name to an external file name, returning the malloc'ed
   string or NULL if not enough memory. */
{
    char *x;                    /* external file name */

    if ((x = malloc(strlen(n) + 1 + PAD)) == NULL)
        return NULL;
#ifdef EBCDIC
    strtoebc(x, n);
#else
    strcpy(x, n);
#endif
    return x;
}

/*
 * XXX use ztimbuf in both POSIX and non POSIX cases ?
 */
void stamp(f, d)
char *f;                        /* name of file to change */
ulg d;                          /* dos-style time to change it to */
/* Set last updated and accessed time of file f to the DOS time d. */
{
#ifdef _POSIX_VERSION
    struct utimbuf u;           /* argument for utime()  const ?? */
#else
    time_t u[2];                /* argument for utime() */
#endif

    /* Convert DOS time to time_t format in u */
#ifdef _POSIX_VERSION
    u.actime = u.modtime = dos2unixtime(d);
    utime(f, &u);
#else
    u[0] = u[1] = dos2unixtime(d);
    utime(f, u);
#endif

}

ulg filetime(f, a, n, t)
char *f;                        /* name of file to get info on */
ulg *a;                         /* return value: file attributes */
long *n;                        /* return value: file size */
iztimes *t;                     /* return value: access, modific. and creation times */
/* If file *f does not exist, return 0.  Else, return the file's last
   modified date and time as an MSDOS date and time.  The date and
   time is returned in a long with the date most significant to allow
   unsigned integer comparison of absolute times.  Also, if a is not
   a NULL pointer, store the file attributes there, with the high two
   bytes being the Unix attributes, and the low byte being a mapping
   of that to DOS attributes.  If n is not NULL, store the file size
   there.  If t is not NULL, the file's access, modification and creation
   times are stored there as UNIX time_t values.
   If f is "-", use standard input as the file. If f is a device, return
   a file size of -1 */
{
    struct stat s;              /* results of stat() */
    /* converted to pointer from using FNMAX - 11/8/04 EG */
    char *name;
    int len = strlen(f);

    if (f == label) {
        if (a != NULL)
            *a = label_mode;
        if (n != NULL)
            *n = -2L;           /* convention for a label name */
        if (t != NULL)
            t->atime = t->mtime = t->ctime = label_utim;
        return label_time;
    }
    if ((name = malloc(len + 1)) == NULL) {
        ZIPERR(ZE_MEM, "filetime");
    }
    strcpy(name, f);
    if (name[len - 1] == '/')
        name[len - 1] = '\0';
    /* not all systems allow stat'ing a file with / appended */
    if (strcmp(f, "-") == 0) {
        if (fstat(fileno(stdin), &s) != 0) {
            free(name);
            error("fstat(stdin)");
        }
    } else if (LSSTAT(name, &s) != 0) {
        /* Accept about any file kind including directories
         * (stored with trailing / with -r option)
         */
        free(name);
        return 0;
    }
    free(name);

    if (a != NULL) {
#ifndef OS390
        *a = ((ulg) s.st_mode << 16) | !(s.st_mode & S_IWRITE);
#else
/*
**  The following defines are copied from the unizip source and represent the
**  legacy Unix mode flags.  These fixed bit masks are no longer required
**  by XOPEN standards - the S_IS### macros being the new recommended method.
**  The approach here of setting the legacy flags by testing the macros should
**  work under any _XOPEN_SOURCE environment (and will just rebuild the same bit
**  mask), but is required if the legacy bit flags differ from legacy Unix.
*/
#define UNX_IFDIR      0040000  /* Unix directory */
#define UNX_IFREG      0100000  /* Unix regular file */
#define UNX_IFSOCK     0140000  /* Unix socket (BSD, not SysV or Amiga) */
#define UNX_IFLNK      0120000  /* Unix symbolic link (not SysV, Amiga) */
#define UNX_IFBLK      0060000  /* Unix block special       (not Amiga) */
#define UNX_IFCHR      0020000  /* Unix character special   (not Amiga) */
#define UNX_IFIFO      0010000  /* Unix fifo    (BCC, not MSC or Amiga) */
        {
            mode_t legacy_modes;

            /* Initialize with permission bits--which are not implementation-optional */
            legacy_modes = s.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX);
            if (S_ISDIR(s.st_mode))
                legacy_modes |= UNX_IFDIR;
            if (S_ISREG(s.st_mode))
                legacy_modes |= UNX_IFREG;
            if (S_ISLNK(s.st_mode))
                legacy_modes |= UNX_IFLNK;
            if (S_ISBLK(s.st_mode))
                legacy_modes |= UNX_IFBLK;
            if (S_ISCHR(s.st_mode))
                legacy_modes |= UNX_IFCHR;
            if (S_ISFIFO(s.st_mode))
                legacy_modes |= UNX_IFIFO;
            if (S_ISSOCK(s.st_mode))
                legacy_modes |= UNX_IFSOCK;
            *a = ((ulg) legacy_modes << 16) | !(s.st_mode & S_IWRITE);
        }
#endif
        if ((s.st_mode & S_IFMT) == S_IFDIR) {
            *a |= MSDOS_DIR_ATTR;
        }
    }
    if (n != NULL)
        *n = (s.st_mode & S_IFMT) == S_IFREG ? s.st_size : -1L;
    if (t != NULL) {
        t->atime = s.st_atime;
        t->mtime = s.st_mtime;
        t->ctime = t->mtime;    /* best guess, (s.st_ctime: last status change!!) */
    }

    return unix2dostime(&s.st_mtime);
}


#ifndef QLZIP                   /* QLZIP Unix2QDOS cross-Zip supplies an extended variant */

int set_extra_field(z, z_utim)
struct zlist far *z;
iztimes *z_utim;
  /* store full data in local header but just modification time stamp info
     in central header */
{
    struct stat s;
    char *name;
    int len = strlen(z->name);

    /* For the full sized UT local field including the UID/GID fields, we
     * have to stat the file again. */

    if ((name = malloc(len + 1)) == NULL) {
        ZIPERR(ZE_MEM, "set_extra_field");
    }
    strcpy(name, z->name);
    if (name[len - 1] == '/')
        name[len - 1] = '\0';
    /* not all systems allow stat'ing a file with / appended */
    if (LSSTAT(name, &s)) {
        free(name);
        return ZE_OPEN;
    }
    free(name);

#define EB_L_UT_SIZE    (EB_HEADSIZE + EB_UT_LEN(2))
#define EB_C_UT_SIZE    (EB_HEADSIZE + EB_UT_LEN(1))
#define EB_L_UX2_SIZE   (EB_HEADSIZE + EB_UX2_MINLEN)
#define EB_C_UX2_SIZE   EB_HEADSIZE
#define EF_L_UNIX_SIZE  (EB_L_UT_SIZE + EB_L_UX2_SIZE)
#define EF_C_UNIX_SIZE  (EB_C_UT_SIZE + EB_C_UX2_SIZE)

    if ((z->extra = (char *) malloc(EF_L_UNIX_SIZE)) == NULL)
        return ZE_MEM;
    if ((z->cextra = (char *) malloc(EF_C_UNIX_SIZE)) == NULL)
        return ZE_MEM;

    z->extra[0] = 'U';
    z->extra[1] = 'T';
    z->extra[2] = (char) EB_UT_LEN(2);  /* length of data part of local e.f. */
    z->extra[3] = 0;
    z->extra[4] = EB_UT_FL_MTIME | EB_UT_FL_ATIME;  /* st_ctime != creation */
    z->extra[5] = (char) (s.st_mtime);
    z->extra[6] = (char) (s.st_mtime >> 8);
    z->extra[7] = (char) (s.st_mtime >> 16);
    z->extra[8] = (char) (s.st_mtime >> 24);
    z->extra[9] = (char) (s.st_atime);
    z->extra[10] = (char) (s.st_atime >> 8);
    z->extra[11] = (char) (s.st_atime >> 16);
    z->extra[12] = (char) (s.st_atime >> 24);
    z->extra[13] = 'U';
    z->extra[14] = 'x';
    z->extra[15] = (char) EB_UX2_MINLEN;    /* length of data part of local e.f. */
    z->extra[16] = 0;
    z->extra[17] = (char) (s.st_uid);
    z->extra[18] = (char) (s.st_uid >> 8);
    z->extra[19] = (char) (s.st_gid);
    z->extra[20] = (char) (s.st_gid >> 8);
    z->ext = EF_L_UNIX_SIZE;

    memcpy(z->cextra, z->extra, EB_C_UT_SIZE);
    z->cextra[EB_LEN] = (char) EB_UT_LEN(1);
    memcpy(z->cextra + EB_C_UT_SIZE, z->extra + EB_L_UT_SIZE, EB_C_UX2_SIZE);
    z->cextra[EB_LEN + EB_C_UT_SIZE] = 0;
    z->cext = EF_C_UNIX_SIZE;

    return ZE_OK;
}

#endif                          /* !QLZIP */


/**
 * \brief Delete the directory *d if it is empty, do nothing otherwise.
 * \param[in] d directory to delete */
 * \return The result of rmdir().
 */
int deletedir(const char *d)
{
    return rmdir(d);
}

#endif                          /* !UTIL */


/******************************/
/*  Function version_local()  */
/******************************/

#if defined(__NetBSD__) || defined(__FreeBSD__) || defined(__386BSD__) || \
    defined(__OpenBSD__) || defined(__bsdi__)
#include <sys/param.h>          /* for the BSD define */
/* if we have something newer than NET/2 we'll use uname(3) */
#if (BSD > 199103)

#endif                          /* BSD > 199103 */
#endif                          /* __{Net,Free,Open,386}BSD__ || __bsdi__ */

void version_local()
{
#define COMPILER_NAME "gcc " __VERSION__
#define COMPILE_DATE " on " __DATE__
    struct utsname uts;

    uname(&uts);
    printf("Compiled with %s for %s on %s.\n\n", COMPILER_NAME, uts->sysname, COMPILE_DATE);
}
