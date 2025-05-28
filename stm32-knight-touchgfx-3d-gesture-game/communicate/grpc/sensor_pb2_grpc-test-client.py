"""The Python implementation of the GRPC helloworld.Greeter client."""

from __future__ import print_function
import logging

import grpc

import sensor_pb2
import sensor_pb2_grpc


def run():
    # NOTE(gRPC Python Team): .close() is possible on a channel and should be
    # used in circumstances in which the with statement does not fit the needs
    # of the code.
    with grpc.insecure_channel('localhost:13038') as channel:
        stub = sensor_pb2_grpc.SensorMXStub(channel)
        response = stub.SetGesture(sensor_pb2.GestureRequest(device_id='kaikutek1', action_id='4', op_1=3, op_2=0))


if __name__ == '__main__':
    logging.basicConfig()
    run()
