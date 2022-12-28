/*
 * Team: WINter
 * Course: IT007.N11
 * File: Lab6
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int no_frames; // number of frames
int no_items; // number of items in the sequence 

int* manual_input();
int* create_default_seq();
void illustrate_FIFO(int *Seq, int frames, int pages);
void illustrate_OPT(int *Seq, int frames, int pages);
void illustrate_LRU(int *Seq, int frames, int pages);

int main()
{
    int choice;
    // start-up interface
    cout << "\n--- Page Replacement algorithm ---";
    cout << "\n1. Default referenced sequence";
    cout << "\n2. Manual input sequence";
    do {
        cout << "\nYour choice (1 or 2): ";
        cin >> choice;
    } while (choice != 1 && choice != 2);

    do {
        cout << "\nInput number of page frames (> 0): ";
        cin >> no_frames;
    } while (no_frames <= 0);

    // create sequence 
    int *seq = NULL;
    if (choice == 1)
    {
        seq = create_default_seq();
    }
    else if (choice == 2)
    {
        seq = manual_input();
    }

    // choose algorithm 
    cout << "\n1. FIFO algorithm";
    cout << "\n2. OPT algorithm";
    cout << "\n3. LRU algorithm";
    do {
        cout << "\nYour choice (1-3): ";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    system("cls");
    cout << "\n--- Page Replacement algorithm ---";
    cout << "\nReference sequence: ";
    for (int i = 0; i < no_items; i++)
        cout << seq[i] << " ";
    if (choice == 1)
    {
        illustrate_FIFO(seq, no_frames, no_items);
    }
    else if (choice == 2)
    {
        illustrate_OPT(seq, no_frames, no_items);
    }
    else if (choice == 3)
    {
        illustrate_LRU(seq, no_frames, no_items);
    }
    return 0;
}

int* manual_input()
{
    // input number of items in the sequence
    do {
        cout << "\nInput number of items (>= 0): ";
        cin >> no_items;
    } while (no_items < 0);

    // input sequence number
    cout << "\nInput items: ";
    int *seq = new int[no_items];
    float temp; 
    for (int i = 0; i < no_items; i++)
    {
        // make sure all items in seq is unsigned int 
        do {
            cin >> temp;
            if (temp < 0)
            {
                cout << "\nError: value must be UNSIGNED INT! Error value = " << temp;
            }
            else if (temp != round(temp))
            {
                cout << "\nError: value must be UNSIGNED INT! Error value = " << temp;
            }
            else 
                break;
            cout << "\nIgnore value\n";
        } while (true);
        seq[i] = temp;
    }

    return seq;
}

int* create_default_seq()
{
    int *seq = NULL;
    // input student ID
    string studentID;
    cout << "\nInput your student ID: ";
    cin >> studentID;
    studentID += "007";

    // parse items in student ID string and create sequence
    no_items = studentID.length();
    seq = new int[no_items];
    for (int i = 0; i < no_items; i++)
    {
        seq[i] = studentID[i] - '0'; // convert char to int
    }

    return seq;
}

void illustrate_FIFO(int *Seq, int frames, int pages)
{
    cout << "\nFIFO algorithm\n";
    int temp[frames];
    int pagefaults = 0, index = 0;
    cout<<"Page\tFrame 1\tFrame 2\tFrame 3\tPage Fault"<<endl;
    for (int i = 0; i < frames; i++) temp[i] = -1;
    for (int i = 0; i < pages; i++)
    {
        int t = 0;
        bool check = false;
        for (int j = 0; j < frames; j++) if (Seq[i] == temp[j]) t++;
        if (t == 0)
        {
            if (pagefaults < frames) temp[index++] = Seq[i];
            else
            {
                temp[index%frames] = Seq[i];
                index++;
            }
            check = true;
            pagefaults++;
        }
        cout<<Seq[i]<<"\t";
        for (int i = 0; i < frames; i++)
        {
            if(temp[i] != -1) cout<<temp[i]<<"\t";
            else cout<<"-\t";
        }
        if (check) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    cout<<"The number of pagefaults: "<<pagefaults;
}

void illustrate_LRU(int *Seq, int frames, int pages)
{
    cout << "\nLRU algorithm\n";
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
}

void illustrate_OPT(int *Seq, int frames, int pages)
{
    cout << "\nOPT algorithm\n";
}