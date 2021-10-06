#include <gtest/gtest.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern "C"
{
	#include "get_next_line.h"
}

// void put_string(void *str)
// {
// 	printf("%s\n", (char *)str);
// }

// void leaky_function(void)
// {
// 	char* sub_proc_leak  = (char*)malloc(1000);
// 	(void)sub_proc_leak;
// }


/* *******
 * my_functions
 *********/


TEST(flat_lst_to_str, single)
{
	t_list *lst = ft_lstnew(strdup("hoge"));
	EXPECT_STREQ("hoge", (char *)lst->content);

	flat_lst_to_str(lst);

	EXPECT_STREQ("hoge", (char *)lst->content);
	ft_lstdelone(lst, free);
}

TEST(flat_lst_to_str, two)
{
	t_list *lst = ft_lstnew(strdup("hoge"));
	ft_lstadd_back(&lst, ft_lstnew(strdup(",fuga")));
	EXPECT_STREQ("hoge", (char *)lst->content);

	flat_lst_to_str(lst);

	EXPECT_STREQ("hoge,fuga", (char *)lst->content);
	ft_lstdelone(lst, free);
}

TEST(flat_lst_to_str, multi)
{
	t_list *lst = ft_lstnew(strdup("123"));
	ft_lstadd_back(&lst, ft_lstnew(strdup("abc")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("ABC")));
	EXPECT_STREQ("123", (char *)lst->content);

	flat_lst_to_str(lst);

	EXPECT_STREQ("123abcABC", (char *)lst->content);
	ft_lstdelone(lst, free);
}

TEST(flat_lst_to_str, multi_new_lines)
{
	t_list *lst = ft_lstnew(strdup("123"));
	ft_lstadd_back(&lst, ft_lstnew(strdup("\n")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("\n\n\n")));
	EXPECT_STREQ("123", (char *)lst->content);

	flat_lst_to_str(lst);

	EXPECT_STREQ("123\n\n\n\n", (char *)lst->content);
	ft_lstdelone(lst, free);
}

TEST(flat_lst_to_str, one_line)
{
	t_list *lst = ft_lstnew(strdup("abc\n"));
	ft_lstadd_back(&lst, ft_lstnew(strdup("xyz\n")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("ABC")));
	EXPECT_STREQ("abc\n", (char *)lst->content);

	flat_lst_to_str(lst);

	EXPECT_STREQ("abc\nxyz\nABC", (char *)lst->content);
	ft_lstdelone(lst, free);
}

TEST(flat_lst_to_str, many_next_line)
{
	t_list *lst = ft_lstnew(strdup("abc\n"));
	ft_lstadd_back(&lst, ft_lstnew(strdup("\n")));
	ft_lstadd_back(&lst, ft_lstnew(strdup("\n")));
	EXPECT_STREQ("abc\n", (char *)lst->content);

	flat_lst_to_str(lst);

	EXPECT_STREQ("abc\n\n\n", (char *)lst->content);
	ft_lstdelone(lst, free);
}

TEST(get_line_from_memo, nl)
{
	t_list *memo = ft_lstnew(strdup("\n"));
	char *s;
	s = get_line_from_memo(memo);
	EXPECT_STREQ(s, "");
	free(s);

	s = get_line_from_memo(memo);
	EXPECT_STREQ(s, NULL);
	free(s);

	ft_lstdelone(memo, free);
}

TEST(get_line_from_memo, normal)
{
	t_list *memo = ft_lstnew(strdup("abc\nxyz\nABC"));
	char *s;
	s = get_line_from_memo(memo);
	EXPECT_STREQ(s, "abc");
	free(s);
	s = get_line_from_memo(memo);
	EXPECT_STREQ(s, "xyz");
	free(s);
	s = get_line_from_memo(memo);
	EXPECT_STREQ(s, "ABC");
	free(s);

	printf("hoge\n");
	s = get_line_from_memo(memo);
	EXPECT_STREQ(s, NULL);
	free(s);

	s = get_line_from_memo(memo);
	EXPECT_STREQ(s, NULL);
	free(s);

	ft_lstdelone(memo, free);
}

/* *******
 * gnl
 *********/

