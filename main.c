#include "ft_printf.h"
#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

int					main(int argc, char **argv);

#define BIG (1 << 20)
#define MAXSHOW 4

static int g_pass, g_fail, g_same, g_diff;
static int g_verbose, g_info, g_gpass, g_gfail, g_shown;
static const char	*g_gname;
static char			g_ctx[512];
static int			g_saved;
static FILE			*g_tmp;
static char			g_a[BIG];
static char			g_b[BIG];
static char			g_long[300001];
static void			*g_heap;
static uint64_t		g_rng = 88172645463325252ULL;

/* ------------------------------------------------------------------ */
/*  capture: run a call with stdout redirected to a temporary file    */
/* ------------------------------------------------------------------ */
static void	cap_start(void)
{
	fflush(stdout);
	g_saved = dup(1);
	g_tmp = tmpfile();
	dup2(fileno(g_tmp), 1);
}

static size_t	cap_end(char *buf)
{
	size_t	n;

	fflush(stdout);
	dup2(g_saved, 1);
	close(g_saved);
	fseek(g_tmp, 0, SEEK_SET);
	n = fread(buf, 1, BIG - 1, g_tmp);
	buf[n] = '\0';
	fclose(g_tmp);
	return (n);
}

static void	show(const char *s, size_t n)
{
	size_t	i;

	putchar('[');
	for (i = 0; i < n && i < 70; i++)
	{
		if (s[i] == '\n')
			printf("\\n");
		else if (s[i] == '\0')
			printf("\\0");
		else if (isprint((unsigned char)s[i]))
			putchar(s[i]);
		else
			printf("\\x%02x", (unsigned char)s[i]);
	}
	if (n > 70)
		printf("...(%zu bytes)", n);
	putchar(']');
}

static void	detail(size_t na, size_t nb, int ra, int rb)
{
	printf("    mine: ");
	show(g_a, na);
	printf(" ret=%d\n    real: ", ra);
	show(g_b, nb);
	printf(" ret=%d\n", rb);
	if (g_ctx[0])
		printf("    %s\n", g_ctx);
}

static void	report(const char *name, size_t na, size_t nb, int ra, int rb)
{
	int	ok;

	ok = (na == nb && memcmp(g_a, g_b, na) == 0 && ra == rb);
	if (g_info)
	{
		if (ok)
			g_same++;
		else
			g_diff++;
		printf("%s %.90s\n", ok ? "[same]" : "[DIFF]", name);
		if (!ok)
			detail(na, nb, ra, rb);
		return ;
	}
	if (ok)
		g_pass++, g_gpass++;
	else
		g_fail++, g_gfail++;
	if (ok && !g_verbose)
		return ;
	if (!ok && g_shown++ >= MAXSHOW)
		return ;
	printf("%s %.90s\n", ok ? "[PASS]" : "[FAIL]", name);
	if (!ok)
		detail(na, nb, ra, rb);
}

static void	group_end(void)
{
	if (!g_gname)
		return ;
	if (g_gfail)
		printf("[FAIL] %s (%d of %d cases failed)\n", g_gname, g_gfail, g_gpass
			+ g_gfail);
	else
		printf("[PASS] %s (%d cases)\n", g_gname, g_gpass);
	g_gname = NULL;
}

static void	group(const char *name)
{
	group_end();
	g_gname = name;
	g_gpass = 0;
	g_gfail = 0;
	g_shown = 0;
}

/* Calls ft_printf and printf with the same arguments, then compares
   the printed bytes AND the return value. */
#define CHECKN(name, ...)                 \
	do                                    \
	{                                     \
		size_t na_, nb_;                  \
		int ra_, rb_;                     \
		cap_start();                      \
		ra_ = ft_printf(__VA_ARGS__);     \
		na_ = cap_end(g_a);               \
		cap_start();                      \
		rb_ = printf(__VA_ARGS__);        \
		nb_ = cap_end(g_b);               \
		report(name, na_, nb_, ra_, rb_); \
	} while (0)
#define CHECK(...) CHECKN(#__VA_ARGS__, __VA_ARGS__)

static void	section(const char *title)
{
	group_end();
	printf("\n== %s ==\n", title);
}

static void	verdict(const char *name, int ok, const char *detail_txt)
{
	group_end();
	if (ok)
		g_pass++;
	else
		g_fail++;
	printf("%s %s %s\n", ok ? "[PASS]" : "[FAIL]", name, detail_txt);
}

/* ------------------------------------------------------------------ */
/*  random value generators                                           */
/* ------------------------------------------------------------------ */
static uint64_t	rnd(void)
{
	g_rng ^= g_rng << 13;
	g_rng ^= g_rng >> 7;
	g_rng ^= g_rng << 17;
	return (g_rng);
}

