
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>



/*
typedef struct s_list
{
	char *data;
}t_list;

void	print(t_list main)
{
	main.data = "karaca";
}

int main()
{
	t_list main;
	main.data = "ahmet";
	print(main);
	printf("%s\n", main.data);
}*/
/*
typedef struct s_list
{
	char *data;
}t_list;

typedef struct s_list_2
{
	t_list *env;
}t_list_2;

void	print(t_list env)
{
	env.data = "karaca";
}

int main()
{
	t_list_2 *main;
	main = (t_list_2 *)malloc(sizeof(t_list_2));
	main->env = (t_list *)malloc(sizeof(t_list));
	main->env->data = "ahmet";
	print((*main->env));
	printf("%s\n", main->env->data);
}*/


typedef struct s_list
{
	char *data;
	struct s_list *next;
}t_list;

typedef struct s_list_2
{
	t_list env;
}t_list_2;

void	print(t_list_2 main)
{
	main.env.data = "karaca";
}

int main()
{
	t_list_2 *main;
	main = (t_list_2 *)malloc(sizeof(t_list_2));
	main->env.data = "ahmet";
	print((*main));
	printf("%s\n", main->env.data);
}