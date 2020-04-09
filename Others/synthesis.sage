F2 = GF(2)
a = [var('a{}'.format(i))for i in range(163)]
x = var('x')


F2Poly = PolynomialRing(F2,a)
F2PolyX = F2Poly[x]
x = F2PolyX(x)
a = [F2Poly(ai) for ai in a]
a2Idx = {ai:i for i,ai in enumerate(a)}
aMod = [ai^2-ai for ai in a]

irr = x^163+x^7+x^6+x^3+1

elem = sum(a[i]*x^i for i in range(163))

def reducePoly(f):
	out = f%irr
	ls = []
	for ai in out.list():
		for v in ai.variables():
			ai %= aMod[a2Idx[v]]
		ls.append(ai)
	out = sum(ai*x^i for i,ai in enumerate(ls))
	return out


sqTable = [x^(2*i)%irr for i in range(163)]
def square(f):
	f = sum(ai*sqTable[i] for i,ai in enumerate(f.list()))
	return reducePoly(f)
def prod(g1, g2): return reducePoly(g1*g2) 

def power2k(g,k):
	incre = F2PolyX((F2PolyX.quo(irr)(x)^(2^k)).lift())
	sqTable = [F2PolyX(1)]
	for i in range(1,163):
		last = (sqTable[-1]*incre) % irr
		sqTable.append(last)
	g = sum(ai*sqTable[i] for i,ai in enumerate(g.list()))
	return g

def power(g,n): #n>0
	if n==1: return g
	if n%2: return prod(g,power(g,n-1))
	return power(square(g),n//2)



