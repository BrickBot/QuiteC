#include <qc.h>

void prints(char *str)
{
        int i=0;

        while(str[i]!=0)
                IRSend(str[i++]);
}

int main()
{
        char c;
        char buf[100];
        int j=0;

        IROn();
        do
        {
                j=0;
                do
                {
                        c=IRReceive();
                        LCDPrintn(j);
                        buf[j++]=c;
                } while (c!=13);
                buf[j++]=0;
                Wait(30);
                prints(buf);
                //PlaySound((buf[0]-'0')%6);
                //WaitSound();
                Wait(30);
        } while (buf[0]!='q');
        IROff();
        return 0;
}
