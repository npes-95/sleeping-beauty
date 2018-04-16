#include <cstdio>
#include "../../lib/circular_buffer/circular_buffer.h"

int main(void)
{
	CircularBuffer<uint32_t> circle(10);
	printf("\n === CPP Circular buffer check ===\n");
	printf("Capacity: %zu\n", circle.size());
	uint32_t x = 1;
	printf("Put 1, val: %d\n", x);
	circle.put(x);
	x = circle.get();
	printf("Popped: %d\n", x);
	printf("Empty: %d\n", circle.empty());

	printf("Adding 9 values\n");
	for(uint32_t i = 0; i < circle.size(); i++)
	{
		circle.put(i);
	}

	printf("Full: %d\n", circle.full());

	printf("Reading back values: ");
	while(!circle.empty())
	{
		printf("%u ", circle.get());
	}
	printf("\n");

	printf("Adding 15 values\n");
	for(uint32_t i = 0; i < circle.size() + 5; i++)
	{
		circle.put(i);
	}

	printf("Full: %d\n", circle.full());

	printf("Reading back values: ");
	while(!circle.empty())
	{
		printf("%u ", circle.get());
	}
	printf("\n");

	printf("Empty: %d\n", circle.empty());
	printf("Full: %d\n", circle.full());

	return 0;
}
