#include <stdio.h>
#include <stdlib.h>

#include "targets.h"
#define N_MIN 1024

typedef	enum			gsize_err_t {
	FILE_ERROR,
	ALLOC_ERROR
}				gsize_err_t;

typedef	struct			gsize_t {
	unsigned		nl;		// number of links
	unsigned		nv;		// number of vertices
	unsigned		*degrees;	// degrees indexed by vertex
	unsigned		dmax;		// maximal degree
	gsize_err_t		err;		// error
}				gsize_t;

int
size_of_graph(gsize_t *gsize) {
	unsigned		nl, nv;
	unsigned		u, v;
	unsigned		*degrees;
	unsigned 		dmax;
	unsigned		imax, ialloc;
	FILE			*fd;

	if ((fd = fopen(FILENAME, "r")) == NULL) {
		gsize->err = FILE_ERROR;
		return (-1);
	}
	ialloc = N_MIN;
	degrees = (unsigned *)malloc(sizeof(*degrees) * (ialloc + 1));
	if (degrees == NULL) {
		gsize->err = ALLOC_ERROR;
		return (-1);
	}
	for (unsigned i = 0; i < ialloc; i++)
		degrees[i] = 0;
	nl = 0;
	nv = 0;
	imax = 0;
	dmax = 0;
	while(fscanf(fd, "%u %u", &u, &v) == 2) {
		if (u > imax) imax = u;
		if (v > imax) imax = v;
		if (ialloc < imax + 1) {
			degrees = realloc(degrees, sizeof(*degrees) * (imax + 1));
			if (degrees == NULL) {
				gsize->err = ALLOC_ERROR;
				return (-1);
			}
			for (unsigned i = ialloc; i <= imax; i++)
				degrees[i] = 0;
			ialloc = imax + 1;
		}
		//printf("%u %u nalloc %u\n", u, v, ialloc);
		if (degrees[u]++ == 0) nv++;
		if (degrees[v]++ == 0) nv++;
		if (degrees[u] > dmax) dmax = degrees[u];
		if (degrees[v] > dmax) dmax = degrees[v];
		nl++;
	}
	fclose(fd);
	gsize->nl = nl;
	gsize->nv = nv;
	gsize->degrees = degrees;
	gsize->dmax = dmax;
	return (0);
}

unsigned *
graph_distributions(gsize_t *gsize) {
	unsigned		*dis;

	if (gsize->degrees == NULL)
		return (NULL);
	if ((dis = (unsigned *)malloc(sizeof(*dis) * (gsize->dmax+1))) == NULL)
		return (NULL);
	for (unsigned d = 0; d <= gsize->dmax; d++)
		dis[d] = 0;
	for (unsigned i = 0; i < gsize->nv; i++)
		dis[gsize->degrees[i]]++;
	return dis;
}
	
unsigned long long
degrees_product(gsize_t *gsize) {
	unsigned long long	q;
	unsigned		u, v;
	FILE			*fd;

	if ((fd = fopen(FILENAME, "r")) == NULL)
		return (0);
	q = 0;
	while(fscanf(fd, "%u %u", &u, &v) == 2) {
		q += gsize->degrees[u] * gsize->degrees[v];
	}
	return (q);
}
/** XXX :	compact the representation to reduce zeros
 *		by addinng one more level of indirection
 */

void
print_gsize_err(gsize_err_t err) {
	printf("error: ");
	switch (err) {
	case FILE_ERROR:
		printf("FILE_ERROR");
		break;
	case ALLOC_ERROR:
		printf("ALLOC_ERROR");
		break;
	}
	printf("\n");
}

#ifdef ESSENTIALS
void
print_gsize_essentials(gsize_t *gsize) {
	printf("nv: %u\nnl: %u\n", gsize->nv, gsize->nl);
	printf("q: %llu\n", degrees_product(gsize));
}
#endif

#ifdef DISTRIBUTIONS
void
print_degree_distribution(gsize_t *gsize) {
	unsigned		*dis;
	
	dis = graph_distributions(gsize);
	for (unsigned d = 0; d < gsize->dmax; d++)
		if (dis[d]) printf("%u %u\n", d, dis[d]);
}
#endif

int
main() {
	struct gsize_t		gsize;
	
	if (size_of_graph(&gsize) == 0) {
#ifdef ESSENTIALS
		print_gsize_essentials(&gsize);
#elif DISTRIBUTIONS
		print_degree_distribution(&gsize);
#endif
		free(gsize.degrees);
		return (0);
	}
	print_gsize_err(gsize.err);
	return (-1);
}
