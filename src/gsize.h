#ifndef __GSIZE_H__
#define __GSIZE_H__

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
size_of_graph(gsize_t *gsize);

unsigned *
graph_distributions(gsize_t *gsize);

void
print_gsize_err(gsize_err_t err);

#endif
