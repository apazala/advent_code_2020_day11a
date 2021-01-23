#include <cstdio>
#include <cstring>

char mat1[100][100];
char mat2[100][100];

int main() {

	FILE *fin = fopen("input.txt", "r");
	if (!fin) {
		fprintf(stderr, "Can't open input file\n");
		return 1;
	}

	int nrows = 0;
	while (fscanf(fin, "%s", mat1[nrows]) == 1)
		nrows++;
	fclose(fin);

	int ncols = strlen(mat1[0]);

	int changed = 1;
	char (*matcurr)[100] = mat1;
	char(*matprev)[100] = mat2;
	char(*mataux)[100];

	while(changed) {
		changed = 0;
		mataux = matprev;
		matprev = matcurr;
		matcurr = mataux;
		for (int i = 0; i < nrows; i++) {
			for (int j = 0; j < ncols; j++) {

				if (matprev[i][j] == '.') {
					matcurr[i][j] = '.';
					continue;
				}

				int occupied = 0;

				for (int r = i - 1; r <= i + 1; r++) {
					if (r < 0 || r >= nrows) continue;
					for (int c = j - 1; c <= j + 1; c++) {
						if (c < 0 || c >= ncols) continue;
						if (r == i && c == j) continue;

						if (matprev[r][c] == '#')
							occupied++;
					}
				}

				if (matprev[i][j] == 'L') {
					if (occupied == 0) {
						matcurr[i][j] = '#';
						changed = 1;
					}
					else {
						matcurr[i][j] = 'L';
					}
				}
				else if (matprev[i][j] == '#') {
					if (occupied >= 4) {
						matcurr[i][j] = 'L';
						changed = 1;
					}
					else {
						matcurr[i][j] = '#';
					}
				}

			}
		}
	}

	int answer = 0;
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (matcurr[i][j] == '#')
				answer++;
		}
	}

	printf("%d\n", answer);

	return 0;

}