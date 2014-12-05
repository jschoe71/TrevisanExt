#include <time.h>

#include "TrevisanExt.cpp"

#define TIMER_SAMPLE_CNT 100
#define SAMPLE_CNT 1

#define CPUCYCLE 3000000000.

void doTiming();
unsigned long long measure_extractor_per_cycle(unsigned long long dtMin);
unsigned int measure_extractor_per_clock(unsigned int dtMin);
unsigned long long calibrate();
unsigned int calibrate_per_clock();
unsigned long long HiResTime(void);

void main()
{
	clock_t start, finish;
	double duration;
	start = clock();

	FILE *fp, *fp2, *fp3;
	fp = fopen("X.txt","r");
	fp2 = fopen("T.txt","r");
	fp3 = fopen("RND.txt","w+");
	ArrayClass X(fp, X_LEN);
	ArrayClass T(fp2, T_LEN);
	ArrayClass RND;
	trevisan_extract(&X,&T,&RND);
	RND.fprint(fp3);
	
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("���� �ð� = %f\n",duration);

	//�ӵ� ����
//	doTiming();
	getchar();
}

void doTiming()
{
	unsigned long long calibration;
    unsigned long long measure_extractor_val;
	unsigned int calibration2;
	unsigned int measure_extractor_val2;
    double measur_sec;
    calibration = calibrate();

    measure_extractor_val = measure_extractor_per_cycle(calibration);
    printf("Cycles for gen %5d bits    : %I64d\n",OUT_LEN, measure_extractor_val);
	printf("bits/Cycles                  : %lf\n",(double)OUT_LEN/(double)measure_extractor_val);
	printf("Throuthput(bits/sec)by cycle : %lf\n\n",(double)OUT_LEN/(double)measure_extractor_val*CPUCYCLE);
	
	
	calibration2 = calibrate_per_clock();
	measure_extractor_val2 = measure_extractor_per_clock(calibration2);
    printf("Second for gen %5d bits    : %lf\n",OUT_LEN, (double)measure_extractor_val2/1000./SAMPLE_CNT);
	printf("Throuthput(bits/sec)by clock : %lf\n",OUT_LEN/((double)measure_extractor_val2/1000./SAMPLE_CNT));
    printf("\n");
}

unsigned long long measure_extractor_per_cycle(unsigned long long dtMin)
{
    unsigned long long tMin = 0xFFFFFFFFFFFFFFFF;         /* big number to start */
    unsigned long long t0,t1,i;
	unsigned long long count;
	FILE *fp, *fp2, *fp3;
	fp = fopen("X.txt","r");
	fp2 = fopen("T.txt","r");
	fp3 = fopen("RND.txt","w+");

	ArrayClass X(fp,X_LEN);
	ArrayClass T(fp2,T_LEN);
	ArrayClass RND;

    for (i=0;i < TIMER_SAMPLE_CNT;i++)  /* calibrate the overhead for measuring time */
        {
        t0 = HiResTime();
		trevisan_extract(&X,&T,&RND);
        t1 = HiResTime();
		
        if (tMin > t1-t0 - dtMin)       /* keep only the minimum time */
            tMin = t1-t0 - dtMin;
        }
    /* now tMin = # clocks required for running RoutineToBeTimed() */
    
    return tMin;
}

unsigned long long calibrate()
{
    unsigned long long dtMin = 0xFFFFFFFFFFFFFFFF;        /* big number to start */
    unsigned long long t0,t1,i;

    for (i=0;i < TIMER_SAMPLE_CNT;i++)  /* calibrate the overhead for measuring time */
        {
        t0 = HiResTime();
        t1 = HiResTime();
        if (dtMin > t1-t0)              /* keep only the minimum time */
            dtMin = t1-t0;
        }
	
    return dtMin;
}


/************** Timing routine (for performance measurements) ***********/
/* By Doug Whiting */
/* unfortunately, this is generally assembly code and not very portable */
#if defined(_M_IX86) || defined(__i386) || defined(_i386) || defined(__i386__) || defined(i386) || \
    defined(_X86_)   || defined(__x86_64__) || defined(_M_X64) || defined(__x86_64)
#define _Is_X86_    1
#endif

#if  defined(_Is_X86_) && (!defined(__STRICT_ANSI__)) && (defined(__GNUC__) || !defined(__STDC__)) && \
    (defined(__BORLANDC__) || defined(_MSC_VER) || defined(__MINGW_H) || defined(__GNUC__))
#define HI_RES_CLK_OK         1          /* it's ok to use RDTSC opcode */

#if defined(_MSC_VER) // && defined(_M_X64)
#include <intrin.h>
#pragma intrinsic(__rdtsc)         /* use MSVC rdtsc call where defined */
#endif

#endif

unsigned long long HiResTime(void)           /* return the current value of time stamp counter */
    {
#if defined(HI_RES_CLK_OK)
    unsigned long long x[2];
#if   defined(__BORLANDC__)
#define COMPILER_ID "BCC"
    __emit__(0x0F,0x31);           /* RDTSC instruction */
    _asm { mov x[0],eax };
#elif defined(_MSC_VER)
#define COMPILER_ID "MSC"
#if defined(_MSC_VER) // && defined(_M_X64)
    x[0] = (unsigned long long) __rdtsc();
#else
    _asm { _emit 0fh }; _asm { _emit 031h };
    _asm { mov x[0],eax };
#endif
#elif defined(__MINGW_H) || defined(__GNUC__)
#define COMPILER_ID "GCC"
    asm volatile("rdtsc" : "=a"(x[0]), "=d"(x[1]));
#else
#error  "HI_RES_CLK_OK -- but no assembler code for this platform (?)"
#endif
    return x[0];
#else
    /* avoid annoying MSVC 9.0 compiler warning #4720 in ANSI mode! */
#if (!defined(_MSC_VER)) || (!defined(__STDC__)) || (_MSC_VER < 1300)
    FatalError("No support for RDTSC on this CPU platform\n");
#endif
    return 0;
#endif /* defined(HI_RES_CLK_OK) */
    }



unsigned int measure_extractor_per_clock(unsigned int dtMin)
{
    unsigned int tMin = 0xFFFFFFFF;         /* big number to start */
    unsigned int t0,t1,i,j;
	unsigned int count;
	FILE *fp, *fp2, *fp3;
	fp = fopen("X.txt","r");
	fp2 = fopen("T.txt","r");
	fp3 = fopen("RND.txt","w+");

	ArrayClass X(fp,X_LEN);
	ArrayClass T(fp2,T_LEN);
	ArrayClass RND;

    for (i=0;i < TIMER_SAMPLE_CNT;i++)  /* calibrate the overhead for measuring time */
        {
        t0 = clock();
		for(j=0;j<SAMPLE_CNT;j++)
		{
			trevisan_extract(&X,&T,&RND);
		}
        t1 = clock();
        if (tMin > t1-t0 - dtMin)       /* keep only the minimum time */
            tMin = t1-t0 - dtMin;
        }
    /* now tMin = # clocks required for running RoutineToBeTimed() */
    
    return tMin;
}

unsigned int calibrate_per_clock()
{
    unsigned int dtMin = 0xFFFFFFFF;        /* big number to start */
    unsigned int t0,t1,i;
	int j;

    for (i=0;i < TIMER_SAMPLE_CNT;i++)  /* calibrate the overhead for measuring time */
        {
        t0 = clock();
		for(j=0;j<SAMPLE_CNT;)
		{
			j++;
		}
        t1 = clock();
        if (dtMin > t1-t0)              /* keep only the minimum time */
            dtMin = t1-t0;
        }
    return dtMin;
}