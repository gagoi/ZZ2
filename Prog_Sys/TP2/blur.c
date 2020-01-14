#include "image.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"
#include "pthread.h"
#include "stdio.h"
#include "time.h"

void * blur_layer(void * args);
void * blur_column(void * args);
void * blur_row(void * args);

void fullBlurRow(char ** args);
void fullBlurLayer(char ** args);
void fullBlurColumn(char ** args);

void * create_args(struct image * pin, struct image * pout, size_t * pblur, size_t * player);

int main(int arg_count, char **args)
{
	clock_t before, after, total;
	if(arg_count == 5)
	{
		printf("Blur using : %c\n", args[4][0]);
		before = clock();
		switch (args[4][0])
		{
			case 'l':
				fullBlurLayer(args);
			break;
			case 'r':
				fullBlurRow(args);
			break;
			case 'c':
				fullBlurColumn(args);
			break;
		}	
		after = clock();

		printf("Exec : %lu -> %f\n", after - before, ((float) after - (float) before) / CLOCKS_PER_SEC);
	}
	else
	{
		fprintf(stderr, "Essaie plutôt : %s input.ppm output.ppm 10\n", args[0]);
	}
}

void fullBlurLayer(char ** args)
{
	struct image input = make_image_from_file(args[1]);
	struct image output = make_image(input.type, input.row_count, input.column_count, input.max_value);
	size_t blur = strtoul(args[3], 0, 0);
	size_t l1 = 0, l2 = 1, l3 = 2;
		
	pthread_t p1, p2, p3;
	void ** arg1, ** arg2, **arg3;

	arg1 = create_args(&input, &output, &blur, &l1);
	arg2 = create_args(&input, &output, &blur, &l2);
	arg3 = create_args(&input, &output, &blur, &l3);

	pthread_create(&p1, 0, blur_layer, arg1);
	pthread_create(&p2, 0, blur_layer, arg2);
	pthread_create(&p3, 0, blur_layer, arg3);

	pthread_join(p1, 0);
	pthread_join(p2, 0);
	pthread_join(p3, 0);
}

void fullBlurRow(char ** args)
{
	struct image input = make_image_from_file(args[1]);
	struct image output = make_image(input.type, input.row_count, input.column_count, input.max_value);
	int i;
	size_t * rows = (size_t *) malloc(sizeof(size_t) * input.row_count);
	pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t) * input.row_count);
	void *** arg = (void ***) malloc(sizeof(void **) * input.row_count);
	size_t blur = strtoul(args[3], 0, 0);

	for (i = 0; i < input.row_count; ++i)
	{
		rows[i] = i;
		arg[i] = create_args(&input, &output, &blur, rows + i);
		pthread_create(threads + i, 0, blur_row, arg[i]);
	}

	for (i = 0; i < input.row_count; ++i)
	{
		pthread_join(threads[i], 0);
	}
	write_image_to_file(&output, args[2]);
}

void fullBlurColumn(char ** args)
{
	struct image input = make_image_from_file(args[1]);
	struct image output = make_image(input.type, input.row_count, input.column_count, input.max_value);
	int i;
	size_t * columns = (size_t *) malloc(sizeof(size_t) * input.row_count);
	pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t) * input.row_count);
	void *** arg = (void ***) malloc(sizeof(void **) * input.row_count);
	size_t blur = strtoul(args[3], 0, 0);

	for (i = 0; i < input.column_count; ++i)
	{
		columns[i] = i;
		arg[i] = create_args(&input, &output, &blur, columns + i);
		pthread_create(threads + i, 0, blur_column, arg[i]);
	}

	for (i = 0; i < input.column_count; ++i)
	{
		pthread_join(threads[i], 0);
	}
	write_image_to_file(&output, args[2]);
}

void * create_args(struct image * pin, struct image * pout, size_t * pblur, size_t * player)
{
	void ** tab = malloc(sizeof(void*) * 4);
	tab[0] = (void*) pin;
	tab[1] = (void*) pout;
	tab[2] = (void*) pblur;
	tab[3] = (void*) player;
	return tab;
}

void * blur_layer(void * args) 
{
	void ** arg = (void**) args;
	struct image * pin = ((struct image *) arg[0]);
	struct image * pout = ((struct image *) arg[1]);
	
	size_t * blur = ((size_t *) arg[2]);
	short * layer = ((short *) arg[3]);

	blur_image_layer(pin, pout, *blur, *layer);
}

void * blur_row(void * args)
{
	void ** arg = (void**) args;
	struct image * pin = ((struct image *) arg[0]);
	struct image * pout = ((struct image *) arg[1]);
	
	size_t * blur = ((size_t *) arg[2]);
	size_t * layer = ((size_t *) arg[3]);

	blur_image_row(pin, pout, *blur, *layer);
}

void * blur_column(void * args)
{
	void ** arg = (void**) args;
	struct image * pin = ((struct image *) arg[0]);
	struct image * pout = ((struct image *) arg[1]);
	
	size_t * blur = ((size_t *) arg[2]);
	size_t * layer = ((size_t *) arg[3]);

	blur_image_column(pin, pout, *blur, *layer);
}
