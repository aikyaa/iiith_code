void display(struct AccountInfo accarr[], int n) {
    int i;

    int numtmp;           // Member (int variable)
    enum Type typtmp;
    char *namtmp;       // Name (char variable)
    float baltmp;

    if(n == 0) {
        printf("No Accounts to display\n");
        return;
    }

    printf("%-10s\t","Account Number");
    printf("%-10s\t","Account Type");
    printf("%-20s\t","Name");
    printf("%-10s\n","Balance");

    printf("----------------------------------------------------------------\n");

    //Sort based on account numbers
    for(i=0;i<n-1;i++) {
        if(accarr[i].accnum > accarr[i+1].accnum) {
            numtmp = accarr[i].accnum;
            typtmp = accarr[i].acctype;
            namtmp = accarr[i].name;
            baltmp = accarr[i].balance;

            accarr[i].accnum = accarr[i+1].accnum;
            accarr[i].acctype = accarr[i+1].acctype;
            accarr[i].name = accarr[i+1].name;
            accarr[i].balance = accarr[i+1].balance;

            accarr[i+1].accnum = numtmp;
            accarr[i+1].acctype = typtmp;
            accarr[i+1].name = namtmp;
            accarr[i+1].balance = baltmp;
        }
    }

    for (i=0;i<n;i++) {
        printf("%-10d\t",accarr[i].accnum);
        printf("%-10s\t",acctypes[accarr[i].acctype]);
        printf("%-20s\t",accarr[i].name);
        printf("%8.2f\n",accarr[i].balance);
    }
    return;
}

void createAccount(struct AccountInfo accarr[], int n, char *accnam, enum Type acctyp, float amount) {
    int i;
    int mxaccnum,found;

    //Compute max account number, find if username & account type already exists
    mxaccnum=0;
    found=0;
    for(i=0;i<n;i++) {
        if(accarr[i].accnum > mxaccnum) {mxaccnum = accarr[i].accnum;}
        if(strcmp(accarr[i].name,accnam) == 0 && accarr[i].acctype == acctyp) {found = 1;}
    }

    if(found == 1) {
        printf("Invalid: user already exists!");
    }
    else {
        //accarr[n] = (struct)malloc(sizeof(struct AccountInfo));
        
        accarr[n].accnum = mxaccnum + 1;
        accarr[n].acctype = acctyp;
        accarr[n].name = accnam;
        accarr[n].balance = amount;
        n = n + 1;
    }

}
