import random
import math
import time
Kn = 200 * (10 **-4)  

two_fi = 0.6 
VTo = -3
lamda = 1

VSB = 0  
VGS = 0
VTN = 0


while True: 
    IDS = round(random.uniform(0.0001, 0.001), 7) 
                                                 
    VGS = round(IDS * (-(2*10**4)),3)         
    VSB = -VGS                               
    
    VTN = round(VTo + (1 * (math.sqrt(VSB+two_fi)-math.sqrt(two_fi))),3)  
   
    IDS1 = round(((VGS-VTN)**2)*(10**-4),7)
    print(f"random IDS:{IDS1}\n*************") 

    print(f"hesaplanan IDS:{IDS}")  

    if(IDS1 == IDS):  
        print("bulundu!\n------------------------")
        print(f"random IDS:{IDS1}")
        print(f"hesaplanan IDS:{IDS}")
        print("------------------------")
        exit(0)
