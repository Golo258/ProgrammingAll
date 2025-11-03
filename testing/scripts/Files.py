

import json


def clear(name_of_collection):
    print("------------------------------------------------------------\n")
    print(name_of_collection)
    
    

def normal_files():
    
    with open("Files/regular.txt", "a") as file:
        file.write("Hello, World!")
    
    with open("Files/regular.txt", "r") as file:
        content = file.read()
        print(content)
    
def json_files():
    # load is loading the content of file 
    # loads is loading a string which contains json inside or a dictionary
    with open("Files/json_file.json", "r") as json_file:
        data = json.load(json_file)
        print(data)
        
    changed_json = {"name": "Alice", "age": 30}
    # dump is updating / creating a files based on string / dict
    # dumps is converting an object into a json string 
    with open("Files/json_file.json", "w") as json_file:
        json.dump(changed_json, json_file)

if __name__ == "__main__":
    clear("Normal")
    normal_files()
    clear("Json")
    json_files()
    
    