static int	rint32(void)
{
	switch (rnd() % 6)
	{
	case 0:
		return ((int)(rnd() % 20) - 10);
	case 1:
		return (INT_MAX - (int)(rnd() % 3));
	case 2:
		return (INT_MIN + (int)(rnd() % 3));
	case 3:
		return ((int)(rnd() % 100000) - 50000);
	default:
		return ((int)rnd());
	}
}

static void	*rptr(void)
{
	switch (rnd() % 7)
	{
	case 0:
		return (NULL);
	case 1:
		return ((void *)(uintptr_t)(rnd() % 4096));
	case 2:
		return ((void *)&g_a[rnd() % 1000]);
	case 3:
		return (g_heap);
	case 4:
		return ((void *)main);
	case 5:
		return ((void *)(uintptr_t)rnd());
	default:
		return ((void *)(uintptr_t)(rnd() >> 16));
	}
}

static char			*g_strs[] = {NULL, "", "a", "hello", "%d", "%", "(null)",
				"h\xc3\xa9llo", "\xff\xfe\x01", "line\nbreak\ttab",
				"0123456789012345678901234567890123456789"};

/* ------------------------------------------------------------------ */
/*  1. conversions, one by one                                        */
/* ------------------------------------------------------------------ */
static void	test_char_str(void)
{
	char	c_neg;
	int		i;

	c_neg = -1;
	group("%c edge cases");
	CHECK("%c", 0);
	CHECK("%c", 255);
	CHECK("%c", 256);
	CHECK("%c", 'A' + 256);
	CHECK("%c", -1);
	CHECK("%c", c_neg);
	CHECK("%c", INT_MAX);
	CHECK("%c", INT_MIN);
	CHECK("%c%c%c", 0, 0, 0);
	CHECK("a%cb%cc", 0, 0);
	for (i = -300; i <= 600; i++)
		CHECK("%c|", i);
	group("%s edge cases");
	CHECK("%s", (char *)NULL);
	CHECK("%s%s%s", (char *)NULL, (char *)NULL, (char *)NULL);
	CHECK("a%sb%sc", (char *)NULL, "");
	CHECK("%s", "");
	CHECK("%s%s%s", "", "", "");
	CHECK("%s", "h\xc3\xa9llo w\xc3\xb6rld");
	CHECK("%s", "\x01\x02\x7f\x80\xff");
	CHECK("%s", "%");
	CHECK("%s", "%%");
	CHECK("%s", "%s%d%c%p");
	CHECK("%s", "line1\nline2\ttab\r\n");
	CHECK("%s%s", g_long, g_long);
	CHECK("%s|%s|%s", g_long, "", g_long + 299990);
	group("%% edge cases");
	CHECK("%%");
	CHECK("%%%%");
	CHECK("%%%%%%%%%%");
	CHECK("100%%");
	CHECK("%%d");
	CHECK("%%s %%c %%p");
	CHECK("%c%%%c", 'a', 'b');
	CHECK("%%%c%%", 'x');
	CHECK("%%%s%%%d%%", "s", 5);
}

static void	test_numbers(void)
{
	unsigned long	p;
	int				i;
	int				k;
	int				v;

	group("%d / %i boundaries");
	for (p = 1; p <= 1000000000UL; p *= 10)
	{
		CHECK("%d", (int)(p - 1));
		CHECK("%d", (int)p);
		CHECK("%d", (int)(p + 1));
		CHECK("%d", -(int)(p - 1));
		CHECK("%d", -(int)p);
		CHECK("%d", -(int)(p + 1));
	}
	for (i = -1000; i <= 1000; i++)
		CHECK("%d|%i", i, -i);
	for (k = 0; k < 31; k++)
		CHECK("%d %d %d %i", 1 << k, -(1 << k), (1 << k) - 1, ~(1 << k));
	CHECK("%d %i", INT_MAX, INT_MIN);
	CHECK("%d %i", INT_MAX - 1, INT_MIN + 1);
	for (i = 0; i < 20000; i++)
	{
		v = rint32();
		CHECK("%d", v);
	}
	group("%u boundaries");
	for (p = 1; p <= 4294967295UL; p *= 10)
	{
		CHECK("%u", (unsigned)(p - 1));
		CHECK("%u", (unsigned)p);
		CHECK("%u", (unsigned)(p + 1));
	}
	CHECK("%u %u %u", 0u, UINT_MAX, UINT_MAX - 1);
	CHECK("%u %u", (unsigned)-1, (unsigned)INT_MIN);
	for (k = 0; k < 32; k++)
		CHECK("%u %u %u", 1u << k, (1u << k) - 1, ~(1u << k));
	for (i = 0; i < 20000; i++)
	{
		v = rint32();
		CHECK("%u", (unsigned)v);
	}
	group("%x / %X boundaries");
	for (k = 0; k < 32; k++)
	{
		CHECK("%x %x %x", 1u << k, (1u << k) - 1, ~(1u << k));
		CHECK("%X %X %X", 1u << k, (1u << k) - 1, ~(1u << k));
	}
	CHECK("%x %X", 0u, 0u);
	CHECK("%x %X", 15u, 15u);
	CHECK("%x %X", 16u, 16u);
	CHECK("%x %X", 0xdeadbeefu, 0xdeadbeefu);
	CHECK("%x %X", 0xabcdef01u, 0xabcdef01u);
	CHECK("%x %X", UINT_MAX, UINT_MAX);
	CHECK("%x %X", (unsigned)-1, (unsigned)INT_MIN);
	for (i = 0; i < 20000; i++)
	{
		v = rint32();
		CHECK("%x", (unsigned)v);
		v = rint32();
		CHECK("%X", (unsigned)v);
	}
}

