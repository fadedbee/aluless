int main(void) {
	for (int i = 1000; i < 1050; i++) {
		*(int *)i = i;
	}
	return 0;
}
