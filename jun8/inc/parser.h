/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 23:42:45 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 23:42:46 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "types.h"

enum e_state
{
	CONFIG,
	IN_MAP
};

enum e_line_type
{
	EMPTY,
	COLOR,
	TEXTURE,
	MAP,
	INVALID
};

typedef struct s_file
{
	int		fd;
	int		line_count;
	char	*name;
	char	*cur_line;
	char	**lines;
}	t_file;

typedef struct s_color
{
	char	id;
	int		rgb[3];
}	t_color;

typedef struct s_texture
{
	int		fd;
	char	id[3];
	char	*path;
}	t_texture;

typedef struct s_config
{
	int			has_floor;
	int			has_ceiling;
	int			has_north;
	int			has_south;
	int			has_east;
	int			has_west;
	int			count;
	int			color_count;
	int			text_count;
	int			map_start;
	int			map_height;
	t_color		floor;
	t_color		ceiling;
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
}	t_config;

typedef struct s_map_2d
{
	int		width;
	int		height;
	int		first_line;
	int		player_x;
	int		player_y;
	char	**matrix;
	char	player_dir;
}	t_map_2d;

typedef struct s_scene
{
	t_config	config;
	t_map		map;
}	t_scene;

/*Parser*/

int				check_color_line(char *color_line, char color_id);
int				check_color_value(char *color_value);
int				is_rgb_range(int value);
int				check_rgbs(char color_id, char *color_value);
int				check_color(char *cur_line, char color_id);

int				is_map_char(char c);
char			*identify_map_line(char *line);
int				check_map_line(char *map_line);
int				is_player_char(char c);
int				is_walkable_char(char c);

int				parser_error(char *msg);
int				parser_error_str(char *msg, char *value);
int				parser_error_char(char *msg, char value);
int				parser_error_count(char *msg, int n);

int				check_texture_line(char *line, char *id);
char			*identify_texture_line(char **lines, char *id);
char			*extract_texture_path(char *line);
t_texture		create_texture(char id[3], char *path);
t_texture		process_texture(t_file *file, char *id);

int				check_file_extension(char *filename, char extension[4]);
int				check_argv(char *argv[]);
int				try_open_file(char *file);
int				get_file_size(t_file *file);
int				get_file_lines(t_file *file);

void			free_color_lines(char *color_lines[]);
void			free_color_codes(int n, char *color_codes[]);
void			free_texture_lines(char *texture_lines[]);
void			free_texture_names(char *texture_names[]);
void			free_texture_list(t_texture texture_list[4]);

void			free_file_lines(char **lines);
void			free_map_data(t_map_2d *map_2d);
void			free_file_attributes(t_file *file);
void			free_data(void *data);
void			textures_clear(t_texture textures[4]);

char			*get_color_value(char *color_line, char color_id);
char			**get_rgbs(char *color_value);
int				get_rgb_component(char *color_value, int index);

int				get_red(char color_id, char *color_value);
int				get_green(char color_id, char *color_value);
int				get_blue(char color_id, char *color_value);
char			get_color_id(char *line);
void			store_color_attributes(char *cur_line, t_color *color, char id);

int				validate_map_size(t_map_2d *map_2d);
int				get_map_width(t_file *file, t_config *config);
void			init_map_matrix(t_map_2d *map_2d);
t_map_2d		*init_map_2d(t_file *file, t_config *config);
void			fill_map_matrix(t_map_2d *map_2d,
					t_config *config, t_file *file);

int				config_is_complete(t_config *config);
int				register_color_id(t_config *config, char color_id);
int				register_texture_id(t_config *config, char texture_id[3]);

t_file			*init_file(char *argv_one);
t_color			init_floor(void);
t_color			init_ceiling(void);
t_config		init_config(void);
void			init_map(t_map *map, t_map_2d *map_2d, t_config *config,
					t_texture textures[4]);

int				validate_player(t_map_2d *map_2d);
int				flood_fill_player_area(t_map_2d *map_2d, char *visited,
					int y, int x);
int				validate_map_enclosure(t_map_2d *map_2d);

t_texture		process_texture_line(char *line);
void			init_textures(t_texture texture_list[4], t_file *file);
int				check_textures_fds(t_texture texture_list[4]);
int				check_valid_fd(char *file_path);
int				check_texture_path(char *path);
int				check_textures_fds(t_texture texture_list[4]);

int				parse_scene(const char *path, t_scene *out);
void			free_scene(t_scene *scene);

char			*skip_leading_spaces(char *line);
char			*gnl_str(int fd);
void			trim_new_line(char *line);
int				get_line_len_no_newline(char *line);
int				rgb_to_hex(int rgb[3]);

int				parse_color(t_file *file, char *cur_line, t_config *config);
int				parse_config_line(t_file *file, t_config *config,
					char *cur_line, enum e_line_type line_type);
int				parse_lines(t_file *file, t_config *config);

#endif