static void	test_pointers(void)
{
	int		k;
	int		i;
	int		local;
	void	*pp;

	group("%p edge cases");
	CHECK("%p", (void *)0);
	CHECK("[%p]", (void *)0);
	CHECK("%p", (void *)1);
	CHECK("%p", (void *)15);
	CHECK("%p", (void *)16);
	CHECK("%p", (void *)-1);
	CHECK("%p", (void *)LONG_MIN);
	CHECK("%p", (void *)LONG_MAX);
	CHECK("%p", (void *)&local);
	CHECK("%p", g_heap);
	CHECK("%p", (void *)main);
	CHECK("%p", (void *)g_a);
	CHECK("%p %p %p", (void *)0, (void *)-1, (void *)0);
	for (k = 0; k < 64; k++)
		CHECK("%p %p", (void *)(1UL << k), (void *)((1UL << k) - 1));
	for (i = 0; i < 20000; i++)
	{
		pp = rptr();
		CHECK("%p", pp);
	}
}

/* ------------------------------------------------------------------ */
/*  2. combinations                                                   */
/* ------------------------------------------------------------------ */
#define D5 "%d%d%d%d%d"
#define D40 D5 D5 D5 D5 D5 D5 D5 D5
#define M8 "%c%s%d%i%u%x%X%p"
#define V8 'a', "str", -1, 2, 3u, 255u, 255u, (void *)&g_pass

