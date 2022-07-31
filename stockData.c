#include "cub3d.h"

void    free_lst(t_list **lst)
{
    t_list  *tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->content);
        free((*lst));
        (*lst) = tmp;
    }
}

void    free_2d(char **p)
{
    int index;

    index = -1;
    while (p[++index])
        free(p[index]);
    free(p);
}

void    check_floor_ceilling(t_data **data, void *path)
{
    char    **spt;
    char    **t;

    spt = ft_split((char *)path, ' ');

    if (ft_strncmp(spt[0], "F", 1) == 0)
    {
        t = ft_split(spt[1], ',');
        (*data)->f.r = ft_atoi(t[0]);
        (*data)->f.g = ft_atoi(t[1]);
        (*data)->f.b = ft_atoi(t[2]);
        free_2d(t);
    }
    if (ft_strncmp(spt[0], "C", 1) == 0)
    {
        t = ft_split(spt[1], ',');
        (*data)->c.r = ft_atoi(t[0]);
        (*data)->c.g = ft_atoi(t[1]);
        (*data)->c.b = ft_atoi(t[2]);
        free_2d(t);
    }
    free_2d(spt);
}

void    check_texture_path(t_data **data, void *path)
{
    char    **spt;
    int     index;

    spt = ft_split((char *)path, ' ');
    // index = open("./texture/hhhhkkk.xpm", O_CREAT, 0777);
    // index = access(spt[1], X_OK);
    // if (index == -1)
        // cub_error("fd", "can't open ", spt[1]);
    if (ft_strcmp(spt[0], "NO") == 0)
        (*data)->no = ft_strdup(spt[1]);
    else if (ft_strcmp(spt[0], "SO") == 0)
        (*data)->so = ft_strdup(spt[1]);
    else if (ft_strcmp(spt[0], "WE") == 0)
        (*data)->we = ft_strdup(spt[1]);
    else if (ft_strcmp(spt[0], "EA") == 0)
        (*data)->ea = ft_strdup(spt[1]);
   free_2d(spt);
}

void    check_map(t_data **data, void *path, t_list  **t)
{
    char    *str;
    int     index;

    str = (char *)path;
    index = 0;
    while (str[index])
        index++;
    str = ft_strtrim(str, "\n");
    if (index > 1)
    {
        // ft_lstadd_back(t, ft_lstnew(ft_strdup(str)));
        printf("%s>+++[%s]+++>%d%s\n",COLOR_SUCCESS,str, index, COLOR_END);
    }
}

void    stock_map(t_list *t, t_data **data)
{
    int index;
    int jndex;
    int n;
    int zndex;
    char    *string;

    n = 0;
    index = ft_lstsize(t);
    (*data)->m = ft_calloc(index, sizeof(int));
    while (t)
    {
        jndex = -1;
        string = ft_strdup((char *)t->content);
        (*data)->m[n] = ft_calloc(ft_strlen(string), sizeof(int));
        while (string[++jndex])
        {
            // (*data)->m[n][jndex] = ft_atoi(&string[jndex]);
        }
        n++;
        free(string);
        t = t->next;
    }
    exit(0);
}

int stock_data(char *argv, t_data **data)
{
    char    *buffer;
    int     fd;
    t_list  *d;
    t_list  *tmp;
    t_list  *t;

    t = NULL;
    (*data)->map = (t_list *)malloc(sizeof(t_list));
    if (!(*data)->map)
        cub_error("malloc", "Can't allocate Data", NULL);
    fd = open(argv, O_RDONLY, 0777);
    if (fd == -1)
        cub_error("fd", "Can't open", argv);
    buffer = get_next_line(fd);
    d = NULL;
    while (buffer)
    {
        ft_lstadd_back(&d, ft_lstnew(ft_strdup(buffer)));
        free(buffer);
        buffer = get_next_line(fd);
    }
    free(buffer);
    tmp = d;
    while (tmp)
    {
        if (
            strncmp((char *)tmp->content, "NO", 2) == 0
            || strncmp((char *)tmp->content, "SO", 2) == 0
            || strncmp((char *)tmp->content, "WE", 2) == 0
            || strncmp((char *)tmp->content, "EA", 2) == 0
        )
            check_texture_path(data, tmp->content);
        else if (
            strncmp((char *)tmp->content, "F", 1) == 0
            || strncmp((char *)tmp->content, "C", 1) == 0
        )
            check_floor_ceilling(data, tmp->content);
        else
            check_map(data, tmp->content, &t);
        tmp= tmp->next;
    }
    stock_map(t, data);
    free_lst(&d);
    return (0);
}