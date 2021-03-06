/********************************************************************************
*    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
*                                                                              *
*              This software is distributed under the terms of the             *
*              GNU Lesser General Public Licence (LGPL) version 3,             *
*                  copied verbatim in the file "LICENSE"                       *
********************************************************************************/
/**
* FairMQShmManager.h
*
* @since 2016-04-08
* @author A. Rybalchenko
*/

#ifndef FAIR_MQ_SHMEM_REGION_H_
#define FAIR_MQ_SHMEM_REGION_H_

#include "FairMQLogger.h"
#include "FairMQUnmanagedRegion.h"

#include <fairmq/Tools.h>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

#include <thread>
#include <unordered_map>

namespace fair
{
namespace mq
{
namespace shmem
{

class Manager;

struct Region
{
    Region(Manager& manager, uint64_t id, uint64_t size, bool remote, FairMQRegionCallback callback = nullptr);

    Region() = delete;

    Region(const Region&) = default;
    Region(Region&&) = default;

    void StartReceivingAcks();
    void ReceiveAcks();

    ~Region();

    Manager& fManager;
    bool fRemote;
    bool fStop;
    std::string fName;
    std::string fQueueName;
    boost::interprocess::shared_memory_object fShmemObject;
    boost::interprocess::mapped_region fRegion;
    std::unique_ptr<boost::interprocess::message_queue> fQueue;
    std::thread fWorker;
    FairMQRegionCallback fCallback;
};

} // namespace shmem
} // namespace mq
} // namespace fair

#endif /* FAIR_MQ_SHMEM_REGION_H_ */
