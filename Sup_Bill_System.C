#include<stdio.h>
#include<conio.h>
void calculate_bill();
void insert_product();
void display_product();
void del_product();
void update_product();
struct product
{
	int p_id;
	char p_name[40];
	float p_price;
	float p_dis;
	float p_vat;
};
	struct product p;

void main()
{
	int ch,a_id;;
	clrscr();
	while(ch!=6)
	{
	clrscr();
	printf("\t\t****************************************************\n");
	printf("\t\t\t Welcome To Supermarket Billing System\n");
	printf("\t\t****************************************************\n\n");
		printf("\t\t\t 1. Calculate Bill \n");
		printf("\t\t\t 2. Insert Product \n");
		printf("\t\t\t 3. Display All Product \n");
		printf("\t\t\t 4. Delete Product \n");
		printf("\t\t\t 5. Update Products \n");
		printf("\t\t\t 6. Exit\n\n");
		printf("Enter Your Choice :");
		scanf("%d",&ch);
		switch(ch)
		{
		case 1: clrscr();
			calculate_bill();
			break;
		case 2: clrscr();
			printf("Enter Admin Id : ");
			scanf("%d",&a_id);
			if(a_id==12345)
			{
			insert_product();
			break;
			}
			else
			{
			 printf("Wrong Admin ID !!");
			 break;
			}
		case 3: clrscr();
			display_product();
			break;
		case 4: clrscr();
			printf("\n\tEnter Admin Id : ");
			scanf("%d",&a_id);
			if(a_id==12345)
			{
			del_product();
			break;
			}
			else
			{
			 printf("\n\tWrong Admin ID !!");
			 break;
			}
		case 5: clrscr();
			printf("\n\tEnter Admin Id : ");
			scanf("%d",&a_id);
			if(a_id==12345)
			{
			update_product();
			break;
			}
			else
			{
			 printf("\n\tWrong Admin ID !!");
			 break;
			}
		case 6: exit(1);
		 default:
			printf("\n \t Wrong Input");

		}
		printf("\nPress Any Key To Continue");
		getch();
	}

}
void calculate_bill()
{
	int p_id1,j,amount,p_weg,flag=0;
	long cash_received,newt_amount;
	float bill,t_bill=0, float_part;
	FILE *fp;
	fp=fopen("prod.dat","r");
	if(fp==NULL)
	{
		printf("\n \tData File Error");
		return;

	}
	display_product();
	printf("How Many Product for Bill : ");
	scanf("%d",&p_weg);
	for(j = 1; j<=p_weg; j++)
	{
	printf("\n\nEnter Your Code :");
	scanf("%d",&p_id1);
	printf("Enter No of Product :");
	scanf("%d",&amount);

	while(fread(&p,sizeof(p),1,fp)>0 && flag==0)
	{

	if(strcmp(p_id1,p.p_id)==0)
		{
		 flag=1;
		 bill=((p.p_price*amount)-(p.p_price*amount*p.p_dis/100))+(((p.p_price*amount)-(p.p_price*amount*p.p_dis/100))*p.p_vat/100);
		 printf("%s ( %0.2f )\n",p.p_name,bill);
		 t_bill=t_bill+bill;
		}
	}
	flag=0;
	fclose(fp);
	fp=fopen("prod.dat","rb");
	}
	printf("------------------------------------------------------------------------------\n");
	printf("\t\t\tTOTAL AMOUNT :\t%0.2f\n", t_bill);
	printf("------------------------------------------------------------------------------\n");
	printf("BALANCE DUE                = %0.2f\n", t_bill);
	newt_amount = t_bill;
	float_part = t_bill - newt_amount;
	if(float_part > 0.50)
		newt_amount += 1;
	printf("BALANCE DUE AFTER ROUNDING = %ld\n", newt_amount);
	A:
	printf("CASH RECEIVED              = ");
	scanf("%ld", &cash_received);
	if(cash_received < newt_amount)
	{
		printf("Amount insufficient. Please provide more money.\n");
		goto A;
	}
	printf("CHANGE TO BE RETURNED      = %ld\n", cash_received - newt_amount);
	printf("------------------------------------------------------------------------------\n");
	printf("\t\t\t** Thank you for shopping with us **\n");
	fclose(fp);

}

