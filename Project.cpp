#include<iostream>
#include<iomanip>
#include<conio.h>
#include<string>
#include<cstring>
#include<fstream>
using namespace std;
//functions Prototypes----------------------------------------------
void Medicine();
void Reciept_info(int Reciept_num); 
void stock();
void list_medicines(int Reciept_num);
void medicines_calculation(int Reciept_num);
//-----------------------------------------------------------------------



int main()
     {
//Main variables
int  option;
int recipt;
while(true)//Main Loop
{
	system("cls");
cout<<"          ***********************************************************"<<endl;
cout<<"          *                                                         *"<<endl;
cout<<"          *           Welcome to  Medical Store                     *"<<endl;
cout<<"          *                                                         *"<<endl;
cout<<"          *                                                         *"<<endl;
cout<<"          ***********************************************************"<<endl;

cout<<endl<<endl<<endl;



menu:
cout<<"         ************************************************************"<<endl;	
cout<<"         *                  1.Purchasing Medicine                   *"<<endl;
cout<<"         *                  2.Add new Stock                         *"<<endl;
cout<<"         *                  3.Recipts' Details                      *"<<endl;
cout<<"         *                  4.Menu                                  *"<<endl;
cout<<"         *                  5.Exit                                  *"<<endl;
cout<<"         ************************************************************"<<endl;

cout<<endl<<"\tPress number"<<endl<<"\t";
cin>>option;

		if(option==4)
		{
		goto menu;		
		}

		else if(option==1)
		{
		Medicine();
		}
		else if(option==2)
		{
		stock();
		}

		else if(option==3)
		{
		system("cls");
		cout<<endl<<"\t\t\t\tReciept's Information"<<endl<<endl;
		cout<<"_______________________________________________________________________________"<<endl<<endl;
		cout<<endl<<"\tEnter the receipt Number"<<endl<<"\t";
		cin>>recipt;

		Reciept_info(recipt);
		}
		else if(option==5)
		{
		cout<<"Exit";
		break;
		}
		else
		{
		cout<<"\tInvalid Selection"<<endl<<endl<<endl;
		goto menu;
		}
}

getch();}


//----------------------------------------------------------------------------------------------------------

//-------------------------------Functions------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------


//function  1 

