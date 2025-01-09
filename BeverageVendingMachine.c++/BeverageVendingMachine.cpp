#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class ChangeManager {
protected:
    int change[7]; // ���� ���� ����
    int coins[7] = { 10000, 5000, 1000, 500, 100, 50, 10 }; // ����� ���� ����

public:
    void updateChangeSupplyWithExactAmounts(const int suppliedAmounts[7]) {
        for (int i = 0; i < 7; ++i) {
            change[i] = suppliedAmounts[i];
        }
    }
    ChangeManager() : change{ 0, 0, 0, 0, 0, 0, 0 } {}
    int getNumberOf10000Won() {
        return change[0];
    }
    int getNumberOf5000Won() {
        return change[1];
    }
    int getNumberOf1000Won() {
        return change[2];
    }
    int getNumberOf500Won() {
        return change[3];
    }
    int getNumberOf100Won() {
        return change[4];
    }
    int getNumberOf50Won() {
        return change[5];
    }
    int getNumberOf10Won() {
        return change[6];
    }

    void supplyChange(int denomination, int amount) {
        for (int i = 0; i < 7; ++i) {
            if (denomination == coins[i]) {
                change[i] += amount;
                return;
            }
        }
    }
    void emptyChangeSupply() {
        for (int i = 0; i < 7; ++i) {
            change[i] = 0;
        }
    }
    int getTotalChangeAmount() {
        int totalAmount = 0;
        for (int i = 0; i < 7; ++i) {
            totalAmount += change[i] * coins[i];
        }
        return totalAmount;
    }
    bool calculateChange(int amount, vector<int>& coinsReturned) {
        coinsReturned.assign(7, 0); 
        for (int i = 0; i < 7; ++i) {
            while (amount >= coins[i] && change[i] > 0) {
                amount -= coins[i];
                change[i]--;
                coinsReturned[i]++;
            }
        }
        return amount == 0;
    }
    void printChangeStatus() {
        // ���� �ð��� ��������
        time_t now = time(0);
        char* dt = ctime(&now);
        printSeparator();
        cout << "< ���� �ܷ� >\n" << endl;
        for (int i = 0; i < 7; i++) {
            cout << coins[i] << "��: " << change[i] << "��" << endl;
        }
        cout << "\n" << "���� �ð�: " << dt << endl; // ���� �ð� ���
    }
    void printSeparator() {
        cout << "--------------------------\n";
    }
};

class MenuManager {
protected:
    vector<int> menuPrices; // �޴� ����
    vector<string> menuNames; // �޴� �̸�

public:

    MenuManager() {}

    virtual void setupMenu() = 0; // ���� �Լ��� �޴� ������ �߻�ȭ

    void displayMenu() {
        printSeparator();
        cout << "< ���� �޴� > \n\n";
        for (size_t i = 0; i < menuNames.size(); i++) {
            cout << menuNames[i] << " (" << menuPrices[i] << "��)" << endl;
        }
        printSeparator();
    }

    int getPrice(const string& beverage) {
        for (size_t i = 0; i < menuNames.size(); ++i) {
            if (menuNames[i] == beverage) {
                return menuPrices[i];
            }
        }
        return -1;
    }
    void printSeparator() {
        cout << "--------------------------\n";
    }
};

class VendingMachine : public ChangeManager, public MenuManager {
protected:
    vector<int> sales; // ���� ��Ȳ
    vector<string> salesNames; // �Ǹŵ� ���� �̸�
    vector<vector<string>> salesTimestamps; // �� ǰ�� �Ǹ� �ð�
    vector<int> monthlySales; // ���� ����

public:
    VendingMachine() :sales(3, 0), monthlySales(12, 0) {}
    void setupMenu() override {
        // �߻� Ŭ����
    }
    void addMonthlySales(int month, int amount) {
        if (month >= 1 && month <= 12) {
            monthlySales[month - 1] += amount;
        }
    }
    bool handleNoChange(vector<int>& coinsReturned, int& paidAmount) {
        // ���� ����� ���� ������ ������
        int man = getNumberOf10000Won();
        int ocheon = getNumberOf5000Won();
        int cheon = getNumberOf1000Won();
        int oback = getNumberOf500Won();
        int back = getNumberOf100Won();
        int osip = getNumberOf50Won();
        int sip = getNumberOf10Won();
        if (calculateChange(paidAmount, coinsReturned)) {
            cout << "�Ž�����: ";
            for (size_t i = 0; i < coinsReturned.size(); ++i) {
                if (coinsReturned[i] > 0) {
                    cout << coins[i] << "��: " << coinsReturned[i] << "�� ";
                }
            }
            cout << endl;
            paidAmount = 0;
            return true; // �Ž����� ó�� ����
        }
        else {
            cout << "������ �Ž������� �����ϴ�. ���Ǳ� ����� �����մϴ�." << endl;
            int suppliedAmounts[7] = { man, ocheon, cheon, oback, back, osip, sip };
            updateChangeSupplyWithExactAmounts(suppliedAmounts);
            printChangeStatus();
            return false; // �Ž����� ó�� ����
        }
    }

