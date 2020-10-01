#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
using namespace std;

class shop
{
    char name[20][20];
public:
    int items;
    float quantity[3];
    float price[3];
    float gstp[3];
    float tprice[3];
    float gstpricep=0;
    void input();
    void output();
    void receipt();
    shop()
    {
        items=0;
    }
};
    class gst:public shop
    {
    public:
        void gstcal();
        void gstout();

    };

//-------------------------INPUT FUNCTION------------------------------

void shop::input()
{
    system("CLS");
    cout<<"Enter number of items:";
    cin>>items;
    for(int i=0;i<items;i++)
    {
        cout<<"Enter name of the item "<<(i+1)<<": ";
        cin>>name[i];
        cout<<"Enter number of quantity: ";
        cin>>quantity[i];
        cout<<"Enter the price of item "<<i+1<<": ";
        cin>>price[i];
        tprice[i]=quantity[i]*price[i];
    }
}
//----------------------END OF INPUT FUNC-------------------

//----------------------OUTPUT FUCNTION---------------------
void shop::output()
{
    int a;
    ifstream read("billno.txt");
    read>>a;
    ofstream write("billno.txt");
    a+=1;
    write<<a;
    write.close();

        {ofstream write("entries.txt",ios::app);
        write<<endl<<"Bill no: "<<a<<endl;
        write<<"------------------------------------------------------------------------"<<endl;
        cout<<endl;
        for(int i=0;i<items;i++)
        {
            write<<"Name: "<<name[i]<<" Quantity: "<<quantity[i]<<" Price: "<<tprice[i]+gstp[i]*quantity[i]<<endl;
            cout<<"\n\t\t\tName: "<<name[i]<<" Quantity: "<<quantity[i]<<" Price: "<<tprice[i]+gstp[i]*quantity[i]<<endl;
        }
        write<<"------------------------------------------------------------------------"<<endl;
        write.close();

    }
}
//----------------------------END OF OUTPUT FUNCTION------------------------------

//----------------------------GST CALCULATION FUNCTION----------------------------
void gst::gstcal()
{
        shop::input();
        for(int i=0;i<items;i++)
        {
            gstp[i]=((tprice[i]*12)/100);
        }

}
//-----------------------------END OF GST CALCULATION FUNCTION----------------------

//-----------------------------GST OUTPUT FUNCTION----------------------------------

void gst::gstout()
{
    shop::output();
    float money=0;
    int total_quantity=0;
    float sum=0;
    float sumt=0;
    for(int i=0;i<items;i++)
    {
        sum+=tprice[i];
        sumt=tprice[i]+gstp[i]+sumt;
        total_quantity+=quantity[i];
        gstpricep=sumt;
    }
    system("CLS");
    cout<<"\n\n\t\t\t==============================================================================";
    cout<<"\n\n\t\t\t                            TOTAL: ";
    cout<<"\n\n\t\t\t==============================================================================";
    cout<<"\n\n\t\t\tQuantity= "<<total_quantity<<"\n\n\t\t\tTotal price of items= "<<sum<<"\n\n\t\t\tTotal price of items with GST: "<<sumt;

    pay:
        cout<<"\n\n\t\t\t***BILL***";
        cout<<"\n\n\t\t\tTotal money given: ";
        cin>>money;
        if(money>=sumt)
        {
            cout<<"\n\n\t\t\tTotal money repaid: "<<money-sumt<<endl;
        }
        else
        {
            cout<<"\n\n\t\t\tMoney paid is less then the total amount,please pay again."<<endl;

            goto pay;
        }

}
//--------------------------------------END OF GST OUTPUT---------------------------
void shop::receipt()
{
    int a;
    char y;
    ifstream rece("billno.txt");
    rece>>a;
    ofstream recee("receipt.txt");
    cout<<"\n\t\t\tDo you want to save the receipt?(y/n): ";
    cin>>y;
    if(y=='y'||y=='Y')
    {
        cout<<"\n\t\t\tsaving receipt";
        for(int i=0;i<4;i++)
        {
            cout<<".";
            Sleep(1000);
        }
        cout<<endl;
        cout<<"\n\t\t\tReceipt is saved!"<<endl;
        ofstream receiipt("Receipt.txt");
         receiipt<<"================================================"<<endl;
         receiipt<<"          THANKS FOR SHOPPING!                  "<<endl;
         receiipt<<"================================================"<<endl;
         receiipt<<"\t\t\n\n";
         receiipt<<"BILL NO: "<<a<<endl;
        for(int i=0;i<items;i++)
        {
            receiipt<<"\tName: "<<name[i]<<endl<<"\tQuantity: "<<quantity[i]<<endl<<"\tPrice: "<<price[i]<<endl<<"\tPrice with GST: "<<(price[i]+gstp[i])*quantity[i]<<endl;
        }
            receiipt<<"\tTotal price with GST: "<<gstpricep<<endl;
    }
    recee.close();
}
//--------------------------------------END OF RECEIPT---------------------------

//--------------------------------------AUTHENTICATION---------------------------

int auth()
{
      cout << "Please enter login password:";
    char pass[10] = { 0 };
    char temp[10] = "0000";
    for (int i = 0; i < 10;i++)
    {
        pass[i] = _getch();
        if (pass[i] == 13)
        {
            pass[i] = '\0';
            break;
        }
        else
        {
            _putch('*');
        }
    }
    if(strcmp(temp,pass)==0)
    {
        cout<<endl;
        cout<<"Login Successful!"<<endl;
        return 1;
    }
    else
        return 0;

}

//----------------------------END OF AUTHENTICATION---------------------------

//----------------------------Driver Code-------------------------------------
int main()
{
    gst obj;
    int check=1, option;
    char ch;
    ifstream in;
    check=auth();
    if(!check)
    {
        for(int i=0;i<2;i++)
        {
            cout<<endl;
            cout<<"Wrong password, Try again.(Attempts remaining: "<<(i+1)<<" )"<<endl;
            if(auth())
            {
                goto welcome;
            }
            else
            {
                cout<<"\n\n\t\t\t All attempts failed.."<<endl;
                cout<<"\n\n\t\t\t Program will now exit."<<endl;
                exit(0);
            }
        }
    }
    else
    {
        welcome:;
            do
            {
                start:
                    system("PAUSE");
                    system("CLS");
                    cout<<"\n\n\t\t\t=======================================";
                    cout<<"\n\n\t\t\t    SHOP BILLING MANAGEMENT SYSTEM";
                    cout<<"\n\n\t\t\t=======================================";
                    cout<<"\n\n\t\t\tOptions:";
                    cout<<"\n\n\t\t\t1). Enter a new entry";
                    cout<<"\n\n\t\t\t2). To check previous entries";
                    cout<<"\n\n\t\t\t3). Exit";
                    cout<<"\n\n\t\t\tEnter your Option Number:";
                    cin>>option;
                    switch(option)
                    {
                    case 1:
                        obj.gstcal();
                        obj.gstout();
                        obj.output();
                        obj.receipt();
                        goto start;
                    case 2:
                        in.open("entries.txt",ios::in);
                        while(in.get(ch))
                        {
                            cout<<ch;
                        }
                        in.close();
                        goto start;
                    case 3:
                        exit(0);
                    default:
                        cout<<"\a";
                        cout<<"\n\n\t\t\tWrong option, please choose the option from 1 to 3."<<endl;
                    }
            }while(option!=3);
            }
    return 0;
}
