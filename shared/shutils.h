/*
 * Shell-like utility functions
 *
 * Copyright 2005, Broadcom Corporation
 * All Rights Reserved.
 * 
 * THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
 * KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
 * SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.
 *
 * $Id$
 */

#ifndef _shutils_h_
#define _shutils_h_

#include <string.h>
#include <signal.h>

#define        MTD_DEV(arg)            "/dev/mtd/"#arg

#define	ARRAY_SIZE(x)	((unsigned)(sizeof(x) / sizeof((x)[0])))

/*
 * Checks if file exists
 * @param	fd	file descriptor
 * @return	return st_mode field (0 if not exists)
 */
extern mode_t exists(const char *path);

/*
 * Reads file and returns contents
 * @param	fd	file descriptor
 * @return	contents of file or NULL if an error occurred
 */
extern char * fd2str(int fd);

/*
 * Reads file and returns contents
 * @param	path	path to file
 * @return	contents of file or NULL if an error occurred
 */
extern char * file2str(const char *path);

/* 
 * Waits for a file descriptor to become available for reading or unblocked signal
 * @param	fd	file descriptor
 * @param	timeout	seconds to wait before timing out or 0 for no timeout
 * @return	1 if descriptor changed status or 0 if timed out or -1 on error
 */
extern int waitfor(int fd, int timeout);

/* 
 * Concatenates NULL-terminated list of arguments into a single
 * commmand and executes it
 * @param	argv	argument list
 * @param	path	NULL, ">output", or ">>output"
 * @param	timeout	seconds to wait before timing out or 0 for no timeout
 * @param	ppid	NULL to wait for child termination or pointer to pid
 * @return	return value of executed command or errno
 */
extern int _eval(char *const argv[], const char *path, int timeout, pid_t *ppid);

/* 
 * Concatenates NULL-terminated list of arguments into a single
 * commmand and executes it
 * @param	argv	argument list
 * @return	stdout of executed command or NULL if an error occurred
 */
extern char * _backtick(char *const argv[]);

/* 
 * Kills process whose PID is stored in plaintext in pidfile
 * @param	pidfile	PID file
 * @return	0 on success and errno on failure
 */
int kill_pidfile_s(const char *pidfile, int sig);

int kill_pidfile(const char *pidfile);

/*
 * fread() with automatic retry on syscall interrupt
 * @param	ptr	location to store to
 * @param	size	size of each element of data
 * @param	nmemb	number of elements
 * @param	stream	file stream
 * @return	number of items successfully read
 */
extern int safe_fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

/*
 * fwrite() with automatic retry on syscall interrupt
 * @param	ptr	location to read from
 * @param	size	size of each element of data
 * @param	nmemb	number of elements
 * @param	stream	file stream
 * @return	number of items successfully written
 */
extern int safe_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

/*
 * Convert Ethernet address string representation to binary data
 * @param	a	string in xx:xx:xx:xx:xx:xx notation
 * @param	e	binary data
 * @return	TRUE if conversion was successful and FALSE otherwise
 */
extern int ether_atoe(const char *a, unsigned char *e);

/*
 * Convert Ethernet address binary data to string representation
 * @param	e	binary data
 * @param	a	string in xx:xx:xx:xx:xx:xx notation
 * @return	a
 */
extern char * ether_etoa(const unsigned char *e, char *a);

/*
 * Concatenate two strings together into a caller supplied buffer
 * @param	s1	first string
 * @param	s2	second string
 * @param	buf	buffer large enough to hold both strings
 * @return	buf
 */
static inline char * strcat_r(const char *s1, const char *s2, char *buf)
{
	strcpy(buf, s1);
	strcat(buf, s2);
	return buf;
}	

/*
 * Search a string backwards for a set of characters
 * This is the reverse version of strspn()
 *
 * @param       s       string to search backwards
 * @param       accept  set of chars for which to search
 * @return      number of characters in the trailing segment of s.
 *              which consist only of characters from accept.
 */
extern size_t sh_strrspn(const char *s, const char *accept);

/*
 * Parse the unit and subunit from an interface string such as wlXX or wlXX.YY
 *
 * @param	ifname	interface string to parse
 * @param	unit	pointer to return the unit number, may pass NULL
 * @param	subunit	pointer to return the subunit number, may pass NULL
 * @return	Returns 0 if the string ends with digits or digits.digits, -1 otherwise.
 *		If ifname ends in digits.digits, then unit and subuint are set
 *		to the first and second values respectively. If ifname ends 
 *		in just digits, unit is set to the value, and subunit is set
 *		to -1. On error both unit and subunit are -1. NULL may be passed
 *		for unit and/or subuint to ignore the value.
 */
extern int get_ifname_unit(const char* ifname, int *unit, int *subunit);

