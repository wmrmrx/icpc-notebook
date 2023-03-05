// Clock
clock_t startTime = clock();
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
