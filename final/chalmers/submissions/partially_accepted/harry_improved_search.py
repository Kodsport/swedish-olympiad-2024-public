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

prevMove = "-1"

while dist:
    if apps == 0:
        for _ in range(dist):
            currRoom = randomMove(currRoom) #Should go in the same direction as before if possible
        print("here")
        exit()


    #Testar att gå ner och kollar ifall någon av dessa minskar avståndet 
    if currRoom[2] == "1":
        print("downright")
        nextRoom = input()
        nextDist = app()
        apps -= 1

        if nextDist < dist:
            dist = nextDist
            currRoom = nextRoom
            continue
        print("up")
        input()

    if currRoom[3] == "1":
        print("downleft")
        nextRoom = input()
        nextDist = app()
        apps -= 1

        if nextDist < dist:
            dist = nextDist
            currRoom = nextRoom
            continue
        print("up")
        input()

print("here")
exit()
