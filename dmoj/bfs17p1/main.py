hobbies = []

input()

hobbies_ = raw_input().split()
for hobby in hobbies_:
    if len(hobby) <= 10:
        hobbies.append(hobby)

print len(hobbies)