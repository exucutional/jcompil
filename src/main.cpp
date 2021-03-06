#include <iostream>
#include <cassert>
#include "cpu/cpu_t.h"
#include "jcompil.hpp"

void testasm()
{
	asm(".intel_syntax noprefix\n\t"
        "add rax, byte [rsp - 1]\n\t"
        "mov rcx, byte [rsp]\n\t"
        "syscall\n\t"
        "call r12\n\t"
        "pop r10\n\t"
        "pop r11\n\t"
        "add r10, r11\n\t"
        "sub r10, r11\n\t"
        "add r8, r8\n\t"
        "add r8, r9\n\t"
        "add r9, r8\n\t"
        "push r10\n\t"
        "push r9\n\t"
        "push r8\n\t"
        "mul r8\n\t"
        "cmp r8, r8\n\t"
        "cmp r8, r9\n\t"
        "cmp r10, r11\n\t"
        "cmp rax, rax\n\t"
        "cmp rax, rcx\n\t"
        "cmp rcx, rax\n\t"
        "cmp rax, rcx\n\t"
        "pop [rax + 1]\n\t"
        "pop [rcx + 16]\n\t"
        "pop [rsp + 16]\n\t"
        "pop [rsp - 8]\n\t"
		".att_syntax noprefix\n\t"
	);
}

const size_t MEMORY_SIZE = 4096;
//old 31 sec
//new 2 sec
int main(int argc, char* argv[])
{
    clock_t exec_time = clock();
    Jcompil jcompil(MEMORY_SIZE);
    FILE *fasm = NULL;
    if (argc < 1)
        assert (0);
    fasm = fopen(argv[1], "r");
    assert(fasm);
    jcompil.assembl(fasm);
    jcompil.translate();
    jcompil.load();
    int temp = jcompil.run();
    exec_time = clock() - exec_time;
    printf("\ntime: %lg\n", (double) exec_time / CLOCKS_PER_SEC);
    //printf("\n%d\n", temp);
    fclose(fasm);
    //testasm();
	return EXIT_SUCCESS;
}