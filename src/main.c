#include <stdio.h>
#include <stdlib.h>

uint8_t RAM[256];
uint8_t ACC;
uint8_t PC;
uint8_t IR;
uint8_t FLAG;


void load_RAM( FILE* code );
void start_processor();
void print();

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
        printf("%X ", value);
        RAM[i] = value;
    }
    printf("\n");
}

void start_processor(){
    ACC = 0;
    IR = 0;
    PC = 0;
    FLAG = 0;
    uint8_t addr;
    while(PC < 255 ){
        print();
        IR = RAM[PC++];
        print();
        switch(IR){
            case 0x00:
                addr = RAM[PC++];
                ACC = RAM[addr];
                break;
            case 0x10:
                addr = RAM[PC++];
                RAM[addr] = ACC;
                break;
            case 0x40:
                addr = RAM[PC++];
                ACC += RAM[addr];
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


void print(){
    printf("ACC: %X, IR: %X, PC: %X, FLAG: %X\n", ACC, IR, PC, FLAG);
    for(int i = 0; i < 256; i++){
        if (i % 16 == 0 && i > 1){
            printf("\n");
        }
        printf("%02X ", RAM[i]);
    }
    printf("\n\n");
}