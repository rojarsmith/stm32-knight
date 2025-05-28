#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifdef SIMULATOR
#include <ctime>
#endif /* SIMULATOR */

#include <iostream>
#include <memory>
#include <string>
#include <thread>

//#include <grpcpp/grpcpp.h>
//#include "grpc/sensor.grpc.pb.h"

//using grpc::Server;
//using grpc::ServerBuilder;
//using grpc::ServerContext;
//using grpc::Status;
//using sensor::GestureRequest;
//using sensor::Value2DoubleRequest;
//using sensor::Value2Int32Request;
//using sensor::Value4Int32Request;
//using sensor::SensorMX;
//
//// Logic and data behind the server's behavior.
//class SensorMXImpl final : public SensorMX::Service {
//	Status SetGesture(ServerContext* context, const GestureRequest* request,
//		::google::protobuf::Empty* reply) override {
//		return Status::OK;
//	}
//
//	Status SetValue2Double(ServerContext* context, const Value2DoubleRequest* request,
//		::google::protobuf::Empty* reply) override {
//		return Status::OK;
//	}
//
//	Status SetValue2Int32(ServerContext* context, const Value2Int32Request* request,
//		::google::protobuf::Empty* reply) override {
//		return Status::OK;
//	}
//
//	Status SetValue4Int32(ServerContext* context, const Value4Int32Request* request,
//		::google::protobuf::Empty* reply) override {
//		if ("kaikutek1" == request->device_id())
//		{
//			v_device_id_ = 1;
//		}
//
//		if ("1" == request->action_id())
//		{
//			v_action_id_ = 1;
//			v_event_id_ = 1;
//		}
//		else if ("4" == request->action_id())
//		{
//			v_action_id_ = 4;
//		}
//		else if ("5" == request->action_id())
//		{
//			v_action_id_ = 5;
//			v_event_id_ = 2;
//		}
//
//		v_op1_ = (int)(request->op_1());
//		v_op2_ = (int)(request->op_2());
//		v_op3_ = (int)(request->op_3());
//		v_op4_ = (int)(request->op_4());
//		if (v_op4_ != 0x1f)
//		{
//			int dbg1 = 0;
//		}
//		return Status::OK;
//	}
//};
//
//void RunServer() {
//	std::string server_address("0.0.0.0:13038");
//	SensorMXImpl service;
//
//	ServerBuilder builder;
//	// Listen on the given address without any authentication mechanism.
//	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//	// Register "service" as the instance through which we'll communicate with
//	// clients. In this case it corresponds to an *synchronous* service.
//	builder.RegisterService(&service);
//	// Finally assemble the server.
//	std::unique_ptr<Server> server(builder.BuildAndStart());
//	std::cout << "Server listening on " << server_address << std::endl;
//
//	// Wait for the server to shutdown. Note that some other thread must be
//	// responsible for shutting down the server for this call to ever return.
//	server->Wait();
//}

Model::Model() : 
	modelListener(0),
	selected_demo_screen_(Defines::GAME2D)
{
	//std::thread tComm(RunServer);
	//tComm.detach();
}

void Model::tick()
{
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);

    current_time_.hours = timenow.tm_hour;
    current_time_.minutes = timenow.tm_min;
    current_time_.seconds = timenow.tm_sec;
    current_time_.milliseconds = 0;
#endif  /*_MSC_VER*/

	if (v_device_id_ == 1)
	{
		mstatus_.device = v_device_id_;
		mstatus_.eve = &v_event_id_;
		mstatus_.act = v_action_id_;
		mstatus_.op1 = v_op1_;
		mstatus_.op2 = v_op2_;
		mstatus_.op3 = v_op3_;
		mstatus_.op4 = v_op4_;

		gestureTick(v_event_id_, v_op4_);
		v_event_id_ = 0;
	}

	mstatus_.tick++;
}

void Model::screenSaverMinorTick()
{
    modelListener->screenSaverMinorTick();
}

void Model::gestureTick(int eve, int op4)
{
	modelListener->gestureTick(eve, op4);
}

MachineStatus* Model::getMachineStatus()
{
	return &mstatus_;
}