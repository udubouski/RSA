#include <iostream>
#include <cmath>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <cstdio>

using namespace std;
#define int64 long long int

/////////////////////////////////////////////////////
// Функция "Решето Эратосфена"
/////////////////////////////////////////////////////
int64* resheto(int64& m, int64 &zk)
{
    bool t=true;
    int64 i,j=0,p=2;
    int64 *mas= new int64[m+1];
    for (i=0;i<=m;i++){
        mas[i]=i;
    }

    mas[1]=0;
    while(t == true)
    {
        for (i=p*p;i<=m;i=i+p)
        {
            mas[i]=0;
        }
        for (i=p;i<=m;i++)
        {
            if (mas[i]>p)
            {
                t=true;
                p=mas[i];
                break;
            }
            else t=false;
        }
    }

    p=0;
    for (i=0;i<=m;i++)
    {
        if(mas[i]!=0)
        p++;
    }
    zk=p;

    int64 *mas1= new int64[p];
    for (i=0;i<=m;i++)
    {
        if(mas[i]!=0)
        {
            mas1[j]=mas[i];
            j++;
        }
    }
    return mas1;
}

/////////////////////////////////////////////////////
// Функция НОД
/////////////////////////////////////////////////////
int64 nod(int64 e,int64 phi)
{
    return phi ? nod(phi,e%phi) : e;
}


/////////////////////////////////////////////////////
// Функция "ASCII code преобразование символов в числа"
/////////////////////////////////////////////////////
int64 * askii(char* str, int64 t)
{
    int64 i;
    int64 *a= new int64[t];
    for (i=0;i<t;i++)
    {
        if (str[i]!=' '){
            a[i]=int64(str[i]);
        }
        else
        {
            a[i]=0;
        }
    }
    return a;
}

/////////////////////////////////////////////////////
// Функция "ASCII code преобразование чисел в символы"
/////////////////////////////////////////////////////
char *text(int64* mas, int64 t)
{
    int64 i;
    char *a= new char[t+1];
    for (i=0;i<t;i++)
    {
        if(mas[i]!=0)
        {
           a[i]=static_cast<char>(mas[i]);
        }
        else a[i]=' ';
    }
    a[t]='\0';
    return a;
}

/////////////////////////////////////////////////////
// Функция возведения в степень по модулю
/////////////////////////////////////////////////////
int64 bpow(int64 x, int64 n, int64 m)
{
  int64 count=1;
  if (!n) return 1;
  while (n) {
    if (n%2==0) {
      n/=2;
      x*=x;
      x %= m;
    }
    else {
      n--;
      count*=x;
      count %=m;
    }
  }
  return count % m;
}

/////////////////////////////////////////////////////
// Функция шифрования\дешифрования
/////////////////////////////////////////////////////
int64* shifr(int64 * mass,int64 t,int64 key,int64 n)
{
    int64 *a= new int64[t];
    for (int64 i=0;i<t;i++)
    {
        if(mass[i]!=0)
        {
          a[i]=bpow(mass[i],key,n);
        }
        else a[i]=mass[i];
    }
    return a;
}

/////////////////////////////////////////////////////
// Функция проверки на ввод числа
/////////////////////////////////////////////////////
void chislo(int64 &m)
{
    while(true)
    {
    cin>>m;
    if(cin.good() && m>2)
    {
        cin.ignore(10, '\n');
        break;
    }
    cin.clear();
    cout<<"Nepravil'niy vvod! Vvedite chislo > 2 :";
    cin.ignore(10, '\n');
    }
}

int main()
{
    int64 m,n,f,q,phi,e,d,i,p,t;
    char cher,selc;

    do{
    cout<<"Vvedite chislo, do kotorogo nugno proizvodit poisk:";
    chislo(m);
    f=q=0;
    int64* msprost;
    cout<<"Spisok prostih chisel do "<<m<<":"<<endl;
    msprost=resheto(m,p);
    for (i=0;i<=p-1;i++)
    {
        cout <<  msprost[i] << " ";
    }
    cout<<endl;
    cout<<"Viberite 2 chisla iz spiska:"<<endl;
    cout<<"r - random"<<endl;
    cout<<"v - vvesti"<<endl;
    cin>>selc;
    if (selc=='r')
    {
        f=msprost[rand() % p];
        do{
            q=msprost[rand() % p];
        }
        while (f<=q);
    }
    else if (selc!='r')
    {
       do{
       cout<<"Pervoe:";
       chislo(f); //.........................................................>>>>>>>>> сделать проверку на ввод из массива
       cout<<"Vtoroe:";
       chislo(q);
        }
       while (f==q);
    }
    cout<<"Pervoe prostoe chislo:"<<f<<endl;
    cout<<"Vtoroe prostoe chislo:"<<q<<endl;

    n=f*q;                                                          // modul N
    cout<<"Modul chisel raven:"<<n<<endl;

    phi=(f-1)*(q-1);
    cout<<"Function Eilera phi("<<n<<")="<<phi<<endl;

    for (e=2;e<=phi;e++)
    {
         if(nod(e,phi) == 1)
            {
            break;
            }
    }

    cout<<"Znachenenie otkritogo klucha:"<<e<<endl;                  // открытый ключ e

    d=1;
    while ((e*d)%phi !=1)                                               // перебор значений секретного ключа
    {
        d++;
    }
    cout<<"Znachenenie secretnogo klucha:"<<d<<endl;

    cout<<"Vvedite soobshenie dlya shifrovania:"<<endl;
    char str[30];
    cin.ignore();
    cin.getline(str,30);

    int64* mas2;                                                             // исходное сообщение в аски
    t=strlen(str);
    mas2=askii(str,t);
    cout<<"ASKII:"<<endl;
    for (i=0;i<t;i++)
    {
        cout<<mas2[i]<<" ";
    }
    cout<<endl;

    ////////////////////////////////////////////////////
    //Зашифровка текста
    ////////////////////////////////////////////////////
    int64* massif;                                                           // зашифрованный текст
    massif=shifr(mas2,t,e,n);
    cout<<"SHIFR:"<<endl;
    for (int64 i=0;i<t;i++)
    {
        cout<<massif[i]<<" ";
    }
    cout<<endl;

    ////////////////////////////////////////////////////
    //Расшифровка текста
    ////////////////////////////////////////////////////
    int64* masdes;                                                           // зашифрованный текст
    masdes=shifr(massif,t,d,n);
    cout<<"DESSHIFR:"<<endl;
    for (int64 i=0;i<t;i++)
    {
        cout<<masdes[i]<<" ";
    }
    cout<<endl;

    char *stroka;
    cout<<"DESSHIFR ASCII:"<<endl;                                           // расшифрованное сообщение в аски
    stroka=text(masdes,t);
    cout<<stroka<<endl;

    delete[] mas2;
    delete[] massif;
    delete[] masdes;

    cout << "Eshe raz ? y/n" << endl;
    cher = _getch();
    }
    while (tolower(cher) == 'y');
    return 0;
}
