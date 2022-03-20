HEADER			=	includes/minishell.h

NAME			=	minishell

MAIN			=	main.c

SRCS			=	srcs/ft_strcmp.c\
					srcs/ft_strnjoin.c\
					srcs/ft_free.c\
					srcs/ft_arrlen.c\
					srcs/ft_split_args.c\
					srcs/ft_getenv.c\
					srcs/ft_cmdpath.c\
					srcs/ft_execve_args.c\
					srcs/ft_token_lstnew.c\
					srcs/ft_token_lstlast.c\
					srcs/ft_token_lstadd_back.c\
					srcs/ft_token_lstclear.c\
					srcs/ft_token_lstsize.c\
					srcs/ft_init_vars.c\
					srcs/ft_handle_signals.c\
					srcs/ft_tokenization.c\
					srcs/ft_verify_syntax.c\
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
				make bonus -C $(LIBFT)

clean:
				$(RM) $(OBJS)
#				make clean -C Libft

fclean:			clean
				$(RM) $(NAME)
#				make fclean -C Libft

re:				fclean all

.PHONY:			all clean fclean re