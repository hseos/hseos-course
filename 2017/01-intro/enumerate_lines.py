import sys
lines = sys.stdin.readlines()
for number, line in enumerate(lines):
    print("%2d: %s" % (number, line[:-1]))
