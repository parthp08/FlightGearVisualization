import struct

def binary_float(num):
	return ''.join('{:0>8b}'.format(c) for c in struct.pack('!f', num))

def binary_double(num):
	return ''.join('{:0>8b}'.format(c) for c in struct.pack('!d', num))

def binary_uint32(num):
	if num <= 0.0:
		num *= -1
	return ''.join('{:0>8b}'.format(c) for c in struct.pack('!L', num))

def reverse_endianness(bin_string):
	bin_len = len(bin_string)//8
	temp = ""
	for i in range(bin_len):
		temp += bin_string[8*(bin_len-1-i):8*(bin_len-i)]
	return temp

def fdm_packet(lon, lat, altitude, phi, theta, psi):
	# net_fdm packet to send to FlightGear
	# this function only generates packet for 6 inputs but can be extended by creating
	# a class or structure of data using structure given here:
	# https://sourceforge.net/p/flightgear/flightgear/ci/next/tree/src/Network/net_fdm.hxx

	zero_float = binary_float(0)
	zero_uint32 = binary_uint32(0)
	packet_str = binary_uint32(24) + zero_uint32 + \
		binary_double(lon) + binary_double(lat) + binary_double(altitude) \
		+ zero_float \
		+ binary_float(phi) + binary_float(theta) + binary_float(psi) \
		+ 2*zero_float + 11*zero_float + 3*zero_float + 2*zero_float \
		+ zero_uint32 + 4*zero_uint32 + 4*9*zero_float \
		+ zero_uint32 + 4*zero_float \
		+ zero_uint32 + 3*zero_uint32 + 3*3*zero_float \
		+ zero_uint32 + zero_uint32 + zero_float + 10*zero_float
	return bytes(int(packet_str[x:x+8], 2) for x in range(0, len(packet_str), 8))

if __name__ == "__main__":

	DEG2RAD = 0.0175
	lon = 40.0 * DEG2RAD
	lat = -120.0 * DEG2RAD
	altitude = 7000
	phi = 2.0 * DEG2RAD
	theta = 5.0 * DEG2RAD
	psi = 0.4 * DEG2RAD

	ans = fdm_packet(lon, lat, altitude, phi, theta, psi)

	print(ans)
	print(len(ans))
	print(type(ans))
	