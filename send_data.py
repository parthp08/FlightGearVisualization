import socket
import time
import fdm_packet

from numpy import genfromtxt
flight_data = genfromtxt('data.csv', delimiter=',')

DEG2RAD = 0.0175

time_data = flight_data[:, 0]
lon = flight_data[:, 1] * DEG2RAD
lat = flight_data[:, 2] * DEG2RAD
altitude = flight_data[:, 3]
phi = flight_data[:, 4] * DEG2RAD
theta = flight_data[:, 5] * DEG2RAD
psi = flight_data[:, 6] * DEG2RAD

print("\nTo start with the simulation, run the following command in separate commandline\
	window at the current file directory location:")
print(f"\nGenerateRunFile.exe {altitude[0]} {psi[0]/DEG2RAD}\n")
print("This command will start FlightGear with approprite settings, now wait for the flight gear to open.\n")

HOST = '127.0.0.1'
PORT = 5502  # port used by the flightgear
serverAddressPort = (HOST, PORT)
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPClientSocket.connect(serverAddressPort)

running = input("Please enter 'Y' when flightgear is ready ('q' to quit): ")
print("Starting the Simulation....")

if (running.lower() == "y"):
    for i in range(0, len(time_data)):

        message = fdm_packet.fdm_packet(
            lon[i], lat[i], altitude[i], phi[i], theta[i], psi[i])

        UDPClientSocket.sendall(message)

        time.sleep(0.1)

    print("End of simulation.")
    UDPClientSocket.close()

else:
    print("ending the simulation here.")
