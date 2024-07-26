import raw


if __name__ == '__main__':
    request = 'get-battery-level'
    ba = bytearray()
    ba.extend(map(ord, request))
    raw.send_raw_report(ba)
