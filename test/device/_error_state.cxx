/********************************************************************************
 *    Copyright (C) 2018 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runner.h"

#include <gtest/gtest.h>
#include <boost/process.hpp>
#include <fairmq/Tools.h>

#include <string>
#include <thread>
#include <iostream>

namespace
{

using namespace std;
using namespace fair::mq::test;
using namespace fair::mq::tools;

void RunErrorStateIn(const string& state, const string& control, const string& input = "")
{
    size_t session{fair::mq::tools::UuidHash()};

    execute_result result{"", 100};
    thread device_thread([&]() {
        stringstream cmd;
        cmd << runTestDevice
            << " --id error_state_" << state << "_"
            << " --control " << control
            << " --session " << session
            << " --color false";
        result = execute(cmd.str(), "[ErrorFound IN " + state + "]", input);
    });

    device_thread.join();

    ASSERT_NE(string::npos, result.console_out.find("going to change to Error state from " + state + "()"));

    exit(result.exit_code);
}

TEST(ErrorState, static_InInit)
{
    EXPECT_EXIT(RunErrorStateIn("Init", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, static_InBind)
{
    EXPECT_EXIT(RunErrorStateIn("Bind", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, static_InConnect)
{
    EXPECT_EXIT(RunErrorStateIn("Connect", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, static_InInitTask)
{
    EXPECT_EXIT(RunErrorStateIn("InitTask", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, static_InPreRun)
{
    EXPECT_EXIT(RunErrorStateIn("PreRun", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, static_InRun)
{
    EXPECT_EXIT(RunErrorStateIn("Run", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, static_InPostRun)
{
    EXPECT_EXIT(RunErrorStateIn("PostRun", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, static_InResetTask)
{
    EXPECT_EXIT(RunErrorStateIn("ResetTask", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, static_InReset)
{
    EXPECT_EXIT(RunErrorStateIn("Reset", "static"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InInit)
{
    EXPECT_EXIT(RunErrorStateIn("Init", "interactive"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InBind)
{
    EXPECT_EXIT(RunErrorStateIn("Bind", "interactive"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InConnect)
{
    EXPECT_EXIT(RunErrorStateIn("Connect", "interactive"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InInitTask)
{
    EXPECT_EXIT(RunErrorStateIn("InitTask", "interactive"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InPreRun)
{
    EXPECT_EXIT(RunErrorStateIn("PreRun", "interactive"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InRun)
{
    EXPECT_EXIT(RunErrorStateIn("Run", "interactive"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InPostRun)
{
    EXPECT_EXIT(RunErrorStateIn("PostRun", "interactive"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InResetTask)
{
    EXPECT_EXIT(RunErrorStateIn("ResetTask", "interactive", "q"), ::testing::ExitedWithCode(1), "");
}
TEST(ErrorState, interactive_InReset)
{
    EXPECT_EXIT(RunErrorStateIn("Reset", "interactive", "q"), ::testing::ExitedWithCode(1), "");
}

} // namespace
