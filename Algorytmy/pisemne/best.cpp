//na poczatku trzeba wepchnac 0 na uzywane deque
int cmp(deque<int> x1, deque<int> x2)//if x1<x2 return 1 if x1==x2 return 2 else return 0
{
    if(x1.size()==x2.size())
    {
        auto i1=x1.begin();
        auto i2=x2.begin();
        while(i1!=x1.end())
        {
            if(*i1<*i2) return 1;
            else if(*i1>*i2) return 0;
            i1++;
            i2++;
        }
        return 2;//ZNACZY ZE x1==x2
    }
    else if(x1.size()<x2.size()) return 1;
    else if(x1.size()>x2.size()) return 0;
    return 1;//NIGDY NIE ZACHODZI, ale kompilator ma problem
}

void wypisz(deque<int> x)
{
    for(auto i = x.begin(); i!=x.end(); i++)
    {
        cout<<*i;
    }
}

deque<int> dodaj(deque<int> x1, deque<int> x2)
{
    deque<int> odp;
    auto i1=x1.rbegin();
    auto i2=x2.rbegin();
    int pom=0;

    while(true)
    {
        odp.push_front((*i1+*i2+pom)%10);
        pom=(*i1+*i2+pom)/10;

        i1++;
        i2++;

        if(i1==x1.rend())
        {
            while(i2!=x2.rend())
            {
                odp.push_front((*i2+pom)%10);
                pom=(*i2+pom)/10;
                i2++;
            }
            if(pom!=0) odp.push_front(pom);
            return odp;
        }
        else if(i2==x2.rend())
        {
            while(i1!=x1.rend())
            {
                odp.push_front((*i1+pom)%10);
                pom=(*i1+pom)/10;
                i1++;
            }
            if(pom!=0) odp.push_front(pom);
            return odp;
        }
    }
    
}

deque<int> odejmij(deque<int> x1, deque<int> x2)//x1>=x2
{
    deque<int> odp;

    auto i1=x1.rbegin();
    auto i2=x2.rbegin();

    while(i2!=x2.rend())
    {
        if(*i1<*i2)
        {
            auto i3=i1;
            i3++;
            while(*i3==0)
            {
                i3++;
            }
            *i3=*i3-1;
            i3--;
            while(i3!=i1)
            {
                *i3=9;
                i3--;
            }
            *i1+=10;
        }
        odp.push_front(*i1-*i2);
        i1++;
        i2++;
    }
    while(i1!=x1.rend())
    {
        odp.push_front(*i1);
        i1++;
    }
    while(odp.front()==0)
    {
        odp.pop_front();
    }
    return odp;
}

bool is_even(deque<int> x)
{
    auto i=x.rbegin();
    if((*i)%2==0) return 1;
    else return 0;
}

deque<int> divide_by_2(deque<int> x)
{
    auto i=x.begin();
    while(i!=x.end())
    {
        if(*i%2)
        {
            auto i_help=i;
            i_help++;
            *i_help+=10;
        }
        *i=*i/2;
        i++;
    }
    while(x.front()==0)
    {
        x.pop_front();
    }
    return x;
}

deque<int> multiply_by_2(deque<int> x)
{
    auto i=x.rbegin();
    int pom=0;
    while(i!=x.rend())
    {
        int teraz=(*i)*2+pom;
        pom=teraz/10;
        *i=teraz%10;
        i++;
    }
    if(pom!=0) x.push_front(pom);
    return x;
}

deque<int> GCD(deque<int> x1, deque<int> x2) //a=x1 b=x2
{
    // base cases (1)
    if (x1.size() == 0) return x2;
    if (x2.size() == 0) return x1;
    if (x1 == x2) return x1;

    if(is_even(x1))
    {
        if(is_even(x2))  // x1 is even, x2 is even (2)
            return multiply_by_2(GCD(divide_by_2(x1),divide_by_2(x2)));
        else            // x1 is even, x2 is odd (3)
            return GCD (divide_by_2(x1),x2);
    }
    else
    {
        if(is_even(x2)) // x1 is odd, x2 is even (3)
            return GCD(x1,divide_by_2(x2));
        else            // x1 is odd, x2 is odd (4)
        {
            if(cmp(x2,x1))
                return GCD(odejmij(x1,x2),x2);
            else
                return GCD(odejmij(x2,x1),x1);
        }
    }
}