void insert_product()
{
	FILE *fp;
	fp=fopen("prod.dat","ab+");

	if(fp==NULL)
	{
		printf("\n \tData File Error ");
		return;

	}
	printf("\t\t Enter New Product\n\n");
	printf(" Enter PRODUCT ID : ");
	scanf("%d",&p.p_id);
	fflush(stdin);
	printf("\n Enter PRODUCT NAME : ");
	gets(p.p_name);
	printf("\n Enter PRODUCT PRICE : ");
	scanf("%f",&p.p_price);
	printf("\n Enter PRODUCT DISCOUNT : ");
	scanf("%f",&p.p_dis);
	printf("\n Enter PRODUCT VAT : ");
	scanf("%f",&p.p_vat);
	fwrite(&p,sizeof(p),1,fp);
	{
		printf("\n\t\tProduct Inserted\n");
	}
	fclose(fp);
}
void display_product()
{
	FILE *fp;
	fp=fopen("prod.dat","rb");

	if(fp==NULL)
	{
		printf("\n \tData File Error");
		return;

	}
	printf("\n\t\t\t All Available Products \n\n");
	printf("Product_ID \t Product_NAME with Details\n\n");
	while(fread(&p,sizeof(p),1,fp)==1)
	{
		printf("%d \t\t%s \t(%0.2f% Discount)",p.p_id,p.p_name,p.p_dis);
		printf("\n\t\tPrice : %0.2f \t%0.2f% VAT \n\n",p.p_price,p.p_vat);
	}
	fclose(fp);

}
void del_product()
{
	int p_id;
	unsigned flag=0;
	FILE *fp,*ft;
	fp=fopen("prod.dat","r");

	if(fp==NULL)
	{
		printf("\n \tData File Error");
		return;

	}
	printf("\n\t\t*************Privious List***************");
	display_product();
	printf("\n\nEnter Product ID to Delete :");
	scanf("%d",&p_id);
	ft=fopen("prod1.dat","ab+");
	while(fread(&p,sizeof(p),1,fp)==1)
	{

	if(strcmp(p_id,p.p_id)!=0)
		{
		 printf("\n\n");
		 fwrite(&p,sizeof(p),1,ft);
		}
	else
		flag=1;
	}
	if(flag==0)
	{
	printf("\n\n\t\t\t No Record Found ");
	}
	fclose(fp);
	fclose(ft);
	remove("prod.dat");
	rename("prod1.dat","prod.dat");
	printf("\n**********************************************************************");
}
void update_product()
{
	int p_id,flag=0;
	FILE *fp;
	fp=fopen("prod.dat","rb+");

	if(fp==NULL)
	{
		printf("\n \tData File Error ");
		return;

	}
	display_product();
	printf("\n\nEnter Product ID which you want to Update : ");
	scanf("%d",&p_id);
	printf("\n\t\t\tProduct Details\n");
	printf("\t\t\t***************\n");
	while(fread(&p,sizeof(p),1,fp)>0 && flag==0)
	{
		if(p.p_id==p_id)
		{
		flag=1;
		printf("%d \t\t%s \t(%0.2f% Discount)",p.p_id,p.p_name,p.p_dis);
		printf("\n\t\tPrice : %0.2f \t%0.2f% VAT ",p.p_price,p.p_vat);
		printf("\n\n*******************************************************************\n");
		printf("\t\t\t Enter New Product Details \n");
		printf("*******************************************************************\n");
		printf("\n Enter PRODUCT ID : ");
		scanf("%d",&p.p_id);
		fflush(stdin);
		printf("\n Enter PRODUCT NAME : ");
		gets(p.p_name);
		printf("\n Enter PRODUCT PRICE : ");
		scanf("%f",&p.p_price);
		printf("\n Enter PRODUCT DISCOUNT : ");
		scanf("%f",&p.p_dis);
		printf("\n Enter PRODUCT VAT : ");
		scanf("%f",&p.p_vat);
		fseek(fp,-(long)sizeof(p),1);
		fwrite(&p,sizeof(p),1,fp);
		printf("\n\t\t Record Updated Sucessfully \n");
		}
	}
	if(flag==0)
	{
		printf("\n\t\t Product Not Avalable \n");

	}
	fclose(fp);
}
