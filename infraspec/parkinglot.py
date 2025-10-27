from datetime import datetime

class Vehicle():
    def __init__(self, license_plate, vehicle_type):
        self.license_plate = license_plate
        self.type = vehicle_type

    def get_license_plate(self):
        return self.license_plate

    def get_type(self):
        return self.type

class Car(Vehicle):
    def __init__(self, license_plate):
        super().__init__(license_plate, "CAR")

class Motorcycle(Vehicle):
    def __init__(self, license_plate):
        super().__init__(license_plate, "MOTORCYCLE")

class ParkingSpot:
    def __init__(self, spot_number, spot_type):
        self.spot_number = spot_number
        self.type = spot_type
        self.is_occupied = False
        self.parked_vehicle = None

    def is_available(self):
        return not self.is_occupied
    
    def park(self, v):
        self.parked_vehicle = v
        self.is_occupied = True

    def unpark(self):
        self.parked_vehicle = None
        self.is_occupied = False
    
    def get_type(self):
        return self.type
        
    def get_spot_number(self):
        return self.spot_number

class ParkingTicket:
    def __init__(self, license_plate, spot_number):
        self.ticket_id = f"{license_plate}_{int(datetime.now().timestamp())}"
        self.license_plate = license_plate
        self.spot_number = spot_number
        self.issue_time = datetime.now()
    
    def get_ticket_id(self):
        return self.ticket_id

class ParkingLot:
    def __init__(self, compact_spots, large_spots, motorbike_spots):
        self.spots = []
        self.active_tickets = {}
        
        current_spot_num = 1
        
        for i in range(compact_spots):
            self.spots.append(ParkingSpot(current_spot_num, "COMPACT"))
            current_spot_num += 1
            
        for i in range(large_spots):
            self.spots.append(ParkingSpot(current_spot_num, "LARGE"))
            current_spot_num += 1
            
        for i in range(motorbike_spots):
            self.spots.append(ParkingSpot(current_spot_num, "MOTORBIKE"))
            current_spot_num += 1

    def park_vehicle(self, vehicle):
        available_spot = self.find_available_spot(vehicle.get_type())
        
        if available_spot:
            available_spot.park(vehicle)
            ticket = ParkingTicket(vehicle.get_license_plate(), available_spot.get_spot_number())
            self.active_tickets[ticket.get_ticket_id()] = ticket
            print(f"Vehicle {vehicle.get_license_plate()} parked successfully in spot {available_spot.get_spot_number()}.")
            return ticket
        
        print(f"Sorry, no available spot for vehicle type: {vehicle.get_type()}")
        return None

    def unpark_vehicle(self, ticket_id):
        if ticket_id in self.active_tickets:
            print(f"Vehicle with ticket {ticket_id} unparked.")
            del self.active_tickets[ticket_id]
        else:
            print("Invalid ticket ID.")

    def find_available_spot(self, vehicle_type):
        for spot in self.spots:
            if spot.is_available() and self.can_vehicle_fit(vehicle_type, spot.get_type()):
                return spot
        return None

    def can_vehicle_fit(self, v_type, s_type):
        if v_type == "MOTORCYCLE":
            return s_type == "MOTORBIKE"
        if v_type == "CAR":
            return s_type == "COMPACT" or s_type == "LARGE"
        if v_type == "TRUCK":
            return s_type == "LARGE"
        return False

if __name__ == "__main__":
    lot = ParkingLot(compact_spots=1, large_spots=1, motorbike_spots=1)
    
    my_car = Car("KA-01-1234")
    my_motorcycle = Motorcycle("TN-02-5678")
    
    ticket1 = lot.park_vehicle(my_car) 
    
    another_car = Car("KL-03-9012")
    lot.park_vehicle(another_car)
    
    ticket2 = lot.park_vehicle(my_motorcycle)

    if ticket1:
        lot.unpark_vehicle(ticket1.get_ticket_id())
        
    lot.park_vehicle(another_car)