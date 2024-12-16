// complemented version HW + HD victim
static __attribute__((noinline)) int victim(void *varg)
{
	struct args_t *arg = varg;

	int curr_shift_first = arg->shift_first;
	int curr_shift_second = arg->shift_second;
	int curr_hamming_first = arg->hamming_first;
	int curr_hamming_second = arg->hamming_second;

	uint64_t first, second;

	first = binary_uint64(curr_hamming_first);
	second = binary_uint64(curr_hamming_second);

	first = first << curr_shift_first;
	second = second << curr_shift_second;

	asm volatile(
		"mov %0,%%r8\n\t"  // set register to operand
		"mov %0,%%r9\n\t"  // set register to operand
		"mov %0,%%r10\n\t" // set register to operand
		"mov %0,%%r11\n\t" // set register to operand
		"mov %1,%%r12\n\t" // set register to operand
		"mov %1,%%rbx\n\t" // set register to operand
		"mov %1,%%rcx\n\t" // set register to operand
		"mov %1,%%rdx\n\t" // set register to operand

    "not %1,%%r13\n\t" // set register to NOTed operand
    "not %1,%%r14\n\t" // set register to NOTed operand
    "mov $0,%%r15\n\t" // set register to zero

		".align 64\n\t"
		"loop:\n\t"

    // original op 1
		"or %0,%%r8\n\t"
		"or %0,%%r9\n\t"
		"or %0,%%r10\n\t"
		"or %0,%%r11\n\t"

    // clear
    "or %%r15,%%r15\n\t"

    // comp ops for 1
    "and %%r13,%%r13\n\t"
    "and %%r13,%%r13\n\t"
    "and %%r13,%%r13\n\t"
    "and %%r13,%%r13\n\t"

    // clear
    "or %%r15,%%r15\n\t"

    // original op 2
		"or %1,%%r12\n\t"
		"or %1,%%rbx\n\t"
		"or %1,%%rcx\n\t"
		"or %1,%%rdx\n\t"

    // clear
    "or %%r15,%%r15\n\t"

    // comp ops for 2
    "and %%r14,%%r14\n\t"
    "and %%r14,%%r14\n\t"
    "and %%r14,%%r14\n\t"
    "and %%r14,%%r14\n\t"

    // clear
    "or %%r15,%%r15\n\t"

		"jmp loop\n\t"
		:
		: "r"(first), "r"(second)
		: "rbx", "rcx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15");

	return 0;
}