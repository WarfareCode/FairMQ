/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * Sink.cxx
 *
 * @since 2014-10-10
 * @author A. Rybalchenko
 */

#include "Sink.h"

using namespace std;

namespace example_region
{

Sink::Sink()
    : fMaxIterations(0)
    , fNumIterations(0)
{
}

void Sink::InitTask()
{
    // Get the fMaxIterations value from the command line options (via fConfig)
    fMaxIterations = fConfig->GetValue<uint64_t>("max-iterations");
}

void Sink::Run()
{
    FairMQChannel& dataInChannel = fChannels.at("data").at(0);

    while (!NewStatePending())
    {
        FairMQMessagePtr msg(dataInChannel.Transport()->CreateMessage());
        dataInChannel.Receive(msg);
        // void* ptr = msg->GetData();

        if (fMaxIterations > 0 && ++fNumIterations >= fMaxIterations)
        {
            LOG(info) << "Configured maximum number of iterations reached. Leaving RUNNING state.";
            break;
        }
    }
}

Sink::~Sink()
{
}

} // namespace example_region
