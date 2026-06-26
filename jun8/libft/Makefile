# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

# Project name
NAME    = libft.a

# Source files
SRCS    = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		  ft_isascii.c ft_isdigit.c ft_isprint.c \
		  ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		  ft_memset.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
		  ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
		  ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_memmove.c \
		  ft_strmapi.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		  ft_striteri.c ft_atoi_base.c ft_isint.c ft_isspace.c ft_atol.c

SRCS_BONUS 	= ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
			ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

# Object files (replace .c with .o)
OBJS    = $(SRCS:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

# Delete command
RM      = rm -f

# Default target
all: $(NAME)

# Create static library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

# Compile .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

# Remove object files and library
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

