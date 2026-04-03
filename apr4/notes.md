## FIX Segfault
-> I need to store the lines into the file attribute as I use gnl: because I want `file->lines to contain the \n`
-> alloc mem for `**lines`
-> fill the each line as we go through our gnl

	-> Re run classify lines with file->lines

### Config
Instead of having bool for each config attribute,
I can have a pointer to each of the config object (color and texture)
	Init them as I do to 0
	As I go through the file, I will check whether the value is different from the init value.

*What makes more sense ?*
	Config has pointers to the objects (color and text)
	OR
	Config has *copy* to the objects (no pointers)
*My take*
It makes more sense to have pointers to the objects because I want color
and texture to be created *once*.
then config will just point to that address.

If I use actual copy I will use the initiate values.

