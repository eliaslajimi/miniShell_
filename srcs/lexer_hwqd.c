#include "minishell.h"

static void dollar(t_hwqd *v, char *word)
{
	if (word[v->i + 1] == '?')
	{
		v->i += 2;
		v->status = (int*)getglobal(STATUS);
		v->str_status = ft_itoa(*(v->status));
		v->result = ft_strjoin(v->result, v->str_status);
	}
	else
	{
		v->i++;
		v->len = 0;
		while (word[v->i] && word[v->i] != '$' && word[v->i] != '\"' && word[v->i] != '\'')
		{
			v->len++;
			v->i++;
		}
		if (swap_dollar(word, v->i - v->len, v->len) != NULL)
		{
			v->result = ft_strjoin(v->result, swap_dollar(word, v->i - v->len, v->len));
		}
		else
		{
			v->result = ft_strjoin(v->result, "");
		}
	}
}

static void double_quote2(t_hwqd *v, char *word)
{
	if (word[v->i + 1] == '?')
	{
		v->i += 2;
		v->status = (int*)getglobal(STATUS);
		v->str_status = ft_itoa(*(v->status));
		v->result = ft_strjoin(v->result, v->str_status);
	}
	else
	{
		v->i++;
		v->len = 0;
		while (word[v->i] != '$' && word[v->i] != '\"' && word[v->i] != '\'')
		{
			v->len++;
			v->i++;
		}
		if (swap_dollar(word, v->i - v->len, v->len) != NULL)
		{
			v->result = ft_strjoin(v->result, swap_dollar(word, v->i - v->len, v->len));
		}
		else
			v->result = ft_strjoin(v->result, "");
	}
}

static void double_quote(t_hwqd *v, char *word)
{
    v->i++;
		while (word[v->i] && word[v->i] != '\"')
		{
		if (word[v->i] != '$')
			v->result = ft_strjoin_char(v->result, word[v->i++]);
		else if (word[v->i] == '$')
		    double_quote2(v, word);
        else if (word[v->i] == '\\')
        {
            if (word[v->i + 1] == '\'' || word[v->i + 1] == '\"')
            {
                v->i++;
                v->result = ft_strjoin_char(v->result, word[v->i++]);
            }
        }
	}
	v->i++;
}

static void single_quote(t_hwqd *v, char *word)
{
    v->i++;
	while (word[v->i] && word[v->i] != '\'')
		v->result = ft_strjoin_char(v->result, word[v->i++]);
	v->i++;
}

char		*handling_word_quotes_dollar(char *word)
{
	t_hwqd	*v;

	if (!(v = malloc(sizeof(t_hwqd))))
        return (NULL);
	v->i = 0;
	v->result = ft_strdup("");
	while (word[v->i])
	{
		if (word[v->i] == '\'')
			single_quote(v, word);
		else if (word[v->i] == '\"')
		    double_quote(v, word);
		else if (word[v->i] == '$')
		{
			dollar(v, word);
		}
			
        else if (word[v->i] == '\\')
        {
   //         if (word[v->i + 1] == '\'' || word[v->i + 1] == '\"')
     //       {
              v->i++;
                v->result = ft_strjoin_char(v->result, word[v->i++]);
  //          }
//			else
//				v->result = ft_strjoin_char(v->result, word[v->i++]);
        }
		else
			v->result = ft_strjoin_char(v->result, word[v->i++]);
	}
	return (v->result);
}