// TEST(get_next_line, empty)
// {
// 	int fd = open("test/empty.txt", O_RDONLY);
// 	char *s;
// 	s = get_next_line(1000);
// 	EXPECT_STREQ(s, NULL);
// 	s = get_next_line(-1);
// 	EXPECT_STREQ(s, NULL);
// 	close(fd);
// 	s = get_next_line(fd);
// 	EXPECT_STREQ(s, NULL);
// }

// TEST(get_next_line, one_line)
// {
// 	int fd = open("test/only_1_line.txt", O_RDONLY);
// 	const char res[] = "abcdef";
// 	char *t;

// 	printf("%d\n", fd);
// 	t = get_next_line(fd);
// 	EXPECT_STREQ(res, t);
// 	free(t);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	close(fd);
// }

// TEST(get_next_line, copy)
// {
// 	int fd = open("test/only_1_line.txt", O_RDONLY);
// 	const char res[] = "abcdef";
// 	char *t;

// 	t = get_next_line(fd);
// 	EXPECT_STREQ(res, t);
// 	free(t);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	close(fd);
// }

// TEST(get_next_line, no_new_line)
// {
// 	int fd = open("test/no_new_line", O_RDONLY);
// 	const char res[] = "abcdef";
// 	char *t;

// 	t = get_next_line(fd);
// 	EXPECT_STREQ(res, t);
// 	free(t);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	close(fd);
// }

// TEST(get_next_line, normal)
// {
// 	int fd = open("test/sample01.txt", O_RDONLY);
// 	const char res[] = "abcdef";
// 	char *t;
// 	printf("%d\n", fd);

// 	for (size_t i = 0; i <= strlen(res); i++)
// 	{
// 		char *s = strndup(&res[i], 1);
// 		t = get_next_line(fd); // 		EXPECT_STREQ(s, t);
// 		free(s);
// 		free(t);
// 	}
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	close(fd);
// }

// TEST(get_next_line, too_long)
// {
// 	int fd = open("test/too_long", O_RDONLY);
// 	char *t;

// 	t = get_next_line(fd);
// 	printf("%s\n", t);
// 	EXPECT_EQ(206, strlen(t));
// 	free(t);

// 	// EXPECT_STREQ(t, NULL);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	close(fd);
// }



// TEST(get_next_line, 10_delemeter)
// {
// 	int fd = open("test/sample10.txt", O_RDONLY);
// 	char *t;

// 	t = get_next_line(fd);
// 	EXPECT_STREQ("987654321", t);
// 	free(t);

// 	t = get_next_line(fd);
// 	EXPECT_STREQ("9876543210", t);
// 	free(t);

// 	t = get_next_line(fd);
// 	EXPECT_STREQ(t, "");
// 	free(t);

// 	t = get_next_line(fd);
// 	EXPECT_STREQ(t, "");
// 	free(t);

// 	close(fd);
// }

// TEST(get_next_line, some_lines)
// {
// 	int fd = open("test/some_lines.txt", O_RDONLY);
// 	char *t;

// 	t = get_next_line(fd);
// 	EXPECT_STREQ("abcdef", t);
// 	free(t);

// 	t = get_next_line(fd);
// 	EXPECT_STREQ("ABCDEF", t);
// 	free(t);

// 	t = get_next_line(fd);
// 	EXPECT_STREQ("1234567890", t);
// 	free(t);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	// t = get_next_line(fd);
// 	// EXPECT_STREQ(t, NULL);
// 	close(fd);
// }


// TEST(get_next_line, new_line_only)
// {
// 	int fd = open("test/new_line_only.txt", O_RDONLY);
// 	char *t;

// 	while ((t = get_next_line(fd)) != NULL)
// 	{
// 		EXPECT_STREQ(t, "");
// 		free(t);
// 	}

// 	close(fd);
// }

TEST(get_next_line, blank)
{
	int fd = open("test/nl", O_RDONLY);
	char *t;

	t = get_next_line(fd);
	EXPECT_STREQ(t, "");
	free(t);

	t = get_next_line(fd);
	EXPECT_STREQ(t, NULL);
	free(t);

	close(fd);
}
