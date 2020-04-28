#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 256

void encode_lli(unsigned long long int n, unsigned char buf[8]);
unsigned long long int decode_lli(unsigned char buf[8]);

float decode_float(unsigned char buf[4]);
void encode_float(float n, unsigned char buf[4]);



int main()
{
	FILE* f;
	f = fopen("f.txt", "wb"); 
	
	unsigned char buf[4] = {0};
	float die = 2.35f;
	
	encode_float(die, buf);	
	for(int i=0;i<4;i++)
	{
		printf("%i: %c(%i)\n", i, buf[i], buf[i]);
	}
	printf("float: %f\n", die);
	//fprintf(f, "%08c", &buf);
	//fputs(buf, f);
	fwrite(buf, sizeof(buf), 1, f);
	//printf("sizeof buf:%i\n", sizeof(buf));
	
	
	fclose(f);
	printf("~~~~~~reading~~~~~~\n");
	f = fopen("f.txt", "rb"); 
	unsigned char buf2[4] = {0};

	fread(buf2, sizeof(buf2), 1, f);
	for(int i=0;i<4;i++)
	{
		printf("%i: %c(%i)\n", i, buf2[i], buf2[i]);
	}	
	float sz = decode_float(buf2);
	printf("float: %f\n", sz);
	
	fclose(f);
	return 0;
}



void encode_lli(unsigned long long int n, unsigned char buf[8])
{
	for(int i=0;i<8;i++)
	{
		buf[7-i] = n%256;
		n /= 256;
	}
}

unsigned long long int decode_lli(unsigned char buf[8])
{
	unsigned long long int n = *(unsigned long long int*)(buf);
	unsigned long long int temp = 1;
	for(int i=0;i<8;i++)
	{
		//temp = (buf[7-i])*pow(256,(i+1));
		
		n += (buf[7-i])*temp;
		temp*=256;
		//printf("n:%lli, temp:%lli\n", n, temp);
	}
	return n;
}

float decode_float(unsigned char buf[4])
{
	float f1 = *(float*)(buf);
	return f1;	
}

void encode_float(float n, unsigned char bytes_temp[4])
{ 
	memcpy(bytes_temp, (unsigned char*) (&n), 4);
	return;
}