void Medicine()
{
//variables

int Reciept_num,Serial;	
string data;
//------------------------------------------------------------------------------------------------------------------------------

     system("cls");
	 cout<<endl<<"\t\t\tSearching and Purchasing Medicines"<<endl<<endl;
     cout<<"_______________________________________________________________________________"<<endl<<endl;
     menu:
     cout<<"\tEnter the Receipt number"<<endl<<"\t";
     cin>>Reciept_num;
	 //----------------------------------Searching Recipt num in account info----------------------------------------
	 ifstream account_data("account.txt");
     while(!account_data.eof())
	 {
		account_data>>Serial;
		getline(account_data,data);
	 if(Serial==Reciept_num)
	 {
     cout<<"\tThis Reciept Number has been used"<<endl<<endl;
	 goto menu;
	 }

	 }
     account_data.close();
	 
	 list_medicines(Reciept_num);

}
//--------------------------------------------------------------------------------
//---------------------------Function list_medicines-----------------------------------------------------
//----------------------------------------------------------------------------------------------
    void list_medicines(int Reciept_num)
    {

    //variables
    string name,rack_no,Exp,Mfg;
    int qty,cost,Sr;	

    //duplicate variables
    string name1,rack_no1,Mfg1,Exp1;
     int Sr1,cost1,qty1;
//----------------------------------------------------------------------------------------------
	
     ifstream read("Info.txt");
     cout<<"#Sr "<<"NAME "<<"   "<<"RACK NO "<<"         "
	 <<"MFG"<<"           "<<"EXP"<<"       "<<"U-COST"<<"   "
	 <<"QTY"<<endl<<endl;

     read>>Sr1>>name1>>rack_no1>>Mfg1>>Exp1>>cost1>>qty1;

     cout<<Sr1<<" "<<name1<<"   \t"<<rack_no1<<"\t"<<Mfg1<<"\t"
	 <<Exp1<<"      "<<cost1<<"     "<<qty1<<endl;


	  while(!read.eof())
	  {
      read>>Sr>>name>>rack_no>>Mfg>>Exp>>cost>>qty;

      if(Sr1!=Sr)

      {
	  cout<<Sr<<" "<<name<<"   \t"<<rack_no<<"\t"<<Mfg<<"\t"
	  <<Exp<<"      "<<cost<<"     "<<qty<<endl;
	  }
	
      Sr1=Sr;

      }

     read.close();//info file closing
	 medicines_calculation(Reciept_num);

}
//--------------------------------------------------------------------------------
//---------------------------Function medicines_calculation -----------------------------------------------------
//----------------------------------------------------------------------------------------------
   void medicines_calculation(int Reciept_num)
    {
	//variables
    string name,rack_no,Exp,Mfg,data;
    int qty,cost,quantity_item,user_account=0,Sr,Medicine_num;	
    char Account_check;

    //duplicate variables
    string name1,rack_no1,Mfg1,Exp1;
    int Sr1,cost1,qty1; 
//--------------------------------------------------------------------------------------------------	    

    cout<<endl<<endl<<"\tEnter the Medicine Number"<<endl<<"\t";
    cin>>Medicine_num;	
	 
//--------------------------------Files  Opening----------------------------------------------------------------------------------------------
    ofstream account_info("account.txt",ios::app);
	ofstream temp_info("complete_record.txt");	
	ifstream read_file("Info.txt");

//-------------------------------------------------------------------------------------------------
    read_file>>Sr1>>name1>>rack_no1>>Mfg1>>Exp1>>cost1>>qty1;

    if(Sr1==Medicine_num)
    {
    label:
	cout<<endl<<"\tEnter the quantity of the medicine "<<name1<<endl<<"\t"; 
    cin>>quantity_item;

	if(quantity_item>qty1)
	{
	cout<<"\tInsufficent Quantity "<<endl<<endl;
	goto label;
	}

    user_account=user_account+(quantity_item*cost1);
    qty1=qty1-quantity_item;
    account_info<<Reciept_num<<"   "<<name1<<"   "<<quantity_item
    <<"     "<<quantity_item*cost1<<"    "<<endl;
    }

    temp_info<<Sr1<<"   "<< name1<<"  "<<rack_no1<<"  "<<Mfg1<<"   "
	<<Exp1<<"  "<<cost1<<"  "<<qty1<<endl;
  
   while(!read_file.eof())
   {
   read_file>>Sr>>name>>rack_no>>Mfg>>Exp>>cost>>qty;
   if(Sr==Medicine_num&&Sr1!=Sr)
   {       		
	label1:		
   cout<<endl<<"\tEnter the quantity of the medicine  "
   <<name<<endl<<"\t"; 
   cin>>quantity_item;
   if(quantity_item>qty)
   {
    cout<<"\tInsufficent Quantity "<<endl<<endl;
	goto label1;
    }

   user_account=user_account+quantity_item*cost;
   qty=qty-quantity_item;

   account_info<<Reciept_num<<"   "<<name<<"   "<<quantity_item
   <<"     "<<quantity_item*cost<<"    "<<endl;
 

   }	
   temp_info<<Sr<<"   "<< name<<"  "<<rack_no<<"  "<<Mfg<<"   "<<Exp<<"  "<<cost<<"  "<<qty<<endl;
   Sr1=Sr;
   


   } 

 
    read_file.close();
    temp_info.close();
	account_info.close();
	
//---------------------------------------Writing on info------------------------------
ifstream read_obj1("complete_record.txt");
ofstream write_obj1("Info.txt");
string line;



    read_obj1>>Sr1>>name1>>rack_no1>>Mfg1>>Exp1>>cost1>>qty1;
    {   
	write_obj1<<Sr1<<" "<<name1<<"   \t"<<rack_no1<<"\t"<<Mfg1<<"\t"
    <<Exp1<<"      "<<cost1<<"     "<<qty1<<endl;
	}
    while(!read_obj1.eof())
    {

	read_obj1>>Sr>>name>>rack_no>>Mfg>>Exp>>cost>>qty;

    if(Sr1!=Sr)

    {
    write_obj1<<Sr<<" "<<name<<"   \t"<<rack_no<<"\t"<<Mfg<<"\t"
	<<Exp<<"      "<<cost<<"     "<<qty<<endl;
    }
	
    Sr1=Sr;

    }
    read_obj1.close();
    write_obj1.close();
    remove("complete_record.txt");
//----------------------------------------------------------------------------------
   cout<<"\tCheck your receipt (Y/N)"<<endl<<"\t";
   cin>>Account_check;
   cout<<endl;
   if(Account_check=='y'||Account_check=='Y')
   Reciept_info(Reciept_num);

   else  list_medicines(Reciept_num);

   }








