#include<stdio.h>
#include<stdlib.h>
int fifo(int,int,int[]);
int lru(int,int,int[]);
int optimal(int,int,int[]);

int fifo(int framenos,int npageref,int pagelst[])
{
   int i,j,k=0,Q[framenos],flag,fault=0;
   int mat[framenos][npageref],r,c=0;
   char st[npageref];
   int m=0;
   for (i=0;i<framenos;i++)
   {
      Q[i]=pagelst[i];
      r=0;
      for (j=0;j<framenos;j++)
      {
         if(j<=i)
         {
            mat[r++][c]=Q[j];
         }
         else
         {
            mat[r++][c]=0;
         }
      }
      c++;
      st[m++]='M';
   }
   while (i<npageref)
   {
      flag=0;
      for (j=0;j<framenos;j++)
      {
         if (Q[j]==pagelst[i])
         {
            flag=1;
            st[m++]='H';
            break;
         }
      }
      if (flag==0)
      {
         Q[k]=pagelst[i];
         k=(k+1)%framenos;
         fault++;
         st[m++]='M';
      }
      r=0;
      for (j=0;j<framenos;j++)
      {
         mat[r++][c]=Q[j];
      }
      c++;
      i++;
   }
   printf("--------------------------------------------------------------------------------------------------------\n");
   for (i=0;i<framenos;i++)
   {
      for (j=0;j<npageref;j++)
      {
         printf("%d  ",mat[i][j]);
      }
      printf("\n");
   }
    printf("--------------------------------------------------------------------------------------------------------\n");
    for (i=0;i<npageref;i++)
       printf("%c  ",st[i]);
    printf("\n--------------------------------------------------------------------------------------------------------\n");
   return fault+framenos;
}
int lru(int framenos,int npageref,int pagelst[])
{
   int ind,i,j,flag,fault=0,Q[framenos];
   int mat[framenos][npageref],r,c=0,m=0;
   char st[npageref];
   for (i=0;i<framenos;i++)
   {
      Q[i]=pagelst[i];
      r=0;
      for (j=0;j<framenos;j++)
      {
         if(j<=i)
         {
            mat[r++][c]=Q[j];
         }
         else
         {
            mat[r++][c]=0;
         }
      }
      c++;
      st[m++]='M';
   }
   while(i<npageref)
   {
      flag=0;
      for (j=0;j<framenos;j++)
      {
         if (Q[j]==pagelst[i])
         {
            flag=1;
            ind=j;
            st[m++]='H';
            break;
         }
      }
      if (flag==0)
      {
         fault++;
         st[m++]='M';
      }
      if (flag!=1)
      {
         for (j=0;j<framenos-1;j++)
         {
            Q[j]=Q[j+1];
         }
         Q[j]=pagelst[i];
      }
      else
      {
         for (j=ind;j<framenos-1;j++)
         {
            Q[j]=Q[j+1];
         }
         Q[j]=pagelst[i];
      }
      r=0;
      for (j=0;j<framenos;j++)
      {
         mat[r++][c]=Q[j];
      }
      c++;
      i++;
   }
    printf("--------------------------------------------------------------------------------------------------------\n");
   for (i=0;i<framenos;i++)
   {
      for (j=0;j<npageref;j++)
      {
         printf("%d  ",mat[i][j]);
      }
      printf("\n");
   }
   printf("--------------------------------------------------------------------------------------------------------\n");
   for (i=0;i<npageref;i++)
       printf("%c  ",st[i]);
    printf("\n--------------------------------------------------------------------------------------------------------\n");
   return fault+framenos;
}
int optimal(int framenos,int npageref,int pagelst[])
{
   int i,j,k,temp[framenos],Q[framenos];
   int fault=0,flag,count,ind;
   int mat[framenos][npageref],r,c=0,m=0;
   char st[npageref];
   for (i=0;i<framenos;i++)
   {
      Q[i]=pagelst[i];
      r=0;
      for (j=0;j<framenos;j++)
      {
         if(j<=i)
         {
            mat[r++][c]=Q[j];
         }
         else
         {
            mat[r++][c]=0;
         }
      }
      c++;
      st[m++]='M';
   }
   while(i<npageref)
   {
      for (j=0;j<framenos;j++)
      {
         temp[j]=Q[j];
      }
      flag=0;
      for (j=0;j<framenos;j++)
      {
         if (Q[j]==pagelst[i])
         {
            flag=1;
            st[m++]='H';
            break;
         }
      }
      if (flag==0)
      {
         fault++;
         st[m++]='M';
         for (k=i+1;k<npageref;k++)
         {
            for (j=0;j<framenos;j++)
            {
               if (temp[j]==pagelst[k])
               {
                  temp[j]=0;
                  break;
               }
            }
            count=0;
            for (j=0;j<framenos;j++)
            {
               if (temp[j]==0)
               {
                  count++;
               }
            }
            if (count==framenos-1)
            {
               for (j=0;j<framenos;j++)
               {
                  if (temp[j]!=0)
                  {
                     ind=j;
                     break;
                  }
               }
               break;
            }
         }
         Q[ind]=pagelst[i];
      }
      r=0;
      for (j=0;j<framenos;j++)
      {
         mat[r++][c]=Q[j];
      }
      c++;
      i++;
   }
   printf("--------------------------------------------------------------------------------------------------------\n");
   for (i=0;i<framenos;i++)
   {
      for (j=0;j<npageref;j++)
      {
         printf("%d  ",mat[i][j]);
      }
      printf("\n");
   }
   printf("--------------------------------------------------------------------------------------------------------\n");
   for (i=0;i<npageref;i++)
       printf("%c  ",st[i]);
    printf("\n--------------------------------------------------------------------------------------------------------\n");
   return fault+framenos;
}

int main()
{
   int framenos,npageref,i,res;
   printf("Frame Size : ");
   scanf("%d",&framenos);
   printf("Page Reference String Length : ");
   scanf("%d",&npageref);
   int pagelst[npageref];
   printf("Page list...\n");
   for (i=0;i<npageref;i++)
   {
      scanf("%d",&pagelst[i]);
   }
   int ch;
   printf("---------------------------\n");
   printf("1.FIFO\n2.LRU\n3.OPTIMAL\n");
   printf("---------------------------\n");
   printf("Your Choice : ");
   scanf("%d",&ch);
   do
   {
      switch(ch)
      {
         case 1:
            {
                printf("----------------------------\n");
               res=fifo(framenos,npageref,pagelst);
               break;
            }
         case 2:
            {
                printf("----------------------------\n");
               res=lru(framenos,npageref,pagelst);
               break;
            }
         case 3:
            {
               printf("----------------------------\n");
               res=optimal(framenos,npageref,pagelst);
               break;
            }
      }
      printf("Page Hit  = %d\n",npageref-res);
      printf("Page Miss = %d\n",res);
      printf("Your Choice : ");
      scanf("%d",&ch);
   }while(ch<=3);
   return 0;
}
