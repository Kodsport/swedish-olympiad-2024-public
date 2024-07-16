#!/usr/bin/python3



def app():
    print("app")
    return int(input())

def randomMove(s):
    for i in [3,2,1,4,0]:
        if s[i]:
            print(["up", "right", "downright", "downleft", "left"][i])
            break
    return input()
    
#Går så långt upp som möjligt
currRoom = input()
while currRoom[0] == "1":
    print("up")
    currRoom = input()

apps = 499
dist = app()

flipped = 0

while dist:
    if apps == 0:
        for _ in range(dist):
            currRoom = randomMove(currRoom) #Should go in the same direction as before if possible
        print("here")
        exit()

    flipped += 1

    if flipped:
        #Testar att gå ner så långt man kan, och kalla antalet våningar den har gått ner för x. sedan testar vi x/2 osv.
        if currRoom[2] == "1":
            jumpSize = 1
            print("downright")
            nextRoom = input()
            while nextRoom[2] == "1" or jumpSize>dist:
                jumpSize += 1
                print("downright")
                nextRoom = input()
            done = 0
            while jumpSize>1:
                nextDist = app()
                apps -= 1
                if nextDist + jumpSize == dist:
                    dist = nextDist
                    currRoom = nextRoom
                    done = 1
                    break
                
                if apps == 0:
                    for _ in range(nextDist):
                        tempRoom = randomMove(tempRoom) #Should go in the same direction as before if possible
                    print("here")
                    exit()

                diff = -(-jumpSize//2)
                for _ in range(diff):
                    print("up")
                    nextRoom = tempRoom = input()
                    jumpSize -= 1
            
            if not done:
                nextDist = app()
                apps -= 1
                if nextDist + 1 == dist:
                    dist = nextDist
                    currRoom = nextRoom
                else:
                    print("left")
                    dist -= 1
                    currRoom = input()

        elif currRoom[3] == "1":
            jumpSize = 1
            print("downleft")
            nextRoom = input()
            while nextRoom[3] == "1" or jumpSize>dist:
                jumpSize += 1
                print("downleft")
                nextRoom = input()
            
            while jumpSize:
                nextDist = app()
                apps -= 1
                if nextDist + jumpSize == dist:
                    dist = nextDist
                    currRoom = nextRoom
                    break
                
                if apps == 0:
                    for _ in range(nextDist):
                        tempRoom = randomMove(tempRoom) #Should go in the same direction as before if possible
                    print("here")
                    exit()

                diff = -(-jumpSize//2)
                for _ in range(diff):
                    print("up")
                    nextRoom = tempRoom = input()
                    jumpSize -= 1
    else:
        if currRoom[3] == "1":
            jumpSize = 1
            print("downleft")
            nextRoom = input()
            while nextRoom[3] == "1" or jumpSize>dist:
                jumpSize += 1
                print("downleft")
                nextRoom = input()
            done = 0
            while jumpSize>1:
                nextDist = app()
                apps -= 1
                if nextDist + jumpSize == dist:
                    dist = nextDist
                    currRoom = nextRoom
                    done = 1
                    break
                
                if apps == 0:
                    for _ in range(nextDist):
                        tempRoom = randomMove(tempRoom) #Should go in the same direction as before if possible
                    print("here")
                    exit()

                diff = -(-jumpSize//2)
                for _ in range(diff):
                    print("up")
                    nextRoom = tempRoom = input()
                    jumpSize -= 1
            
            if not done:
                nextDist = app()
                apps -= 1
                if nextDist + 1 == dist:
                    dist = nextDist
                    currRoom = nextRoom
                else:
                    print("right")
                    dist -= 1
                    currRoom = input()

        elif currRoom[2] == "1":
            jumpSize = 1
            print("downright")
            nextRoom = input()
            while nextRoom[2] == "1" or jumpSize>dist:
                jumpSize += 1
                print("downright")
                nextRoom = input()
            
            while jumpSize:
                nextDist = app()
                apps -= 1
                if nextDist + jumpSize == dist:
                    dist = nextDist
                    currRoom = nextRoom
                    break
                
                if apps == 0:
                    for _ in range(nextDist):
                        tempRoom = randomMove(tempRoom) #Should go in the same direction as before if possible
                    print("here")
                    exit()

                diff = -(-jumpSize//2)
                for _ in range(diff):
                    print("up")
                    nextRoom = tempRoom = input()
                    jumpSize -= 1

print("here")
exit()