    void validateAndProcessPayment(int& paidAmount) {
        cout << "���� �ݾ��� �Է����ּ��� (�Ϸ� �� '�Ϸ�'): " << endl;
        while (true) {
            string input;
            cin >> input;

            // ����ڰ� �Է� �ϷḦ ���� ���
            if (input == "�Ϸ�") {
                break;
            }

            try {
                int amount = stoi(input);
                // �Է°����� 1�� �ڸ����� �����ϰ� ������ �ƴ��� Ȯ��
                amount = amount / 10 * 10;
                if (amount > 0) {
                    paidAmount += amount;
                    updateChangeSupply(amount);
                    cout << "���� �ݾ��� ������Ʈ �Ǿ����ϴ�: " << paidAmount << "��" << endl;
                }
                else {
                    cout << "10000��, 5000��, 1000��, 500��, 100��, 50��, 10���� �����ϼ��� \n" << "���� �ݾ��� �Է����ּ��� (�Ϸ� �� '�Ϸ�'): " << endl;
                }
            }
            catch (const invalid_argument&) {
                cout << "�߸��� �Է��Դϴ�. ���� �ݾ��� ���ڷ� �Է����ּ���: " << endl;
            }
        }
    }
    void updateChangeSupply(int amount) {
        // 1�� �ڸ����� ������ �ݾ����� ���� ���� ���� ������Ʈ
        amount = amount / 10 * 10;
        for (int i = 0; i < 7; i++) {
            while (amount >= coins[i]) {
                amount -= coins[i];
                change[i]++;
            }
        }
    }

    void printMonthlySalesReport() {
        printSeparator();
        cout << "\n< �� ������Ȳ ���� >" << endl;
        for (size_t i = 0; i < monthlySales.size(); i++) {
            cout << i + 1 << "��: " << monthlySales[i] << "��" << endl;
            cout << endl;
        }
    }
    virtual void printSalesReport(const string& period) {
        printSeparator();
        cout << "\n" << period << " < ������Ȳ ���� >" << endl;
        for (size_t i = 0; i < sales.size(); i++) {
            cout << salesNames[i] << ": " << sales[i] << "��" << endl;
            // �� ǰ�� �Ǹ� �ð� ���
            for (const string& timestamp : salesTimestamps[i]) {
                cout << "�Ǹ� �ð�: " << timestamp;
            }
            cout << endl;
        }
    }
    void printSeparator() {
        cout << "--------------------------\n";
    }
};

