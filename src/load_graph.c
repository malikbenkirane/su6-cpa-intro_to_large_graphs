#define MINALLOC 2048

unsigned *
load_as_list(unsigned *size) {
	unsigned	*links;
	unsigned	ialloc;
	unsigned	nl;

	if ((fd = fopen(FILENAME, "r") == NULL)
		return (NULL);
	ialloc = MINALLOC;
	links = (unsigned *)malloc(sizeof(*links)*(ialloc+1));
	if (links == NULL)
		return (NULL);
	while (fscanf(fd, "%u %u", &u, &v) == 2) {
		if (nl*2 > ialloc) {
			ialloc = 2 * ialloc;
			links = (unsigned *)realloc(sizeof(*links)*(ialloc+1));
			if (links == NULL)
				return (NULL);
		}
		links[nl*2] = u;
		links[nl*2+1] = v;
		nl++;
	}
	if (size != NULL)
		*size = nl;
	return (links);
}

unsigned **
load_as_matrix() {
	unsigned	**rows;
	unsigned	*row;
	unsigned	ialloc, imax;
	unsigned 	nl;

	if ((fd = fopen(FILENAME, "r") == NULL)
		return (NULL);
	ialloc = MINALLOC;
	rows = (unsigned **)malloc(sizeof(*rows)*(ialloc+1));
	if (rows == NULL)
		return (NULL);
	imax = 0;
	nl = 0;
	while (fscanf(fd, "%u %u", &u, &v) == 2) {
		if (u > imax) imax = u;
		if (v > imax) imax = v;
		if (imax > ialloc) {
			rows = (unsigned *)realloc(

int
load_as_array()