//function Reciept_info
void Reciept_info (int Reciept_num)    
{
int ac_num,qty_data,price,final_price=0,paid_amount;
float  discount;
string name_data;
//duplicate
int ac_num1,qty_data1,price1,counter=0;
string name_data1;
//-------------------------------------------------------------------------------------------------------------
   
   
    
    cout<<"\tReceipt Number "<<"\tMedicine Name:"<<"\tQuantity:"
    <<"   "<<"Amount"<<endl<<endl;
    ifstream read_obj("account.txt");
    while(!read_obj.eof())
    {
    read_obj>>ac_num>>name_data>>qty_data>>price;
	if(ac_num==Reciept_num)
	{
	counter++;
	}

    }
    read_obj.close();//temp record file closing

	int i=1;
	ifstream read1("account.txt");
	while (!read1.eof())
	{

    read1>>ac_num1>>name_data1>>qty_data1>>price1;
	if(ac_num1==Reciept_num&&i<counter)
	{
	cout<<"    \t"<<ac_num1<<"       \t"<<name_data1<<"        \t"
    <<qty_data1<<"           \t"<<price1<<endl<<endl;
	final_price+=price1;
	i++;
	}

	}
	read1.close();






//-----
    cout<<"\tTotal Amount: "<<final_price<<endl<<endl<<endl;
	if(final_price==0)
    cout<<"\tNo receipt is available on this number"<<endl; 
	
	else if(final_price<50&&final_price>0)
    {
    cout<<"\tPaid_Amount:  Rs."<<final_price<<endl<<endl;
    cout<<"\tNo discount is given on the Amount less than 50"<<endl<<endl<<endl;
    }

   else if(final_price>=50&&final_price<=100)
   {
   discount=0.1;
   paid_amount=final_price-final_price*discount;
   cout<<"\t Discount:"<<discount*100<<"%"<<"\tPaid_Amount:  Rs."<<paid_amount
   <<endl<<endl<<endl;
   }

  else if(final_price>100&&final_price<=500)
  {
  discount=0.3;
  paid_amount=final_price-final_price*discount;
  cout<<"\t Discount:"<<discount*100<<"%"<<"\tPaid_Amount:  Rs."<<paid_amount
  <<endl<<endl<<endl;
  }
  else if(final_price>=1000)
  {
  discount=0.5;
  paid_amount=final_price-final_price*discount;
  cout<<"\t Discount:"<<discount*100<<"%"<<"\tPaid_Amount:  Rs."<<paid_amount
  <<endl<<endl<<endl;
  }
  cout<<"____________________________________________________________________________"
  <<endl<<endl<<endl;

  char menu;
  cout<<"\tPress 'M' or 'm' for main menu and 'N' for new recipt"<<endl<<"\t";
  cin>>menu;
  if(menu=='M'||menu=='m')
  main();
   
  else
  Medicine();
    
  }
	
//--------------------------------------------------------------------------------------------
void stock()
{
system("cls");
cout<<endl<<"\t\t\t\tAdd New Stock"<<endl<<endl;
cout<<"____________________________________________________________________________"<<endl<<endl;

string name,Mfg,Exp,check;
int Sr,rack_no,cost,qty;

		menu:
		ofstream write("Info.txt", ios::app);
		system("cls");
		cout<<endl<<"\t\t\t\tAdd New Stock"<<endl<<endl;
		cout<<"____________________________________________________________________________"<<endl<<endl;
		cout<<endl<<"\tEnter the Serial Number"<<endl<<"\t";
		cin>>Sr;
		cout<<"\tEnter the Medicine Name"<<endl<<"\t";
		cin>>name;
		cout<<"\tEnter the Rack Number"<<endl<<"\t";
		cin>>rack_no;
		cout<<"\tEnter the MFG Date (Enter like this dd-mm-yyyy)"<<endl<<"\t";
		cin>>Mfg;
		cout<<"\tEnter the EXP Date (Enter like this dd-mm-yyyy)"<<endl<<"\t";
		cin>>Exp;
		cout<<"\tEnter the Per Unit Cost"<<endl<<"\t";
		cin>>cost;
		cout<<"\tEnter the Total Quantity"<<endl<<"\t";
		cin>>qty;
		cout<<"\tPress 'S' or 's' for saving it and N for removing it "<<endl<<"\t";
		cin>>check;
		if(check=="S"||check=="s")
		{
		write<<Sr<<" "<<name<<"   \t"<<rack_no<<"\t"<<Mfg<<"\t"
		<<Exp<<"      "<<cost<<"     "<<qty<<endl;
		write.close();
		}
		else 
		{
		goto menu;
		write.close();
		}

		cout<<"\tStock has been  added successfully"<<endl<<endl;
		cout<<"\tPress 'A' or 'a' for adding more stock and 'M' to go to  main menu"<<endl<<"\t";
		cin>>check;
		if(check=="A"||check=="a")
		goto menu;
}



