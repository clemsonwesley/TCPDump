def main():
    log_file = open('/etc/log', 'r')
    trusted_ips = open('trustedIPs', 'r')
    data_out = open('flaggedData.txt', 'w')
    ip_out = open('flaggedIPs.txt', 'w')
    logging=False
    # Get set of flagged IPs
    for line in log_file:
        line = line.split()
        if (line[1].strip()=="IP"):
            logging=False
            bad_address = line[2].split('.')[0:-1]
            address = '.'.join(bad_address)
            if (address not in open('trustedIPs').read()):
                data_out.write("-----------\n")
                # If an IP address is flagged, get its info
                data_info = "Address: " + address + " Flags: " + line[6] + " Length: " + line[-1] + "\n"
                ip_out.write(address + "\n")
                data_out.write(data_info)
                logging=True
        elif logging:
            data_out.write(''.join(line) + "\n")

    log_file.close()
    trusted_ips.close()
    data_out.close()
    ip_out.close()

main()
