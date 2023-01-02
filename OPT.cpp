#include <iostream>

using namespace std;

int main()
{
    int n, f;

    cout << "Nhap so trang: ";
    cin >> n;
    int *seq = new int[n];
    cout << "Nhap chuoi trang: ";
    for(int i = 0; i < n; i++)
    {
        cin >> seq[i];
    }

    cout << "Nhap so khung trang";
    cin >> f;
    // Tao mang 2 chieu = -1
    int **table = new int*[n];
    for(int i = 0; i < n; i++)
    {
        table[i] = new int[f];
    }
    for(int i = 0; i<n;i++)
    {
        for(int j = 0; j < f; j++)
        {
            table[i][j] = -1;
        }
    }

    string *page_fault = new string[n] ;// Co loi trang hay khong: Y or N

    table[0][0] = seq[0];
    page_fault[0] = "Yes";
    int i = 1;
    int count_first = 1; // su ly K fame dau tien
    for(int i = 1; i < n; i++)
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
                            if(table[i][j] == -1) count++;
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
                                if(table[i][j] == -1)
                                    table[i][j] = seq[i];
                            }
                            break;
                        }
                    }
                }

            }
        }
    }
    // xuất bảng
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << seq[i] << "   ";
    }

    cout << endl;
    for(int j = 0; j < f; j++)
    {
        for(int i = 0; i < n; i++)
        {
            cout << table[i][j] << "   ";
        }
        cout << endl;
    }
    for(int i = 0; i < n; i++)
    {
        cout << page_fault[i] << "  ";
    }

    return 0;
}
// 1 2 3 4 2 1 5 6 2 1 2 3 7 6 3 2 1 2 3 6
//
