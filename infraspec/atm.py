from datetime import datetime
import random

class Card:
    def __init__(self, card_number, pin):
        self.card_number = card_number
        self.pin = pin
    
    def get_card_number(self):
        return self.card_number
    
    def get_pin(self):
        return self.pin

class BankAccount:
    def __init__(self, account_number, balance):
        self.account_number = account_number
        self.balance = balance
    
    def get_balance(self):
        return self.balance
    
    def withdraw(self, amount):
        self.balance = self.balance - amount

class HDFCBankService:
    def authenticate(self, card_number, pin):
        print("HDFC Bank is authenticating...")
        return True 

    def check_balance(self, card_number):
        print("HDFC Bank is checking balance...")
        return 1000.00 

    def withdraw(self, card_number, amount):
        print(f"HDFC Bank is processing withdrawal of {amount}")

class Transaction:
    def __init__(self):
        self.transaction_id = int(random.random() * 1000)
        self.date = datetime.now()

class Withdrawal(Transaction):
    def __init__(self, amount):
        super().__init__()
        self.amount = amount

class ATM:
    def __init__(self, bank_service):
        self.bank_service = bank_service
        self.current_card = None
        self.is_authenticated = False

    def insert_card(self, card):
        self.current_card = card
        print("Card inserted. Please enter PIN.")

    def enter_pin(self, pin):
        if self.current_card is None:
            print("Please insert a card first.")
            return
        
        if self.bank_service.authenticate(self.current_card.get_card_number(), pin):
            self.is_authenticated = True
            print("Authentication successful.")
        else:
            print("Invalid PIN.")
            self.eject_card()

    def withdraw_money(self, amount):
        if not self.is_authenticated:
            print("Please authenticate first.")
            return
        
        balance = self.bank_service.check_balance(self.current_card.get_card_number())
        
        if balance >= amount:
            self.bank_service.withdraw(self.current_card.get_card_number(), amount)
            print("Please collect your cash.")
        else:
            print("Insufficient funds.")
        
        self.eject_card()
    
    def eject_card(self):
        self.current_card = None
        self.is_authenticated = False
        print("Card ejected. Thank you.")

# --- Example Usage ---
if __name__ == "__main__":
    
    my_bank = HDFCBankService()
    atm = ATM(my_bank)
    
    my_card = Card("123456789", "1234")
    
    print("--- Transaction 1 (Success) ---")
    atm.insert_card(my_card)
    atm.enter_pin("1234")
    atm.withdraw_money(500)
    
    print("\n--- Transaction 2 (Fail) ---")
    atm.insert_card(my_card)
    atm.enter_pin("1234")
    atm.withdraw_money(2000)