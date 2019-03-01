#include <stdio.h>
#include <stdlib.h>
#include "targets.h"
#define MINALLOC 2048

#ifdef PPTI
#include "memtest.h"
#endif

#ifdef LOADLIST
unsigned *
load_as_list(unsigned *size) {
	unsigned	*links;
	unsigned	ialloc;
	unsigned	nl;
	unsigned	u, v;
	FILE		*fd;

	if ((fd = fopen(FILENAME, "r")) == NULL)
		return (NULL);
	ialloc = MINALLOC;
	links = (unsigned *)malloc(sizeof(*links)*(ialloc+1));
	if (links == NULL)
		return (NULL);
	nl = 0;
	while (fscanf(fd, "%u %u", &u, &v) == 2) {
		if (nl*2 > ialloc) {
			ialloc = 2 * ialloc;
			links = (unsigned *)realloc(links, sizeof(*links)*(ialloc+1));
			if (links == NULL)
				return (NULL);
		}
		links[nl*2] = u;
		links[nl*2+1] = v;
		nl++;
	}
	if (size != NULL)
		*size = nl;
	fclose(fd);
	return (links);
}
#endif

#ifdef LOADMATRIX
unsigned **
load_as_matrix(unsigned *size) {
	unsigned	**rows;
	unsigned	ialloc, imax;
	unsigned 	nl;
	unsigned 	u, v;
	FILE		*fd;

	if ((fd = fopen(FILENAME, "r")) == NULL)
		return (NULL);
	ialloc = MINALLOC;
	rows = (unsigned **)malloc(sizeof(*rows)*(ialloc+1));
	if (rows == NULL)
		return (NULL);
	for (unsigned i = 0; i <= ialloc; i++) {
		rows[i] = (unsigned *)malloc(sizeof(**rows)*(ialloc+1));
		if (rows[i] == NULL)
			return NULL;
		for (unsigned j = 0; j <= ialloc; j++)
			rows[i][j] = 0;
	}
	imax = 0;
	nl = 0;
	while (fscanf(fd, "%u %u", &u, &v) == 2) {
		if (u > imax) imax = u;
		if (v > imax) imax = v;
		if (imax > ialloc) {
			rows = (unsigned **)realloc(rows, sizeof(*rows)*(imax+1));
			if (rows == NULL)
				return NULL;
			for (unsigned i = 0; i <= ialloc; i++) {
				rows[i] = (unsigned *)realloc(rows[i], sizeof(**rows)*(imax+1));
				if (rows[i] == NULL)
					return NULL;
				for (unsigned j = ialloc + 1; j <= imax; j++)
					rows[i][j] = 0;
			}
			for (unsigned i = ialloc+1; i <= imax; i++) {
				rows[i] = (unsigned *)malloc(sizeof(**rows)*(imax+1));
				if (rows[i] == NULL)
					return NULL;
				for (unsigned j = 0; j <= imax; j++)
					rows[i][j] = 0;
			}
			ialloc = imax;
		}
		rows[u][v] = 1;
		rows[v][u] = 1;
	}
	if (size != NULL)
		*size = imax + 1;
	fclose(fd);
	return rows;
}
#endif

typedef struct		glist_t
{
	unsigned	nl;
	unsigned	nv;
	unsigned	dmax;
	unsigned	umax;
	unsigned	*cd;
	unsigned	*adj;
}			glist_t;

