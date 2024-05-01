
/* 
 * Designer:   Zuo Yiyang 1220008661 
*/

#include "minicpu.h"

/* ALU */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero){
	unsigned* extended_value;
	if(ALUControl == 0x0)
		*ALUresult = A+B; //add
	
	else if(ALUControl == 0x1)
		*ALUresult = A-B; //sub
	
	else if(ALUControl == 0x2)
		//we can use the mechanism of directly converting unsigned to signed number in C to implement the signed 'set on less than'
		*ALUresult = ((signed)A < (signed)B)?1:0;
	
	//set on less than(signed)
	else if(ALUControl == 0x3)
		*ALUresult = (A < B)?1:0; //set on less than(unsigned)
	
	else if(ALUControl == 0x4)
		*ALUresult = A & B; //AND
	
	else if(ALUControl == 0x5)
		*ALUresult = A | B; //OR
	
	else if(ALUControl == 0x6)
		*ALUresult = B << 16; // Shift B left by 16 bits
	
	else if(ALUControl == 0x7)
		*ALUresult = ~(A | B); //NOR

	if(*ALUresult == 0) Zero = 0; 
}

/* instruction fetch */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction){
	if(PC >= 0x4000 && PC <= 0xFFFF){
		if(PC % 4 == 0){
			*instruction = Mem[PC>>2];
			return 0;
		}
	}
	return 1;
}


/* instruction partition */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec){
	*op = instruction >> 26;
	/*The operation (instruction >> 26) shifts the bits of
	instruction 26 places to the right, thus obtaining the first 6 bits from the leftmost to right*/

	*r1 = (instruction >> 21) & 0x1F;
	*r2 = (instruction >> 16) & 0x1F;
	*r3 = (instruction >> 11) & 0x1F;
	/*Since 0x1F is 00011111, after AND operations, we can extract the first 5 bits from left to right*/

	*funct = instruction & 0x3F;
	*offset = instruction & 0xFFFF;
	*jsec = instruction & 0x3FFFFFF;
	/*Likewise, since we know that
	funct -> instruction[0-5](6 bits), indicating that 6 1's
	offset -> instruction[0-15](16 bits), indicating that 16 1's
	jsec -> instruction[0-25](26 bits), indicating that 26 1's*/
}



/* instruction decode */
int instruction_decode(unsigned op,struct_controls *controls){
	if(op == 0x0){//R-format
		controls->RegWrite = 1;
		controls->RegDst = 1;
		controls->ALUOp = 7;
		controls->ALUSrc = 0;
		controls->MemtoReg = 0;
		controls->MemRead = 2;
		controls->MemWrite = 0;
		controls->Branch = 0;
		controls->Jump = 0;
	}
		
	else if(op == 0x8){
		controls->RegWrite = 1;
		controls->RegDst = 0;
		controls->ALUOp = 0;
		controls->ALUSrc = 1;
		controls->MemtoReg = 0;
		controls->MemRead = 2;
		controls->MemWrite = 0;
		controls->Branch = 0;
		controls->Jump = 0;
	}
	//add immediate
		
	else if(op == 0x23){
		controls->RegWrite = 1;
		controls->RegDst = 0;
		controls->ALUOp = 0;
		controls->ALUSrc = 1;
		controls->MemtoReg = 1;
		controls->MemRead = 1;
		controls->MemWrite = 0;
		controls->Branch = 0;
		controls->Jump = 0;
	}
	//load word

	else if(op == 0x2B){
		controls->RegWrite = 0;
		controls->RegDst = 2;
		controls->ALUOp = 0;
		controls->ALUSrc = 1;
		controls->MemtoReg = 2;
		controls->MemRead = 2;
		controls->MemWrite = 1;
		controls->Branch = 0;
		controls->Jump = 0;
	}
	//store word

	else if(op == 0xF){
		controls->RegWrite = 1;
		controls->RegDst = 0;
		controls->ALUOp = 6;
		controls->ALUSrc = 1;
		controls->MemtoReg = 0;
		controls->MemRead = 0;
		controls->MemWrite = 0;
		controls->Branch = 0;
		controls->Jump = 0;
	}
	//load upper immediate

	else if(op == 0x4){
		controls->RegWrite = 0;
		controls->RegDst = 2;
		controls->ALUOp = 1;
		controls->ALUSrc = 0;
		controls->MemtoReg = 2;
		controls->MemRead = 0;
		controls->MemWrite = 0;
		controls->Branch = 1;
		controls->Jump = 0;
	}
	//branch on equal

	else if(op == 0xA){
		controls->RegWrite = 1;
		controls->RegDst = 0;
		controls->ALUOp = 2;
		controls->ALUSrc = 1;
		controls->MemtoReg = 0;
		controls->MemRead = 0;
		controls->MemWrite = 0;
		controls->Branch = 0;
		controls->Jump = 0;
	}
	//set less than immediate

	else if(op == 0xB){
		controls->RegWrite = 1;
		controls->RegDst = 0;
		controls->ALUOp = 3;
		controls->ALUSrc = 1;
		controls->MemtoReg = 0;
		controls->MemRead = 0;
		controls->MemWrite = 0;
		controls->Branch = 0;
		controls->Jump = 0;
	}
	//set less than immediate unsigned

	else if(op == 0x2){
		controls->RegWrite = 0;
		controls->RegDst = 2;
		controls->ALUOp = 0;
		controls->ALUSrc = 2;
		controls->MemtoReg = 2;
		controls->MemRead = 2;
		controls->Jump = 1;
		controls->MemWrite = 0;
		controls->RegWrite = 0;
		//To ensure that any data cannot be written into memory and register
		
	}
	//unconditional jump

	else return 1;	//invalid instruction or 'halt' condition occurs
	return 0;
}

