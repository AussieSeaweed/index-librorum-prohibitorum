L = input()
S = input()

if S <= L:
    print "Congratulations, you are within the speed limit!"
else:
    D = S - L
    if 1 <= D and D <= 20:
        print "You are speeding and your fine is $100."
    elif 21 <= D and D <= 30:
        print "You are speeding and your fine is $270."
    else:
        print "You are speeding and your fine is $500."