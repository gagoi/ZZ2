#include "image.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"

int main(int arg_count, char **args)
{
	if(arg_count == 4)
	{
		struct image input = make_image_from_file(args[1]);
		struct image output = make_image(input.type, input.row_count, input.column_count, input.max_value);
		//blur_image(&input, &output, strtoul(args[3], 0, 0));

		FILE * r_f = tmpfile();
		FILE * g_f = tmpfile();
		FILE * b_f = tmpfile();


		// struct image r_out = make_image(input.type, input.row_count, input.column_count, input.max_value);
		// struct image g_out = make_image(input.type, input.row_count, input.column_count, input.max_value);
		// struct image b_out = make_image(input.type, input.row_count, input.column_count, input.max_value);
		
		int r_pid = fork();
		int g_pid;
		int b_pid;
		int c;
		if (r_pid == 0)
		{
			struct image r = make_image(input.type, input.row_count, input.column_count, input.max_value);
			blur_image_layer(&input, &r, strtoul(args[3], 0, 0), 0);
			write_image_to_stream(&r, r_f);
			rewind(r_f);
		} 
		else
		{
			g_pid = fork();
			if (g_pid == 0)
			{
				struct image g = make_image(input.type, input.row_count, input.column_count, input.max_value);
				blur_image_layer(&input, &g, strtoul(args[3], 0, 0), 1);
				write_image_to_stream(&g, g_f);
				rewind(g_f);
			}
			else
			{
				b_pid = fork();
				if (b_pid == 0)
				{
					struct image b = make_image(input.type, input.row_count, input.column_count, input.max_value);
					blur_image_layer(&input, &b, strtoul(args[3], 0, 0), 2);
					write_image_to_stream(&b, b_f);
					rewind(b_f);
				}
				else
				{
					waitpid(r_pid, &c, WCONTINUED);
					waitpid(g_pid, &c, WCONTINUED);
					waitpid(b_pid, &c, WCONTINUED);

					struct image r_out = make_image_from_stream(r_f);
					struct image g_out = make_image_from_stream(g_f);
					struct image b_out = make_image_from_stream(b_f);

					copy_image_layer(&b_out, &output, 2);
					copy_image_layer(&g_out, &output, 1);
					copy_image_layer(&r_out, &output, 0);
					write_image_to_file(&output, args[2]);
				}
				
			}
			
		}
	}
	else
	{
		fprintf(stderr, "Essaie plutôt : %s input.ppm output.ppm 10\n", args[0]);
	}
}
