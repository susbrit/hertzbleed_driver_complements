// complemented version of HW victim
static __attribute__((noinline)) int victim(void *varg)
{
	struct args_t *arg = varg;

	int shift_first = arg->shift_first;
	int shift_second = arg->shift_second;
	int hamming_first = arg->hamming_first;
	int hamming_second = arg->hamming_second;

	uint64_t first, second;

	if (hamming_first < 100) {
		first = binary_uint64(hamming_first);
		second = binary_uint64(hamming_second);

		// Shift operand with given shift
		if (shift_first >= 0) {
			first = (first << shift_first);
		} else {
			first = (first << (-shift_first));
			first = ~first;
		}

		// Shift operand with given shift
		if (shift_second >= 0) {
			second = (second << shift_second);
		} else {
			second = (second << (-shift_second));
			second = ~second;
		}

	} else {
		hamming_first = hamming_first - 100; // selector for independence checking experiment
		// hamming_first = 0: first = second = 0x0000000000000000
		// hamming_first = 1: first = second = 0x00000000000000FF
		// hamming_first = 2: first = second = 0x000000000000FF00
		// hamming_first = 3: first = second = 0x000000000000FFFF
		// hamming_first = 4: first = second = 0x0000000000FF0000
		// hamming_first = 5: first = second = 0x0000000000FF00FF
		// hamming_first = 6: first = second = 0x0000000000FFFF00
		// hamming_first = 7: first = second = 0x0000000000FFFFFF
		first = dependency(hamming_first);
		second = first;
	}

	asm volatile(
		"mov %0,%%rbx\n\t" // set register to operand
		"mov %0,%%rcx\n\t" // set register to operand
		"mov %0,%%rdx\n\t" // set register to operand
		"mov %0,%%rsi\n\t" // set register to operand
		"mov %0,%%rdi\n\t" // set register to operand
		"mov %0,%%r8\n\t"  // set register to operand
		"mov %0,%%r9\n\t"  // set register to operand
		"mov %0,%%r10\n\t" // set register to operand
		"mov %0,%%r11\n\t" // set register to operand
		"mov %0,%%r12\n\t" // set register to operand

    // set reserved registers for complement
		"not %0,%%r13\n\t" // set register to inverse operand
		"not %1,%%r14\n\t" // set register to inverse operand

		".align 64\n\t"
		"loop:\n\t"

		"or %1,%%rbx\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rcx\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rdx\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rdx\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rsi\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rdi\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r8\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r9\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r10\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r11\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r12\n\t"
    "and %%r13,%%r14,%%r15\n\t"

    "or %1,%%rbx\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rcx\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rdx\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rdx\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rsi\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%rdi\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r8\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r9\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r10\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r11\n\t"
    "and %%r13,%%r14,%%r15\n\t"
		"or %1,%%r12\n\t"
    "and %%r13,%%r14,%%r15\n\t"

		"jmp loop\n\t"
		:
		: "r"(first), "r"(second)
		: "rbx", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15");

	return 0;
}