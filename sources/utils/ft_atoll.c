#include "minishell.h"
#include <limits.h>

static size_t	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	add_safe(int a, int b, int *limits)
{
	if (a > INT_MAX - b)
		*limits = 1;
	return (a + b);
}

long long	ft_atoll(const char *nptr, int *limits)
{
	long long		sum;
	size_t			is_neg;
	size_t			i;

	i = 0;
	sum = 0;
	is_neg = 0;
	while (is_whitespace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_neg = 1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		sum = add_safe((sum * 10), (nptr[i] - '0'), limits);
		if (*limits)
			return (0);
		i++;
	}
	if (is_neg)
		return ((sum * -1) % 256);
	return (sum % 256);
}
