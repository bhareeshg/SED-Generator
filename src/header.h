#define NOD 3
#define MAX_SIZE 10000
#define MNOF 10

int nof=3;
int size=422;
long ind[MAX_SIZE][NOD];
double temp[MAX_SIZE];
long li[MAX_SIZE];
double data[MAX_SIZE][5];
char Tfilename[200];
char *Qfilename;

char QfilenameArray[MNOF][200];
char Ofilename[200];
char Sedfilename[200];
char Histfilename[200];

char dataString[MAX_SIZE][30];

struct nodeStruct{
long index;
struct nodeStruct *left;
struct nodeStruct *right;
};

double frequency[15];
double f0Mag[15];

int NOCString;
int *pci;
int *freqInd;
int pciArray[MNOF][15];
int freqIndArray[MNOF][15];
int nofreq[MNOF];
int NOCStringArray[MNOF];

char buffer[2000];
size_t len = 0;
char *line=NULL;

typedef struct nodeStruct node;
FILE *foutput;
FILE *fsed;
FILE *fhist;

