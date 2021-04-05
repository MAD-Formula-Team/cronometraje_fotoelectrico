

1) Use hcitool scan to find the Mac address of the device.

The device should be set to slave mode with a known pin. If you don't use a known pin, ubuntu makes one up and you generally won't have time to enter it in the clunky menus of your measuring tool.

2) Pair the device in the bluetooth gui menu. Default pin: 1234

3) in /etc/bluetooth/rfcomm.conf

rfcomm0 {
        bind no;
        device [mac_address_found_with_hcitool];
        channel 1;
        comment "Serial Port";
        }

The "bind no" is important, otherwise it will try to autmatically bind, which presents all sorts of problems for actually accessing the device (as it's quite picky about when its associated)

4) sudo rfcomm connect rtcomm0 [mac_address_found_with_hcitool]

If you have errors, restart the bluetooth service.

5) cat /dev/rfcomm0

Now you can get o transmit tata through the /dev/rfcomm0 file

