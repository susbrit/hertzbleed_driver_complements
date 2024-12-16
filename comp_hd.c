// UNCOMPLEMENTED VERSION
static __attribute__((noinline)) int victim(void *varg)
{
        struct args_t *arg = varg;
        uint64_t my_uint64 = 0x0000FFFFFFFF0000;
        uint64_t count = (uint64_t)arg->selector;

        asm volatile(
                ".align 64\t\n"

                "loop:\n\t"

                "shlx %0, %1, %%rbx\n\t"
                "shlx %0, %1, %%rcx\n\t"
                "shrx %0, %1, %%rsi\n\t"
                "shrx %0, %1, %%rdi\n\t"
                "shlx %0, %1, %%r8\n\t"
                "shlx %0, %1, %%r9\n\t"
                "shrx %0, %1, %%r10\n\t"
                "shrx %0, %1, %%r11\n\t"
                "shlx %0, %1, %%r12\n\t"
                "shlx %0, %1, %%r13\n\t"

                "shrx %0, %1, %%rbx\n\t"
                "shrx %0, %1, %%rcx\n\t"
                "shlx %0, %1, %%rsi\n\t"
                "shlx %0, %1, %%rdi\n\t"
                "shrx %0, %1, %%r8\n\t"
                "shrx %0, %1, %%r9\n\t"
                "shlx %0, %1, %%r10\n\t"
                "shlx %0, %1, %%r11\n\t"
                "shrx %0, %1, %%r12\n\t"
                "shrx %0, %1, %%r13\n\t"

                "jmp loop\n\t"
                :
                : "r"(count), "r"(my_uint64)
                : "rbx", "rcx", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13");
        return 0;
}

// COMPLEMENTED VERSION
static __attribute__((noinline)) int victim(void *varg)
{
        struct args_t *arg = varg;
        uint64_t my_uint64 = 0x0000FFFFFFFF0000;
        uint64_t count = (uint64_t)arg->selector;

        asm volatile(
                ".align 64\t\n"
                "not %0, %%r14\n\t"

                "loop:\n\t"

                "shlx %0, %1, %%rbx\n\t"
                "shlx %0, %1, %%rcx\n\t"
                "shrx %0, %1, %%rsi\n\t"
                "shrx %0, %1, %%rdi\n\t"
                "shlx %0, %1, %%r8\n\t"
                "shlx %0, %1, %%r9\n\t"
                "shrx %0, %1, %%r10\n\t"
                "shrx %0, %1, %%r11\n\t"
                "shlx %0, %1, %%r12\n\t"
                "shlx %0, %1, %%r13\n\t"

                "shrx %%r14, %1, %%rbx\n\t"
                "shrx %%r14, %1, %%rcx\n\t"
                "shlx %%r14, %1, %%rsi\n\t"
                "shlx %%r14, %1, %%rdi\n\t"
                "shrx %%r14, %1, %%r8\n\t"
                "shrx %%r14, %1, %%r9\n\t"
                "shlx %%r14, %1, %%r10\n\t"
                "shlx %%r14, %1, %%r11\n\t"
                "shrx %%r14, %1, %%r12\n\t"
                "shrx %%r14, %1, %%r13\n\t"

                "shrx %0, %1, %%rbx\n\t"
                "shrx %0, %1, %%rcx\n\t"
                "shlx %0, %1, %%rsi\n\t"
                "shlx %0, %1, %%rdi\n\t"
                "shrx %0, %1, %%r8\n\t"
                "shrx %0, %1, %%r9\n\t"
                "shlx %0, %1, %%r10\n\t"
                "shlx %0, %1, %%r11\n\t"
                "shrx %0, %1, %%r12\n\t"
                "shrx %0, %1, %%r13\n\t"

                "shlx %%r14, %1, %%rbx\n\t"
                "shlx %%r14, %1, %%rcx\n\t"
                "shrx %%r14, %1, %%rsi\n\t"
                "shrx %%r14, %1, %%rdi\n\t"
                "shlx %%r14, %1, %%r8\n\t"
                "shlx %%r14, %1, %%r9\n\t"
                "shrx %%r14, %1, %%r10\n\t"
                "shrx %%r14, %1, %%r11\n\t"
                "shlx %%r14, %1, %%r12\n\t"
                "shlx %%r14, %1, %%r13\n\t"

                "jmp loop\n\t"
                :
                : "r"(count), "r"(my_uint64)
                : "rbx", "rcx", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14");
        return 0;
}