/* Read Register */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2){
	*data1 = Reg[r1];
	*data2 = Reg[r2];
}


/* Sign Extend */
void sign_extend(unsigned offset,unsigned *extended_value){
	if(offset & 0x8000)
		*extended_value = offset | 0xFFFF0000;
	else *extended_value = offset & 0x0000FFFF;
}

/* ALU operations */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero){
	if(ALUSrc == 1) data2 = extended_value;
	switch(ALUOp){
		// R-type
		case 7:
			// funct = 0x20 = 32
			if(funct==0x20) ALU(data1,data2,0x0,ALUresult,Zero);	//add
			else if(funct == 0x22) ALU(data1, data2, 0x1, ALUresult, Zero); //sub
			else if(funct == 0x24) ALU(data1, data2, 0x4, ALUresult, Zero); //and
			else if(funct == 0x25) ALU(data1, data2, 0x5, ALUresult, Zero); //or
			else if(funct == 0x2A) ALU(data1, data2, 0x2, ALUresult, Zero); //set less than (signed)
			else if(funct == 0x2B) ALU(data1, data2, 0x3, ALUresult, Zero); //set less than (unsigned)
			else return 1;	//invalid funct
			break;
		case 6:
			ALU(data1, data2, ALUOp, ALUresult, Zero);
			break;
		case 5:
			ALU(data1, data2, ALUOp, ALUresult, Zero);
			break;
		case 4:
			ALU(data1, data2, ALUOp, ALUresult, Zero);
			break;
		case 3:
			ALU(data1, data2, ALUOp, ALUresult, Zero);
			break;
		case 2:
			ALU(data1, data2, ALUOp, ALUresult, Zero);
			break;
		case 1:
			ALU(data1, data2, ALUOp, ALUresult, Zero);
			break;
		case 0:
			ALU(data1, data2, ALUOp, ALUresult, Zero);
			break;
		default:
			return 1;		//invalid ALUop
	}
	return 0;
}

/* Read / Write Memory */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem){
	if(ALUresult >= 0x0000 && ALUresult <= 0xFFFF && (ALUresult >>2 <<2 == ALUresult)){
		if(MemRead==1)
			*memdata = Mem[ALUresult>>2];
		if(MemWrite == 1)
			Mem[ALUresult >> 2] = data2;
		return 0;
	}
	else if(MemRead != 1 && MemWrite != 1)
		return 0;

	return 1;
}

 
/* Write Register */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg){
	if(RegWrite == 1){
		if(MemtoReg == 1){
			if(RegDst == 0)
				Reg[r2] = memdata;
			else if(RegDst == 1)
				Reg[r3] = memdata;
		}
			
		else if(MemtoReg == 0){
			if(RegDst == 0)
				Reg[r2] = ALUresult;
			else if(RegDst == 1)
				Reg[r3] = ALUresult;
		}	
	}
}

/* PC update */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC){
	if(((*PC) >= 0x4000 && (*PC) <= 0xFFFF) && (*PC) >>2 << 2 == (*PC))
			*PC+=4;
	
	if((Branch == 1) && ((*PC) >= 0x4000 && (*PC) <= 0xFFFF) && (*PC) >>2 << 2 == (*PC)) 
		*PC = *PC + 4 + extended_value << 2;
	else if((Branch == 1 && Zero == 1) && ((*PC) >= 0x4000 && (*PC) <= 0xFFFF) && (*PC) >>2 << 2 == (*PC))
		*PC += extended_value << 2;

	if((Jump == '1') && ((*PC) >= 0x4000 && (*PC) <= 0xFFFF) && (*PC) >>2 << 2 == (*PC)) 
		*PC = (*PC) & 0xF0000000 | (jsec << 2);
}
