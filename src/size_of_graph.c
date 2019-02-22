#include <stdio.h>
#include <stdlib.h>

#include "targets.h"
#define N_MIN 1024

typedef	enum		gsize_err_t {
	FILE_ERROR,
	INDEXING_ERROR,
	ALLOC_ERROR
}			gsize_err_t;

typedef	struct		gsize_t {
	unsigned	nl;
	unsigned	nv;
	unsigned	*degrees;
	gsize_err_t	err;
}			gsize_t;

int	size_of_graph(gsize_t *gsize) {

	unsigned	nl, nv;
	unsigned	u, v;
	unsigned	*degrees;
	unsigned	imax, nalloc;
	FILE		*fd;

	if ((fd = fopen(FILENAME, "r")) == NULL) {
		gsize->err = FILE_ERROR;
		return (-1);
	}
	nalloc = N_MIN;
	degrees = (unsigned *)malloc(sizeof(*degrees) * nalloc);
	if (degrees == NULL) {
		gsize->err = ALLOC_ERROR;
		return (-1);
	}
	for (int i = 0; i < nalloc; i++)
		degrees[i] = 0;
	nl = 0;
	nv = 0;
	imax = 0;
	while(fscanf(fd, "%u %u", &u, &v) == 2) {
		if (u > imax) imax = u;
		if (v > imax) imax = v;
		if (nalloc < imax + 1) {
			for (int i = nalloc; i <= imax; i++)
				degrees[i] = 0;
			nalloc = imax + 1;
			if ((degrees = realloc(degrees, nalloc)) == NULL) {
				gsize->err = ALLOC_ERROR;
				return (-1);
			}
		}
		if (degrees[u] == 0) nv++;
		if (degrees[v] == 0) nv++;
		degrees[u]++;
		degrees[v]++;
		nl++;
	}
	fclose(fd);
	gsize->nl = nl;
	gsize->nv = nv;
	gsize->degrees = degrees;
	return (0);
}

void	print_gsize_err(gsize_err_t err) {
	printf("error: ");
	switch (err) {
	case FILE_ERROR:
		printf("FILE_ERROR");
		break;
	case INDEXING_ERROR:
		printf("INDEXING_ERROR");
		break;
	case ALLOC_ERROR:
		printf("ALLOC_ERROR");
		break;
	}
	printf("\n");
}

int	main() {
	struct gsize_t gsize;
	
	if (size_of_graph(&gsize) == 0) {
		printf("nv: %d\nnl: %d\n", gsize.nv, gsize.nl);
		return(0);
	}
	print_gsize_err(gsize.err);
	return (-1);
}
