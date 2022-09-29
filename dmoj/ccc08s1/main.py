city, temp = raw_input().split()
coldestCity = city
coldestTemp = int(temp)

while city != "Waterloo":
    city, temp = raw_input().split()
    temp = int(temp)
    if temp < coldestTemp:
        coldestCity = city
        coldestTemp = temp

print(coldestCity)