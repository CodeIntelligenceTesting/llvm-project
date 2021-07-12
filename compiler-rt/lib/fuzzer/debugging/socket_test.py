import hashlib
from socket import socket, AF_UNIX, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR
from struct import unpack, pack

import click
import numpy as np


def server(input_):
    return hashlib.sha224(input_).digest()


def client():
    for _ in range(100):
        yield np.random.bytes(10)
    yield b''


@click.command()
@click.option('--role', default='server', help='Server or client role?')
@click.option('--addr', default='/tmp/test.sock', help='socket address')
def main(role='server', addr='/tmp/test.sock'):
    with socket(AF_UNIX, SOCK_STREAM) as sock:
        if role == 'server':
            sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
            sock.bind(addr)
            sock.listen(1)
            conn, _ = sock.accept()
            with conn:
                input_ = True
                while input_:
                    len_ = unpack('I', conn.recv(4))[0]
                    input_ = conn.recv(len_)
                    print('RECV>> ' + str(input_))
                    result = server(input_)
                    conn.sendall(pack('I', len(result)) + result)
                    print('SENT>> ' + str(result))
        else:
            sock.connect(addr)

            inputs = client()
            for input_ in inputs:
                sock.sendall(pack('I', len(input_)) + input_)
                print('SENT>> ' + str(input_))
                len_ = unpack('I', sock.recv(4))[0]
                result = sock.recv(len_)
                print('RECV>> ' + str(result))


if __name__ == '__main__':
    main()
