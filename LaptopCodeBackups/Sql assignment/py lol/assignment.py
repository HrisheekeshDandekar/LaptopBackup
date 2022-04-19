################## Loops , Conditions ################## 

students = 0
while(True):
    try:
        students = int(input("Enter total records to fill : "))
    except:
        print("[ ERROR ] Enter a valid input")
        
    if(students > 0):
        break
    print("[ ERROR ] must be a positive integer")

for i in range(students):
    while(True):
        preferance = input("Enter your preferance [online/offline] : ")
        if( preferance == "offline" or preferance == "Offline" ):  
            print("Input Accepted")
            break;
        
        elif(preferance == "online" or preferance == "Online" ):
            print("Input Accepted")
            break;
        else:
            print("[ ERROR ] invalid input.\n\n\t Options [ online / offline ] \ntry again\n\n")    
            
    while(True):
            batch = input("\n\tEnter your batch:[A1 / A2 / A3] : ")
            if(batch == "A1" or batch == "A2" or batch == "A3"):
                name = input ("Enter your name : ")
                print("\n============================")
                print("Your name : " + name)
                print("Your Batch : " + batch)
                print("Your Preferance : " + preferance)
                print("============================\n")
                break
            else:
                print("[ ERROR ] invalid input.\n\n\t Options [A1 / A2 / A3] \ntry again\n\n") 

################## Assignment [ Print Reverse , Add Reverse ] ################## 

num = input()
print(ord(num))
asd = input()
# Reverse Print and add
while(True):  #Asking input till correct format is found
    try:
        arr = list(map(int , input("Enter Array Input:").split()))
        break
    except:
        print("[ ERROR ] Invalid Input (enter integers)\n")
        
# Printing in reverse without altering contents
print("\n\n=== Reverse Array ===")
for i in range(len(arr)):
    print(arr[len(arr) - i - 1] , end = ' ')


#Loop for adding and displaying output
print("\n========================\nResult of array being reversed and added to itslef is: ")
for j in range(len(arr)):
    print(arr[len(arr) - j - 1] + arr[j] , end = ' ')
