/* 
 * A program to test the bytewise addition algorithm used in Aluless.
 */

#include <stdio.h>
#include <stdint.h>

int main(void) {
	const uint32_t a = 255 << 24;
	const uint32_t b = 2 << 24;

	const uint8_t *pa = (uint8_t *)&a;
	const uint32_t a0 = pa[0];
	const uint32_t a1 = pa[1];
	const uint32_t a2 = pa[2];
	const uint32_t a3 = pa[3];
	const uint8_t *pb = (uint8_t *)&b;
	const uint32_t b0 = pb[0];
	const uint32_t b1 = pb[1];
	const uint32_t b2 = pb[2];
	const uint32_t b3 = pb[3];

	const uint8_t d0 = (a0 + b0) & 0xFF;
	const uint8_t t0 = (a0 + b0) >> 8;

	const uint8_t t1 = (t0 + a1) & 0xFF;
	const uint8_t t2 = (t0 + a1) >> 8;
	const uint8_t d1 = (t1 + b1) & 0xFF;
	const uint8_t t3 = (t1 + b1) >> 8;
	const uint8_t t4 = t2 | t3;

	const uint8_t t5 = (t4 + a2) & 0xFF;
	const uint8_t t6 = (t4 + a2) >> 8;
	const uint8_t d2 = (t5 + b2) & 0xFF;
	const uint8_t t7 = (t5 + b2) >> 8;
	const uint8_t t8 = t6 | t7;

	const uint8_t t9 = (t8 + a3) & 0xFF;
	const uint8_t d3 = (t9 + b3) & 0xFF;

	printf("d0 = %u, ", d0);
	printf("t0 = %u, ", t0);

	printf("t1 = %u, ", t1);
	printf("t2 = %u, ", t2);
	printf("d1 = %u, ", d1);
	printf("t3 = %u, ", t3);
	printf("t4 = %u, ", t4);

	printf("t5 = %u, ", t5);
	printf("t6 = %u, ", t6);
	printf("d2 = %u, ", d2);
	printf("t7 = %u, ", t7);
	printf("t8 = %u, ", t8);

	printf("t9 = %u, ", t9);
	printf("d3 = %u\n", d3);

	uint32_t d = 0;
	uint8_t *pd = (uint8_t *)&d;
	pd[0] = d0;
	pd[1] = d1;
	pd[2] = d2;
	pd[3] = d3;

	printf("%u + %u == %u, %u\n", a, b, d, a + b);

	return 0;
}