int
load_as_glist(glist_t *g)
{
	unsigned	u, v;
	unsigned	nl, nv;
	unsigned	*cd, *degrees, *adj;
	unsigned	*marks;
	unsigned	ialloc, imax, dmax;
	FILE		*fd;

	if ((fd = fopen(FILENAME, "r")) == NULL)
		return (1);
	ialloc = MINALLOC;
	degrees = (unsigned *)malloc(sizeof(*degrees)*(ialloc+1));
	if (degrees == NULL)
		return (1);
	for (unsigned i = 0; i <= ialloc; i++)
		degrees[i] = 0;
	nl = 0;
	nv = 0;
	imax = 0;
	dmax = 0;
	while (fscanf(fd, "%u %u", &u, &v) == 2) { // O(m)
		if (u > imax) imax = u;
		if (v > imax) imax = v;
		if (imax > ialloc) {
			degrees = (unsigned *)realloc(degrees, sizeof(*degrees)*(imax+1));
			if (degrees == NULL)
				return (1);
			for (unsigned i = ialloc + 1; i <= imax; i++)
				degrees[i] = 0;
			ialloc = imax;
		}
		if (degrees[u]++ == 0) nv++;
		if (degrees[v]++ == 0) nv++;
		if (degrees[u] > dmax) dmax = degrees[u];
		if (degrees[v] > dmax) dmax = degrees[v];
		nl++;
	}
	adj = (unsigned *)malloc(sizeof(*adj)*nv);
	cd = (unsigned *)malloc(sizeof(*cd)*(dmax+1));
	marks = (unsigned *)malloc(sizeof(*marks)*(dmax+1));
	for (unsigned d = 0; d <= dmax; d++) { // O(dmax)
		cd[d] = 0;
		marks[d] = 0;
	}
	for (unsigned i = 0; i <= ialloc; i++) // O(n)
		/**
		 * nb: cd[0] is unused because
		 * otherwise the node is not there
		 */
		if (degrees[i] > 0)
			cd[degrees[i]]++;
	for (unsigned d = 0; d < dmax; d++) // O(dmax)
		cd[d+1] += cd[d];
	for (unsigned i = 0; i <= ialloc; i++)
		if (degrees[i] > 0)
			adj[cd[degrees[i]-1]+marks[degrees[i]]++] = i;
	fclose(fd);
	g->nl = nl;
	g->nv = nv;
	g->cd = cd;
	g->adj = adj;
	g->umax = ialloc;
	g->dmax = dmax;
	free(marks);
	free(degrees);
	return (0);
}

#ifdef PRINT
#ifdef LOADMATRIX
void
print_matrix(unsigned size, unsigned **rows) {
	for (unsigned i = 0; i < size; i++) {
		for (unsigned j = 0; j < size; j++)
			printf("%u", rows[i][j]);
		printf("\n");
	}
}
#endif
#endif

#ifdef PRINT
#ifdef LOADLIST
void
print_links(unsigned size, unsigned *links) {
	for (unsigned i = 0; i < size; i++)
		printf("%u %u\n", links[2*i], links[2*i+1]);
}
#endif
#endif

int
main() {
#ifdef LOADMATRIX
#ifdef EMAIL
	unsigned 	size;
	unsigned	**rows;

	rows = load_as_matrix(&size);
	if (rows == NULL) return (-1);
	printf("loaded matrix (%ux%u)\n", size, size);
#ifdef PRINT
	print_matrix(size, rows);
#endif
#endif
#elif LOADLIST
	unsigned 	size;
	unsigned	*links;

	links = load_as_list(&size);
	if (links == NULL) return (-1);
	printf("loaded links (m=%u)\n", size);
#ifdef PRINT
	print_links(size, links);
#endif
#elif LOADADJ
	glist_t		g;

	load_as_glist(&g);
#ifdef PRINT
	for (unsigned d = 1; d <= g.dmax; d++) {
		printf("%u:", d);
		for (unsigned ui = g.cd[d-1]; ui < g.cd[d]; ui++)
			printf(" %u", g.adj[ui]);
		printf("\n");
	}
#endif
	printf("loaded adj (nl=%u, nv=%u)\n", g.nl, g.nv);
#endif
#ifdef PPTI
	printf("memory used: %d KB", get_memory_use());
#endif
#ifdef LOADMATRIX
	for (unsigned i = 0; i < size; i++)
		free(rows[i]);
	free(rows);
#elif LOADLIST
	free(links);
#elif LOADADJ
	free(g.cd);
	free(g.adj);
#endif
	return 0;
}
