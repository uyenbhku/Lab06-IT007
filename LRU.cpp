#include <iostream>

using namespace std;

int main()
{
    int pages;
    cout<<"Enter the number of pages: "; cin>>pages;
    int Seq[pages];
    cout<<"Enter sequence number: ";
    for (int i = 0; i < pages; i++) cin>>Seq[i];
    int frames;
    cout<<"Enter frame: "; cin>>frames;
    int temp[frames], state[frames];
    int pagefaults = 0, index = 0;
    cout<<"Page\tFrame 1\tFrame 2\tFrame 3\tPage Fault"<<endl;
    for (int i = 0; i < frames; i++)
    {
        temp[i] = -1;
        state[i] = -1;
    }
    for (int i = 0; i < pages; i++)
    {
        cout<<Seq[i]<<"\t";
        int t = 0;
        bool check = false;
        for (int j = 0; j < frames; j++) if (Seq[i] == temp[j]) t++;
        if (t == 0)
        {
            if (pagefaults < frames)
            {
                temp[index] = Seq[i];
                state[index++] = i;
            }
            else
            {
                int min = 0;
                for (int j = 0; j < frames; j++) if (state[j] < state[min]) min = j;
                temp[min] = Seq[i];
                state[min] = i;
            }
            check = true;
            pagefaults++;
        }
        else for (int j = 0; j < frames; j++) if (temp[j] == Seq[i]) state[j] = i;
        for (int i = 0; i < frames; i++)
        {
            if(temp[i] != -1) cout<<temp[i]<<"\t";
            else cout<<"-\t";
        }
        if (check) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    cout<<"The number of pagefaults: "<<pagefaults;
    return 0;
}
