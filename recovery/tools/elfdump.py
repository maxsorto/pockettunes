import struct,sys
E=sys.argv[1]; d=open(E,'rb').read()
shoff,=struct.unpack_from('<I',d,0x20); shentsize,shnum,shstrndx=struct.unpack_from('<HHH',d,0x2e)
secs=[]
for i in range(shnum):
    nm,typ,fl,addr,off,size=struct.unpack_from('<IIIIII',d,shoff+i*shentsize)
    secs.append((addr,off,size,typ))
def rd(a,n):
    for addr,off,size,typ in secs:
        if addr and addr<=a<addr+size and typ!=8: return d[off+a-addr:off+a-addr+n]
    return None
def u32(a): return struct.unpack('<I',rd(a,4))[0]
def u16s(a,n): return struct.unpack('<%dH'%n,rd(a,2*n))
def cstr(a):
    b=rd(a,256); return b[:b.index(0)].decode('latin1') if b else None
if __name__=='__main__':
    for a in sys.argv[2:]:
        a=int(a,16)
        print(hex(a), cstr(a))