class BeverageVendingMachine : public VendingMachine {
private:
    int index; // ���������� ���õ� ������ �ε���
    vector<vector<string>> salesTimestamps; // �� ǰ�� �Ǹ� �ð�
public:
    BeverageVendingMachine() : VendingMachine(), index(-1) {
        setupMenu(); // �����ڿ��� �޴� ����
        salesTimestamps.resize(menuNames.size()); // �� ǰ�� �Ǹ� �ð��� ������ ������ ũ�⸦ �޴��� ����ŭ �ʱ�ȭ
    }
    void setupMenu() override {
        // ��ü���� �޴� �׸� ����
        menuNames = { "�ݶ�", "���̴�", "��" };
        menuPrices = { 1050, 1240, 800 };
        salesNames = menuNames; 
    }
    void printSalesReport(const string& period) override {
        printSeparator();
        cout << "\n" << period << " < ������Ȳ ���� >" << endl;
        for (size_t i = 0; i < sales.size(); i++) {
            cout << salesNames[i] << ": " << sales[i] << "��" << endl;
            // �� ǰ�� �Ǹ� �ð� ���
            for (const string& timestamp : salesTimestamps[i]) {
                cout << "�Ǹ� �ð�: " << timestamp;
            }
            cout << endl;
        }
    }
    void selectBeverage(int month) {
        int paidAmount = 0;
        string input;

        displayMenu();
        validateAndProcessPayment(paidAmount);

        while (paidAmount >= 0) {
            printChangeStatus();
            displayMenu();
            printSeparator();
            cout << "���� �ݾ�: " << paidAmount << "��\n" << endl;
            printSeparator();
            cout << "< ����� ���� > \n" << endl;
            for (size_t i = 0; i < menuNames.size(); i++) {
                if (paidAmount >= menuPrices[i]) {
                    cout << menuNames[i] << " (" << menuPrices[i] << "��)" << endl;
                }
            }
            printSeparator();
            cout << "���Ḧ ���� �Ͻÿ�. (�ݾ� �߰� �� '�߰�' , �Ž����� �� '�Ž�����', ���� �� '����'): ";
            cin >> input;

            if (input == "�߰�") {
                validateAndProcessPayment(paidAmount);
                continue;
            }
            else if (input == "�Ž�����") {
                vector<int> coinsReturned;
                bool success = handleNoChange(coinsReturned, paidAmount);
                if (!success) {
                    break; // �Ž����� �������� ���� ���α׷� ����
                }
                continue;
            }
            else if (input == "����") {
                vector<int> coinsReturned;
                handleNoChange(coinsReturned, paidAmount);
                break; // ���α׷� ����
            }
            int price = getPrice(input);
            if (price != -1) {
                // ���ᰡ �޴��� ���� ���
                index = -1;
                for (size_t i = 0; i < menuNames.size(); i++) {
                    if (menuNames[i] == input) {
                        index = i; // ���õ� ������ �ε����� ������Ʈ
                        break;
                    }
                }
                if (index != -1 && paidAmount >= price) {
                    time_t now = time(0);
                    char* dt = ctime(&now);
                    salesTimestamps[index].push_back(string(dt)); // ���������� ������ ������ �Ǹ� �ð� �߰�
                    paidAmount -= price;
                    sales[index] += price; // ���������� ������ ������ ���� �߰�
                    addMonthlySales(month, price); // ���� ���� �߰�
                    cout << input << "�� �����ϼ̽��ϴ�. ���ᰡ ���ɴϴ�." << endl;
                }

                else {
                    cout << "�ݾ��� �����մϴ�. �߰� �ݾ��� �Է��ϼ���." << endl;
                }
            }
            else {
                cout << "�����Ͻ� ����� �޴��� �����ϴ�. �ٽ� �����ϼ���." << endl;
            }
            vector<int> coinsReturned;
            bool success = handleNoChange(coinsReturned, paidAmount);
            if (!success) {
                break; // �Ž����� �������� ���� ���α׷� ����
            }
            continue;
        }
    }
    void printSeparator() {
        cout << "--------------------------\n";
    }
};
int main() {
    // ���Ǳ� ��ü ����
    BeverageVendingMachine machine;

    // ���� �� ���� ����
    machine.supplyChange(10000, 1);
    machine.supplyChange(5000, 1);
    machine.supplyChange(1000, 1);
    machine.supplyChange(500, 1);
    machine.supplyChange(100, 1);
    machine.supplyChange(50, 0);
    machine.supplyChange(10, 200);

    // ���� �� ����   
    machine.addMonthlySales(1, 447350);
    machine.addMonthlySales(2, 413470);
    machine.addMonthlySales(3, 625160);
    machine.addMonthlySales(4, 524500);

    // ���� �ð��� ������� ���� ����
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentMonth = ltm->tm_mon + 1; 

    // �: ���� �ݾ׿� ���� ���� ���� ���� ��� �� ����
    machine.selectBeverage(currentMonth); 

    // ������Ȳ ���� ���
    machine.printSalesReport("����");
    machine.printMonthlySalesReport(); 

    return 0;
}