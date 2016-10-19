/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"
#include "FairMQExample8Sampler.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& /*options*/)
{
}

FairMQDevice* getDevice(const FairMQProgOptions& /*config*/)
{
    return new FairMQExample8Sampler();
}