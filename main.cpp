/*
 * Team: WINter
 * Course: IT007.N11
 * File: Lab6
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime> // for benchmark
using namespace std;

#define EMPTY_PAGE -1

int no_frames = 0; // number of frames
int no_pages = 0; // number of pages in the sequence 

int* manual_input();
int* create_default_seq();
void illustrate_FIFO(int *Seq, int frames, int pages);
void illustrate_OPT(int *seq, int f, int n);
void illustrate_LRU(int *Seq, int frames, int pages);

int main()
{
    int choice;
    enum input_choices {DEFAULT_INPUT_CHOICE = 1, MANUAL_INPUT_CHOICE};
    // start-up interface
    cout << "\n--- Page Replacement algorithm ---";
    cout << "\n1. Default referenced sequence";
    cout << "\n2. Manual input sequence";
    do {
        cout << "\nYour choice (1 or 2): ";
        cin >> choice;
    } while (choice != DEFAULT_INPUT_CHOICE && choice != MANUAL_INPUT_CHOICE);

    do {
        cout << "\nInput number of page frames (> 0): ";
        cin >> no_frames;
    } while (no_frames <= 0);

    int *seq = NULL; // page sequence 
    // create/input sequence 
    if (choice == DEFAULT_INPUT_CHOICE)
    {
        seq = create_default_seq();
    }
    else if (choice == MANUAL_INPUT_CHOICE)
    {
        seq = manual_input();
    }

    enum algo_choices {FIFO_CHOICE = 1, OPT_CHOICE, LRU_CHOICE};
    // choose algorithm 
    cout << "\n1. FIFO algorithm";
    cout << "\n2. OPT algorithm";
    cout << "\n3. LRU algorithm";
    do {
        cout << "\nYour choice (1-3): ";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    //system("cls");
    cout << "\n--- Page Replacement algorithm ---";
    cout << "\nReference sequence: ";
    for (int i = 0; i < no_pages; i++)
        cout << seq[i] << " ";
    if (choice == FIFO_CHOICE)
    {
        // benchmark
        clock_t startT = clock(); // start time

        illustrate_FIFO(seq, no_frames, no_pages);
        
        clock_t endT = clock(); // end time
        cout << "\nTime executing the given test with FIFO: " << ((double)endT - startT)/CLOCKS_PER_SEC << " seconds" ;

    }
    else if (choice == OPT_CHOICE)
    {
        // benchmark
        clock_t startT = clock(); // start time

        illustrate_OPT(seq, no_frames, no_pages);
        
        clock_t endT = clock(); // end time
        cout << "\nTime executing the given test with OPT: " << ((double)endT - startT)/CLOCKS_PER_SEC << " seconds" ;

    }
    else if (choice == LRU_CHOICE)
    {
        // benchmark 
        clock_t startT = clock(); // start time

        illustrate_LRU(seq, no_frames, no_pages);

        clock_t endT = clock(); // end time
        cout << "\nTime executing the given test with LRU: " << ((double)endT - startT)/CLOCKS_PER_SEC << " seconds" ;
    }
    return 0;
}


int* manual_input()
{
    // input number of pages in the sequence
    do {
        cout << "\nInput number of pages (>= 0): ";
        cin >> no_pages;
    } while (no_pages < 0);

    // input sequence number
    cout << "\nInput reference sequence (each page is separated by a space ' '): ";
    int *seq = new int[no_pages];
    float temp; 
    for (int i = 0; i < no_pages; i++)
    {
        // make sure all pages in seq are unsigned int 
        do {
            cin >> temp;
            if (temp < 0)
            {
                cout << "\nError: value must be UNSIGNED INT!";
            }
            else if (temp != round(temp))
            {
                cout << "\nError: value must be UNSIGNED INT!";
            }
            else 
                break;
            cout << "\nIgnore value " << temp << endl;
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

    // parse pages from studentID string and create sequence
    no_pages = studentID.length();
    seq = new int[no_pages];
    int ctoi_value = 0;   // value after convert char to int
    for (int i = 0; i < no_pages; i++)
    {
        ctoi_value = studentID[i] - '0';
        // handle invalid digit
        if (ctoi_value < 0 || ctoi_value > 9) // not a number 
        {
            cout << "\nError: Invalid digit, cannot convert char '" << studentID[i] << "' to int. End parsing...";
            no_pages = i; // update new number of pages at where the error happened 
            cout << "\nNew number of pages: " << no_pages << endl;
            break; // end parsing at the time error happened 
        } 
        seq[i] = ctoi_value; // convert char to int
    }

    return seq;
}


// @author: Nguyen Nguyen Giap 
void illustrate_FIFO(int *Seq, int frames, int pages)
{
    cout << "\nFIFO algorithm\n";

    int temp[frames];
    int pagefaults = 0, index = 0;
    // initialize 
    for (int i = 0; i < frames; i++) temp[i] = EMPTY_PAGE;

    // computing and printing 
    cout<<"Page\t";
    for (int i = 0; i < frames; i++)
    {
        cout << "Frame " << i+1 << "\t";
    }
    cout << "Page Fault" << endl;
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
        cout << Seq[i] << "\t";
        for (int i = 0; i < frames; i++)
        {
            if (temp[i] != EMPTY_PAGE) cout << temp[i] << "\t";
            else cout << "-\t";
        }
        if (check) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    cout << "The number of pagefaults: " << pagefaults;
}


// @author: Nguyen Nguyen Giap 
void illustrate_LRU(int *Seq, int frames, int pages)
{
    cout << "\nLRU algorithm\n";

    int temp[frames], state[frames];
    int pagefaults = 0, index = 0;
    // initialize 
    for (int i = 0; i < frames; i++)
    {
        temp[i] = EMPTY_PAGE;
        state[i] = -1;
    }

    // computing and printing 
    cout<<"Page\t";
    for (int i = 0; i < frames; i++)
    {
        cout<<"Frame "<<i+1<<"\t";
    }
    cout<<"Page Fault"<<endl;
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
            if (temp[i] != EMPTY_PAGE) cout << temp[i] << "\t";
            else cout << "-\t";
        }
        if (check) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    cout<<"The number of pagefaults: "<<pagefaults;
}


// @author: Nguyen Thi Thuy
void illustrate_OPT(int *seq, int f, int n)
{
    cout << "\nOPT algorithm\n";

    // Tao mang 2 chieu = -1
    int **table = new int*[n];
    for(int i = 0; i < n; i++)
    {
        table[i] = new int[f];
    }
    // initialize
    for(int i = 0; i<n;i++)
    {
        for(int j = 0; j < f; j++)
        {
            table[i][j] = EMPTY_PAGE;
        }
    }

    string *page_fault = new string[n] ;// Co loi trang hay khong: Y or N

    // computing and printing 
    cout<<"Page\t";
    for (int i = 0; i < f; i++)
    {
        cout<<"Frame "<<i+1<<"\t";
    }
    cout<<"Page Fault"<<endl;

    int i = 0;
    table[0][i] = seq[i];
    page_fault[i] = "Yes";

    cout << seq[i] << "\t";
    for (int j = 0; j < f; j++)
    {
        if (table[i][j] != EMPTY_PAGE) cout << table[i][j] << "\t";
        else cout << "-\t";
    }
    cout<<page_fault[i]<<endl;

    int no_pagefaults = 1; // dem so page faults

    int count_first = 1; // xu ly K frames dau tien
    for(i=i+1; i < n; i++)
    {
        bool flag = true ;// kiem tra co xay ra loi trang hay khong
        for(int j = 0; j < f; j++)
        {
            if(table[i-1][j] == seq[i])
            {
                flag = false;
                break;
            }
        }

        if(flag == false) // khong xay ra loi trang thi sao chep cot cua table
        {
            for(int j = 0; j < f; j++)
            {
                table[i][j] = table[i-1][j];
            }
            page_fault[i] = "No";

        }
        else // co xay ra loi trang
        {
            page_fault[i] = "Yes";
            no_pagefaults++; // cap nhat so page faults 
            
            if (count_first < f) // khong can thay the trang
            {
                table[i][count_first] = seq[i];
                for(int j = 0; j < count_first; j++)
                {
                    table[i][j] = table[i-1][j];
                }
                count_first++;
            }
            else // Phai thay the trang
            {
                bool flag1;  // kiem tra table[i-1][j] co duoc su dung trong tuong lai khong
                for(int j = 0; j < f; j++)
                {
                    flag1 = false;
                    for(int k = i+1; k<n;k++)
                    {
                        if(seq[k] == table[i-1][j])
                        {
                            flag1 = true;
                            break;
                        }
                    }
                    if (flag1 == false) // khoong dung trong tuong lai nua thi chon trang nay de thay
                    {
                        for(int l = 0; l < f; l++) // giu nguyen cac trang con lai
                        {
                            table[i][l] = table[i-1][l];
                        }
                        table[i][j] = seq[i];
                        break;
                    }
                }

                if(flag1 == true) // flag1 = false chung to chua thay trang (vi all cac page deu duoc su dung trong tuong lai,
                        // di kiem page lau duoc su dung nhat
                {
                    for(int k = i+1; k<n;k++)
                    {
                        int count = 0;
                        for(int j = 0; j<f; j++)
                        {
                            if(table[i][j] == EMPTY_PAGE) count++;
                        }
                        if(count > 1)
                        {
                            for(int j = 0; j<f; j++)
                            {
                                if(table[i-1][j] == seq[k])
                                {
                                    table[i][j] = seq[k];
                                    break;
                                }
                            }
                        }
                        else
                        {
                            for(int j = 0; j<f; j++)
                            {
                                cout << table[i][j];
                                if(table[i][j] == EMPTY_PAGE)
                                    table[i][j] = seq[i];
                            }
                            break;
                        }
                    }
                }

            }
        }

        cout << seq[i] << "\t";
        for (int j = 0; j < f; j++)
        {
            if (table[i][j] != EMPTY_PAGE) cout << table[i][j] << "\t";
            else cout << "-\t";
        }
        cout<<page_fault[i]<<endl;
    }
    cout<<"The number of pagefaults: "<<no_pagefaults;
}