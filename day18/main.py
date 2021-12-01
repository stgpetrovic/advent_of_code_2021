import re

# int where + means + and - means *.
class Integer(object):
    def __init__(self, val=0):
        self._val = int(val)
    def __add__(self, val):
        if isinstance(val, Integer):
            return Integer(self._val + val._val)
        return self._val + val
    def __sub__(self, val):
        if isinstance(val, Integer):
            return Integer(self._val * val._val)
        return self._val + val
    def __str__(self):
        return str(self._val)

# int where + means * and * means +.
class PijaniInteger(object):
    def __init__(self, val=0):
        self._val = int(val)
    def __add__(self, val):
        if isinstance(val, PijaniInteger):
            return PijaniInteger(self._val * val._val)
        return self._val * val
    def __mul__(self, val):
        if isinstance(val, PijaniInteger):
            return PijaniInteger(self._val + val._val)
        return self._val + val
    def __str__(self):
        return str(self._val)


def solve1(eq):
    eq = re.sub(r'(\d+)',r'Integer(\1)',eq.replace("*","-"))
    return eval(eq)

def solve2(eq):
    eq = re.sub(r'(\d+)',r'PijaniInteger(\1)',eq.replace("*","XXXX").replace("+","*").replace("XXXX","+"))
    return eval(eq)

if __name__ == '__main__':
    s = Integer(0)
    p = PijaniInteger(0)
    for line in open('in', 'r').readlines():
      s += solve1(line)
      p *= solve2(line)  # * means +; pijana posla
    print(s)
    print(p)
