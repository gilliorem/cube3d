void	print_color(t_color color_list[2])
{
	printf("%c\n", color_list[0].id);
	printf("%i,", color_list[0].rgb[0]);
	printf("%i,", color_list[0].rgb[1]);
	printf("%i\n", color_list[0].rgb[2]);
}