/*
 * Set the ip configuration index given the eth name
 * Updates both wlXX_ipconfig_index and lanYY_ifname.
 * 
 * @param	eth_ifname 	pointer to eth interface name
 * @return	0 if successful -1 if not.
 */
 extern int set_ipconfig_index(const char *eth_ifname, int index);

/*
 * Get the ip configuration index if it exists given the 
 * eth name.
 * 
 * @param	wl_ifname 	pointer to eth interface name
 * @return	index or -1 if not found
 */
extern int get_ipconfig_index(const char *eth_ifname);

/*
 * Get interfaces belonging to a specific bridge.
 * 
 * @param	bridge_name 	pointer to bridge interface name
 * @return	list on interfaces beloging to the bridge
 */	
extern char *
get_bridged_interfaces(const char *bridge_name);

/*
 * Get product id & fw version from flash
 */
extern int get_fw_ver(char *productid, char *fwver);

enum {
        MDL_UNKNOWN,
	MDL_MN700,
        MDL_WL700G,
	MDL_WL500GX,
	MDL_WL550GE,
	MDL_WL320GE,
	MDL_WL330GE,
	MDL_WL500GP,
	MDL_WL500GPV2,
	MDL_WL500W,
	MDL_WL520GU,
	MDL_DIR320,
	MDL_RTN16,
	MDL_RTN12,
	MDL_RTN12B1,
	MDL_RTN10,
	MDL_RTN10U,
	MDL_WNR3500L,
};

extern int get_model(void);

/* 
		remove_from_list
		Remove the specified word from the list.

		@param name word to be removed from the list
		@param list List to modify
		@param listsize Max size the list can occupy

		@return	error code
*/
extern int remove_from_list(const char *name, char *list, int listsize);

/*
		add_to_list
		Add the specified interface(string) to the list as long as
		it will fit in the space left in the list.  

		@param name Name of interface to be added to the list
		@param list List to modify
		@param listsize Max size the list can occupy

		@return	error code
*/
extern int add_to_list(const char *name, char *list, int listsize);

extern char *find_in_list(const char *haystack, const char *needle);

extern int nvifname_to_osifname( const char *nvifname, char *osifname_buf, 
								int osifname_buf_len );
extern int osifname_to_nvifname( const char *osifname, char *nvifname_buf, 
								int nvifname_buf_len );

/* Check for a blank character; that is, a space or a tab */
#ifndef isblank
# define isblank(c) ((c) == ' ' || (c) == '\t')
#endif

/* Strip trailing CR/NL from string <s> */
#define chomp(s) ({ \
	char *c = (s) + strlen((s)) - 1; \
	while ((c > (s)) && (*c == '\n' || *c == '\r')) \
		*c-- = '\0'; \
	s; \
})

/* Simple version of _backtick() */
#define backtick(cmd, args...) ({ \
	const char * const argv[] = { cmd, ## args, NULL }; \
	_backtick((char * const *)argv); \
})

/* Simple version of _eval() (no timeout and wait for child termination) */
#define eval(cmd, args...) ({ \
	const char * const argv[] = { cmd, ## args, NULL }; \
	_eval((char * const *)argv, ">/dev/null", 0, NULL); \
})

/* Copy each token in wordlist delimited by space into word */
#define foreach(word, wordlist, next) \
	for (next = &wordlist[strspn(wordlist, " ")], \
	     strncpy(word, next, sizeof(word)), \
	     word[strcspn(word, " ")] = '\0', \
	     word[sizeof(word) - 1] = '\0', \
	     next = strchr(next, ' '); \
	     strlen(word); \
	     next = next ? &next[strspn(next, " ")] : "", \
	     strncpy(word, next, sizeof(word)), \
	     word[strcspn(word, " ")] = '\0', \
	     word[sizeof(word) - 1] = '\0', \
	     next = strchr(next, ' '))

/* Return NUL instead of NULL if undefined */
#define safe_getenv(s) (getenv(s) ? : "")

#if defined(linux) && defined(DEBUG)
# ifdef DEBUG_TO_SYSLOG
# define cprintf cprintf_syslog
extern void cprintf_syslog( char * fmt, ... );
# else
/* Print directly to the console */
#define cprintf(fmt, args...) do { \
	FILE *fp = fopen("/dev/console", "w"); \
	if (fp) { \
		fprintf(fp, fmt, ## args); \
		fclose(fp); \
	} \
} while (0)
# endif

#else
#define cprintf(fmt, args...) 
#endif

/* Debug print */
#ifdef DEBUG
#define dprintf(fmt, args...) cprintf("%s: " fmt, __FUNCTION__, ## args)
#else
#define dprintf(fmt, args...)
#endif /*DEBUG*/


#endif /* _shutils_h_ */
