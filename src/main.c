#include <stdio.h>
#include <stdlib.h>

uint8_t RAM[256];
uint8_t ACC;
uint8_t PC;
uint8_t IR;
uint8_t FLAG;


void load_RAM( FILE* code );
void start_processor();

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s <File Name>\n", argv[0]);
        return 1;   
    }
    FILE *code;
    

    code = fopen(argv[1], "r");

    if(code == NULL){
        printf("Error\n");
        return 1;
    }
    printf("You entered: %s, file opened.\n", argv[1]);
    
    load_RAM(code);
    fclose(code);
    start_processor();
    return 0;
}



void load_RAM( FILE* code ){
    char hex[3];
    for(int i = 0; fscanf(code, "%2s", hex) == 1; i++){ 
        int value = (int)strtol(hex, NULL, 16);
        printf("%X\n", value);
        RAM[i] = value;
    }
}

void start_processor(){
    ACC = 0;
    IR = 0;
    PC = 0;
    FLAG = 0;
    uint8_t addr;
    while(PC < 255 ){
        printf("ACC: %X, IR: %X, PC: %X, FLAG: %X\n", ACC, IR, PC, FLAG);
        IR = RAM[PC++];
        printf("ACC: %X, IR: %X, PC: %X, FLAG: %X\n", ACC, IR, PC, FLAG);
        switch(IR){
            case 0x00:
                addr = RAM[PC++];
                ACC = RAM[addr];
                break;
            case 0x90:
                addr = RAM[PC++];
                PC = addr;
                break;
            default:
                break;
        }
        getchar();
    }
    
}