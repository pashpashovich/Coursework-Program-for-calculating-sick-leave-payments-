#include "Check.h"

void checkChoice(int* x, int a, int b) { // ������� �������� �� ������������ �������� �������� � ��������� �� a �� b
    while (true)
    {
        char st[10000]; // ������ ��������
        char prev = '\0'; // ���������� ��� ����������� �������
        int i = 0; // ������� ��������� ������� ��������
        while (true)
        {
            st[i] = _getch(); // ���� 1 �������
            if ((st[i] == 13) && i != 0) break; // ��������� ���� ������, ���� ����� enter
            if (st[i] == 8 && i > 0) { // ���� ��������, �� ������� ���������� �������
                cout << "\b";
                cout << " ";
                cout << "\b";
                i--;
                continue;
            }
            if (st[i] < 48 || st[i]>57) // ���� �� �����, �� �������� ������� ������ ������
                continue;
            if (st[i] == '0' && prev == '0' && i == 1) continue; // ���� ��� ������ 0 � ������ ������ �����, �� �������� ������� ������ ������
            cout << st[i]; // ���� �� ��, �� ������� ������ ������ �� �����
            prev = st[i]; // ������������ ������ ������ � �����������
            i++; // ��������� � ���������� �������
        }
        st[i] = '\0'; // ����������� ������ ����-������������ 
        if ((atoi(st)) >= a && (atoi(st)) <= b)
        {
            *x = atoi(st); // ���������� ��������������� � ���� int ������
            cout << endl;
            break;
        }
        else cout << "\n������������ ����! ���������� ��� ���)" << endl;
    }
}


    double checkDouble()
    {
        char st[10000]; // ������ ��������
        int i = 0; // ������� ��������� ������� ��������
        char prev = '\0';  // ���������� ��� ����������� �������
        int commas = 0;  // ���������� ��� ���-�� ������� 
        int eshki = 0; // ���������� ��� ���-�� e 
        int minuses = 0; // ���������� ��� ���-�� - 
        int numE = 0; // ���������� ��� ������� ���� � �����
        while (true)
        {
            st[i] = _getch(); // ���� 1 �������
            if (i == 1 && st[i] == 13 && st[0] == '-') continue; // ��������� ���� ������ ���� '-'
            if (st[0] == '-' && st[1] == ',' && st[2] == 13) continue; // ���� -, , �� ��������� 
            if ((st[i] == 13) && i != 0) break; // ��������� ���� ������, ���� ����� enter
            if (st[i] == 8 && i > 0) { // ���� ��������, �� ������� ���������� �������
                cout << "\b";
                cout << " ";
                cout << "\b";
                i--;
                continue;
            }
            if (!(isdigit((unsigned char)st[i]) || st[i] == ',' || st[i] == 'e' || st[i] == 'E' || st[i] == '-')) // ���� �� �����, �� ',', �� 'e', �� '-', �� �������� ������� ������ ������
                continue;
            if (st[0] == '-' && (st[1] == 'e' || st[1] == 'E' || st[1] == '0')) continue; // ���� -�  ��� -0, �� ��������� 
            if (st[i] == ',' && commas == 0) // ���� ������� ������ �� �����, �� �����
                commas++;
            else // ���� �� ������, �� �������� ������� ������ ������
                if (st[i] == ',') continue;
            if ((st[i] == 'e' || st[i] == 'E') && eshki == 0 && i != 0) // ���� e ������ �� ����� � �� �� ������ �����, �� ���������
            {
                numE = -1; // ������� ���� ����������
                eshki++; // ��������� ���-�� ����
            }
            else // � ������ ������� �������� ������
                if (st[i] == 'e' || st[i] == 'E') continue;

            if (!(i > 0 && st[i] == '-' && (prev == 'e' || prev == 'E'))) // ���� '-' ����� e, �� ��
            {
                if (st[i] == '-' && i != 0) continue; // ���� '-' �� �� ������ ����� � �� ����� �, �� �������� ������� ������ ������
            }
            if (st[i] == '0' && prev == '0' && numE == 1) continue; // ���� ��� ������ 0 � ������ ������ ����� ��� ����� �, �� �������� ������� ������ ������
            if (numE == 2 && st[i] == '0' && prev == '0' && st[i - 2] == '-') continue; // ���� ��� ������ 0 � ������ ������ ����� ����� '-' ��� ����� �, �� �������� ������� ������ ������
            prev = st[i]; // ������������ ������ ������ � �����������
            cout << st[i]; // ���� �� ��, �� ������� ������ ������ �� �����
            numE++; // ����������� ������� ����
            i++; // ��������� � ���������� �������
        }
        st[i] = '\0'; // ����������� ������ ����-������������ 
        return atof(st); // ���������� ��������������� � ���� double ������
    }
