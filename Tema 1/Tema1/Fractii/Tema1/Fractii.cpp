/*Complexitatea este n log n, datorita utilizarii quicksort*/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;   
int euclid(int a, int b) {
    while (a != b)
    {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}
struct fractie {
    int numarator, numitor;
    void reducere(){
        int temp = euclid(numarator, numitor);
        numarator /= temp;
        numitor /= temp;
    }
   void aritmetica(char semn, fractie operand2){
       int temp = numitor * operand2.numitor / euclid(numitor, operand2.numitor);
       switch (semn)
       {
       case '+':
           numarator = numarator * temp / numitor + operand2.numarator * temp / operand2.numitor;;
           numitor = temp;
           break;
       case '-':
           numarator = numarator * temp / numitor - operand2.numarator * temp / operand2.numitor;;
           numitor = temp;
           break;
       case '*':
           numarator *= operand2.numarator;
           numitor *= operand2.numitor;
           break;
       case '/':
           numarator *= operand2.numitor;
           numitor *= operand2.numarator;
           break;
       }
       
    }
   bool comparatie(fractie operand2)
   {
       int temp = numitor * operand2.numitor / euclid(numitor, operand2.numitor);
       if (numarator * (temp / numitor) > operand2.numarator * (temp / operand2.numitor))
               return 1;
           else
               return 0;
   }
   float conversie(){
       return (float)numarator / numitor;
    }
};
void citire(vector<fractie>& input,int& lungime) {
    ifstream f("input.txt");
    f >> lungime;
    input.resize(lungime);
    for (int i = 0; i < lungime; i++)
        f >> input[i].numarator >> input[i].numitor;

}
void suma(vector<fractie>input,int lungime)
{
    fractie adunare;
    adunare = input[0];
    for (int i = 1; i < lungime; i++)
        adunare.aritmetica('+', input[i]);
    adunare.reducere();
    cout << adunare.numarator << "/" << adunare.numitor << endl;
}
int partitie(vector<fractie>& input, int minim, int maxim)
{
    fractie pivot = input[maxim]; 
    int i = (minim - 1); 
    for (int j = minim; j <= maxim - 1 ; j++)
    {
        if (input[j].comparatie(pivot)==0)
        {
            i++; 
            swap(input[i], input[j]);
        }
    }
    swap(input[i + 1], input[maxim]);
    return (i + 1);
}
void sortare(vector<fractie>& input, int minim, int maxim)
{
    if (minim < maxim)
    {
        int p = partitie(input, minim, maxim);
        sortare(input, minim, p - 1);  
        sortare(input, p + 1, maxim); 
    }
}
void reducere(vector<fractie>& input, int lungime)
{
    for (int i = 0; i < lungime; i++)
        input[i].reducere();
}
void afisare(vector<fractie>input,int lungime) {
    for (int i = 0; i < lungime; i++)
        cout << input[i].numarator << "/" << input[i].numitor << endl;
}
int main()
{
    vector<fractie> input;
    int lungime;
    citire(input,lungime);
    reducere(input, lungime);
    sortare(input, 0, lungime - 1);
    suma(input, lungime);
    afisare(input, lungime);
    return 0;
}

