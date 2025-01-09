#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class ChangeManager {
protected:
    int change[7]; // 동전 보급 상태
    int coins[7] = { 10000, 5000, 1000, 500, 100, 50, 10 }; // 지폐와 동전 종류

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
        // 현재 시간을 가져오기
        time_t now = time(0);
        char* dt = ctime(&now);
        printSeparator();
        cout << "< 동전 잔량 >\n" << endl;
        for (int i = 0; i < 7; i++) {
            cout << coins[i] << "원: " << change[i] << "개" << endl;
        }
        cout << "\n" << "현재 시간: " << dt << endl; // 현재 시간 출력
    }
    void printSeparator() {
        cout << "--------------------------\n";
    }
};

class MenuManager {
protected:
    vector<int> menuPrices; // 메뉴 가격
    vector<string> menuNames; // 메뉴 이름

public:

    MenuManager() {}

    virtual void setupMenu() = 0; // 가상 함수로 메뉴 설정을 추상화

    void displayMenu() {
        printSeparator();
        cout << "< 음료 메뉴 > \n\n";
        for (size_t i = 0; i < menuNames.size(); i++) {
            cout << menuNames[i] << " (" << menuPrices[i] << "원)" << endl;
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
    vector<int> sales; // 매출 현황
    vector<string> salesNames; // 판매된 음료 이름
    vector<vector<string>> salesTimestamps; // 각 품목별 판매 시간
    vector<int> monthlySales; // 월별 매출

public:
    VendingMachine() :sales(3, 0), monthlySales(12, 0) {}
    void setupMenu() override {
        // 추상 클래스
    }
    void addMonthlySales(int month, int amount) {
        if (month >= 1 && month <= 12) {
            monthlySales[month - 1] += amount;
        }
    }
    bool handleNoChange(vector<int>& coinsReturned, int& paidAmount) {
        // 현재 지폐와 동전 수량을 가져옴
        int man = getNumberOf10000Won();
        int ocheon = getNumberOf5000Won();
        int cheon = getNumberOf1000Won();
        int oback = getNumberOf500Won();
        int back = getNumberOf100Won();
        int osip = getNumberOf50Won();
        int sip = getNumberOf10Won();
        if (calculateChange(paidAmount, coinsReturned)) {
            cout << "거스름돈: ";
            for (size_t i = 0; i < coinsReturned.size(); ++i) {
                if (coinsReturned[i] > 0) {
                    cout << coins[i] << "원: " << coinsReturned[i] << "개 ";
                }
            }
            cout << endl;
            paidAmount = 0;
            return true; // 거스름돈 처리 성공
        }
        else {
            cout << "적절한 거스름돈이 없습니다. 자판기 사용을 중지합니다." << endl;
            int suppliedAmounts[7] = { man, ocheon, cheon, oback, back, osip, sip };
            updateChangeSupplyWithExactAmounts(suppliedAmounts);
            printChangeStatus();
            return false; // 거스름돈 처리 실패
        }
    }

    void validateAndProcessPayment(int& paidAmount) {
        cout << "지불 금액을 입력해주세요 (완료 시 '완료'): " << endl;
        while (true) {
            string input;
            cin >> input;

            // 사용자가 입력 완료를 원할 경우
            if (input == "완료") {
                break;
            }

            try {
                int amount = stoi(input);
                // 입력값에서 1의 자릿수를 제외하고 음수가 아닌지 확인
                amount = amount / 10 * 10;
                if (amount > 0) {
                    paidAmount += amount;
                    updateChangeSupply(amount);
                    cout << "지불 금액이 업데이트 되었습니다: " << paidAmount << "원" << endl;
                }
                else {
                    cout << "10000원, 5000원, 1000원, 500원, 100원, 50원, 10원을 지불하세요 \n" << "지불 금액을 입력해주세요 (완료 시 '완료'): " << endl;
                }
            }
            catch (const invalid_argument&) {
                cout << "잘못된 입력입니다. 지불 금액을 숫자로 입력해주세요: " << endl;
            }
        }
    }
    void updateChangeSupply(int amount) {
        // 1의 자릿수를 제외한 금액으로 동전 보급 상태 업데이트
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
        cout << "\n< 월 매출현황 보고서 >" << endl;
        for (size_t i = 0; i < monthlySales.size(); i++) {
            cout << i + 1 << "월: " << monthlySales[i] << "원" << endl;
            cout << endl;
        }
    }
    virtual void printSalesReport(const string& period) {
        printSeparator();
        cout << "\n" << period << " < 매출현황 보고서 >" << endl;
        for (size_t i = 0; i < sales.size(); i++) {
            cout << salesNames[i] << ": " << sales[i] << "원" << endl;
            // 각 품목별 판매 시간 출력
            for (const string& timestamp : salesTimestamps[i]) {
                cout << "판매 시간: " << timestamp;
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
    int index; // 마지막으로 선택된 음료의 인덱스
    vector<vector<string>> salesTimestamps; // 각 품목별 판매 시간
public:
    BeverageVendingMachine() : VendingMachine(), index(-1) {
        setupMenu(); // 생성자에서 메뉴 설정
        salesTimestamps.resize(menuNames.size()); // 각 품목별 판매 시간을 저장할 벡터의 크기를 메뉴의 수만큼 초기화
    }
    void setupMenu() override {
        // 구체적인 메뉴 항목 설정
        menuNames = { "콜라", "사이다", "물" };
        menuPrices = { 1050, 1240, 800 };
        salesNames = menuNames; 
    }
    void printSalesReport(const string& period) override {
        printSeparator();
        cout << "\n" << period << " < 매출현황 보고서 >" << endl;
        for (size_t i = 0; i < sales.size(); i++) {
            cout << salesNames[i] << ": " << sales[i] << "원" << endl;
            // 각 품목별 판매 시간 출력
            for (const string& timestamp : salesTimestamps[i]) {
                cout << "판매 시간: " << timestamp;
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
            cout << "현재 금액: " << paidAmount << "원\n" << endl;
            printSeparator();
            cout << "< 음료수 선택 > \n" << endl;
            for (size_t i = 0; i < menuNames.size(); i++) {
                if (paidAmount >= menuPrices[i]) {
                    cout << menuNames[i] << " (" << menuPrices[i] << "원)" << endl;
                }
            }
            printSeparator();
            cout << "음료를 선택 하시오. (금액 추가 시 '추가' , 거스름돈 시 '거스름돈', 종료 시 '종료'): ";
            cin >> input;

            if (input == "추가") {
                validateAndProcessPayment(paidAmount);
                continue;
            }
            else if (input == "거스름돈") {
                vector<int> coinsReturned;
                bool success = handleNoChange(coinsReturned, paidAmount);
                if (!success) {
                    break; // 거스름돈 부족으로 인한 프로그램 종료
                }
                continue;
            }
            else if (input == "종료") {
                vector<int> coinsReturned;
                handleNoChange(coinsReturned, paidAmount);
                break; // 프로그램 종료
            }
            int price = getPrice(input);
            if (price != -1) {
                // 음료가 메뉴에 있을 경우
                index = -1;
                for (size_t i = 0; i < menuNames.size(); i++) {
                    if (menuNames[i] == input) {
                        index = i; // 선택된 음료의 인덱스를 업데이트
                        break;
                    }
                }
                if (index != -1 && paidAmount >= price) {
                    time_t now = time(0);
                    char* dt = ctime(&now);
                    salesTimestamps[index].push_back(string(dt)); // 마지막으로 선택한 음료의 판매 시간 추가
                    paidAmount -= price;
                    sales[index] += price; // 마지막으로 선택한 음료의 매출 추가
                    addMonthlySales(month, price); // 월별 매출 추가
                    cout << input << "를 선택하셨습니다. 음료가 나옵니다." << endl;
                }

                else {
                    cout << "금액이 부족합니다. 추가 금액을 입력하세요." << endl;
                }
            }
            else {
                cout << "선택하신 음료는 메뉴에 없습니다. 다시 선택하세요." << endl;
            }
            vector<int> coinsReturned;
            bool success = handleNoChange(coinsReturned, paidAmount);
            if (!success) {
                break; // 거스름돈 부족으로 인한 프로그램 종료
            }
            continue;
        }
    }
    void printSeparator() {
        cout << "--------------------------\n";
    }
};
int main() {
    // 자판기 객체 생성
    BeverageVendingMachine machine;

    // 지폐 및 동전 보급
    machine.supplyChange(10000, 1);
    machine.supplyChange(5000, 1);
    machine.supplyChange(1000, 1);
    machine.supplyChange(500, 1);
    machine.supplyChange(100, 1);
    machine.supplyChange(50, 0);
    machine.supplyChange(10, 200);

    // 저번 달 매출   
    machine.addMonthlySales(1, 447350);
    machine.addMonthlySales(2, 413470);
    machine.addMonthlySales(3, 625160);
    machine.addMonthlySales(4, 524500);

    // 현재 시간을 기반으로 월을 설정
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentMonth = ltm->tm_mon + 1; 

    // 운영: 투입 금액에 따른 구매 가능 음료 출력 및 선택
    machine.selectBeverage(currentMonth); 

    // 매출현황 보고서 출력
    machine.printSalesReport("일일");
    machine.printMonthlySalesReport(); 

    return 0;
}