# 🥤 Beverage Vending Machine Program

## 🌟 소개
이 프로젝트는 음료 자판기의 동작을 시뮬레이션하는 C++ 기반 프로젝트입니다.  
사용자는 금액을 투입하고 음료를 선택하여 구매할 수 있으며 <br>거스름돈 처리, 지폐 및 동전 보급, 월별 매출 관리 기능을 제공합니다.  
프로그램은 다양한 음료 메뉴와 지폐/동전 관리를 통해 현실적인 자판기 시스템을 구현합니다.

---

## 🔑 주요 기능
### 1️⃣ 메뉴 관리
- 📝 음료 메뉴와 가격을 설정하고, 사용자가 선택할 수 있도록 출력합니다.
- 🛠️ 메뉴는 생성자에서 초기화되며, 메뉴 항목과 가격을 동적으로 변경할 수 있습니다.

### 2️⃣ 금액 투입 및 검증
- 💰 사용자는 10원부터 10,000원까지 다양한 지폐 및 동전을 투입할 수 있습니다.
- 🚨 잘못된 금액(1의 자리 금액)을 입력하거나 유효하지 않은 입력을 할 경우 예외 처리를 통해 다시 입력받습니다.
- ✅ 사용자가 입력한 금액을 기반으로 구매 가능한 음료를 출력합니다.

### 3️⃣ 음료 선택 및 구매
- 🛒 사용자는 금액을 투입한 후 구매 가능한 음료를 선택할 수 있습니다.
- 💸 선택한 음료의 가격이 투입한 금액보다 적거나 같을 경우 구매가 완료되며, 매출에 반영됩니다.
- 📋 구매한 음료와 구매 시간을 기록하여 일일 매출 보고서에 포함시킵니다.

### 4️⃣ 거스름돈 처리
- 💵 사용자가 거스름돈을 요청할 경우 자판기에 보유한 동전과 지폐를 사용하여 거스름돈을 반환합니다.
- ❌ 반환할 금액이 자판기 내 보유한 동전과 지폐로 정확히 처리할 수 없는 경우, 거스름돈 부족 메시지를 출력하고 자판기 운영을 중지합니다.

### 5️⃣ 매출 관리
- 📊 월별 매출을 관리하며, 현재 월과 지난 달의 매출 보고서를 출력합니다.
- 📆 일일 매출과 판매된 음료의 판매 시간도 함께 출력됩니다.

---

## 🛠️ 클래스 설명
### `ChangeManager`
- 🏦 지폐 및 동전 보급 상태를 관리하는 클래스입니다.
- 🧾 동전 보급, 거스름돈 반환, 동전 잔량 출력 기능을 제공합니다.
- **주요 메서드**:
  - `supplyChange`: 특정 지폐 또는 동전을 보급합니다.
  - `calculateChange`: 거스름돈을 계산하고 반환합니다.
  - `printChangeStatus`: 현재 동전 보급 상태를 출력합니다.

### `MenuManager`
- 🍹 자판기 메뉴(음료 이름과 가격)를 관리하는 클래스입니다.
- **주요 메서드**:
  - `setupMenu`: 메뉴 이름과 가격을 설정합니다.
  - `displayMenu`: 현재 설정된 메뉴와 가격을 출력합니다.
  - `getPrice`: 사용자가 선택한 음료의 가격을 반환합니다.

### `VendingMachine`
- `ChangeManager`와 `MenuManager`를 상속받아 자판기 전체 동작을 관리하는 클래스입니다.
- **주요 메서드**:
  - `validateAndProcessPayment`: 사용자로부터 금액을 입력받고 검증합니다.
  - `handleNoChange`: 거스름돈 반환을 처리합니다.
  - `printSalesReport`: 일일 매출 보고서를 출력합니다.
  - `printMonthlySalesReport`: 월별 매출 보고서를 출력합니다.

### `BeverageVendingMachine`
- `VendingMachine`을 상속받아 구체적인 음료 메뉴와 매출 관리를 담당하는 클래스입니다.
- **주요 메서드**:
  - `setupMenu`: 음료 이름과 가격을 설정합니다.
  - `selectBeverage`: 사용자가 금액을 투입한 후 음료를 선택하고 구매할 수 있도록 처리합니다.

---

## 📂 파일 설명
- **`main.cpp`**: 프로그램의 메인 파일로, 자판기 객체를 생성하고 운영하는 코드를 포함합니다.
- **`ChangeManager`**: 지폐 및 동전 관리를 위한 클래스를 정의합니다.
- **`MenuManager`**: 음료 메뉴 관리를 위한 클래스를 정의합니다.
- **`VendingMachine`**: 자판기의 전체 동작을 관리하는 클래스를 정의합니다.
- **`BeverageVendingMachine`**: 구체적인 음료 자판기의 동작을 구현하는 클래스를 정의합니다.
