from namjaeFinal import MyHost

if __name__ == '__main__':
    i0 = int(input('Host ID: '))

    print('1. Server')
    print('2. Client')
    i1 = int(input('>>> '))

    host = MyHost(i0, 'Host_'+str(i0))
    
    if i1 == 1:
        host.open_server()
    elif i1 == 2:
        host.connect_server(int(input('Server host ID: ')))
    print('Connect_OK')

    host.run()

    f = open('Data.txt', 'rt')
    d = f.read()
    while True:
        a = input('Press Enter..')
        if a == 'exit':
            break
        host.send2oppo(d)
