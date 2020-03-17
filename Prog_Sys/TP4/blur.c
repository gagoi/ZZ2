#include "image.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"
#include "sys/mman.h"
#include <string.h>
#include "fcntl.h"

#define NUMBER_PID 10

void blurLayer(const char * fileName, struct image * input, size_t radius, size_t layer);
void blurRow(const char * fileName, struct image * input, size_t layer, size_t start, size_t number);

int main(int arg_count, char **args)
{
	if(arg_count == 5)
	{
		struct image input = make_image_from_file(args[1]);
		//struct image output = make_image(input.type, input.row_count, input.column_count, input.max_value);
		//blur_image(&input, &output, strtoul(args[3], 0, 0));

		const char * fileName = "out.img";
		if (args[4][0] == 'c')
		{
			int r_pid = fork();
			int g_pid;
			int b_pid;
			int c;
			if (r_pid == 0)
			{
				blurLayer(fileName, &input, strtoul(args[3], 0, 0), 0);
				return 0;
			} 
			else
			{
				g_pid = fork();
				if (g_pid == 0)
				{
					blurLayer(fileName, &input, strtoul(args[3], 0, 0), 1);
					return 0;
				}
				else
				{
					b_pid = fork();
					if (b_pid == 0)
					{
						blurLayer(fileName, &input, strtoul(args[3], 0, 0), 2);
						return 0;
					}
					else
					{
						waitpid(r_pid, &c, WCONTINUED);
						waitpid(g_pid, &c, WCONTINUED);
						waitpid(b_pid, &c, WCONTINUED);
						int fd = open(fileName, O_RDWR | O_CREAT, 0600);
						void * myout = mmap(0, get_image_byte_count(&input), PROT_WRITE, MAP_SHARED, fd, 0);
						ftruncate(fd, get_image_byte_count(&input));
						struct image out = make_image_from_memory(input.type, input.row_count, input.column_count, input.max_value, myout);
						write_image_to_file(&out, args[2]);
						munmap(myout, get_image_byte_count(&input));
						close (fd);
					}
				}
			}
		} else if (args[4][0] == 'r')
		{
			int * pids = (int *) malloc(sizeof(int) * NUMBER_PID);
			int c;
			size_t i;

			for (i = 0; i < NUMBER_PID; ++i)
			{
				pids[i] = fork();
				if (pids[i] != 0) continue;
				else
				{
					blurRow(fileName, &input, strtoul(args[3], 0, 0), i * (input.row_count / NUMBER_PID), input.row_count / NUMBER_PID);
					return 0;
				}
			}

			if (i * (input.row_count / NUMBER_PID) != input.row_count) blurRow(fileName, &input, strtoul(args[3], 0, 0),  i * (input.row_count / NUMBER_PID), input.row_count -  i * (input.row_count / NUMBER_PID));

			for (i = 0; i < NUMBER_PID; ++i)
			{
				waitpid(pids[i], &c, WCONTINUED);
			}
			int fd = open(fileName, O_RDWR | O_CREAT, 0600);
			void * myout = mmap(0, get_image_byte_count(&input), PROT_WRITE, MAP_SHARED, fd, 0);
			ftruncate(fd, get_image_byte_count(&input));
			struct image out = make_image_from_memory(input.type, input.row_count, input.column_count, input.max_value, myout);
			write_image_to_file(&out, args[2]);
			munmap(myout, get_image_byte_count(&input));
			close (fd);
			free(pids);
		}
	}
	else
	{
		fprintf(stderr, "Essaie plutôt : %s input.ppm output.ppm 10 {c/r}\n", args[0]);
		fprintf(stderr, "Avec c pour utiliser les couleurs et r pour les lignes\n");
	}
}

void blurLayer(const char * fileName, struct image * input, size_t radius, size_t layer)
{
	int fd = open(fileName, O_RDWR | O_CREAT, 0600);
	size_t size = get_image_byte_count(input);
	void * myout = mmap(0, size, PROT_WRITE, MAP_SHARED, fd, 0);
	ftruncate(fd, size);
	struct image out = make_image_from_memory(input->type, input->row_count, input->column_count, input->max_value, myout);
	blur_image_layer(input, &out, radius, layer);
	
	munmap(myout, size);
	close(fd);
}

void blurRow(const char * fileName, struct image * input, size_t radius, size_t start, size_t number)
{
	int fd = open(fileName, O_RDWR | O_CREAT, 0600);
	size_t i;
	size_t size = get_image_byte_count(input);
	void * myout = mmap(0, size, PROT_WRITE, MAP_SHARED, fd, 0);
	ftruncate(fd, size);
	struct image out = make_image_from_memory(input->type, input->row_count, input->column_count, input->max_value, myout);
	//blur_image_layer(input, &out, radius, layer);
	for (i = 0; i < number; ++i)
		blur_image_row(input, &out, radius, start + i);
	munmap(myout, size);
	close(fd);
}