class DataHandler():

    def __init__(self):
        self.data = []
    def insert_data(self, key, value):
        self.data.append( f"{key}: {value}")

    def retrieve_data(self, index):
        return self.data[index]

    def display_data(self):
        print("Data in the database:")
        for current_index in self.data:
            print(f"{current_index=}")

class DataProcessor:
    def __init__(self):
        self.department_list = []
        self.text_list = []
    def add_data(self, name, department):
        self.department_list.append({"name" : name, "department" : department})


    def count_people_in_department(self, department):
        count = sum(1 for person in self.department_list if person['department'] == department)
        return count

    def count_indexes_in_text(self):
        return len(self.text_list)