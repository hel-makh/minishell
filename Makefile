HEADER			=	includes/minishell.h

NAME			=	minishell

MAIN			=	main.c

SRCS			=	srcs/ft_strcmp.c\
					srcs/ft_strnjoin.c\
					srcs/ft_free.c\
					srcs/ft_arrlen.c\
					srcs/ft_add_str2arr.c\
					srcs/ft_lstnew.c\
					srcs/ft_lstlast.c\
					srcs/ft_lstadd_back.c\
					srcs/ft_lstclear.c\
					srcs/ft_lstsize.c\
					srcs/ft_cmd_lstnew.c\
					srcs/ft_cmd_lstlast.c\
					srcs/ft_cmd_lstadd_back.c\
					srcs/ft_cmd_lstclear.c\
					srcs/ft_cmd_lstsize.c\
					srcs/ft_init_vars.c\
					srcs/ft_handle_signals.c\
					srcs/ft_tokenization.c\
					srcs/ft_verify_syntax.c\
					srcs/ft_parse_cmds.c\
					srcs/ft_free_program.c

OBJS			=	$(SRCS:.c=.o)\
					$(MAIN:.c=.o)

LIBFT			=	./Libft

LIB				=	./Libft/libft.a

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

.c.o:
				# $(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(HEADER) $(LIB)
				$(CC) $(CFLAGS) $(MAIN) $(SRCS) $(LIB) -o $(NAME) -lreadline -L/goinfre/hel-makh/.brew/opt/readline/lib -I/goinfre/hel-makh/.brew/opt/readline/include

all:			$(NAME)
				./$(NAME)

$(LIB):
				make -C $(LIBFT)

clean:
				$(RM) $(OBJS)
				# make clean -C Libft

fclean:			clean
				$(RM) $(NAME)
				# make fclean -C Libft

re:				fclean all

.PHONY:			all clean fclean re