static void	test_combinations(void)
{
	group("everything mixed");
	CHECK("%c %s %d %i %u %x %X %p %%", 'z', "s", 1, 2, 3u, 4u, 5u, (void *)6);
	CHECK("%p %X %x %u %i %d %s %c", (void *)6, 5u, 4u, 3u, 2, 1, "s", 'z');
	CHECK("%s%s%s%s%s", "a", "b", "c", "d", "e");
	CHECK("%d%d%d%d%d%d%d%d%d%d", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	CHECK("%c%c%c%c%c%c%c%c%c%c", 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'j');
	CHECK("%x%X%x%X%x%X%x%X", 10u, 11u, 12u, 13u, 14u, 15u, 16u, 17u);
	CHECK("%d%s%d%s%d%s", INT_MIN, "", INT_MAX, (char *)NULL, 0, "x");
	CHECK("%d is %i, %u is %x, %c%c%c", -5, 5, 5u, 255u, 'o', 'k', '!');
	CHECK("hello", 1, 2, 3);
	CHECK("%d", 1, 2, 3);
	group("many arguments (stack passing)");
	CHECK(D40, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
		19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
		37, 38, 39, 40);
	CHECK(M8 M8 M8, V8, V8, V8);
	CHECK(M8 M8 M8 M8, V8, V8, V8, V8);
}

/* ------------------------------------------------------------------ */
/*  3. fuzzer: random format strings, random values                   */
/* ------------------------------------------------------------------ */
/* NOTE: every argument is passed as a 64-bit intptr_t. That is only
   "defined" on x86-64 Linux (like the 42 machines), where an int is read
   from the low 32 bits of the slot. */
static void	test_fuzz(int rounds)
{
	static const char	*spec[] = {"%c", "%s", "%d", "%i", "%u", "%x", "%X",
			"%p", "%%"};
	static const char	*lit[] = {"a", "-", " | ", "\n", "0x", "(null)", "12",
			"  "};
	char				fmt[256];
	intptr_t			a[8];

	int n, k, t, i;
	group("fuzzer: random formats and values");
	for (i = 0; i < rounds; i++)
	{
		fmt[0] = '\0';
		memset(a, 0, sizeof(a));
		n = 0;
		for (k = 1 + (int)(rnd() % 7); k > 0; k--)
		{
			t = (int)(rnd() % 12);
			if (t >= 9)
			{
				strcat(fmt, lit[rnd() % 8]);
				continue ;
			}
			strcat(fmt, spec[t]);
			if (t == 0 || t == 2 || t == 3)
				a[n++] = (intptr_t)rint32();
			else if (t == 1)
				a[n++] = (intptr_t)g_strs[rnd() % 11];
			else if (t == 4 || t == 5 || t == 6)
				a[n++] = (intptr_t)(unsigned)rint32();
			else if (t == 7)
				a[n++] = (intptr_t)rptr();
		}
		snprintf(g_ctx, sizeof(g_ctx), "args: %lx %lx %lx %lx %lx %lx %lx",
			(unsigned long)a[0], (unsigned long)a[1], (unsigned long)a[2],
			(unsigned long)a[3], (unsigned long)a[4], (unsigned long)a[5],
			(unsigned long)a[6]);
		CHECKN(fmt, fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
		g_ctx[0] = '\0';
	}
}

/* ------------------------------------------------------------------ */
/*  4. system behavior: leaks, write errors                           */
/* ------------------------------------------------------------------ */
static void	test_leak(void)
{
	struct rusage r0, r1;
	int saved, devnull, i;
	group_end();
	fflush(stdout);
	saved = dup(1);
	devnull = open("/dev/null", O_WRONLY);
	dup2(devnull, 1);
	getrusage(RUSAGE_SELF, &r0);
	for (i = 0; i < 100000; i++)
		ft_printf("%d %i %u %x %X %p %s %c", INT_MIN, INT_MAX, UINT_MAX,
			UINT_MAX, UINT_MAX, (void *)&r0, "str", 'c');
	getrusage(RUSAGE_SELF, &r1);
	dup2(saved, 1);
	close(saved);
	close(devnull);
	i = (int)(r1.ru_maxrss - r0.ru_maxrss);
	verdict("no memory leak (100000 calls, every conversion)", i < 1024, "");
	printf("       max RSS grew %d KB\n", i);
}

static int	call_with_stdout(int fd)
{
	int	saved;
	int	r;

	fflush(stdout);
	saved = dup(1);
	if (fd >= 0)
		dup2(fd, 1);
	else
		close(1);
	r = ft_printf("hello %d world %s %c\n", 42, "abcdefghij", 'x');
	dup2(saved, 1);
	close(saved);
	return (r);
}

static void	test_write_errors(void)
{
	FILE	*f;

	struct rlimit old, lim;
	int p[2], r, fd;
	group_end();
	r = call_with_stdout(-1);
	verdict("stdout closed -> -1", r == -1, "");
	signal(SIGPIPE, SIG_IGN);
	if (pipe(p) == 0)
	{
		close(p[0]);
		r = call_with_stdout(p[1]);
		close(p[1]);
		verdict("broken pipe (EPIPE) -> -1", r == -1, "");
	}
	fd = open("/dev/full", O_WRONLY);
	r = call_with_stdout(fd);
	close(fd);
	verdict("/dev/full (ENOSPC) -> -1", r == -1, "");
	getrlimit(RLIMIT_FSIZE, &old);
	lim = old;
	lim.rlim_cur = 10;
	f = tmpfile();
	signal(SIGXFSZ, SIG_IGN);
	fflush(stdout);
	setrlimit(RLIMIT_FSIZE, &lim);
	r = call_with_stdout(fileno(f));
	setrlimit(RLIMIT_FSIZE, &old);
	fclose(f);
	verdict("write fails after 10 bytes (halfway) -> -1", r == -1, "");
}

/* ------------------------------------------------------------------ */
/*  5. undefined / unsupported: informational only                    */
/* ------------------------------------------------------------------ */
static void	test_undefined(void)
{
	group_end();
	g_info = 1;
	printf("\n== undefined / unsupported (mandatory only, informational) ==\n");
	printf("-- incomplete or unknown conversions --\n");
	CHECK("%");
	CHECK("ab%");
	CHECK("%%%");
	CHECK("%%%%%");
	CHECK("100%");
	CHECK("%\n");
	CHECK("% ");
	CHECK("%k");
	CHECK("a%yb");
	CHECK("%!");
	CHECK("%@ %d", 1);
	CHECK("%;%d", 1);
	CHECK("%%k%k%%");
	g_info = 0;
}

int	main(int argc, char **argv)
{
	g_verbose = (argc > 1 && !strcmp(argv[1], "-v"));
	g_heap = malloc(1);
	memset(g_long, 'a', 300000);
	section("conversions");
	test_char_str();
	test_numbers();
	test_pointers();
	section("combinations");
	test_combinations();
	section("fuzzer: random formats, random values");
	test_fuzz(30000);
	section("system behavior");
	test_leak();
	test_write_errors();
	test_undefined();
	printf("\n== result: %d passed, %d failed ==\n", g_pass, g_fail);
	printf("== undefined/unsupported: %d same as printf, %d differ"
			" (informational) ==\n",
			g_same,
			g_diff);
	free(g_heap);
	return (g_fail != 0);
}