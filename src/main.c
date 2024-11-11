#include "core.h"
#include "stdio.h"
#include "types.h"
#include <string.h>
#include "disasm.h"

int load_bios(CPU *cpu, char * filename){
    FILE * bios_f = fopen(filename, "rb"); 
    if (bios_f == NULL) {
        printf("unable to open file\n"); 
        return -1;
    }
    MemorySector * biosSector = &cpu->memory.sectors[0];
    size_t s = fread(biosSector->sector_buffer, 1, biosSector->sector_size, bios_f);
    if (s < 0) return -1;     
    return 0;
}
int main(int argc, char ** argv){
    if (argc == 1) {
        printf("no filename argument provided\n");
        return -1;
    }
    CPU cpu;    
    init_cpu(&cpu);
    if (load_bios(&cpu, argv[1]) != 0){
        printf("Error: unable to load bios with filename: %s", argv[1]);
        return -1;
    }
    while (1){
        printf("PC: %x\n", *cpu.registers.PC);
        instruction_t encoded_instruction;
        char decoded_instruction[64];
        memset(decoded_instruction, 0, 64);
        memory_read_word(*cpu.registers.PC, &cpu.memory, &encoded_instruction);
        decode_arm_instruction(encoded_instruction, decoded_instruction);
        printf("Encoded Instruction: %08x, ASM: %s\n", encoded_instruction, decoded_instruction);
        getchar();
        execute_instruction(encoded_instruction, &cpu);

    }
}
